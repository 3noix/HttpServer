#include "HttpData.h"
#include "HttpRequest.h"
#include "HttpResponse.h"


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
HttpData::HttpData(HttpRequest *request, HttpResponse *response) : request{request}, response{response}
{
}

HttpData::~HttpData()
{
	delete request;
	delete response;
}

// CHECK FINISHED /////////////////////////////////////////////////////////////
void HttpData::checkFinished()
{
	if (finished)
		throw HttpException(HttpStatus::None);
}

