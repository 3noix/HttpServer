#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H


#include <QtPromise>
#include <QTimer>

#include "HttpData.h"
#include "HttpRequestHandler.h"
#include "HttpRequestRouter.h"
using QtPromise::QPromise;


class RequestHandler : public HttpRequestHandler
{
	public:
		RequestHandler();
		RequestHandler(const RequestHandler &other) = delete;
		RequestHandler(RequestHandler &&other) = delete;
		RequestHandler& operator=(const RequestHandler &other) = delete;
		RequestHandler& operator=(RequestHandler &&other) = delete;
		~RequestHandler() = default;

		HttpPromise handle(HttpDataPtr data);

		HttpPromise handleGetUsername(HttpDataPtr data);
		HttpPromise handleGzipTest(HttpDataPtr data);
		HttpPromise handleFormTest(HttpDataPtr data);
		HttpPromise handleFileTest(HttpDataPtr data);
		HttpPromise handleErrorTest(HttpDataPtr data);
		HttpPromise handleAsyncTest(HttpDataPtr data);


	private:
		HttpRequestRouter router;
};


#endif

