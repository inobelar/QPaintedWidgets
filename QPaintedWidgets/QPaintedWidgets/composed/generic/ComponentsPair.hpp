#ifndef Q_PAINTED_WIDGETS___COMPOSED___GENERIC___COMPONENTS_PAIR_HPP
#define Q_PAINTED_WIDGETS___COMPOSED___GENERIC___COMPONENTS_PAIR_HPP

#include "ComponentsTuple.hpp"

/**
    Simple alias for ComponentsTuple with convenient accessors:
        .first();
        .second();
    like in std::pair
 */

namespace QPaintedWidgets {

template <typename ComponentFirst, typename ComponentSecond>
struct ComponentsPair : public ComponentsTuple<ComponentFirst, ComponentSecond>
{
    static_assert (std::is_base_of<components::Component, ComponentFirst>::value == true,
                   "ComponentFirst must be derived from Component");

    static_assert (std::is_base_of<components::Component, ComponentSecond>::value == true,
                   "ComponentSecond must be derived from Component");

    // -------------------------------------------------------------------------

    using base_t = ComponentsTuple<ComponentFirst, ComponentSecond>;
    using base_t::base_t;

    using first_t  = ComponentFirst;
    using second_t = ComponentSecond;

    // -------------------------------------------------------------------------
    // Convenient aliases

    first_t*  first()  { return base_t::template get<0>(); }
    second_t* second() { return base_t::template get<1>(); }

    const first_t*  first()  const { return base_t::template get<0>(); }
    const second_t* second() const { return base_t::template get<1>(); }

};

} // namespace QPaintedWidgets

#endif // Q_PAINTED_WIDGETS___COMPOSED___GENERIC___COMPONENTS_PAIR_HPP
