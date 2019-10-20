#ifndef CPPRESTAPI_CONTROLLER
#define CPPRESTAPI_CONTROLLER

#include <cpprest/uri.h>
#include <cpprestapi/route.hpp>
#include <cpprestapi/utility.hpp>
#include <map>
#include <memory>

namespace web
{
    namespace api
    {
        class path_exception : public web::uri_exception
        {
        public:
            path_exception() : uri_exception() {}
            path_exception(std::string msg) : uri_exception(std::move(msg)) {}
        };

        class controller_base
        {
        private:
            using route_ptr = std::unique_ptr<route_base>;

            std::map<utility::string_t, route_ptr> routes;

        protected:
            CPPRESTAPI_API static bool validate_path(const utility::string_t& path);

            template <typename... Args>
            void support(const utility::string_t& path, std::function<void(web::http::http_request, Args...)>&& handler)
            {
                support(path, std::make_unique<route<Args...>>(path, std::move(handler)));
            }
            void support(const utility::string_t& path, route_ptr&& route)
            {
                if (!validate_path(path))
                    throw path_exception{ "Path is invalid." };
                routes.emplace(path, std::move(route));
            }

        public:
            void handle(const utility::string_t& path);
        };
    } // namespace api
} // namespace web

#endif // !CPPRESTAPI_CONTROLLER
