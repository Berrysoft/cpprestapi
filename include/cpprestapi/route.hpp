#ifndef CPPRESTAPI_ROUTE
#define CPPRESTAPI_ROUTE

#include <cpprest/http_msg.h>
#include <functional>
#include <optional>
#include <vector>

namespace web::api
{
    class route_base
    {
    private:
        std::optional<web::http::method> mtd;

    protected:
        route_base() : mtd(std::nullopt) {}
        route_base(const web::http::method& mtd) : mtd(mtd) {}

    public:
        virtual ~route_base() {}

    public:
        virtual std::size_t params_size() const noexcept = 0;
        const std::optional<web::http::method>& accept_method() const noexcept { return mtd; }
        virtual void execute(web::http::http_request message, std::vector<utility::string_t>&& params) const = 0;
    };

    namespace details
    {
        template <typename T>
        inline T get_param(const utility::string_t& param)
        {
            utility::istringstream_t stream{ param };
            T result;
            stream >> result;
            return result;
        }

        template <>
        inline utility::string_t get_param<utility::string_t>(const utility::string_t& param)
        {
            return std::move(param);
        }
    } // namespace details

    template <typename Result, typename... Args>
    class route : public route_base
    {
    private:
        using handler_type = std::function<Result(web::http::http_request, Args...)>;

        handler_type handler;

    public:
        route(handler_type&& handler) : route_base(), handler(std::move(handler)) {}
        route(const web::http::method& mtd, handler_type&& handler) : route_base(mtd), handler(std::move(handler)) {}
        ~route() override {}

        std::size_t params_size() const noexcept override { return sizeof...(Args); }

        void execute(web::http::http_request message, std::vector<utility::string_t>&& params) const override
        {
            execute(std::move(message), std::move(params), std::index_sequence_for<Args...>{});
        }

    private:
        template <std::size_t... Indicies>
        void execute(web::http::http_request message, std::vector<utility::string_t>&& params, std::index_sequence<Indicies...>) const
        {
            execute(std::move(message), details::get_param<Args>(params[Indicies])...);
        }

    public:
        void execute(web::http::http_request message, Args&&... args) const
        {
            handler(std::move(message), std::forward<Args>(args)...);
        }
    };

    template <typename Result, typename... Args>
    class route<pplx::task<Result>, Args...> : public route_base
    {
    private:
        using handler_type = std::function<pplx::task<Result>(web::http::http_request, Args...)>;

        handler_type handler;

    public:
        route(handler_type&& handler) : route_base(), handler(std::move(handler)) {}
        route(const web::http::method& mtd, handler_type&& handler) : route_base(mtd), handler(std::move(handler)) {}
        ~route() override {}

        std::size_t params_size() const noexcept override { return sizeof...(Args); }

        void execute(web::http::http_request message, std::vector<utility::string_t>&& params) const override
        {
            execute(std::move(message), std::move(params), std::index_sequence_for<Args...>{});
        }

    private:
        template <std::size_t... Indicies>
        void execute(web::http::http_request message, std::vector<utility::string_t>&& params, std::index_sequence<Indicies...>) const
        {
            execute(std::move(message), details::get_param<Args>(params[Indicies])...);
        }

    public:
        void execute(web::http::http_request message, Args&&... args) const
        {
            handler(std::move(message), std::forward<Args>(args)...).wait();
        }
    };
} // namespace web::api

#endif // !CPPRESTAPI_ROUTE
