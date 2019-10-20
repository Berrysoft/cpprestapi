#include <cpprestapi/controller.hpp>

using namespace utility;
using namespace web;
using namespace web::http;
using namespace std;

namespace web
{
    namespace api
    {
        bool controller_base::validate_path(const string_t& path)
        {
            bool par = false;
            for (size_t i = 0; i < path.length(); i++)
            {
                switch (path[i])
                {
                case '{':
                    if (par)
                        return false;
                    else
                        par = true;
                    break;
                case '}':
                    if (!par)
                        return false;
                    else
                        par = false;
                    if (i + 1 < path.length() && path[i + 1] != '/')
                        return false;
                    break;
                }
            }
            return true;
        }

        void parse(const string_t& route, const string_t& path, route_base* r, http_request message)
        {
        }

        void controller_base::handle(const string_t& path, http_request message)
        {
            for (auto& pair : routes)
            {
                size_t i;
                for (i = 0; i < pair.first.length() && i < path.length(); i++)
                {
                    if (pair.first[i] != path[i]) break;
                }
                if (i < pair.first.length() && i < path.length() && pair.first[i] == '{')
                {
                    parse(pair.first.substr(i), path.substr(i), pair.second.get(), move(message));
                    break;
                }
            }
        }
    } // namespace api
} // namespace web
