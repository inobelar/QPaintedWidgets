#ifndef Q_PAINTED_WIDGETS___COMPOSED___GENERIC___WITH_MARGIN_T_HPP
#define Q_PAINTED_WIDGETS___COMPOSED___GENERIC___WITH_MARGIN_T_HPP

#include <QMargins>
#include <QPainter>

namespace QPaintedWidgets {

template <typename BaseT>
class WithMarginT : public BaseT
{
protected:

    QMargins _margin;

    virtual void on_margin_changed() = 0;

public:

    using self_t = WithMarginT<BaseT>;

    using base_t = BaseT;

    using base_t::base_t;

    self_t& setContentMargin(const QMargins& margins)
    {
        if(_margin == margins) return (*this);

        _margin = margins;

        on_margin_changed();

        return (*this);
    }

    QMargins getContentMargin() const {
        return _margin;
    }

    // -------------------------------------------------------------------------
    // Convenient helpers

    self_t& setContentMarginsHV(int horizontal, int vertical)
    {
        return setContentMargin({horizontal, vertical, horizontal, vertical});
    }

    self_t& setContentMarginsAll(int padding)
    {
        return setContentMargin({padding, padding, padding, padding});
    }

    // -------------------------------------------------------------------------

    QRect get_margin_rect(const QRect& r) const
    {
        if(_margin.isNull())
        {
            return r;
        }
        else
        {
            QRect rect = r;
            rect.setLeft  ( rect.left()   + _margin.left()   );
            rect.setRight ( rect.right()  - _margin.right()  );
            rect.setTop   ( rect.top()    + _margin.top()    );
            rect.setBottom( rect.bottom() - _margin.bottom() );
            return rect;
        }
    }

    QSize get_margin_size() const
    {
        return {
            _margin.left() + _margin.right(),
            _margin.top()  + _margin.bottom()
        };
    }
};

} // namespace QPaintedWidgets

#endif // Q_PAINTED_WIDGETS___COMPOSED___GENERIC___WITH_MARGIN_T_HPP
