#ifndef CPPRESTAPI_UTILITY
#define CPPRESTAPI_UTILITY

#ifdef CPPRESTAPI_STATIC_DEFINE
#define CPPRESTAPI_API
#else // CPPRESTAPI_STATIC_DEFINE
#ifndef CPPRESTAPI_API
#if defined(_MSC_VER)
#ifdef cpprestapi_EXPORTS
#define CPPRESTAPI_API __declspec(dllexport)
#else // cpprestapi_EXPORTS
#define CPPRESTAPI_API __declspec(dllimport)
#endif // cpprestapi_EXPORTS
#elif defined(__GNUC__)
#ifdef cpprestapi_EXPORTS
#define CPPRESTAPI_API __attribute__((visibility("default")))
#else // cpprestapi_EXPORTS
#define CPPRESTAPI_API
#endif // cpprestapi_EXPORTS
#else
#define CPPRESTAPI_API
#endif
#endif // !CPPRESTAPI_API
#endif // CPPRESTAPI_STATIC_DEFINE

#endif // !CPPRESTAPI_UTILITY
