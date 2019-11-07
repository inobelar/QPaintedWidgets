#ifndef Q_PAINTED_WIDGETS___COMPONENTS___TEXT_HPP
#define Q_PAINTED_WIDGETS___COMPONENTS___TEXT_HPP

#include "AbstractText.hpp"

namespace QPaintedWidgets {

namespace components {

class Text : public AbstractText
{
    QString _text;

public:

    using self_t = Text;

    using base_t = AbstractText;
    using base_t::base_t;

    // -------------------------------------------------------------------------

    self_t& setText(const QString& text) override;
    QString getText() const override;

    // -------------------------------------------------------------------------

    QSizeF getSize() const;

    virtual QSize minimumSize() const override;

    virtual void draw(QPainter& p, const QPen& pen, const QRect& rect) override;

    virtual void draw(QPainter &p, const QRect &rect) override;
};

} // namespace components

} // namespace QPaintedWidgets

#endif // Q_PAINTED_WIDGETS___COMPONENTS___TEXT_HPP
