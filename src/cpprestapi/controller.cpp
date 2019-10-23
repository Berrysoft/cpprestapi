#include <algorithm>
#include <cpprestapi/controller.hpp>

using namespace utility;
using namespace web;
using namespace web::http;
using namespace std;

namespace web::api
{
    bool controller_base::handle(const route_path& path, http_request message) const
    {
        for (auto& pair : routes)
        {
            const optional<method>& acc_mtd = pair.second->accept_method();
            if ((!acc_mtd || *acc_mtd == message.method()) && pair.first.size() <= path.size())
            {
                vector<string_t> params(pair.second->params_size());
                auto lit = pair.first.begin(), rit = path.begin();
                for (; lit != pair.first.end() && rit != path.end(); lit++, rit++)
                {
                    if (lit->index() == 0 && get<string_t>(*lit) != get<string_t>(*rit))
                    {
                        goto contouter;
                    }
                    else if (lit->index() == 1)
                    {
                        params[get<size_t>(*lit)] = get<string_t>(*rit);
                    }
                }
                if (lit != pair.first.end() || rit != path.end())
                {
                    goto contouter;
                }
                pair.second->execute(move(message), move(params));
                return true;
            }
        contouter:;
        }
        return false;
    }
} // namespace web::api
