#ifndef CPPRESTAPI_CONTROLLER
#define CPPRESTAPI_CONTROLLER

#include <cpprest/uri.h>
#include <cpprestapi/route.hpp>
#include <cpprestapi/route_path.hpp>
#include <cpprestapi/utility.hpp>
#include <memory>
#include <unordered_map>

namespace web::api
{
    namespace details
    {
        template <typename _Tp, typename _Class, typename... _Args>
        constexpr std::function<_Class(_Args...)> mem_fn_bind(_Class (_Tp::*__f)(_Args...), _Tp* __t)
        {
            return [=](_Args... args) { return (__t->*__f)(std::move(args)...); };
        }
    } // namespace details

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
        template <typename T, typename... Args>
        void support(const utility::string_t& path, void (T::*f)(web::http::http_request, Args...), T* t)
        {
            support(path, details::mem_fn_bind(f, t));
        }
        void support(route_path&& path, route_ptr&& route)
        {
            routes.emplace(path, std::move(route));
        }

    public:
        CPPRESTAPI_API void handle(const route_path& path, web::http::http_request message) const;
    };
} // namespace web::api

#endif // !CPPRESTAPI_CONTROLLER
