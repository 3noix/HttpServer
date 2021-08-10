#include "MyHttpServer.h"


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
MyHttpServer::MyHttpServer(const HttpServerConfig &config, QObject *parent) : HttpServer{config,parent}
{
	this->addRoute("GET", "^/user/(\\d*)/?$", this, &MyHttpServer::handleGetUserName);
}


// HANDLE GET USER NAME ///////////////////////////////////////////////////////
HttpPromise MyHttpServer::handleGetUserName(HttpDataPtr data)
{
	auto match = data->state["match"].value<QRegularExpressionMatch>();
	int userId = match.captured(1).toInt();

	QJsonObject jsonOutput;
	jsonOutput["userId"] = userId;
	jsonOutput["userName"] = "Bob";

	data->response->setStatus(HttpStatus::Ok, QJsonDocument{jsonOutput});
	return HttpPromise::resolve(data);
}

