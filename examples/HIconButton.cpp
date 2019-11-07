#include "HIconButton.hpp"

#include "QPaintedWidgets/components/Icon.hpp"
#include "QPaintedWidgets/components/TextStatic.hpp"
#include "QPaintedWidgets/components/RectFilledRounded.hpp"
#include "QPaintedWidgets/components/RectFilledRoundedWithBorder.hpp"

#include "QPaintedWidgets/composed/generic/ComponentsPair.hpp"
#include "QPaintedWidgets/composed/generic/tuple_aligned/TupleHorizontalStretched.hpp"
#include "QPaintedWidgets/composed/generic/WithMargin.hpp"
#include "QPaintedWidgets/composed/generic/WithSpacing.hpp"
#include "QPaintedWidgets/composed/generic/WithMinSize.hpp"
#include "QPaintedWidgets/composed/generic/Nested.hpp"

using namespace QPaintedWidgets;

using Gfx_Icon_in_Rect
    = Nested < ComponentsPair <
        WithMinSize< components::RectFilledRoundedWithBorder >,
        components::Icon
    > >;

using Gfx_Items
    = TupleHorizontalStretched < WithSpacing < ComponentsPair <
        Gfx_Icon_in_Rect,
        components::TextStatic
    > >, 0, 1>;

using GfxView
    = Nested < ComponentsPair <
        components::RectFilledRounded,
        WithMargin< Gfx_Items >
    > >;

struct HIconButton::Gfx : public GfxView
{
    using GfxView::GfxView;

    auto item_bg() -> decltype( this->first() )
    {
        return this->first();
    }

    auto item_items() -> decltype ( this->second() )
    {
        return this->second();
    }

    // -------------------

    auto item_icon_in_rect() -> decltype ( item_items()->first() )
    {
        return item_items()->first();
    }

    auto item_text() -> decltype ( item_items()->second() )
    {
        return item_items()->second();
    }

    // -------------------

    auto item_icon_rect() -> decltype ( item_icon_in_rect()->first() )
    {
        return item_icon_in_rect()->first();
    }

    auto item_icon() -> decltype ( item_icon_in_rect()->second() )
    {
        return item_icon_in_rect()->second();
    }
};

// std::make_unique for c++11 (via: https://stackoverflow.com/a/17903225)
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

HIconButton::HIconButton(QWidget *parent)
    : base_t(parent)
{
    gfx = make_unique<Gfx>(this);

    gfx->item_items()->setContentMargin({4, 4, 4, 4});
    gfx->item_items()->setSpacing(8);


    gfx->item_icon()->setSize({32, 32});
    gfx->item_icon_rect()->setCustomMinSize({60, 60});

    gfx->item_text()->setText("Text");

}

HIconButton::~HIconButton()
{

}

// -----------------------------------------------------------------------------

void HIconButton::setText(const QString &text)
{
    gfx->item_text()->setText(text);
}

QString HIconButton::getText() const
{
    return gfx->item_text()->getText();
}

// -----------------------------------------------------------------------------

void HIconButton::setIcon(const QIcon &icon)
{
    gfx->item_icon()->setIcon(icon);
}

// -----------------------------------------------------------------------------

void HIconButton::setActivated(bool activated)
{
    if(_activated == activated) return;

    _activated = activated;

    {
        if(_activated)
        {
            // TODO
        }
        else
        {
            // TODO
        }
    }

    this->update();
}

bool HIconButton::isActivated() const
{
    return _activated;
}

// -----------------------------------------------------------------------------

QSize HIconButton::minimumSizeHint() const
{
    return gfx->minimumSize();
}

#include <QPainter>

void HIconButton::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    gfx->draw(p, this->rect());
}
