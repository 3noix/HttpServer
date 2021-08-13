#ifndef HTTP_SERVER_HTTPSERVER_H
#define HTTP_SERVER_HTTPSERVER_H

#include "HttpConnection.h"
#include "HttpServerConfig.h"
#include "HttpRequestRouter.h"
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
		HttpServer(const HttpServerConfig &config, QObject *parent = nullptr);
		HttpServer(const HttpServer &other) = delete;
		HttpServer(HttpServer &&other) = delete;
		HttpServer& operator=(const HttpServer &other) = delete;
		HttpServer& operator=(HttpServer &&other) = delete;
		~HttpServer();

		bool loadSslConfig(const QString &sslCertPath, const QString &sslKeyPath, const QByteArray &sslKeyPassPhrase);
		bool listen();
		void close();

		// forward addRoute to the router
		void addRoute(QString method, QString regex, HttpFunc handler);
		void addRoute(std::vector<QString> methods, QString regex, HttpFunc handler);
		template <typename T> void addRoute(QString method, QString regex, T *inst, HttpPromise (T::*handler)(HttpDataPtr)) {return router.addRoute(method, regex, inst, handler);};
		template <typename T> void addRoute(QString method, QString regex, T *inst, HttpPromise (T::*handler)(HttpDataPtr) const) {return router.addRoute(method, regex, inst, handler);};
		template <typename T> void addRoute(std::vector<QString> methods, QString regex, T *inst, HttpPromise (T::*handler)(HttpDataPtr)) {return router.addRoute(methods, regex, inst, handler);};
		template <typename T> void addRoute(std::vector<QString> methods, QString regex, T *inst, HttpPromise (T::*handler)(HttpDataPtr) const) {return router.addRoute(methods, regex, inst, handler);};


	signals:
		void handleConnection(int socketDescriptor);


	protected:
		virtual void incomingConnection(qintptr socketDescriptor) override final;
		virtual HttpPromise handle(HttpDataPtr data);
		virtual HttpPromise handleRequestNotManagedByRouter(HttpDataPtr data);


	private slots:
		void connectionDisconnected();


	private:
		HttpRequestRouter router;
		HttpServerConfig config;
		QSslConfiguration sslConfig;
		std::vector<HttpConnection*> connections;
};


#endif

