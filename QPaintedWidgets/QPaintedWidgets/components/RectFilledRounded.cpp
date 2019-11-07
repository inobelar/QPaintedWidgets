#include "RectFilledRounded.hpp"

QPaintedWidgets::components::RectFilledRounded::self_t& QPaintedWidgets::components::RectFilledRounded::setRounding(int radius)
{
    if(_rounding == radius) return (*this);

    _rounding = radius;
    base_t::widget->update();

    return (*this);
}

int QPaintedWidgets::components::RectFilledRounded::getRounding() const {
    return _rounding;
}

// -----------------------------------------------------------------------------

#include <QPainter>

void QPaintedWidgets::components::RectFilledRounded::draw(QPainter &p, const QBrush &brush, const QRect &rect)
{
    p.save();
    {
        // Draw background (rounded) rect
        if(_rounding > 0)
        {
            p.setPen(Qt::NoPen);
            p.setBrush(brush);

            p.setRenderHint(QPainter::RenderHint::Antialiasing, true); // For smoothing corners
            {
                p.drawRoundedRect(rect, _rounding, _rounding);
            }
            p.setRenderHint(QPainter::RenderHint::Antialiasing, false);
        }
        else
        {
            p.fillRect(rect, brush);
        }
    }
    p.restore();
}

void QPaintedWidgets::components::RectFilledRounded::draw(QPainter &p, const QRect &rect)
{
    this->draw(p, get_displayed_brush(), rect);
}
