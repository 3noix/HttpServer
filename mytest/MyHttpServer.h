#ifndef MY_HTTP_SERVER
#define MY_HTTP_SERVER


#include "HttpServer.h"
#include "HttpData.h"


class MyHttpServer : public HttpServer
{
	public:
		MyHttpServer(const HttpServerConfig &config, QObject *parent = nullptr);
		MyHttpServer(const MyHttpServer &other) = delete;
		MyHttpServer(MyHttpServer &&other) = delete;
		MyHttpServer& operator=(const MyHttpServer &other) = delete;
		MyHttpServer& operator=(MyHttpServer &&other) = delete;
		~MyHttpServer() = default;


	private:
		HttpPromise handleGetUserName(HttpDataPtr data);
};


#endif

