#include "LineVertical.hpp"

QSize QPaintedWidgets::components::LineVertical::minimumSize() const
{
    return {
        _pen.width(),    // min Width
        _pen.width() * 2 // min Height
    };
}

#include <QPainter>

void QPaintedWidgets::components::LineVertical::draw(QPainter &p, const QRect &rect)
{
    p.save();
    {
        const qreal x_middle = rect.left() + (rect.width() / 2.0); // same as rect.center().x()

        const qreal y_offset = _pen.widthF() / 2.0;

        const QLineF line(x_middle, rect.top()    + y_offset,
                          x_middle, rect.bottom() - y_offset);

        p.setPen(_pen);
        p.setBrush(Qt::NoBrush);
        p.drawLine(line);
    }
    p.restore();
}
