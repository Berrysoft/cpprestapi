#include <cpprestapi/controller.hpp>

using namespace utility;

namespace web
{
    namespace api
    {
        bool controller_base::validate_path(const utility::string_t& path)
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
    } // namespace api
} // namespace web
