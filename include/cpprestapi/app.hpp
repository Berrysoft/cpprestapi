#ifndef CPPRESTAPI_APP
#define CPPRESTAPI_APP

#include <cpprest/http_listener.h>

namespace web::api
{
    namespace listener
    {
        using namespace web::http::experimental::listener;
    }

    class app
    {
    private:
        listener::http_listener listener;

    public:
        app() : listener() {}
        app(web::uri address) : listener(std::move(address)) {}
        app(web::uri address, listener::http_listener_config config) : listener(std::move(address), std::move(config)) {}
    };
} // namespace web::api

#endif // !CPPRESTAPI_APP
