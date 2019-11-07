#include "Pixmap.hpp"


QPaintedWidgets::components::Pixmap::self_t &QPaintedWidgets::components::Pixmap::setPixmap(const QPixmap &pixmap)
{
    // if(_pixmap == pixmap) return (*this);

    _pixmap = pixmap;

    this->update(); // Redraw

    return (*this);
}

QPixmap QPaintedWidgets::components::Pixmap::getPixmap() const
{
    return _pixmap;
}

// -----------------------------------------------------------------------------

#include <QPainter>

void QPaintedWidgets::components::Pixmap::draw(QPainter &p, const QRect &rect)
{
    p.drawPixmap(rect, _pixmap);
}
