#include "TextOutlined.hpp"

// =============================================================================

template <typename T>
static bool field_changed(T& curr_value, const T& new_value) {
    const bool changed = (curr_value != new_value);
    curr_value = new_value;
    return changed;
}

bool QPaintedWidgets::components::TextOutlined::CacheParams::update(
        int outline_distance,
        const QColor &outline_color,
        const QColor &text_color,
        const Qt::Alignment text_align,
        const QFont &text_font,
        const QString &text_text)
{
    // Update previous state & return result is something changed
    const bool f1 = field_changed(_outline_distance, outline_distance);
    const bool f2 = field_changed(_outline_color, outline_color);
    const bool f3 = field_changed(_text_color, text_color);
    const bool f4 = field_changed(_text_align, text_align);
    const bool f5 = field_changed(_text_font, text_font);
    const bool f6 = field_changed(_text_text, text_text);

    return (f1 || f2 || f3 || f4 || f5 || f6);
}

// =============================================================================

QPaintedWidgets::components::TextOutlined::self_t &QPaintedWidgets::components::TextOutlined::setOutlineColor(const QColor &color)
{
    if(_outline_color == color) return (*this);

    _outline_color = color;

    this->update();

    return (*this);
}

QColor QPaintedWidgets::components::TextOutlined::getOutlineColor() const
{
    return _outline_color;
}

// -----------------------------------------------------------------------------

QPaintedWidgets::components::TextOutlined::self_t &QPaintedWidgets::components::TextOutlined::setOutlineDistance(int distance)
{
    if(_outline_distance == distance) return (*this);

    _outline_distance = distance;

    this->update();

    return (*this);
}

int QPaintedWidgets::components::TextOutlined::getOutlineDistance() const
{
    return _outline_distance;
}

// -----------------------------------------------------------------------------

QPaintedWidgets::components::TextOutlined::self_t &QPaintedWidgets::components::TextOutlined::setOutline(const QColor &color, int distance)
{
    setOutlineColor(color);
    setOutlineDistance(distance);

    return (*this);
}

QPaintedWidgets::components::TextOutlined::self_t &QPaintedWidgets::components::TextOutlined::setOutlineDisabled()
{
    return setOutline(Qt::transparent, 0);
}

// -----------------------------------------------------------------------------

bool QPaintedWidgets::components::TextOutlined::isOutlineEnabled() const
{
    return (_outline_color    != Qt::transparent) &&
           (_outline_distance > 0);
}

// -----------------------------------------------------------------------------

#include <QPainter>
#include "QPaintedWidgets/painting/pos_from_alignment.hpp"

#include <QFontMetrics>

#include "QPaintedWidgets/painting/signed_distance_field.hpp"

QImage make_sdf_outline(int distance, const QColor& outline_color,
                        const QSize& img_size,
                        Qt::Alignment text_align, const QFont& text_font, const QColor& text_color, const QString& text)
{
    /*
        IMPORTANT NOTE: Instead of simple QImage format `RGBA8888` used
        `RGBA8888_Premultiplied` for corrent pictures displaying. On some
        platforms/Qt-versions text over outline displayed good without it.
        BUT on Qt5.3 it is required to use such format, since otherwise
        text looks "dirty".
     */


    // Create transparent image for drawing text upon it
    QImage img_text(img_size, QImage::Format_RGBA8888_Premultiplied);
    img_text.fill(Qt::transparent);

    // Draw text
    {
        QPainter painter(&img_text);

        // Disable text (subpixel) antialiasing, since its produces 'dirty' pixels :)
        painter.setRenderHint(QPainter::RenderHint::Antialiasing,     false);
        painter.setRenderHint(QPainter::RenderHint::TextAntialiasing, false);


        painter.setFont(text_font);

        painter.setPen(text_color);
        painter.setBrush(Qt::NoBrush);

        painter.drawText(0, 0, img_text.width(), img_text.height(), text_align, text);
    }

    // -------------------------------------------------------------------------

    QImage img_field(img_size, QImage::Format_RGBA8888_Premultiplied);
    img_field.fill(Qt::transparent);

    const auto pixel_search_func = [&img_text](int x, int y) -> bool
    {
        // Since text displayed semi-transperent, we calculate distance only for
        // the only for most opaque pixels
        const QRgb pixel = img_text.pixel(x, y);
        return qAlpha(pixel) > 128;
    };

    const auto field = QPaintedWidgets::sdf::make_field(distance, img_size.width(), img_size.height(), pixel_search_func);

    for(int x = 0; x < img_size.width(); ++x)
    {
        for(int y = 0; y < img_size.height(); ++y)
        {
            const int idx = (x + (y * img_size.width()));
            const float& distance = field[idx];

            // // ----------------------------------------
            // // Debug grayscale drawing:
            // const int gray = (distance * 255);
            // const QRgb col = qRgb(gray, gray, gray);
            // img_field.setPixel(x, y, col);
            // // ----------------------------------------

            if( distance < 1.0 )
            {
                // TODO: future: currently here is only 'linear beavior' - alpha
                // the same as distance. BUT it may be flexible! For example by
                // using solid/cosine/trapesoid functions, which give alpha by
                // normalized distance. This may be cool feature, for tweakable
                // outlining or even multiple!
                const int alpha = (distance * 255);

                const QRgb outline = qRgba(outline_color.red(), outline_color.green(), outline_color.blue(), alpha);
                const QRgb outline_premultiplied = qPremultiply(outline); // Needed to utilize color glitches. Used since QImage format is RGBA >PREMULTIPLIED<
                img_field.setPixel(x, y, outline_premultiplied);
            }
        }
    }

    // -------------------------------------------------------------------------

    // Draw image-with-text over image-with-outline
    {
        QPainter painter(&img_field);

        painter.drawImage(img_field.rect(), img_text);
    }

    return img_field;
}

