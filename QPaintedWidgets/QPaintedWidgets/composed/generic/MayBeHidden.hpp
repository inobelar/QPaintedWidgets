#ifndef Q_PAINTED_WIDGETS___COMPOSED___GENERIC___MAY_BE_HIDDEN_HPP
#define Q_PAINTED_WIDGETS___COMPOSED___GENERIC___MAY_BE_HIDDEN_HPP

#include "QPaintedWidgets/components/Component.hpp"

/**
    Special wrapper, that allows show/hide component.

    That cause resizing components near it (in case of vertical or horizontal
    layouts/tuples/etc).

    NOTE: this special type MUST be last in types-chain, because most of the
    components ignores base-type `minimumSize()` implementation and overrides
    it by self custom behavior.

    TL;DR:
    @code{.cpp}
        MayBeHidden < WithSpacing <
            Nested < ComponentsTuple < RectFilled, Icon > >
        > >
    @endcode

    not this:
    @code{.cpp}
        WithSpacing < MayBeHidden < // <-- `WithSpacing` or another custom type may change `minimumSize()`
            Nested < ComponentsTuple < RectFilled, Icon> >
        > >
    @endcode
 */

namespace QPaintedWidgets {

template <typename BaseT>
class MayBeHidden : public BaseT
{
    static_assert (std::is_base_of<components::Component, BaseT>::value == true,
                   "BaseT must be derived from Component");

    bool _is_visible = true;

    bool _keep_space = false;

public:

    using self_t = MayBeHidden<BaseT>;

    using base_t = BaseT;

    using base_t::base_t;

    // -------------------------------------------------------------------------

    self_t& setVisible(bool visible)
    {
        if(_is_visible == visible) return (*this);

        _is_visible = visible;

        base_t::widget->updateGeometry(); // Update min size
        base_t::widget->update(); // Redraw

        return (*this);
    }

    // - - - - -

    // Common helpers
    self_t& show() { return setVisible(true); }
    self_t& hide() { return setVisible(false); }

    bool isVisible() const { return  _is_visible; }
    bool isHidden()  const { return !_is_visible; }

    // -------------------------------------------------------------------------

    self_t& setKeepSpace(bool keepSpace)
    {
        if(_keep_space == keepSpace) return (*this);

        _keep_space = keepSpace;

        base_t::widget->updateGeometry(); // Update min size
        base_t::widget->update(); // Redraw

        return (*this);
    }

    bool isKeepSpace() const {
        return _keep_space;
    }

    // -------------------------------------------------------------------------

    virtual QSize minimumSize() const override
    {
        if(_is_visible) {
            return base_t::minimumSize();
        } else {
            if(_keep_space == true)
                return base_t::minimumSize();
            else
                return {0, 0};
        }
    }

    virtual void draw(QPainter& p, const QRect& rect) override
    {
        if(_is_visible) {
            base_t::draw(p, rect);
        } // else
            // Do nothing - it's hidden
        // }
    }
};

} // namespace QPaintedWidgets

#endif // Q_PAINTED_WIDGETS___COMPOSED___GENERIC___MAY_BE_HIDDEN_HPP
