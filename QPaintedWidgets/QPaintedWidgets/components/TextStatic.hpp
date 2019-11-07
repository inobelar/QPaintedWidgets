#ifndef Q_PAINTED_WIDGETS___COMPONENTS___TEXT_STATIC_HPP
#define Q_PAINTED_WIDGETS___COMPONENTS___TEXT_STATIC_HPP

#include "AbstractText.hpp"

#include <QStaticText>

namespace QPaintedWidgets {

namespace components {

/*
    Note:
        - multiline text support achieved by using QChar(QChar::LineSeparator)
          instead of '\n'
 */

class TextStatic: public AbstractText
{
    QStaticText _text;

    void on_font_change() override {
        _text.prepare(QTransform(), base_t::_font);
    }

public:

    using self_t = TextStatic;

    using base_t = AbstractText;

    using base_t::base_t;

    // -------------------------------------------------------------------------

    self_t& setText(const QString& text) override;
    QString getText() const override;

    // -------------------------------------------------------------------------

    self_t& setTextFormat(Qt::TextFormat textFormat);
    Qt::TextFormat getTextFormat() const;

    // -------------------------------------------------------------------------

    self_t& setTextOption(const QTextOption& textOption);
    QTextOption getTextOption() const;

    // -------------------------------------------------------------------------

    QSizeF getSize() const;

    // -------------------------------------------------------------------------

    virtual QSize minimumSize() const override;

    virtual void draw(QPainter& p, const QPen& pen, const QRect& rect) override;

    virtual void draw(QPainter &p, const QRect &rect) override;
};

} // namespace components

} // namespace QPaintedWidgets

#endif // Q_PAINTED_WIDGETS___COMPONENTS___TEXT_STATIC_HPP
