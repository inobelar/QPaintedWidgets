#include "HLineWidget.hpp"

#include "QPaintedWidgets/components/LineHorizontal.hpp"

struct QPaintedWidgets::HLineWidget::Gfx : public components::LineHorizontal
{
    using base_t = components::LineHorizontal;
    using base_t::base_t;
};

QPaintedWidgets::HLineWidget::HLineWidget(QWidget *parent)
    : base_t(parent)
{
    _line = std::unique_ptr<Gfx>( new Gfx(this) ); // same as std::make_unique<Gfx>(this)
}

QPaintedWidgets::HLineWidget::HLineWidget(const QPen &pen, QWidget *parent)
    : HLineWidget(parent)
{
    this->setPen(pen);
}

QPaintedWidgets::HLineWidget::~HLineWidget()
{}

// -----------------------------------------------------------------------------

QSize QPaintedWidgets::HLineWidget::minimumSizeHint() const
{
    return _line->minimumSize();
}

// -----------------------------------------------------------------------------

void QPaintedWidgets::HLineWidget::setPen(const QPen &pen)
{
    _line->setPen(pen);
}

QPen QPaintedWidgets::HLineWidget::getPen() const
{
    return _line->getPen();
}

// -----------------------------------------------------------------------------

#include <QPainter>

void QPaintedWidgets::HLineWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    _line->draw(p, this->rect());
}