/*
// STUPID NAIVE DIRTY SINGLE-PIXEL GARBAGE CODE, STORED HERE FOR HISTORICAL REASON.
// instead it used Signed-Distance-Field with additiona caching

const QColor color_text    = _pen.color();
const QColor color_outline = _outline_color;
const QColor color_back    = Qt::transparent;

QImage img(rect.size(), QImage::Format_RGBA8888);
img.fill(color_back);
{

    QPainter img_painter(&img);
    img_painter.setRenderHint(QPainter::RenderHint::Antialiasing,     false);
    img_painter.setRenderHint(QPainter::RenderHint::TextAntialiasing, false);

    img_painter.setFont(base_t::_font);

    // Draw text
    img_painter.setPen(color_text);
    img_painter.setBrush(Qt::NoBrush);
    img_painter.drawText(0, 0, img.width(), img.height(), _alignment, getText());

    // Do single-pixel outlining.
    // This is really crappy algo, written in few minutes.
    {
        static const std::array<QPoint, 8> offsets = {
            QPoint(-1, -1), QPoint(0, -1), QPoint(+1, -1), // all: negative y
            QPoint(-1,  0),                QPoint(+1,  0), // all: zero y
            QPoint(-1, +1), QPoint(0, +1), QPoint(+1, +1)  // all: positive y
        };

        // Traverse the whole image ...
        for(int y = 0; y < img.height(); ++y)
        {
            for(int x = 0; x < img.width(); ++x)
            {
                const QColor curr_pix_color = QColor::fromRgb( img.pixel(x, y) );

                // And only for pixels with color of (rendered) text
                if(curr_pix_color == color_text)
                {
                    // Check nearby pixels
                    for(const QPoint& nearby : offsets)
                    {
                        const QPoint near_pos = QPoint(x, y) + nearby;

                        // >>> It is safe, out-of-bounds not blow-up everything <<<
                        const QColor near_color = QColor::fromRgb(img.pixel(near_pos.x(), near_pos.y()));

                        // And each pixel, which NEAR text color, BUT not that color - mark as 'outline'
                        if(near_color != color_text)
                        {
                            img.setPixel(near_pos, color_outline.rgb());
                        }

                    }
                }

            }
        }
    }
}
*/

void QPaintedWidgets::components::TextOutlined::draw(QPainter &p, const QPen &pen, const QRect &rect)
{
    if( !isOutlineEnabled() )
    {
        base_t::draw(p, pen, rect);
    }
    else // Outline enabled
    {
        p.save();
        {
            const QSize rect_size = rect.size();

            const QColor        text_color = getPen().color();
            const Qt::Alignment text_align = getAlignment();
            const QFont         text_font  = getFont();
            const QString       text_text  = getText();

            const bool cache_need_to_update = _cache_params.update(
                        _outline_distance,
                        _outline_color,
                        text_color,
                        text_align,
                        text_font,
                        text_text);

            // Update cached pixmap on resize or parameters change.
            // It is really important to re-use pre-rendered pixmap, instead of
            // extremely slow SDF-re-calculation on each QWidget::paintEvent()
            if( (rect_size != _cache_pixmap.size()) || cache_need_to_update)
            {
                _cache_pixmap = QPixmap::fromImage(
                            make_sdf_outline(_outline_distance, _outline_color,
                                             rect_size,
                                             text_align, text_font, text_color, text_text)
                );
            }


            // Draw resulting image
            p.drawPixmap(rect, _cache_pixmap);

        }
        p.restore();
    }
}
