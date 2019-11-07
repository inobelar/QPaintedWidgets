#include "AbstractLine.hpp"

QPaintedWidgets::components::AbstractLine::self_t& QPaintedWidgets::components::AbstractLine::setPen(const QPen &pen)
{
    if(_pen == pen) return (*this);

    const bool width_changed = (_pen.width() != pen.width());

    _pen = pen;

    if(width_changed)
        base_t::widget->updateGeometry();

    this->update(); // Redraw

    return (*this);
}

QPen QPaintedWidgets::components::AbstractLine::getPen() const
{
    return _pen;
}
