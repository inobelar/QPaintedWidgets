#ifndef Q_PAINTED_WIDGETS___COMPONENTS___ABSTRACT_TEXT_HPP
#define Q_PAINTED_WIDGETS___COMPONENTS___ABSTRACT_TEXT_HPP

#include "Component.hpp"

#include <QPen>

namespace QPaintedWidgets {

namespace components {

class AbstractText : public Component
{
protected:
    QPen _pen = QPen{Qt::white};
    QPen _pen_hovered = QPen{Qt::white};
    QPen _pen_pressed = QPen{Qt::white};
    QPen _pen_disabled = QColor(255,255,255, 100);

    QFont _font;

    Qt::Alignment _alignment = Qt::AlignCenter;

    virtual void on_font_change() {}

public:

    using self_t = AbstractText;

    using base_t = Component;

    explicit AbstractText(QWidget* w);

    // -------------------------------------------------------------------------

    virtual self_t& setText(const QString& text) = 0;
    virtual QString getText() const = 0;

    // -------------------------------------------------------------------------

    self_t& setPen(const QPen& pen);
    QPen getPen() const;

    // -------------------------------------------------------------------------

    self_t& setPenHovered(const QPen& pen);
    QPen getPenHovered() const;

    // -------------------------------------------------------------------------

    self_t& setPenPressed(const QPen& pen);
    QPen getPenPressed() const;

    // -------------------------------------------------------------------------

    self_t& setPenDisabled(const QPen& pen);
    QPen getPenDisabled() const;

    // -------------------------------------------------------------------------

    self_t& setFont(const QFont font);
    QFont getFont() const;

    // -------------------------------------------------------------------------

    // Helper
    self_t& setFontPixelSize(int size);
    self_t& setFontBold(bool enable);

    // -------------------------------------------------------------------------

    self_t& setAlignment(const Qt::Alignment alignment);
    Qt::Alignment getAlignment() const;

    // -------------------------------------------------------------------------
    // Similar to Background::get_brush()
    virtual QPen get_displayed_pen();

    virtual void draw(QPainter& p, const QPen& pen, const QRect& rect) = 0;

    virtual void draw(QPainter &p, const QRect &rect) override;

};

} // namespace components

} // namespace QPaintedWidgets

#endif // Q_PAINTED_WIDGETS___COMPONENTS___ABSTRACT_TEXT_HPP
