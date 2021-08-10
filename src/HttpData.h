#ifndef HTTP_SERVER_HTTP_DATA_H
#define HTTP_SERVER_HTTP_DATA_H


#include "util.h"
#include <unordered_map>
#include <QString>
#include <QVariant>

class HttpRequest;
class HttpResponse;


struct HTTPSERVER_EXPORT HttpData
{
	HttpRequest *request = nullptr;
	HttpResponse *response = nullptr;
	std::unordered_map<QString, QVariant> state;
	bool finished = false;

	HttpData(HttpRequest *request, HttpResponse *response);
	~HttpData();

	void checkFinished();
};


#endif

