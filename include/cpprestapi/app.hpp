#ifndef CPPRESTAPI_APP
#define CPPRESTAPI_APP

#include <cpprest/http_listener.h>
#include <cpprestapi/controller.hpp>
#include <cpprestapi/route_path.hpp>
#include <cpprestapi/utility.hpp>
#include <unordered_map>
#include <memory>

namespace web
{
    namespace api
    {
        namespace listener
        {
            using namespace web::http::experimental::listener;
        }

        class app
        {
        private:
            using controller_ptr = std::unique_ptr<controller_base>;

            listener::http_listener listener;
            std::unordered_map<route_path, controller_ptr> routes;

        protected:
            void support_global() { listener.support(std::bind(std::mem_fn(&app::global_handler), this, std::placeholders::_1)); }
            CPPRESTAPI_API void global_handler(web::http::http_request message);

        public:
            app() : listener() { support_global(); }
            app(web::uri address) : listener(std::move(address)) { support_global(); }
            app(web::uri address, listener::http_listener_config config) : listener(std::move(address), std::move(config)) { support_global(); }

            template <typename C, typename... Args, typename = std::enable_if_t<std::is_base_of_v<controller_base, C>>>
            void support(const utility::string_t& path, Args&&... args)
            {
                support(path, std::make_unique<C>(std::forward<Args>(args)...));
            }
            void support(route_path&& path, controller_ptr&& controller) { routes.emplace(path, std::move(controller)); }

            pplx::task<void> open() { return listener.open(); }
            pplx::task<void> close() { return listener.close(); }
        };
    } // namespace api
} // namespace web

#endif // !CPPRESTAPI_APP
