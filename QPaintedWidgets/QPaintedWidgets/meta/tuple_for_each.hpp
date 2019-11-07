#ifndef Q_PAINTED_WIDGETS___META___TUPLE_FOR_EACH_HPP
#define Q_PAINTED_WIDGETS___META___TUPLE_FOR_EACH_HPP

#include <tuple>

// via: https://stackoverflow.com/a/16387374

// Alternate solution:
//     - https://stackoverflow.com/a/26912970
//           + Port of std::index_sequence for c++11: https://stackoverflow.com/a/32223343
//
// In case of post c++11 version - use it:
//     - https://www.fluentcpp.com/2019/03/08/stl-algorithms-on-tuples/

namespace QPaintedWidgets {

namespace meta {

namespace detail
{
    template <int... Is>
    struct seq { };

    template <int N, int... Is>
    struct gen_seq : gen_seq<N - 1, N - 1, Is...> { };

    template <int... Is>
    struct gen_seq<0, Is...> : seq<Is...> { };
}

namespace detail
{
    template <typename T, typename F, int... Is>
    inline void for_each(T& tuple, F&& func, seq<Is...>)
    {
        auto l = { (func(std::get<Is>(tuple)), 0)... };
        (void)l; // Suppress compiler warning
    }

    template <typename T, typename F, int... Is>
    inline void for_each(const T& tuple, F&& func, seq<Is...>)
    {
        auto l = { (func(std::get<Is>(tuple)), 0)... };
        (void)l; // Suppress compiler warning
    }
}

template <typename... Ts, typename F>
inline void for_each_in_tuple(std::tuple<Ts...>& tuple, F&& func)
{
    constexpr auto COUNT = sizeof...(Ts);
    detail::for_each(tuple, func, detail::gen_seq<COUNT>());
}

template <typename... Ts, typename F>
inline void for_each_in_tuple(const std::tuple<Ts...>& tuple, F&& func)
{
    constexpr auto COUNT = sizeof...(Ts);
    detail::for_each(tuple, func, detail::gen_seq<COUNT>());
}

} // namespace meta

} // namespace QPaintedWidgets


#endif // Q_PAINTED_WIDGETS___META___TUPLE_FOR_EACH_HPP
