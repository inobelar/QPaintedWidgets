#ifndef Q_PAINTED_WIDGETS___COMPONENTS___RECT_FILLED_WITH_BORDER_HPP
#define Q_PAINTED_WIDGETS___COMPONENTS___RECT_FILLED_WITH_BORDER_HPP

#include "RectFilled.hpp"

#include <QPen>

namespace QPaintedWidgets {

namespace components {

class RectFilledWithBorder : public RectFilled
{
    QPen _pen          = QColor(0, 0, 0, 200);
    QPen _pen_hovered  = QColor(0, 0, 0, 255);
    QPen _pen_pressed  = QColor(0, 0, 0, 255);
    QPen _pen_disabled = QColor(0, 0, 0, 150);

    using RectFilled::draw; // Default draw (without border) disabled

public:

    using self_t = RectFilledWithBorder;

    using base_t = RectFilled;

    using base_t::base_t;

    // -------------------------------------------------------------------------

    self_t& setPen(const QPen& pen);
    QPen getPen() const;

    // -------------------------------------------------------------------------

    self_t& setPenHovered(const QPen& pen);
    QPen getPenHovered() const;

    // -------------------------------------------------------------------------

    self_t& setPenPressed(const QPen& pen);
    QPen getPenPressed() const;

    // -------------------------------------------------------------------------

    self_t& setPenDisabled(const QPen& pen);
    QPen getPenDisabled() const;

    // -------------------------------------------------------------------------

    virtual QPen get_displayed_pen() const;

    virtual void draw(QPainter& p, const QPen& pen, const QBrush& brush, const QRect& rect);

    virtual void draw(QPainter &p, const QRect &rect) override;
};

} // namespace components

} // namespace QPaintedWidgets

#endif // Q_PAINTED_WIDGETS___COMPONENTS___RECT_FILLED_WITH_BORDER_HPP
