#ifndef GUI_HELPERS__POS_FROM_ALIGNMENT_HPP
#define GUI_HELPERS__POS_FROM_ALIGNMENT_HPP

#include <QRect>

namespace QPaintedWidgets {

namespace helpers {

QPointF pos_from_alignment(const Qt::Alignment align, const QRectF &rect, const QSizeF &size);

QPoint  pos_from_alignment(const Qt::Alignment align, const QRect &rect, const QSize &size);

} // namespace helpers

} // namespace QPaintedWidgets

#endif // GUI_HELPERS__POS_FROM_ALIGNMENT_HPP
