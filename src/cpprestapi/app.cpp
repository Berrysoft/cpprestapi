#include <cpprestapi/app.hpp>

using namespace utility;
using namespace web::http;
using namespace std;

namespace web
{
    namespace api
    {
        void app::global_handler(http_request message)
        {
            string_t path = message.relative_uri().to_string();
            for (auto& pair : routes)
            {
                size_t i;
                for (i = 0; i < pair.first.length() && i < path.length(); i++)
                {
                    if (pair.first[i] != path[i]) break;
                }
                if (i >= pair.first.length())
                {
                    string_t subpath = path.substr(i);
                    pair.second->handle(subpath, move(message));
                    break;
                }
            }
        }
    } // namespace api
} // namespace web
