#include "api_controller.hpp"
#include <functional>

using namespace std;
using namespace web::http;
using namespace utility;

api_controller::api_controller()
{
    this->support(methods::GET, U("/hello"), &api_controller::get_hello, this);
    this->support(methods::GET, U("/hello/{0}"), &api_controller::get_hello_name, this);
    this->support(methods::GET, U("/hello/{0}/{1}"), &api_controller::get_hello_name_times, this);
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
