#ifndef CPPRESTAPI_ROUTE
#define CPPRESTAPI_ROUTE

#include <cpprest/http_msg.h>
#include <functional>
#include <vector>

namespace web
{
    namespace api
    {
        struct route_base
        {
            virtual std::size_t params_size() const noexcept = 0;
            virtual void execute(web::http::http_request message, std::vector<utility::string_t>&& params) const = 0;
        };

        namespace details
        {
            template <typename T>
            T get_param(const utility::string_t& param)
            {
                utility::istringstream_t stream{ param };
                T result;
                stream << result;
                return result;
            }
        } // namespace details

        template <typename... Args>
        class route : public route_base
        {
        private:
            using handler_type = std::function<void(web::http::http_request, Args...)>;

            handler_type handler;

        public:
            route(handler_type&& handler) : handler(std::move(handler)) {}

            std::size_t params_size() const noexcept override { return sizeof...(Args); }

            void execute(web::http::http_request message, std::vector<utility::string_t>&& params) const override
            {
                // TODO
            }

            void execute(web::http::http_request message, Args&&... args) const { handler(std::move(message), std::forward<Args>(args)...) }
        };
    } // namespace api
} // namespace web

#endif // !CPPRESTAPI_ROUTE
