#ifndef Q_PAINTED_WIDGETS___COMPOSED___GENERIC___WITH_MARGIN_HPP
#define Q_PAINTED_WIDGETS___COMPOSED___GENERIC___WITH_MARGIN_HPP

#include "WithMarginT.hpp"

#include "QPaintedWidgets/components/Component.hpp"

namespace QPaintedWidgets {

template <typename BaseT>
class WithMargin : public WithMarginT<BaseT>
{
    static_assert (std::is_base_of<components::Component, BaseT>::value == true,
                   "BaseT must be derived from Component");

    void on_margin_changed() override
    {
        base_t::widget->updateGeometry(); // Cause calling this->sizeHint()
        base_t::widget->update(); // Redraw
    }

public:

    using self_t = WithMargin<BaseT>;

    using base_t = WithMarginT<BaseT>;

    using base_t::base_t;

    // -------------------------------------------------------------------------

    virtual QSize minimumSize() const override
    {
        return base_t::minimumSize() + base_t::get_margin_size();
    }

    virtual void draw(QPainter& p, const QRect& rect) override
    {
        base_t::draw(p, base_t::get_margin_rect(rect) );
    }

};

} // namespace QPaintedWidgets

#endif // Q_PAINTED_WIDGETS___COMPOSED___GENERIC___WITH_MARGIN_HPP
