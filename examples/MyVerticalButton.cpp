#include "MyVerticalButton.hpp"

#include "QPaintedWidgets/components/Icon.hpp"
#include "QPaintedWidgets/components/Text.hpp"
#include "QPaintedWidgets/components/RectFilledRounded.hpp"

#include "QPaintedWidgets/composed/generic/ComponentsTuple.hpp"
#include "QPaintedWidgets/composed/generic/tuple_aligned/TupleVerticalStretched.hpp"
#include "QPaintedWidgets/composed/generic/Nested.hpp"

using namespace QPaintedWidgets;

using GfxView
    = Nested < ComponentsTuple <
        components::RectFilledRounded,
        TupleVerticalStretched < ComponentsTuple<
            components::Icon,
            components::Text
        >, 2, 1 >
    > >;

struct MyVerticalButton::Gfx : public GfxView
{
    using GfxView::GfxView;
};

MyVerticalButton::MyVerticalButton(QWidget *parent)
    : base_t(parent)
{
    gfx = std::unique_ptr<Gfx>( new Gfx(this) );

    auto bg = gfx->get<0>();

    auto icon = gfx->get<1>()->get<0>();
    auto text = gfx->get<1>()->get<1>();

    icon->setSize({60, 60});

    text->setText("Text")
            .setAlignment(Qt::AlignTop | Qt::AlignHCenter);
}

MyVerticalButton::~MyVerticalButton()
{ }

QSize MyVerticalButton::minimumSizeHint() const
{
    return gfx->minimumSize();
}

void MyVerticalButton::setIcon(const QIcon &icon)
{
    gfx->get<1>()->get<0>()->setIcon(icon);
}

#include <QPainter>

void MyVerticalButton::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    gfx->draw(p, this->rect());
}
