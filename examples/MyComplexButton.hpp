#ifndef MY_COMPLEX_BUTTON_HPP
#define MY_COMPLEX_BUTTON_HPP

#include <QAbstractButton>

#include "QPaintedWidgets/components/Text.hpp"
#include "QPaintedWidgets/components/TextStatic.hpp"
#include "QPaintedWidgets/components/Icon.hpp"
#include "QPaintedWidgets/components/RectFilledRoundedWithBorder.hpp"
#include "QPaintedWidgets/components/LineVertical.hpp"
#include "QPaintedWidgets/components/LineHorizontal.hpp"


#include "QPaintedWidgets/composed/generic/tuple_aligned/TupleVertical.hpp"
#include "QPaintedWidgets/composed/generic/tuple_aligned/TupleHorizontal.hpp"

#include "QPaintedWidgets/composed/generic/tuple_aligned/TupleHorizontalStretched.hpp"
#include "QPaintedWidgets/composed/generic/tuple_aligned/TupleVerticalStretched.hpp"

#include "QPaintedWidgets/composed/generic/ComponentsPair.hpp"

#include "QPaintedWidgets/composed/generic/WithSpacing.hpp"
#include "QPaintedWidgets/composed/generic/WithMargin.hpp"

#include "QPaintedWidgets/composed/generic/Nested.hpp"
#include "QPaintedWidgets/composed/generic/MayBeHidden.hpp"

using namespace QPaintedWidgets;

class MyComplexButton : public QAbstractButton
{
    Q_OBJECT

    using Gfx = WithMargin < TupleVerticalStretched < ComponentsTuple
    <
        TupleHorizontal < ComponentsTuple
        <
            // Left side
            TupleVertical < ComponentsTuple
            <
                components::TextStatic,
                components::TextStatic,
                components::TextStatic
            > >,

            components::LineVertical,

            // Right side
            TupleVertical < ComponentsTuple
            <
                components::TextStatic,
                components::TextStatic,
                components::TextStatic
            > >
        > >,

        components::LineHorizontal,

        // Middle horizontal labels
        TupleHorizontal < WithSpacing < ComponentsTuple
        <
            components::TextStatic,
            components::TextStatic,
            components::TextStatic
        > > >,

        components::LineHorizontal,

        // Bottom - stretched widgets
        TupleHorizontalStretched < WithSpacing < ComponentsTuple
        <
            Nested < ComponentsPair // Icon in rectangle
            <
                components::RectFilledRoundedWithBorder,
                WithMargin< components::Icon >
            > >,
            MayBeHidden < Nested < ComponentsPair // Optionally hidden
            <
                components::RectFilledRoundedWithBorder,
                components::Text
            > > >,
            Nested < ComponentsPair
            <
                components::RectFilledRoundedWithBorder,
                components::Text
            > >
        > >, 0, 1, 2>

    >, 1, 0, 1, 0, 1> >;

    Gfx gfx { this };

public:

    using base_t = QAbstractButton;
    explicit MyComplexButton(QWidget *parent = nullptr);

    virtual QSize minimumSizeHint() const override;

protected:
    virtual void paintEvent(QPaintEvent *) override;
};

#endif // MY_COMPLEX_BUTTON_HPP
