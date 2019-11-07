#ifndef Q_PAINTED_WIDGETS___COMPOSED___GENERIC___TUPLE_ALIGNED___CENTERED___VERTICALLY_CENTERED_HPP
#define Q_PAINTED_WIDGETS___COMPOSED___GENERIC___TUPLE_ALIGNED___CENTERED___VERTICALLY_CENTERED_HPP

#include "QPaintedWidgets/composed/generic/tuple_aligned/TupleVertical.hpp"

namespace QPaintedWidgets {

template <typename BaseT>
struct VerticallyCentered : public TupleVertical<BaseT>
{
    static_assert (BaseT::count() == 3,
                   "Components count must be exactly 3 (top, middle, bottom)");

    // -------------------------------------------------------------------------

    using base_t = TupleVertical<BaseT>;

    using base_t::base_t;

    // -------------------------------------------------------------------------

    using top_t    = typename base_t::template nth_item_t<0>;
    using middle_t = typename base_t::template nth_item_t<1>;
    using bottom_t = typename base_t::template nth_item_t<2>;

    // -------------------------------------------------------------------------
    // Convenient aliases

    top_t    top()    { return base_t::template get<0>(); }
    middle_t middle() { return base_t::template get<1>(); }
    bottom_t bottom() { return base_t::template get<2>(); }

    const top_t    top()    const { return base_t::template get<0>(); }
    const middle_t middle() const { return base_t::template get<1>(); }
    const bottom_t bottom() const { return base_t::template get<2>(); }

    // -------------------------------------------------------------------------

    virtual void draw(QPainter& p, const QRect& rect) override
    {
        auto* component_top    = top();
        auto* component_middle = middle();
        auto* component_bottom = bottom();


        const QSize middle_size = component_middle->minimumSize();
        const int mid_half_height = (middle_size.height() / 2);

        const int center_y = rect.center().y();
        const int top_y = center_y - mid_half_height;
        const int bot_y = center_y + mid_half_height;


        // Calculate bounding rectangles for each component
        QRect rect_top = rect;
        rect_top.setBottom(top_y - (base_t::__spacing()) );

        QRect rect_bottom = rect;
        rect_bottom.setTop(bot_y + (base_t::__spacing()) );

        QRect rect_middle = rect;
        rect_middle.setTop   (top_y);
        rect_middle.setBottom(bot_y);


        // Draw components in related rectangles
        component_top   ->draw(p, rect_top   );
        component_middle->draw(p, rect_middle);
        component_bottom->draw(p, rect_bottom);
    }
};

} // namespace QPaintedWidgets

#endif // Q_PAINTED_WIDGETS___COMPOSED___GENERIC___TUPLE_ALIGNED___CENTERED___VERTICALLY_CENTERED_HPP
