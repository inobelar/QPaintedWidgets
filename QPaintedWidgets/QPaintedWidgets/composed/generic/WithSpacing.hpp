#ifndef Q_PAINTED_WIDGETS___COMPOSED___GENERIC___WITH_SPACING_HPP
#define Q_PAINTED_WIDGETS___COMPOSED___GENERIC___WITH_SPACING_HPP

#include "QPaintedWidgets/components/Component.hpp"

// Special Wrapper/Attribute, that determines spacing between components

// NOTE: must be used BEFORE Horizontal/Vertical Tuple type

namespace QPaintedWidgets {

template <typename BaseT>
class WithSpacing: public BaseT
{
    static_assert(std::is_base_of<components::Component, BaseT>::value == true,
                  "BaseT must be derived from Component");

    int _spacing = 0;

public:

    using self_t = WithSpacing<BaseT>;

    using base_t = BaseT;

    using base_t::base_t;

    // -------------------------------------------------------------------------

    self_t& setSpacing(int spacing)
    {
        if(_spacing == spacing) return (*this);

        _spacing = spacing;

        auto* widget = base_t::widget;
        widget->updateGeometry();
        widget->update();

        return (*this);
    }

    int getSpacing() const
    {
        return _spacing;
    }
};

} // namespace QPaintedWidgets

#endif // Q_PAINTED_WIDGETS___COMPOSED___GENERIC___WITH_SPACING_HPP
