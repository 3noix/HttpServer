#ifndef HTTP_SERVER_HTTP_REQUEST_ROUTER_H
#define HTTP_SERVER_HTTP_REQUEST_ROUTER_H


#include <functional>
#include <list>
#include <QtPromise>
#include <vector>

#include "const.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "util.h"


struct HttpRequestRoute
{
	std::vector<QString> methods;
	QRegularExpression pathRegex;
	HttpFunc handler;
};


class HTTPSERVER_EXPORT HttpRequestRouter
{
	public:
		void addRoute(QString method, QString regex, HttpFunc handler);
		void addRoute(std::vector<QString> methods, QString regex, HttpFunc handler);

		// Allows registering member functions using addRoute(..., <CLASS>, &Class:memberFunction)
		template <typename T>
		void addRoute(QString method, QString regex, T *inst, HttpPromise (T::*handler)(HttpDataPtr))
		{
			return addRoute(method, regex, std::bind(handler, inst, std::placeholders::_1));
		}

		template <typename T>
		void addRoute(QString method, QString regex, T *inst, HttpPromise (T::*handler)(HttpDataPtr) const)
		{
			return addRoute(method, regex, std::bind(handler, inst, std::placeholders::_1));
		}

		template <typename T>
		void addRoute(std::vector<QString> methods, QString regex, T *inst, HttpPromise (T::*handler)(HttpDataPtr))
		{
			return addRoute(methods, regex, std::bind(handler, inst, std::placeholders::_1));
		}

		template <typename T>
		void addRoute(std::vector<QString> methods, QString regex, T *inst, HttpPromise (T::*handler)(HttpDataPtr) const)
		{
			return addRoute(methods, regex, std::bind(handler, inst, std::placeholders::_1));
		}

		HttpPromise route(HttpDataPtr data, bool *foundRoute = nullptr);


	private:
		std::list<HttpRequestRoute> routes;
};


#endif

