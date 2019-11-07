#ifndef Q_PAINTED_WIDGETS___COMPOSED___GENERIC___TUPLE_ALIGNED___CENTERED___HORIZONTALLY_CENTERED_HPP
#define Q_PAINTED_WIDGETS___COMPOSED___GENERIC___TUPLE_ALIGNED___CENTERED___HORIZONTALLY_CENTERED_HPP

#include "QPaintedWidgets/composed/generic/tuple_aligned/TupleHorizontal.hpp"

namespace QPaintedWidgets {

template <typename BaseT>
struct HorizontallyCentered : public TupleHorizontal<BaseT>
{
    static_assert (BaseT::count() == 3,
                   "Components count must be exactly 3 (left, middle, right)");

    // -------------------------------------------------------------------------

    using base_t = TupleHorizontal<BaseT>;

    using base_t::base_t;

    // -------------------------------------------------------------------------

    using left_t   = typename base_t::template nth_item_t<0>;
    using middle_t = typename base_t::template nth_item_t<1>;
    using right_t  = typename base_t::template nth_item_t<2>;

    // -------------------------------------------------------------------------
    // Convenient aliases

    left_t   left()   { return base_t::template get<0>(); }
    middle_t middle() { return base_t::template get<1>(); }
    right_t  right()  { return base_t::template get<2>(); }

    const left_t   left()   const { return base_t::template get<0>(); }
    const middle_t middle() const { return base_t::template get<1>(); }
    const right_t  right()  const { return base_t::template get<2>(); }

    // -------------------------------------------------------------------------

    virtual void draw(QPainter& p, const QRect& rect) override
    {
        auto* component_left   = left();
        auto* component_middle = middle();
        auto* component_right  = right();


        const QSize middle_size = component_middle->minimumSize();
        const int mid_half_width = (middle_size.width() / 2);

        const int center_x = rect.center().x();
        const int left_x  = center_x - mid_half_width;
        const int right_x = center_x + mid_half_width;


        // Calculate bounding rectangles for each component
        QRect rect_left = rect;
        rect_left.setRight(left_x  - (base_t::__spacing()) );

        QRect rect_right = rect;
        rect_right.setLeft(right_x + (base_t::__spacing()) );

        QRect rect_middle = rect;
        rect_middle.setLeft (left_x );
        rect_middle.setRight(right_x);


        // Draw components in related rectangles
        component_left  ->draw(p, rect_left  );
        component_middle->draw(p, rect_middle);
        component_right ->draw(p, rect_right );
    }
};

} // namespace QPaintedWidgets

#endif // Q_PAINTED_WIDGETS___COMPOSED___GENERIC___TUPLE_ALIGNED___CENTERED___HORIZONTALLY_CENTERED_HPP
