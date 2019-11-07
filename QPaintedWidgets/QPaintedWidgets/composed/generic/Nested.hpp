#ifndef Q_PAINTED_WIDGETS___COMPOSED__NESTED_HPP
#define Q_PAINTED_WIDGETS___COMPOSED__NESTED_HPP

#include "ComponentsTuple.hpp"

/**
    Special container component, for internal components, to draw them
    sequentially one above the others.

    For example (text draw above rectangle):

    @code{.cpp}
    Nested < ComponentsTuple <
        components::RectFilled,
        components::Text
    > >
    @endcode
 */

namespace QPaintedWidgets {

template <typename BaseT>
struct Nested : public BaseT
{
    // TODO: somehow add checking, that BaseT is derived from ComponentsTuple<ComponentsT ...>

    // TODO: add static_assert(num_components >= 2), because for single component its ... nonsense :D

    using base_t = BaseT;

    using base_t::base_t;

    virtual QSize minimumSize() const override
    {
        int max_width  = 0;
        int max_height = 0;
        base_t::for_each([&max_width, &max_height](const components::Component* component)
        {
            const auto min_size = component->minimumSize();
            max_width  = std::max(max_width,  min_size.width() );
            max_height = std::max(max_height, min_size.height());
        });

        return { max_width, max_height };
    }

    virtual void draw(QPainter& p, const QRect& rect) override
    {
        base_t::for_each([&p, &rect](components::Component* component)
        {
            component->draw(p, rect);
        });
    }
};

// Common shortcut
template <typename ... ComponentsT>
using Tuple_Nested = Nested< ComponentsTuple<ComponentsT...> >;

} // namespace QPaintedWidgets

#endif // Q_PAINTED_WIDGETS___COMPOSED__NESTED_HPP
