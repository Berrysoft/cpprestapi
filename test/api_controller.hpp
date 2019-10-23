#ifndef CPPRESTAPI_TEST_API_CONTROLLER
#define CPPRESTAPI_TEST_API_CONTROLLER

#include <cpprestapi/controller.hpp>

class api_controller : public web::api::controller_base
{
public:
    api_controller();

    void get_hello(web::http::http_request message) { get_hello_name(std::move(message), U("world")); }
    void get_hello_name(web::http::http_request message, utility::string_t name) { get_hello_name_times(std::move(message), std::move(name), 0); }
    void get_hello_name_times(web::http::http_request message, utility::string_t name, std::size_t times);
};

#endif // !CPPRESTAPI_TEST_API_CONTROLLER
