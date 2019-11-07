#include "VLineWidget.hpp"

#include "QPaintedWidgets/components/LineVertical.hpp"

struct QPaintedWidgets::VLineWidget::Gfx : public components::LineVertical
{
    using base_t = components::LineVertical;
    using base_t::base_t;
};

QPaintedWidgets::VLineWidget::VLineWidget(QWidget *parent)
    : base_t(parent)
{
    _line = std::unique_ptr<Gfx>( new Gfx(this) ); // same as std::make_unique<Gfx>(this)
}

QPaintedWidgets::VLineWidget::VLineWidget(const QPen &pen, QWidget *parent)
    : VLineWidget(parent)
{
    this->setPen(pen);
}

QPaintedWidgets::VLineWidget::~VLineWidget()
{}

// -----------------------------------------------------------------------------

QSize QPaintedWidgets::VLineWidget::minimumSizeHint() const
{
    return _line->minimumSize();
}

// -----------------------------------------------------------------------------

void QPaintedWidgets::VLineWidget::setPen(const QPen &pen)
{
    _line->setPen(pen);
}

QPen QPaintedWidgets::VLineWidget::getPen() const
{
    return _line->getPen();
}

// -----------------------------------------------------------------------------

#include <QPainter>

void QPaintedWidgets::VLineWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    _line->draw(p, this->rect());
}
