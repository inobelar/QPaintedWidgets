#include "Icon.hpp"

#include <QPainter>
#include "QPaintedWidgets/painting/pos_from_alignment.hpp"

#include <QAbstractButton>

QPaintedWidgets::components::Icon::self_t& QPaintedWidgets::components::Icon::setIcon(const QIcon &icon)
{
    _icon = icon;

    this->update();

    return (*this);
}

QIcon QPaintedWidgets::components::Icon::getIcon() const
{
    return _icon;
}

QPaintedWidgets::components::Icon::self_t& QPaintedWidgets::components::Icon::setIconHovered(const QIcon &icon)
{
    _icon_hovered = icon;

    this->update();

    return (*this);
}

QIcon QPaintedWidgets::components::Icon::getIconHovered() const
{
    return _icon_hovered;
}

QPaintedWidgets::components::Icon::self_t& QPaintedWidgets::components::Icon::setIconPressed(const QIcon &icon)
{
    _icon_pressed = icon;

    this->update();

    return (*this);
}

QIcon QPaintedWidgets::components::Icon::getIconPressed() const
{
    return _icon_pressed;
}

QPaintedWidgets::components::Icon::self_t& QPaintedWidgets::components::Icon::setIconDisabled(const QIcon &icon)
{
    _icon_disabled = icon;

    this->update();

    return (*this);
}

QIcon QPaintedWidgets::components::Icon::getIconDisabled() const
{
    return _icon_disabled;
}

QPaintedWidgets::components::Icon::self_t& QPaintedWidgets::components::Icon::setSize(const QSize &size)
{
    if(_size == size) return (*this);

    _size = size;

    // TODO: update minimum size
    base_t::widget->updateGeometry();

    this->update();

    return (*this);
}

QSize QPaintedWidgets::components::Icon::getSize() const
{
    return _size;
}

QPaintedWidgets::components::Icon::self_t& QPaintedWidgets::components::Icon::setAlignment(const Qt::Alignment alignment)
{
    if(_alignment == alignment) return (*this);

    _alignment = alignment;
    this->update();

    return (*this);
}

Qt::Alignment QPaintedWidgets::components::Icon::getAlignment() const
{
    return _alignment;
}

QSize QPaintedWidgets::components::Icon::minimumSize() const
{
    return this->getSize();
}

std::pair<QIcon, QIcon::Mode> QPaintedWidgets::components::Icon::get_icon() const
{
    QIcon       icon = _icon;
    QIcon::Mode mode = QIcon::Mode::Normal;

    if(base_t::widget->isEnabled())
    {
        const bool hovered = base_t::hovered_by_cursor();

        if(std::is_base_of<QAbstractButton, QWidget>::value)
        {
            QAbstractButton* btn = static_cast<QAbstractButton*>( base_t::widget );

            if(btn->isDown()) // Pressed
            {
                if(_icon_pressed.isNull())
                    mode = QIcon::Mode::Selected;
                else
                    icon = _icon_pressed;
            }
            else // Not pressed
            {
                if(hovered)
                {
                    if(_icon_hovered.isNull())
                        mode = QIcon::Mode::Active;
                    else
                        icon = _icon_hovered;
                }
            }
        }
        else // Not Button, but may be hovered
        {
            if(hovered)
            {
                if(_icon_hovered.isNull())
                    mode = QIcon::Mode::Active;
                else
                    icon = _icon_hovered;
            }
        }
    }
    else // Disabled
    {
        if(_icon_disabled.isNull())
            mode = QIcon::Mode::Disabled;
        else
            icon = _icon_disabled;
    }

    return {icon, mode};
}

void QPaintedWidgets::components::Icon::draw(QPainter &p, const QRect &rect, const QIcon &icon, const QIcon::Mode mode)
{
    QSize icon_size;
    if(_size.isValid())
    {
        icon_size.rwidth()  = std::min(rect.width(),  _size.width());
        icon_size.rheight() = std::min(rect.height(), _size.height());
    }
    else
    {
        icon_size = rect.size();
    }

    QRect icon_rect;
    if(icon_size == rect.size()) // Dynamic scaling (or icon_size the same as current rect sizer)
    {
        icon_rect = rect;
    }
    else // Some kind of fixed scaling
    {
        icon_rect = QRect(0, 0, icon_size.width(), icon_size.height());
        icon_rect.moveTopLeft( helpers::pos_from_alignment(_alignment, rect, icon_size) );
    }

    icon.paint(&p, icon_rect, _alignment, mode);
}

void QPaintedWidgets::components::Icon::draw(QPainter &p, const QRect &rect)
{
    const auto icon_and_mode = get_icon();
    this->draw(p, rect, icon_and_mode.first, icon_and_mode.second);
}
