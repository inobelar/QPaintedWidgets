#include "MyComplexButton.hpp"

#include <QStyle>

MyComplexButton::MyComplexButton(QWidget *parent)
    : base_t(parent)
{
    gfx.setContentMargin({10, 5, 10, 5});

    auto left_side = gfx.get<0>()->get<0>();
    left_side->get<0>()->setText("Left Top").setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    left_side->get<1>()->setText("Left Middle");
    left_side->get<2>()->setText("Left Bottom").setAlignment(Qt::AlignRight | Qt::AlignVCenter);


    auto right_side = gfx.get<0>()->get<2>();
    right_side->get<0>()->setText("Right Top").setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    right_side->get<1>()->setText("Right Middle");
    right_side->get<2>()->setText("Right Bottom").setAlignment(Qt::AlignLeft | Qt::AlignVCenter);


    auto middle_side = gfx.get<2>();
    middle_side->get<0>()->setText("Left").setPen({Qt::blue});
    middle_side->get<1>()->setText("Middle");
    middle_side->get<2>()->setText("Right").setPen({Qt::red});
    middle_side->setSpacing(10);


    auto bottom_side = gfx.get<4>();
    bottom_side->get<0>()->second()->setIcon( this->style()->standardIcon(QStyle::StandardPixmap::SP_MediaPlay) ).setSize({32, 32});
    bottom_side->get<0>()->second()->setContentMargin({10, 10, 10, 10});
    bottom_side->get<1>()->second()->setText("Second");
    bottom_side->get<2>()->second()->setText("Third");
    bottom_side->setSpacing(10);

    connect(this, &QAbstractButton::clicked, this, [this] {
        auto text = gfx.get<4>()->get<1>(); // 'Second' text
        text->setVisible( !text->isVisible());
    });
}

QSize MyComplexButton::minimumSizeHint() const
{
    return gfx.minimumSize();
}

#include <QPainter>

void MyComplexButton::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    gfx.draw(p, this->rect());
}
