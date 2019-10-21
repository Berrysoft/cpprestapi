#include "api_controller.hpp"
#include <functional>

using namespace std;
using namespace web::http;
using namespace utility;

template <typename _Tp, typename _Class, typename... _Args>
constexpr decltype(auto) mem_fn_bind(_Class (_Tp::*__f)(_Args...), _Tp* __t)
{
    return [=](_Args... args) { return (__t->*__f)(args...); };
}

api_controller::api_controller()
{
    this->support(U("/hello"), function<void(http_request)>(mem_fn_bind(&api_controller::get_hello, this)));
    this->support(U("/hello/{0}"), function<void(http_request, string_t)>(mem_fn_bind(&api_controller::get_hello_name, this)));
}

void api_controller::get_hello_name(web::http::http_request message, utility::string_t name)
{
    utf8ostringstream stream;
    stream << "Hello, " << name.c_str() << '!';
    message.reply(status_codes::OK, stream.str());
}
