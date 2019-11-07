#include "LineHorizontal.hpp"

QSize QPaintedWidgets::components::LineHorizontal::minimumSize() const
{
    return {
        _pen.width() * 2, // min Width
        _pen.width()      // min Height
    };
}

#include <QPainter>

void QPaintedWidgets::components::LineHorizontal::draw(QPainter &p, const QRect &rect)
{
    p.save();
    {
        const qreal y_middle = rect.top() + (rect.height() / 2.0); // same as rect.center().y()

        const qreal x_offset = _pen.widthF() / 2.0;

        const QLineF line(rect.left()  + x_offset, y_middle,
                          rect.right() - x_offset, y_middle);

        p.setPen(_pen);
        p.setBrush(Qt::NoBrush);
        p.drawLine(line);
    }
    p.restore();
}
