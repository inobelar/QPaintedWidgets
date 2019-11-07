#ifndef Q_PAINTED_WIDGETS___COMPONENTS___LINE_HORIZONTAL_HPP
#define Q_PAINTED_WIDGETS___COMPONENTS___LINE_HORIZONTAL_HPP

#include "AbstractLine.hpp"

namespace QPaintedWidgets {

namespace components {

struct LineHorizontal : public AbstractLine
{
    using self_t = LineHorizontal;

    using base_t = AbstractLine;

    using base_t::base_t;

    // -------------------------------------------------------------------------

    virtual QSize minimumSize() const override;

    virtual void draw(QPainter& p, const QRect& rect) override;
};

} // namespace components

} // namespace QPaintedWidgets

#endif // Q_PAINTED_WIDGETS___COMPONENTS___LINE_HORIZONTAL_HPP
