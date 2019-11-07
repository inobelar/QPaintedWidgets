#include "pos_from_alignment.hpp"

template <typename PointT, typename RectT, typename SizeT>
PointT post_from_alignment_t(const Qt::Alignment align, const RectT& rect, const SizeT& size)
{
    PointT pos = rect.topLeft(); // Qt::AlignLeft | Qt::AlignTop

    if     (align & Qt::AlignHCenter) { pos.rx() = rect.center().x() - (size.width()/2); }
    else if(align & Qt::AlignRight)   { pos.rx() = rect.right()      - (size.width()  ); }

    if     (align & Qt::AlignVCenter) { pos.ry() = rect.center().y() - (size.height()/2); }
    else if(align & Qt::AlignBottom)  { pos.ry() = rect.bottom()     - (size.height()  ); }

    return pos;
}


QPointF QPaintedWidgets::helpers::pos_from_alignment(const Qt::Alignment align, const QRectF& rect, const QSizeF& size)
{
    return post_from_alignment_t<QPointF, QRectF, QSizeF>(align, rect, size);
}

QPoint QPaintedWidgets::helpers::pos_from_alignment(const Qt::Alignment align, const QRect& rect, const QSize& size)
{
    return post_from_alignment_t<QPoint, QRect, QSize>(align, rect, size);
}
