#ifndef CPPRESTAPI_CONTROLLER
#define CPPRESTAPI_CONTROLLER

#include <cpprest/uri.h>
#include <cpprestapi/route.hpp>
#include <cpprestapi/route_path.hpp>
#include <cpprestapi/utility.hpp>
#include <memory>
#include <unordered_map>

namespace web
{
    namespace api
    {
        class controller_base
        {
        private:
            using route_ptr = std::unique_ptr<route_base>;

            std::unordered_map<route_path, route_ptr> routes;

        protected:
            template <typename... Args>
            void support(const utility::string_t& path, std::function<void(web::http::http_request, Args...)>&& handler)
            {
                support(path, std::make_unique<route<Args...>>(std::move(handler)));
            }
            void support(route_path&& path, route_ptr&& route)
            {
                routes.emplace(path, std::move(route));
            }

        public:
            CPPRESTAPI_API void handle(const route_path& path, web::http::http_request message) const;
        };
    } // namespace api
} // namespace web

#endif // !CPPRESTAPI_CONTROLLER
