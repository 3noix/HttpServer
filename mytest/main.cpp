#include <QCoreApplication>
#include <iostream>
#include "MyHttpServer.h"


int main(int argc, char *argv[])
{
	QCoreApplication app{argc,argv};

	HttpServerConfig config;
	config.host = QHostAddress::LocalHost;
	config.port = 1234;
	config.verbosity = HttpServerConfig::Verbose::Critical;

	MyHttpServer server{config};
	if (!server.listen()) {
		std::cerr << "Failed to listen" << std::endl;
		std::cout << "Press a key to terminate" << std::endl;
		std::cin.get();
		return 1;
	}

	std::cout << "The http server is running" << std::endl;
	return app.exec();
}

