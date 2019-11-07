#ifndef Q_PAINTED_WIDGETS___COMPOSED___GENERIC___TUPLE_ALIGNED___TUPLE_STRETCHED_HPP
#define Q_PAINTED_WIDGETS___COMPOSED___GENERIC___TUPLE_ALIGNED___TUPLE_STRETCHED_HPP

#include <array>

// Special wrapper for stretch-factors agregation

namespace QPaintedWidgets {

template <typename BaseT, std::size_t ... StretchFactors>
struct Tuple_Stretched : public BaseT
{
    // TODO: somehow add checking, that BaseT is derived from ComponentsTuple<ComponentsT ...>

    using base_t = BaseT;

    using base_t::base_t;

    static constexpr std::size_t STRETCHES_COUNT = (sizeof...(StretchFactors));

    static_assert (STRETCHES_COUNT > 0,
                   "Stretch factors count must be greater then zero");

    static_assert (STRETCHES_COUNT == base_t::count(),
                   "Stertch factors count must be the same as components count");

    using stretches_t = std::array<std::size_t, STRETCHES_COUNT>;

    // Not constexpr member field, but constexpr static method, because we
    // cannot create field here, without out-of-class initialization
    static constexpr stretches_t get_stretches()
    {
        return { StretchFactors ... };
    }
};

} // namespace QPaintedWidgets

#endif // Q_PAINTED_WIDGETS___COMPOSED___GENERIC___TUPLE_ALIGNED___TUPLE_STRETCHED_HPP
