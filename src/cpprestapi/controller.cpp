#include <algorithm>
#include <cpprestapi/controller.hpp>

using namespace utility;
using namespace web;
using namespace web::http;
using namespace std;

namespace web
{
    namespace api
    {
        void controller_base::handle(const route_path& path, http_request message) const
        {
            for (auto& pair : routes)
            {
                if (pair.first.size() <= path.size())
                {
                    if (equal(pair.first.begin(), pair.first.end(), path.begin(), path.begin() + pair.first.size()))
                    {
                        // TODO
                    }
                }
            }
        }
    } // namespace api
} // namespace web
