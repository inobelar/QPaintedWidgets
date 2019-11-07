#ifndef Q_PAINTED_WIDGETS___COMPONENTS___PIXMAP_HPP
#define Q_PAINTED_WIDGETS___COMPONENTS___PIXMAP_HPP

#include "Component.hpp"

// TODO: unfinished

namespace QPaintedWidgets {

namespace components {

class Pixmap : public Component
{
    QPixmap _pixmap;

    bool _aspect = false;

public:

    using self_t = Pixmap;

    using base_t = Component;

    using base_t::base_t;

    // -------------------------------------------------------------------------

    self_t& setPixmap(const QPixmap& pixmap);
    QPixmap getPixmap() const;

    // -------------------------------------------------------------------------

    virtual void draw(QPainter &p, const QRect &rect) override;
};

} // namespace components

} // namespace QPaintedWidgets


#endif // Q_PAINTED_WIDGETS___COMPONENTS___PIXMAP_HPP
