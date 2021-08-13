#ifndef MY_SERVER_H
#define MY_SERVER_H


#include "HttpServer.h"


class MyServer : public HttpServer
{
	public:
		MyServer(const HttpServerConfig &config, QObject *parent = nullptr);
		MyServer(const MyServer &other) = delete;
		MyServer(MyServer &&other) = delete;
		MyServer& operator=(const MyServer &other) = delete;
		MyServer& operator=(MyServer &&other) = delete;
		~MyServer() = default;


	private:
		HttpPromise handleGetUsername(HttpDataPtr data);
		HttpPromise handleGzipTest(HttpDataPtr data);
		HttpPromise handleFormTest(HttpDataPtr data);
		HttpPromise handleFileTest(HttpDataPtr data);
		HttpPromise handleErrorTest(HttpDataPtr data);
		HttpPromise handleAsyncTest(HttpDataPtr data);
};


#endif

