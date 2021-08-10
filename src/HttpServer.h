#ifndef HTTP_SERVER_HTTPSERVER_H
#define HTTP_SERVER_HTTPSERVER_H

#include "HttpConnection.h"
#include "HttpServerConfig.h"
#include "HttpRequestHandler.h"
#include "util.h"

#include <QBasicTimer>
#include <QSslKey>
#include <QTcpServer>


// HTTP server is HTTP/1.1 compliant and is based on RFC7230 series.
// This specification was created in June 2014 and obsoletes RFC2616, RFC2145
class HTTPSERVER_EXPORT HttpServer : public QTcpServer
{
	Q_OBJECT

	public:
		HttpServer(const HttpServerConfig &config, HttpRequestHandler *requestHandler, QObject *parent = nullptr);
		HttpServer(const HttpServer &other) = delete;
		HttpServer(HttpServer &&other) = delete;
		HttpServer& operator=(const HttpServer &other) = delete;
		HttpServer& operator=(HttpServer &&other) = delete;
		~HttpServer();

		bool listen();
		void close();


	signals:
		void handleConnection(int socketDescriptor);


	protected:
		void incomingConnection(qintptr socketDescriptor);


	private slots:
		void connectionDisconnected();


	private:
		void loadSslConfig();

		HttpServerConfig config;
		HttpRequestHandler *requestHandler = nullptr;
		QSslConfiguration *sslConfig = nullptr;
		std::vector<HttpConnection*> connections;
};


#endif

