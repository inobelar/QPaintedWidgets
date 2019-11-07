#ifndef Q_PAINTED_WIDGETS___COMPSED___GENERIC___WITH_MIN_SIZE_HPP
#define Q_PAINTED_WIDGETS___COMPSED___GENERIC___WITH_MIN_SIZE_HPP

#include "QPaintedWidgets/components/Component.hpp"

#include "QPaintedWidgets/painting/pos_from_alignment.hpp"

namespace QPaintedWidgets {

template <typename BaseT>
class WithMinSize : public BaseT
{
    static_assert (std::is_base_of<components::Component, BaseT>::value == true,
                   "BaseT must be derived from Component");

    QSize _custom_min_size = {0, 0};
    Qt::Alignment _custom_alignment = Qt::AlignCenter;

public:

    using self_t = WithMinSize<BaseT>;

    using base_t = BaseT;

    using base_t::base_t;

    // -------------------------------------------------------------------------

    self_t& setCustomMinSize(const QSize& size)
    {
        if(_custom_min_size == size) return (*this);

        _custom_min_size = size;

        base_t::widget->updateGeometry();
        base_t::widget->update();

        return (*this);
    }

    QSize getCustomMinSize() const {
        return _custom_min_size;
    }

    // -------------------------------------------------------------------------

    self_t& setCustomAlignment(const Qt::Alignment alignment)
    {
        if(_custom_alignment == alignment) return (*this);

        _custom_alignment = alignment;

        base_t::widget->updateGeometry();
        base_t::widget->update();

        return (*this);
    }

    Qt::Alignment getCustomAlignment() const {
        return _custom_alignment;
    }

    // -------------------------------------------------------------------------

    virtual QSize minimumSize() const override
    {
        const auto content_size = base_t::minimumSize();

        const QSize min_size = {
            std::max(_custom_min_size.width(),  content_size.width()),
            std::max(_custom_min_size.height(), content_size.height())
        };

        return min_size;
    }

    virtual void draw(QPainter& p, const QRect& rect) override
    {
        const QSize min_size = this->minimumSize();
        QRect custom_rect(0, 0, min_size.width(), min_size.height());
        custom_rect.moveTopLeft( helpers::pos_from_alignment(_custom_alignment, rect, min_size));

        base_t::draw(p, custom_rect);
    }
};

} // namespace QPaintedWidgets


#endif // Q_PAINTED_WIDGETS___COMPSED___GENERIC___WITH_MIN_SIZE_HPP
