#include "Empty.hpp"

QPaintedWidgets::components::Empty::self_t& QPaintedWidgets::components::Empty::setMinimumSize(const QSize &size)
{
    if(_minSize == size) return (*this);

    _minSize = size;

    auto* widget = base_t::widget;
    widget->updateGeometry();
    widget->update();

    return (*this);
}

QSize QPaintedWidgets::components::Empty::getMinimumSize() const
{
    return _minSize;
}

// -----------------------------------------------------------------------------

QSize QPaintedWidgets::components::Empty::minimumSize() const
{
    return getMinimumSize();
}

void QPaintedWidgets::components::Empty::draw(QPainter &p, const QRect &rect)
{
    Q_UNUSED(p)
    Q_UNUSED(rect)
}
