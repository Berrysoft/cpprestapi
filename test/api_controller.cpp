#include "api_controller.hpp"
#include <functional>

using namespace std;
using namespace web::http;
using namespace utility;

template <typename _Tp, typename _Class, typename... _Args>
constexpr std::function<_Class(_Args...)> mem_fn_bind(_Class (_Tp::*__f)(_Args...), _Tp* __t)
{
    return [=](_Args... args) { return (__t->*__f)(std::move(args)...); };
}

api_controller::api_controller()
{
    this->support(U("/hello"), mem_fn_bind(&api_controller::get_hello, this));
    this->support(U("/hello/{0}"), mem_fn_bind(&api_controller::get_hello_name, this));
    this->support(U("/hello/{0}/{1}"), mem_fn_bind(&api_controller::get_hello_name_times, this));
}

void api_controller::get_hello_name_times(http_request message, string_t name, size_t times)
{
    ostringstream_t stream;
    stream << U("Hello, ") << name;
    if (times)
    {
        stream << U(", ") << times << U(" times");
    }
    stream << U('!');
    message.reply(status_codes::OK, stream.str());
}
