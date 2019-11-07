#include "IconWidget.hpp"

#include "QPaintedWidgets/components/Icon.hpp"

struct QPaintedWidgets::IconWidget::Gfx : public components::Icon
{
    using base_t = components::Icon;
    using base_t::base_t;
};

QPaintedWidgets::IconWidget::IconWidget(QWidget *parent)
    : base_t(parent)
{
    _icon = std::unique_ptr<Gfx>( new Gfx(this) ); // same as std::unique_ptr<Gfx>(this)
}

QPaintedWidgets::IconWidget::IconWidget(const QIcon &icon_, QWidget* parent)
    : IconWidget(parent)
{
    _icon->setIcon(icon_);
}

QPaintedWidgets::IconWidget::~IconWidget()
{}

// -----------------------------------------------------------------------------

QSize QPaintedWidgets::IconWidget::minimumSizeHint() const
{
    return _icon->minimumSize();
}

// -----------------------------------------------------------------------------

void QPaintedWidgets::IconWidget::setIcon(const QIcon &icon)
{
    _icon->setIcon(icon);
}

QIcon QPaintedWidgets::IconWidget::getIcon() const
{
    return _icon->getIcon();
}

void QPaintedWidgets::IconWidget::setIconSize(const QSize &size)
{
    _icon->setSize(size);
}

QSize QPaintedWidgets::IconWidget::getIconSize() const
{
    return _icon->getSize();
}

// -----------------------------------------------------------------------------

#include <QPainter>

void QPaintedWidgets::IconWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    _icon->draw(p, this->rect());
}
