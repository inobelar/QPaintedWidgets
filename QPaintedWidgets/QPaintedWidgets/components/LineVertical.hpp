#ifndef Q_PAINTED_WIDGETS___COMPONENTS___V_LINE_HPP
#define Q_PAINTED_WIDGETS___COMPONENTS___V_LINE_HPP

#include "AbstractLine.hpp"

namespace QPaintedWidgets {

namespace components {

struct LineVertical : public AbstractLine
{
    using self_t = LineVertical;

    using base_t = AbstractLine;

    using base_t::base_t;

    // -------------------------------------------------------------------------

    virtual QSize minimumSize() const override;

    virtual void draw(QPainter& p, const QRect& rect) override;
};

} // namespace components

} // namespace QPaintedWidgets

#endif // Q_PAINTED_WIDGETS___COMPONENTS___V_LINE_HPP
