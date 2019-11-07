#ifndef Q_PAINTED_WIDGETS___COMPONENTS___PRIMITIVES___CIRCLE_HPP
#define Q_PAINTED_WIDGETS___COMPONENTS___PRIMITIVES___CIRCLE_HPP

#include "QPaintedWidgets/components/Component.hpp"

namespace QPaintedWidgets {

namespace components {

struct Circle : public components::Component
{
    using self_t = Circle;

    using base_t = components::Component;

    using base_t::base_t;

    virtual void draw(QPainter &p, const QRect &rect) override
    {
        // TODO
    }
};

} // namespace components

} // namespace QPaintedWidgets

#endif // Q_PAINTED_WIDGETS___COMPONENTS___PRIMITIVES___CIRCLE_HPP
