#include "AbstractText.hpp"

QPaintedWidgets::components::AbstractText::AbstractText(QWidget *w)
    : base_t(w)
{
    _font = base_t::widget->font();
}

// -----------------------------------------------------------------------------

QPaintedWidgets::components::AbstractText::self_t& QPaintedWidgets::components::AbstractText::setPen(const QPen &pen)
{
    if(_pen == pen) return (*this);

    _pen = pen;
    this->update();

    return (*this);
}

QPen QPaintedWidgets::components::AbstractText::getPen() const
{
    return _pen;
}

// -----------------------------------------------------------------------------

QPaintedWidgets::components::AbstractText::self_t& QPaintedWidgets::components::AbstractText::setPenHovered(const QPen &pen)
{
    if(_pen_hovered == pen) return (*this);

    _pen_hovered = pen;
    this->update();

    return (*this);
}

QPen QPaintedWidgets::components::AbstractText::getPenHovered() const
{
    return _pen_hovered;
}

// -----------------------------------------------------------------------------

QPaintedWidgets::components::AbstractText::self_t& QPaintedWidgets::components::AbstractText::setPenPressed(const QPen &pen)
{
    if(_pen_pressed == pen) return (*this);

    _pen_pressed = pen;
    this->update();

    return (*this);
}

QPen QPaintedWidgets::components::AbstractText::getPenPressed() const
{
    return _pen_pressed;
}

// -----------------------------------------------------------------------------

QPaintedWidgets::components::AbstractText::self_t& QPaintedWidgets::components::AbstractText::setPenDisabled(const QPen &pen)
{
    if(_pen_disabled == pen) return (*this);

    _pen_disabled = pen;
    this->update();

    return (*this);
}

QPen QPaintedWidgets::components::AbstractText::getPenDisabled() const
{
    return _pen_disabled;
}

// -----------------------------------------------------------------------------

QPaintedWidgets::components::AbstractText::self_t& QPaintedWidgets::components::AbstractText::setFont(const QFont font)
{
    if(_font == font) return (*this);

    _font = font;

    on_font_change();

    // TODO: update minimum_size
    base_t::widget->updateGeometry();

    this->update();

    return (*this);
}

QFont QPaintedWidgets::components::AbstractText::getFont() const
{
    return _font;
}

// -----------------------------------------------------------------------------

QPaintedWidgets::components::AbstractText::self_t& QPaintedWidgets::components::AbstractText::setFontPixelSize(int size)
{
    if(_font.pixelSize() == size) return (*this);

    _font.setPixelSize(size);

    on_font_change();

    // TODO: update minimum_size
    base_t::widget->updateGeometry();

    this->update();

    return (*this);
}

QPaintedWidgets::components::AbstractText::self_t& QPaintedWidgets::components::AbstractText::setFontBold(bool enable)
{
    if(_font.bold() == enable) return (*this);

    _font.setBold(enable);

    on_font_change();

    // TODO: update minimum size
    base_t::widget->updateGeometry();

    this->update();

    return (*this);
}

// -----------------------------------------------------------------------------

QPaintedWidgets::components::AbstractText::self_t& QPaintedWidgets::components::AbstractText::setAlignment(const Qt::Alignment alignment)
{
    if(_alignment == alignment) return (*this);

    _alignment = alignment;
    this->update();

    return (*this);
}

Qt::Alignment QPaintedWidgets::components::AbstractText::getAlignment() const
{
    return _alignment;
}

// -----------------------------------------------------------------------------

#include <QAbstractButton>

QPen QPaintedWidgets::components::AbstractText::get_displayed_pen()
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

void QPaintedWidgets::components::AbstractText::draw(QPainter &p, const QRect &rect)
{
    this->draw(p, get_displayed_pen(), rect);
}
