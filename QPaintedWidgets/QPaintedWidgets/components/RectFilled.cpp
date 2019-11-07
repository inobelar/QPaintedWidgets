#include "RectFilled.hpp"

QPaintedWidgets::components::RectFilled::self_t& QPaintedWidgets::components::RectFilled::setBrush(const QBrush &brush)
{
    if(_brush == brush) return (*this);

    _brush = brush;
    this->update();

    return (*this);
}

QBrush QPaintedWidgets::components::RectFilled::getBrush() const
{
    return _brush;
}

// -----------------------------------------------------------------------------

QPaintedWidgets::components::RectFilled::self_t& QPaintedWidgets::components::RectFilled::setBrushHovered(const QBrush &brush)
{
    if(_brush_hovered == brush) return (*this);

    _brush_hovered = brush;
    this->update();

    return (*this);
}

QBrush QPaintedWidgets::components::RectFilled::getBrushHovered() const
{
    return _brush_hovered;
}

// -----------------------------------------------------------------------------

QPaintedWidgets::components::RectFilled::self_t& QPaintedWidgets::components::RectFilled::setBrushPressed(const QBrush &brush)
{
    if(_brush_pressed == brush) return (*this);

    _brush_pressed = brush;
    this->update();

    return (*this);
}

QBrush QPaintedWidgets::components::RectFilled::getPressedBrush() const
{
    return _brush_pressed;
}

// -----------------------------------------------------------------------------

QPaintedWidgets::components::RectFilled::self_t& QPaintedWidgets::components::RectFilled::setBrushDisabled(const QBrush &brush)
{
    if(_brush_disabled == brush) return (*this);

    _brush_disabled = brush;
    this->update();

    return (*this);
}

QBrush QPaintedWidgets::components::RectFilled::getBrushDisabled() const
{
    return _brush_disabled;
}

// -----------------------------------------------------------------------------

#include <QPainter>
#include <QAbstractButton>

QBrush QPaintedWidgets::components::RectFilled::get_displayed_brush() const
{
    QBrush brush = _brush;

    if(base_t::widget->isEnabled())
    {
        const bool hovered = base_t::hovered_by_cursor();

        if(auto* btn = qobject_cast<QAbstractButton*>(base_t::widget)) // If widget is button - check is it pressed
        {
            if(btn->isDown()) // Button pressed
            {
                brush = _brush_pressed;
            }
            else // Not pressed, but may be hovered
            {
                if(hovered)
                {
                    brush = _brush_hovered;
                }
            }
        }
        else // Not Button, but may hovered
        {
            if(hovered)
            {
                brush = _brush_hovered;
            }
        }
    }
    else // Disabled
    {
        brush = _brush_disabled;
    }

    return brush;
}

void QPaintedWidgets::components::RectFilled::draw(QPainter &p, const QBrush &brush, const QRect &rect)
{
    p.fillRect(rect, brush);
}

void QPaintedWidgets::components::RectFilled::draw(QPainter &p, const QRect &rect)
{
    this->draw(p, get_displayed_brush(), rect);
}
