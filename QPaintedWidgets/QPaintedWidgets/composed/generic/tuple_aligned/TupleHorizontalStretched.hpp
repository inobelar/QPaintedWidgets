#ifndef Q_PAINTED_WIDGETS___COMPOSED___GENERIC___TUPLE_ALIGNED___TUPLE_HORIZONTAL_STRETCHED_HPP
#define Q_PAINTED_WIDGETS___COMPOSED___GENERIC___TUPLE_ALIGNED___TUPLE_HORIZONTAL_STRETCHED_HPP

#include "TupleHorizontal.hpp"
#include "Tuple_Stretched.hpp"

namespace QPaintedWidgets {

template <typename BaseT, std::size_t ... StretchFactors>
struct TupleHorizontalStretched : public Tuple_Stretched< TupleHorizontal<BaseT>, StretchFactors ... >
{
    // TODO: somehow make: <..., std::size_t ... StretchFactors = make_n_indexes<sizeof...(BaseT::Components)>(0)> - if not specified == all zeroes

    using base_t = Tuple_Stretched< TupleHorizontal<BaseT>, StretchFactors ... >;

    using base_t::base_t;

    virtual void draw(QPainter& p, const QRect& rect) override
    {
        constexpr std::size_t COUNT = base_t::count();

        const std::array<qreal, COUNT> widths = base_t::calc_components_widths();

        // ---------------------------------------------------------------------

        constexpr typename base_t::stretches_t STRETCH_FACTORS = base_t::get_stretches();
        const auto rects = make_stretched_rects_horizontal(rect, widths, STRETCH_FACTORS, base_t::__spacing());

        std::size_t i = 0;
        base_t::for_each([&p, &i, rects](components::Component* component)
        {
            component->draw(p, rects[i].toRect());
            ++i;
        });
    }
};

} // namespace QPaintedWidgets

#endif // Q_PAINTED_WIDGETS___COMPOSED___GENERIC___TUPLE_ALIGNED___TUPLE_HORIZONTAL_STRETCHED_HPP
