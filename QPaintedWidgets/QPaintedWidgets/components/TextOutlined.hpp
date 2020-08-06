#ifndef Q_PAINTED_WIDGETS___COMPONENTS___TEXT_OUTLINED_HPP
#define Q_PAINTED_WIDGETS___COMPONENTS___TEXT_OUTLINED_HPP

#include "Text.hpp"

namespace QPaintedWidgets {

namespace components {

class TextOutlined : public Text
{
    int    _outline_distance = 0;
    QColor _outline_color    = Qt::transparent;

    class CacheParams
    {
        int    _outline_distance = -1;
        QColor _outline_color    = Qt::transparent;

        QColor        _text_color;
        Qt::Alignment _text_align;
        QFont         _text_font;
        QString       _text_text;

    public:
        // Returns true, if any field being changed
        bool update(int outline_distance,
                    const QColor& outline_color,
                    const QColor& text_color,
                    const Qt::Alignment text_align,
                    const QFont& text_font,
                    const QString& text_text);
    };

    CacheParams _cache_params;
    QPixmap _cache_pixmap;

public:

    using self_t = TextOutlined;

    using base_t = Text;
    using base_t::base_t;

    // -------------------------------------------------------------------------

    self_t& setOutlineColor(const QColor& color);
    QColor getOutlineColor() const;

    self_t& setOutlineDistance(int distance);
    int getOutlineDistance() const;

    // Convenient helpers
    self_t& setOutline(const QColor& color, int distance);
    self_t& setOutlineDisabled();

    bool isOutlineEnabled() const;

    // -------------------------------------------------------------------------

    virtual void draw(QPainter& p, const QPen& pen, const QRect& rect) override;
};

} // namespace components

} // namespace QPaintedWidgets

#endif // Q_PAINTED_WIDGETS___COMPONENTS___TEXT_OUTLINED_HPP
