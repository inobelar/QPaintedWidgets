#ifndef Q_PAINTED_WIDGETS___COMPONENTS___RECT_FILLED_HPP
#define Q_PAINTED_WIDGETS___COMPONENTS___RECT_FILLED_HPP

#include "Component.hpp"

namespace QPaintedWidgets {

namespace components {

class RectFilled : public Component
{
    QBrush _brush          = QColor{255,255,255, 150};
    QBrush _brush_hovered  = QBrush(QColor(255, 255, 255, 170));
    QBrush _brush_pressed  = QBrush(QColor(255, 255, 255, 200));
    QBrush _brush_disabled = QBrush(QColor(255,255,255, 50), Qt::BrushStyle::Dense6Pattern);

public:

    using self_t = RectFilled;

    using base_t = Component;

    using base_t::base_t;

    // -------------------------------------------------------------------------

    self_t& setBrush(const QBrush& brush);
    QBrush getBrush() const;

    // -------------------------------------------------------------------------

    self_t& setBrushHovered(const QBrush& brush);
    QBrush getBrushHovered() const;

    // -------------------------------------------------------------------------

    self_t& setBrushPressed(const QBrush& brush);
    QBrush getPressedBrush() const;

    // -------------------------------------------------------------------------

    self_t& setBrushDisabled(const QBrush& brush);
    QBrush getBrushDisabled() const;

    // -------------------------------------------------------------------------

    virtual QBrush get_displayed_brush() const;

    virtual void draw(QPainter& p, const QBrush& brush, const QRect& rect);

    virtual void draw(QPainter &p, const QRect &rect) override;
};

} // namespace components

} // namespace QPaintedWidgets

#endif // Q_PAINTED_WIDGETS___COMPONENTS___RECT_FILLED_HPP
