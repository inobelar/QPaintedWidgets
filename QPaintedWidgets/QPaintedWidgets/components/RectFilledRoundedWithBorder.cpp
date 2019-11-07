#include "RectFilledRoundedWithBorder.hpp"

QPaintedWidgets::components::RectFilledRoundedWithBorder::self_t& QPaintedWidgets::components::RectFilledRoundedWithBorder::setRounding(int radius)
{
    if(_rounding == radius) return (*this);

    _rounding = radius;

    this->update();

    return (*this);
}

int QPaintedWidgets::components::RectFilledRoundedWithBorder::getRounding() const
{
    return _rounding;
}

// -----------------------------------------------------------------------------

#include <QPainter>

void QPaintedWidgets::components::RectFilledRoundedWithBorder::draw(QPainter &p, const QPen &pen, const QBrush &brush, const QRect &rect)
{
    p.save();
    {
        /*
        p.setPen(pen);
        p.setBrush(brush);

        // Draw background (rounded) rect
        if(_rounding > 0)
        {
            p.setRenderHint(QPainter::RenderHint::Antialiasing, true); // For smoothing corners
            {
                p.drawRoundedRect(rect, _rounding, _rounding);
            }
            p.setRenderHint(QPainter::RenderHint::Antialiasing, false);
        }
        else
        {
            p.drawRect(rect);
        }
        */

        if(_rounding > 0)
        {

            p.setRenderHint(QPainter::RenderHint::Antialiasing, true); // For smoothing corners
            {
                // For better looking draw two rects separately (border over filled)

                const auto smoothed_rect = QRectF(rect).translated(0.5, 0.5);

                p.setPen(Qt::NoPen);
                p.setBrush(brush);
                p.drawRoundedRect(smoothed_rect, _rounding, _rounding);

                p.setPen(pen);
                p.setBrush(Qt::NoBrush);
                p.drawRoundedRect(smoothed_rect, _rounding, _rounding);
            }
            p.setRenderHint(QPainter::RenderHint::Antialiasing, false);
        }
        else
        {
            p.setPen(Qt::NoPen);
            p.setBrush(brush);
            p.drawRect(rect);

            p.setPen(pen);
            p.setBrush(Qt::NoBrush);
            p.drawRect(rect);
        }

    }
    p.restore();
}

void QPaintedWidgets::components::RectFilledRoundedWithBorder::draw(QPainter &p, const QRect &rect)
{
    this->draw(p, get_displayed_pen(), get_displayed_brush(), rect);
}
