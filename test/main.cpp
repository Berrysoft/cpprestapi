#include "api_controller.hpp"
#include <cpprestapi/app.hpp>
#include <iostream>

#ifdef WIN32
#include <Windows.h>
#else
#include <csignal>
#endif

using namespace web;
using namespace web::api;
using namespace std;

volatile bool global_exit = false;

#ifdef WIN32
BOOL WINAPI int_handler(DWORD dwCtrlType)
{
    return global_exit = (dwCtrlType == CTRL_C_EVENT);
}
#else
void int_handler(int sig)
{
    global_exit = true;
}
#endif

int main()
{
#ifdef WIN32
    SetConsoleCtrlHandler(int_handler, TRUE);
#else
    signal(SIGINT, int_handler);
#endif

    app a{ U("http://127.0.0.1:2333") };
    a.support<api_controller>(U("/api"));
    a.open().wait();

    cout << "Server started." << endl;
    cout << "Press Ctrl+C to exit." << endl;

    while (!global_exit)
        ;

    a.close().wait();
    cout << "Server exited." << endl;
}
