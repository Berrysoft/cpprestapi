#ifndef CPPRESTAPI_ROUTE_PATH
#define CPPRESTAPI_ROUTE_PATH

#include <algorithm>
#include <cpprest/base_uri.h>
#include <cpprestapi/utility.hpp>
#include <variant>
#include <vector>

namespace web
{
    namespace api
    {
        using route_node = std::variant<utility::string_t, std::size_t>;

        class route_path
        {
        private:
            std::vector<route_node> paths;

            route_path(std::vector<route_node>&& paths) : paths(std::move(paths)) {}

        public:
            route_path() : paths() {}
            CPPRESTAPI_API route_path(const utility::string_t& path);

            auto begin() const noexcept { return paths.begin(); }
            auto end() const noexcept { return paths.end(); }

            std::size_t size() const noexcept { return paths.size(); }

            route_path sub_path(std::size_t index) { return route_path(std::vector<route_node>(paths.begin() + index, paths.end())); }

            friend struct std::hash<route_path>;
        };

        inline bool operator==(const route_path& p1, const route_path& p2) { return std::equal(p1.begin(), p1.end(), p2.begin(), p2.end()); }
        inline bool operator!=(const route_path& p1, const route_path& p2) { return !(p1 == p2); }

        class path_exception : public web::uri_exception
        {
        public:
            path_exception(std::string msg) : uri_exception(std::move(msg)) {}
        };
    } // namespace api
} // namespace web

namespace std
{
    template <>
    struct hash<web::api::route_path>
    {
        using argument_type = web::api::route_path;
        using result_type = size_t;

        result_type operator()(const argument_type& path) const noexcept
        {
            result_type result{};
            for (auto& node : path)
            {
                switch (node.index())
                {
                case 0:
                    result ^= hash<utility::string_t>{}(get<utility::string_t>(node));
                    break;
                case 1:
                    result ^= hash<size_t>{}(get<size_t>(node));
                    break;
                }
            }
            return result;
        }
    };
} // namespace std

#endif // !CPPRESTAPI_ROUTE_PATH
