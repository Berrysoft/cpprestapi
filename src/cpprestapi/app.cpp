#include <cpprestapi/app.hpp>

using namespace utility;
using namespace web::http;
using namespace std;

namespace web::api
{
    void app::global_handler(http_request message)
    {
        route_path path = message.relative_uri().to_string();
        for (auto& pair : routes)
        {
            if (pair.first.size() <= path.size())
            {
                if (equal(pair.first.begin(), pair.first.end(), path.begin(), path.begin() + pair.first.size()))
                {
                    if (pair.second->handle(path.sub_path(pair.first.size()), move(message)))
                        return;
                }
            }
        }
        global_not_found(move(message));
    }

    void app::global_not_found(http_request message)
    {
        message.reply(status_codes::NotFound);
    }
} // namespace web::api
