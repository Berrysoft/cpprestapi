#include "api_controller.hpp"
#include <cpprestapi/app.hpp>
#include <iostream>

using namespace web;
using namespace web::api;
using namespace std;

int main()
{
    app a{ U("http://127.0.0.1:2333") };
    a.support<api_controller>(U("/api"));
    a.open().wait();

    cout << "Press ENTER to exit." << endl;

    string line;
    getline(cin, line);

    a.close().wait();
}
