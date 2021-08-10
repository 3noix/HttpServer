#include "HttpServer.h"


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
HttpServer::HttpServer(const HttpServerConfig &config, HttpRequestHandler *requestHandler, QObject *parent) :
	QTcpServer{parent},
	config{config},
	requestHandler{requestHandler}
{
	setMaxPendingConnections(config.maxPendingConnections);
}

HttpServer::~HttpServer()
{
	for (HttpConnection *connection : connections) {delete connection;}
	close();
}


// LISTEN /////////////////////////////////////////////////////////////////////
bool HttpServer::listen()
{
	if (!QTcpServer::listen(config.host, config.port))
	{
		if (config.verbosity >= HttpServerConfig::Verbose::Warning) {
			qWarning().noquote() << QString("Unable to listen on %1:%2: %3").arg(config.host.toString()).arg(config.port).arg(errorString());
		}

		return false;
	}

	if (config.verbosity >= HttpServerConfig::Verbose::Info) {qInfo() << "Listening...";}
	return true;
}

// CLOSE //////////////////////////////////////////////////////////////////////
void HttpServer::close()
{
	QTcpServer::close();
}

// LOAD SSL CONFIG ////////////////////////////////////////////////////////////
bool HttpServer::loadSslConfig(const QString &sslCertPath, const QString &sslKeyPath, const QByteArray &sslKeyPassPhrase)
{
	// TODO Want to handle caching SSL sessions here if able too

	if (sslKeyPath.isEmpty() || sslCertPath.isEmpty()) {
		if (config.verbosity >= HttpServerConfig::Verbose::Warning) {
			qWarning().noquote() << QString("SSL certificate path or SSL key path missing");
		}
		return false;
	}

	if (!QSslSocket::supportsSsl())
	{
		if (config.verbosity >= HttpServerConfig::Verbose::Warning) {
			qWarning().noquote() << QString("OpenSSL is not supported for HTTP server (OpenSSL Qt build version: %1). Disabling TLS").arg(QSslSocket::sslLibraryBuildVersionString());
		}
		return false;
	}

	// Load the SSL certificate
	QFile certFile{sslCertPath};
	if (!certFile.open(QIODevice::ReadOnly))
	{
		if (config.verbosity >= HttpServerConfig::Verbose::Warning) {
			qWarning().noquote() << QString("Failed to open SSL certificate file for HTTP server: %1 (%2). Disabling TLS").arg(sslCertPath).arg(certFile.errorString());
		}
		return false;
	}

	QSslCertificate certificate{&certFile, QSsl::Pem};
	certFile.close();

	if (certificate.isNull())
	{
		if (config.verbosity >= HttpServerConfig::Verbose::Warning) {
			qWarning().noquote() << QString("Invalid SSL certificate file for HTTP server: %1. Disabling TLS").arg(sslCertPath);
		}
		return false;
	}

	// Load the key file
	QFile keyFile{sslKeyPath};
	if (!keyFile.open(QIODevice::ReadOnly))
	{
		if (config.verbosity >= HttpServerConfig::Verbose::Warning) {
			qWarning().noquote() << QString("Failed to open private SSL key file for HTTP server: %1 (%2). Disabling TLS").arg(sslKeyPath).arg(keyFile.errorString());
		}
		return false;
	}

	QSslKey sslKey{&keyFile, QSsl::Rsa, QSsl::Pem, QSsl::PrivateKey, sslKeyPassPhrase};
	keyFile.close();

	if (sslKey.isNull())
	{
		if (config.verbosity >= HttpServerConfig::Verbose::Warning) {
			qWarning().noquote() << QString("Invalid private SSL key for HTTP server: %1. Disabling TLS").arg(sslKeyPath);
		}
		return false;
	}

	sslConfig = QSslConfiguration{};
	sslConfig.setLocalCertificate(certificate);
	sslConfig.setPrivateKey(sslKey);
	sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);
	sslConfig.setProtocol(QSsl::SecureProtocols);

	if (config.verbosity >= HttpServerConfig::Verbose::Debug)
		qDebug().noquote() << "Successfully setup SSL configuration, HTTPS enabled";

	return true;
}

// INCOMING CONNECTION ////////////////////////////////////////////////////////
void HttpServer::incomingConnection(qintptr socketDescriptor)
{
	if ((int)connections.size() >= config.maxConnections)
	{
		// Create TCP socket
		// Delete the socket automatically once a disconnected signal is received
		QTcpSocket *socket = new QTcpSocket{this};
		connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

		if (!socket->setSocketDescriptor(socketDescriptor))
		{
			if (config.verbosity >= HttpServerConfig::Verbose::Critical) {
				qCritical() << QString("Invalid socket descriptor given (%1)").arg(socket->errorString());
			}

			return;
		}

		if (config.verbosity >= HttpServerConfig::Verbose::Warning) {
			qWarning() << QString("Maximum connections reached (%1). Rejecting connection from %2").arg(config.maxConnections).arg(socket->peerAddress().toString());
		}

		HttpResponse *response = new HttpResponse{&config};
		response->setError(HttpStatus::ServiceUnavailable, "Too many connections", true);
		response->prepareToSend();

		// Assume that the entire request will be written in one go, relatively safe assumption
		response->writeChunk(socket);
		delete response;

		// This will disconnect after all bytes have been written
		socket->disconnectFromHost();
		return;
	}

	HttpConnection *connection = new HttpConnection{&config, requestHandler, socketDescriptor, &sslConfig};
	connect(connection, &HttpConnection::disconnected, this, &HttpServer::connectionDisconnected);
	connections.push_back(connection);
}

// CONNECTION DISCONNECTED ////////////////////////////////////////////////////
void HttpServer::connectionDisconnected()
{
	HttpConnection *connection = dynamic_cast<HttpConnection *>(sender());
	if (!connection) {return;}

	// Remove connection from connections list
	auto it = std::find(connections.begin(), connections.end(), connection);
	if (it != connections.end()) {connections.erase(it);}

	// We do delete later here because if this signal was emitted while socket is disconnecting, it still needs the
	// socket reference for a bit
	connection->deleteLater();
}

