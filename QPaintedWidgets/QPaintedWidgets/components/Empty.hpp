#ifndef Q_PAINTED_WIDGETS___COMPONENTS___EMPTY_HPP
#define Q_PAINTED_WIDGETS___COMPONENTS___EMPTY_HPP

#include "Component.hpp"

namespace QPaintedWidgets {

namespace components {

class Empty : public Component
{
    QSize _minSize = {0, 0};

public:

    using self_t = Empty;

    using base_t = Component;

    using base_t::base_t;

    // -------------------------------------------------------------------------

    self_t& setMinimumSize(const QSize& size);
    QSize getMinimumSize() const;

    // -------------------------------------------------------------------------

    virtual QSize minimumSize() const override;

    virtual void draw(QPainter &p, const QRect &rect) override;
};

} // namespace components

} // namespace QPaintedWidgets

#endif // Q_PAINTED_WIDGETS___COMPONENTS___EMPTY_HPP
