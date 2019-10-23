#include <cpprestapi/route_path.hpp>

using namespace utility;
using namespace web;
using namespace std;

namespace web::api
{
    route_path::route_path(const string_t& path) : paths()
    {
        for (const string_t& str : uri::split_path(path))
        {
            if (str.front() == '{')
            {
                if (str.back() == '}')
                {
                    istringstream_t stream{ str.substr(1, str.length() - 2) };
                    size_t index;
                    stream >> index;
                    paths.emplace_back(index);
                }
                else
                {
                    throw path_exception("Invalid parameter.");
                }
            }
            else
            {
                paths.emplace_back(move(str));
            }
        }
    }
} // namespace web::api
