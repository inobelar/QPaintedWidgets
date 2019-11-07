#ifndef Q_PAINTED_WIDGETS___COMPOSED___GENERIC___TUPLE_ALIGNED___TUPLE_HORIZONTAL_HPP
#define Q_PAINTED_WIDGETS___COMPOSED___GENERIC___TUPLE_ALIGNED___TUPLE_HORIZONTAL_HPP

#include "Tuple_Aligned.hpp"

#include "QPaintedWidgets/painting/rect_split.hpp"

namespace QPaintedWidgets {

template <typename BaseT>
struct TupleHorizontal : public Tuple_Aligned<BaseT>
{
    using base_t = Tuple_Aligned<BaseT>;

    using base_t::base_t;

    virtual QSize minimumSize() const override
    {
        int total_width = 0;
        int max_height  = 0;
        base_t::for_each([&total_width, &max_height](const components::Component* component)
        {
            const auto min_size = component->minimumSize();
            total_width += min_size.width();
            max_height   = std::max(max_height, min_size.height());
        });

        return { total_width + base_t::__total_spacing() , max_height };
    }

    std::array<qreal, base_t::count()> calc_components_widths() const
    {
        std::array<qreal, base_t::count()> widths = {0.0};

        std::size_t i = 0;
        base_t::for_each([&i, &widths](const components::Component* component)
        {
            widths[i] = component->minimumSize().width();
            ++i;
        });

        return widths;
    }

    virtual void draw(QPainter& p, const QRect& rect) override
    {
        constexpr std::size_t COUNT = base_t::count();

        const std::array<qreal, COUNT> widths = calc_components_widths();

        // ---------------------------------------------------------------------

        const auto rects = make_rects_horizontal<COUNT>(rect, widths, base_t::__spacing());

        std::size_t i = 0;
        base_t::for_each([&p, &i, rects](components::Component* component)
        {
            component->draw(p, rects[i].toRect());
            ++i;
        });
    }
};

// Common alias
template <typename ... ComponentsT>
using HBox = TupleHorizontal< ComponentsTuple<ComponentsT...> >;

} // namespace QPaintedWidgets

#endif // Q_PAINTED_WIDGETS___COMPOSED___GENERIC___TUPLE_ALIGNED___TUPLE_HORIZONTAL_HPP
