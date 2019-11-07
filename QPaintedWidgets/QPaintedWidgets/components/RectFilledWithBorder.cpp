#include "RectFilledWithBorder.hpp"

QPaintedWidgets::components::RectFilledWithBorder::self_t& QPaintedWidgets::components::RectFilledWithBorder::setPen(const QPen &pen)
{
    if(_pen == pen) return (*this);

    _pen = pen;

    this->update();

    return (*this);
}

QPen QPaintedWidgets::components::RectFilledWithBorder::getPen() const
{
    return _pen;
}

// -----------------------------------------------------------------------------

QPaintedWidgets::components::RectFilledWithBorder::self_t& QPaintedWidgets::components::RectFilledWithBorder::setPenHovered(const QPen &pen)
{
    if(_pen_hovered == pen) return (*this);

    _pen_hovered = pen;

    this->update();

    return (*this);
}

QPen QPaintedWidgets::components::RectFilledWithBorder::getPenHovered() const
{
    return _pen_hovered;
}

// -----------------------------------------------------------------------------

QPaintedWidgets::components::RectFilledWithBorder::self_t& QPaintedWidgets::components::RectFilledWithBorder::setPenPressed(const QPen &pen)
{
    if(_pen_pressed == pen) return (*this);

    _pen_pressed = pen;

    this->update();

    return (*this);
}

QPen QPaintedWidgets::components::RectFilledWithBorder::getPenPressed() const
{
    return _pen_pressed;
}

// -----------------------------------------------------------------------------

QPaintedWidgets::components::RectFilledWithBorder::self_t& QPaintedWidgets::components::RectFilledWithBorder::setPenDisabled(const QPen &pen)
{
    if(_pen_disabled == pen) return (*this);

    _pen_disabled = pen;

    this->update();

    return (*this);
}

QPen QPaintedWidgets::components::RectFilledWithBorder::getPenDisabled() const
{
    return _pen_disabled;
}

// -----------------------------------------------------------------------------

#include <QAbstractButton>

QPen QPaintedWidgets::components::RectFilledWithBorder::get_displayed_pen() const
{
    QPen pen = _pen;

    if(base_t::widget->isEnabled())
    {
        const bool hovered = base_t::hovered_by_cursor();

        if(auto* btn = qobject_cast<QAbstractButton*>(base_t::widget))
        {
            if(btn->isDown()) // Button Pressed
            {
                pen = _pen_pressed;
            }
            else // Not pressed, but may be hovered
            {
                if(hovered)
                {
                    pen = _pen_hovered;
                }
            }
        }
        else // Not button, but may be hovered
        {
            if(hovered)
            {
                pen = _pen_hovered;
            }
        }
    }
    else // Disabled
    {
        pen = _pen_disabled;
    }

    return pen;
}

#include <QPainter>

void QPaintedWidgets::components::RectFilledWithBorder::draw(QPainter &p, const QPen &pen, const QBrush &brush, const QRect &rect)
{
    p.save();
    {
        p.setPen(pen);
        p.setBrush(brush);

        p.drawRect(rect);
    }
    p.restore();
}

void QPaintedWidgets::components::RectFilledWithBorder::draw(QPainter &p, const QRect &rect)
{
    this->draw(p, get_displayed_pen(), get_displayed_brush(), rect);
}
