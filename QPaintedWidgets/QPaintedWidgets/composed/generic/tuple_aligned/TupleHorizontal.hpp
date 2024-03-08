#ifndef Q_PAINTED_WIDGETS___COMPOSED___GENERIC___TUPLE_ALIGNED___TUPLE_HORIZONTAL_HPP
#define Q_PAINTED_WIDGETS___COMPOSED___GENERIC___TUPLE_ALIGNED___TUPLE_HORIZONTAL_HPP

#include "Tuple_Aligned.hpp"

#include "QPaintedWidgets/painting/rect_split.hpp"
#include "QPaintedWidgets/meta/std_array_size.hpp"

namespace QPaintedWidgets {

template <typename BaseT>
class TupleHorizontal : public Tuple_Aligned<BaseT>
{
public:
    using base_t = Tuple_Aligned<BaseT>;

    using base_t::base_t;

    using rects_array_t = std::array<QRect, base_t::count()>;

protected:

    // Items calculated rectangles, to get when they needed
    rects_array_t _rects;

public:

    const rects_array_t& get_rects() const { return _rects; }

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

        // Store calculated items rectangles
        static_assert(meta::array_size<decltype(_rects)>::size == meta::array_size<decltype(rects)>::size, "Rects arrays sizes mismatch");
        for(std::size_t i = 0; i < rects.size(); ++i)
        {
            _rects[i] = rects[i].toRect();
        }

        // ---------------------------------------------------------------------

        std::size_t i = 0;
        base_t::for_each([&p, &i, this](components::Component* component)
        {
            component->draw(p, _rects[i]);
            ++i;
        });
    }
};

// Common alias
template <typename ... ComponentsT>
using HBox = TupleHorizontal< ComponentsTuple<ComponentsT...> >;

} // namespace QPaintedWidgets

#endif // Q_PAINTED_WIDGETS___COMPOSED___GENERIC___TUPLE_ALIGNED___TUPLE_HORIZONTAL_HPP
