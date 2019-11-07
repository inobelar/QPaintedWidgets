#ifndef Q_PAINTED_WIDGETS___COMPOSED___GENERIC___TUPLE_ALIGNED_HPP
#define Q_PAINTED_WIDGETS___COMPOSED___GENERIC___TUPLE_ALIGNED_HPP

#include "QPaintedWidgets/composed/generic/ComponentsTuple.hpp"

// Special wrapper for compile-time checking for spacing-between-components existance

namespace QPaintedWidgets {

template <typename BaseT>
class Tuple_Aligned : public BaseT
{
    // TODO: somehow add checking, that BaseT is derived from ComponentsTuple<ComponentsT ...>

    // -------------------------------------------------------------------------

    // via: https://stackoverflow.com/a/55191593

    template <typename ... Ts>
    struct voider {
        using type = void;
    };

    template <typename T, typename = void>
    struct has_getSpacing : std::false_type{};

    template <typename T>
    struct has_getSpacing<T, typename voider<decltype(std::declval<T>().getSpacing())>::type> : std::true_type{};

    // NOTE: decltype() above requires RTTI :C

    // -------------------------------------------------------------------------

public:

    using base_t = BaseT;
    using base_t::base_t;

protected:

    // -------------------------------------------------------------------------
    // SFINAE selected methods to produce spacing, depending on casesm when it's
    // available or not

    // If Base Type NOT derived from WithSpacing<> - as spacing used simply nothing
    template<typename T = BaseT>
        constexpr
        typename std::enable_if< has_getSpacing<T>::value == false, int>::type
    __spacing() const {
        return 0;
    }

    // If Base Type IS derived from WithSpacing<> - as spacing used WithSpacing::getSpacing()
    template<typename T = BaseT>
        typename std::enable_if< has_getSpacing<T>::value == true, int>::type
    __spacing() const {
        return base_t::getSpacing();
    }

    // -------------------------------------------------------------------------

    int __total_spacing() const { // Total spacing sum between components
        constexpr int spaces_count = (base_t::count() - 1);
        return spaces_count * __spacing();
    }
};

} // namespace QPaintedWidgets

#endif // Q_PAINTED_WIDGETS___COMPOSED___GENERIC___TUPLE_ALIGNED_HPP
