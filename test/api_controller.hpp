#ifndef CPPRESTAPI_TEST_API_CONTROLLER
#define CPPRESTAPI_TEST_API_CONTROLLER

#include <cpprestapi/controller.hpp>

class api_controller : public web::api::controller_base
{
public:
    api_controller();

    void get_hello(web::http::http_request message) { get_hello_name(std::move(message), U("world")); }
    void get_hello_name(web::http::http_request message, utility::string_t name);
};

#endif // !CPPRESTAPI_TEST_API_CONTROLLER
