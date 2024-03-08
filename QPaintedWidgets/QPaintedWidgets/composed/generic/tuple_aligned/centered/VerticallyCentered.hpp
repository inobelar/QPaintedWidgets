#ifndef Q_PAINTED_WIDGETS___COMPOSED___GENERIC___TUPLE_ALIGNED___CENTERED___VERTICALLY_CENTERED_HPP
#define Q_PAINTED_WIDGETS___COMPOSED___GENERIC___TUPLE_ALIGNED___CENTERED___VERTICALLY_CENTERED_HPP

#include "QPaintedWidgets/composed/generic/tuple_aligned/TupleVertical.hpp"

namespace QPaintedWidgets {

template <typename BaseT>
class VerticallyCentered : public TupleVertical<BaseT>
{
    // Items calculated rectangles, to get when they needed
    QRect _rect_top;
    QRect _rect_middle;
    QRect _rect_bottom;

    static_assert (BaseT::count() == 3,
                   "Components count must be exactly 3 (top, middle, bottom)");

public:

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

    const QRect& rect_top()    const { return _rect_top;    }
    const QRect& rect_middle() const { return _rect_middle; }
    const QRect& rect_bottom() const { return _rect_bottom; }

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
        _rect_top = rect;
        _rect_top.setBottom(top_y - (base_t::__spacing()) );

        _rect_bottom = rect;
        _rect_bottom.setTop(bot_y + (base_t::__spacing()) );

        _rect_middle = rect;
        _rect_middle.setTop   (top_y);
        _rect_middle.setBottom(bot_y);


        // Draw components in related rectangles
        component_top   ->draw(p, _rect_top   );
        component_middle->draw(p, _rect_middle);
        component_bottom->draw(p, _rect_bottom);
    }
};

} // namespace QPaintedWidgets

#endif // Q_PAINTED_WIDGETS___COMPOSED___GENERIC___TUPLE_ALIGNED___CENTERED___VERTICALLY_CENTERED_HPP
