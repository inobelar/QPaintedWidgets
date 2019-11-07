#ifndef Q_PAINTED_WIDGETS___COMPONENTS___ICON_HPP
#define Q_PAINTED_WIDGETS___COMPONENTS___ICON_HPP

#include "Component.hpp"

#include <QIcon>

namespace QPaintedWidgets {

namespace components {

class Icon : public Component
{
    QIcon _icon;
    QIcon _icon_hovered;
    QIcon _icon_pressed;
    QIcon _icon_disabled;

    // TODO: cached (once-rendered) icons
//    QPixmap _pix_icon;
//    QPixmap _pix_icon_hovered;
//    QPixmap _pix_icon_pressed;
//    QPixmap _pix_icon_disabled;

    QSize _size = {24, 24};

    Qt::Alignment _alignment = Qt::AlignCenter;

public:

    using self_t = Icon;

    using base_t = Component;

    using base_t::base_t;

    // -------------------------------------------------------------------------

    self_t& setIcon(const QIcon& icon);
    QIcon getIcon() const;

    self_t& setIconHovered(const QIcon& icon);
    QIcon getIconHovered() const;

    self_t& setIconPressed(const QIcon& icon);
    QIcon getIconPressed() const;

    self_t& setIconDisabled(const QIcon& icon);
    QIcon getIconDisabled() const;

    // -------------------------------------------------------------------------

    self_t& setSize(const QSize& size);
    QSize getSize() const;

    // -------------------------------------------------------------------------

    self_t& setAlignment(const Qt::Alignment alignment);
    Qt::Alignment getAlignment() const;

    // -------------------------------------------------------------------------

    virtual QSize minimumSize() const override;

    // Similar to Background::get_background_brush()
    virtual std::pair<QIcon, QIcon::Mode> get_icon() const;

    virtual void draw(QPainter& p, const QRect& rect, const QIcon& icon, const QIcon::Mode mode);

    virtual void draw(QPainter &p, const QRect &rect) override;
};

} // namespace components

} // namespace QPaintedWidgets

#endif // Q_PAINTED_WIDGETS___COMPONENTS___ICON_HPP
