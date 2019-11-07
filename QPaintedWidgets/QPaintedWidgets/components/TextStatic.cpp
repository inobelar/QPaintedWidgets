#include "TextStatic.hpp"

QPaintedWidgets::components::TextStatic::self_t& QPaintedWidgets::components::TextStatic::setText(const QString &text)
{
    if(_text.text() == text) return (*this);

    _text.setText(text);

    // Update minimum size
    _text.prepare(QTransform(), base_t::_font);
    base_t::widget->updateGeometry();

    this->update(); // Redraw

    return (*this);
}

QString QPaintedWidgets::components::TextStatic::getText() const
{
    return _text.text();
}

// -----------------------------------------------------------------------------

QPaintedWidgets::components::TextStatic::self_t& QPaintedWidgets::components::TextStatic::setTextFormat(Qt::TextFormat textFormat)
{
    if(_text.textFormat() == textFormat) return (*this);

    _text.setTextFormat(textFormat);

    // Update minimum size
    _text.prepare(QTransform(), base_t::_font);
    base_t::widget->updateGeometry();

    this->update(); // Redraw

    return (*this);
}

Qt::TextFormat QPaintedWidgets::components::TextStatic::getTextFormat() const
{
    return _text.textFormat();
}

// -----------------------------------------------------------------------------

QPaintedWidgets::components::TextStatic::self_t& QPaintedWidgets::components::TextStatic::setTextOption(const QTextOption &textOption)
{
    _text.setTextOption(textOption);
    base_t::widget->updateGeometry();

    this->update();

    return (*this);
}

QTextOption QPaintedWidgets::components::TextStatic::getTextOption() const
{
    return _text.textOption();
}

// -----------------------------------------------------------------------------

QSizeF QPaintedWidgets::components::TextStatic::getSize() const
{
    return _text.size();
}

QSize QPaintedWidgets::components::TextStatic::minimumSize() const
{
    return this->getSize().toSize();
}

// -----------------------------------------------------------------------------

#include <QPainter>
#include "QPaintedWidgets/painting/pos_from_alignment.hpp"

void QPaintedWidgets::components::TextStatic::draw(QPainter &p, const QPen &pen, const QRect &rect)
{
    p.save();
    {
        p.setFont(base_t::_font);

        p.setPen(pen);
        p.setBrush(Qt::NoBrush);
        p.drawStaticText( helpers::pos_from_alignment(base_t::_alignment, rect, _text.size()), _text);
    }
    p.restore();
}

void QPaintedWidgets::components::TextStatic::draw(QPainter &p, const QRect &rect)
{
    this->draw(p, get_displayed_pen(), rect);
}
