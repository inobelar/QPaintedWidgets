#ifndef Q_PAINTED_WIDGETS___COMPOSED___GENERIC___TUPLE_ALIGNED___TUPLE_VERTICAL_HPP
#define Q_PAINTED_WIDGETS___COMPOSED___GENERIC___TUPLE_ALIGNED___TUPLE_VERTICAL_HPP

#include "Tuple_Aligned.hpp"

#include "QPaintedWidgets/painting/rect_split.hpp"
#include "QPaintedWidgets/meta/std_array_size.hpp"

namespace QPaintedWidgets {

template <typename BaseT>
class TupleVertical : public Tuple_Aligned<BaseT>
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
        int max_width    = 0;
        int total_height = 0;
        base_t::for_each([&max_width, &total_height](const components::Component* component)
        {
            const auto min_size = component->minimumSize();
            max_width     = std::max(max_width, min_size.width());
            total_height += min_size.height();
        });

        return { max_width, total_height + base_t::__total_spacing() };
    }

    std::array<qreal, base_t::count()> calc_components_heights() const
    {
        std::array<qreal, base_t::count()> heights = {0.0};

        std::size_t i = 0;
        base_t::for_each([&i, &heights](const components::Component* component)
        {
            heights[i] = component->minimumSize().height();
            ++i;
        });

        return heights;
    }

    virtual void draw(QPainter& p, const QRect& rect) override
    {
        constexpr std::size_t COUNT = base_t::count();

        const std::array<qreal, COUNT> heights = calc_components_heights();

        // ---------------------------------------------------------------------

        const auto rects = make_rects_vertical<COUNT>(rect, heights, base_t::__total_spacing());

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
using VBox = TupleVertical< ComponentsTuple<ComponentsT...> >;

} // namespace QPaintedWidgets

#endif // Q_PAINTED_WIDGETS___COMPOSED___GENERIC___TUPLE_ALIGNED___TUPLE_VERTICAL_HPP
