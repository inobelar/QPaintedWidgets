#ifndef Q_PAINTED_WIDGETS___COMPONENTS___RECT_FILLED_ROUNDED_WITH_BORDER_HPP
#define Q_PAINTED_WIDGETS___COMPONENTS___RECT_FILLED_ROUNDED_WITH_BORDER_HPP

#include "RectFilledWithBorder.hpp"

namespace QPaintedWidgets {

namespace components {

class RectFilledRoundedWithBorder : public RectFilledWithBorder
{
    int _rounding = 4;

public:

    using self_t = RectFilledRoundedWithBorder;

    using base_t = RectFilledWithBorder;

    using base_t::base_t;

    // -------------------------------------------------------------------------

    self_t& setRounding(int radius);
    int getRounding() const;

    // -------------------------------------------------------------------------

    virtual void draw(QPainter &p, const QPen &pen, const QBrush &brush, const QRect &rect) override;

    virtual void draw(QPainter& p, const QRect& rect) override;
};

} // namespace components

} // namespace QPaintedWidgets

#endif // Q_PAINTED_WIDGETS___COMPONENTS___RECT_FILLED_ROUNDED_WITH_BORDER_HPP
