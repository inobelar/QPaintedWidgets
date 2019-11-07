#include "Text.hpp"

QPaintedWidgets::components::Text::self_t& QPaintedWidgets::components::Text::setText(const QString &text)
{
    if(_text == text) return (*this);

    _text = text;

    // Update minimum size
    base_t::widget->updateGeometry();

    this->update();

    return (*this);
}

QString QPaintedWidgets::components::Text::getText() const
{
    return _text;
}

// -----------------------------------------------------------------------------

#include <limits>

QSizeF QPaintedWidgets::components::Text::getSize() const
{
    // NOTE: this line not work well with multi-line text (new line characters ignored)
    // NOTE: have no idea why, it's return not-the-same size as QStaticText::size()
    //     return QFontMetricsF(base_t::_font).boundingRect(_text).size();

    // Size of bounding box, with support of multi-line text
    // References:
    // - https://doc.qt.io/archives/qt-4.8/qfontmetrics.html#boundingRect-5
    // - https://stackoverflow.com/a/37674690
    {
        constexpr int int_max = std::numeric_limits<int>::max();

        return QFontMetrics(base_t::_font).boundingRect(0, 0, int_max, int_max, _alignment /*no extra flags*/, _text).size();
    }
}

QSize QPaintedWidgets::components::Text::minimumSize() const
{
    return getSize().toSize();
}

// -----------------------------------------------------------------------------

#include <QPainter>

void QPaintedWidgets::components::Text::draw(QPainter &p, const QPen &pen, const QRect &rect)
{
    p.save();
    {
        p.setFont(base_t::_font);

        p.setPen(pen);
        p.setBrush(Qt::NoBrush);
        p.drawText(rect, _alignment, _text);
    }
    p.restore();
}

void QPaintedWidgets::components::Text::draw(QPainter &p, const QRect &rect)
{
    this->draw(p, get_displayed_pen(), rect);
}
