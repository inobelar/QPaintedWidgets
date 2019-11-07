#ifndef Q_PAINTED_WIDGETS___COMPONENTS___RECT_FILLED_ROUNDED_HPP
#define Q_PAINTED_WIDGETS___COMPONENTS___RECT_FILLED_ROUNDED_HPP

#include "RectFilled.hpp"

namespace QPaintedWidgets {

namespace components {

class RectFilledRounded : public RectFilled
{
    int _rounding = 4;

public:

    using self_t = RectFilledRounded;

    using base_t = RectFilled;

    using base_t::base_t;

    // -------------------------------------------------------------------------

    self_t& setRounding(int radius);
    int getRounding() const;

    // -------------------------------------------------------------------------

    virtual void draw(QPainter& p, const QBrush& brush, const QRect& rect) override;

    virtual void draw(QPainter &p, const QRect &rect) override;
};

} // namespace components

} // namespace QPaintedWidgets

#endif // Q_PAINTED_WIDGETS___COMPONENTS___RECT_FILLED_ROUNDED_HPP
