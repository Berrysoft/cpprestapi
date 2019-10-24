#include "api_controller.hpp"
#include <condition_variable>
#include <cpprestapi/app.hpp>
#include <iostream>
#include <mutex>

#ifdef WIN32
#include <Windows.h>
#else
#include <csignal>
#endif

using namespace web;
using namespace web::api;
using namespace std;

mutex mtx;
condition_variable cond;

#ifdef WIN32
BOOL WINAPI int_handler(DWORD dwCtrlType)
{
    if (dwCtrlType == CTRL_C_EVENT)
    {
        cond.notify_all();
        return TRUE;
    }
    return FALSE;
}
#else
void int_handler(int sig)
{
    cond.notify_all();
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

    {
        unique_lock lock{ mtx };
        cond.wait(lock);
    }

    a.close().wait();
    cout << "Server exited." << endl;
}
