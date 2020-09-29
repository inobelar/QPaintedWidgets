# Qt Painted Widgets (Experimental/WIP)

<p align="center">
  <a href="http://hits.dwyl.com/inobelar/QPaintedWidgets">
    <img title="HitCount" src="http://hits.dwyl.com/inobelar/QPaintedWidgets.svg"/>
  </a>
</p>

Simple [DSL](https://en.wikipedia.org/wiki/Domain-specific_language)-like library for creating complex QWidget's design in declerative compile-time manner. 

The **Main Goal**: utilize boilerplate during creation widgets, which appearance based on custom [`QWidget::paintEvent(QPaintEvent*)`](https://doc.qt.io/qt-5/qwidget.html#paintEvent) implementation. For example in embedded-like software, where [QSS](https://doc.qt.io/qt-5/stylesheet.html) and QML may drop perfomance drastically. **TL;DR**: as said Bjarne Stroustrup: "[Make Simple Tasks Simple](https://youtu.be/nesCaocNjtQ)".

Language version: **C++11**. *Sorry, I use it in embedded, where compilers still not so smart.*

Inspired by: [Flutter](https://flutter.dev/), [SwiftUI](https://developer.apple.com/xcode/swiftui/) and [QML](https://doc.qt.io/qt-5/qtqml-index.html)

## Usage

In your `*.pro` file add next line:

```
inlude(<path/to>/QPaintedWidgets/q_painted_widgets.pri)
```

- **Advantages**:
    - All types known in compile time, no [types erasure](https://en.wikipedia.org/wiki/Generics_in_Java#Problems_with_type_erasure)
    - Easily extentible & opened for aliases
    - Drawing of multiple (event nested/packed) components can be easily combined with custom painting code (before and after).
    - [Method chaining](https://en.wikipedia.org/wiki/Method_chaining): most of the `Component`'s setters allow chaining like 
        ```c++
        text.setText("Lorem Ipsum")
            .setAlignment(Qt::AlignLeft | Qt::AlignVCenter)
            .setFontBold(true)
            .setFontPixelSize(24)
            .setPen(Qt::blue);
        ```
    - Built-in support for styling and auto update next states: `Normal`, `Hovered`, `Pressed`, `Disabled`
- **Disadvantages**:
    - Not dynamic: you cannot add/remove components in run-time
    - On components properties change - repainted the **whole** widget (by calling `QWidget::update()` internally)
    - Size of nested/packed components un-acessible (calculated during drawing)
    - Written in c++11, without such useful things as: [concepts](https://en.cppreference.com/w/cpp/language/constraints), [if constexpr](https://en.cppreference.com/w/cpp/language/if), [fold expressions](https://en.cppreference.com/w/cpp/language/fold), [using parameter pack](https://en.cppreference.com/w/cpp/language/parameter_pack#Using-declarations)
    - Due to templated-nature, debugging kinda difficult

## Examples of usage

- Simple single-component widgets in [widgets/](./QPaintedWidgets/QPaintedWidgets/widgets/) directory

### Components usage (simplest case)

1. Describe component look:
    ```c++
    using View
        = TupleVertical < ComponentsTuple <
            components::Text, // Top    text
            components::Text, // Middle Text
            components::Text  // Bottom text
        > >;
    ```
2. Use component inside widget:
    ```c++
    class MyWidget : public QWidget
    {
        Q_OBJECT

        View graphics { this };

    public:
        explicit MyWidget(QWidget* parent = nullptr)
            : QWidget(parent)
        {}

        QSize minimumSizeHint() const override {
            return graphics.minimumSize(); // Restrict widget mimimum size
        }

        // Accessors for setting text
        void setTextTop   (const QString& text) { graphics.get<0>()->setText(text); }
        void setTextMiddle(const QString& text) { graphics.get<1>()->setText(text); }
        void setTextBottom(const QString& text) { graphics.get<2>()->setText(text); }

    protected:
        void paintEvent(QPaintEvent* ) override {
            QPainter p(this);
            graphics.draw(p, this->rect()); // Draw graphics inside widget
        }
    }
    ```

### PIMPL

To make compilation time shorter and not distribute `QPaintedWidgets` types over your project, useful to use [PIMPL](https://en.cppreference.com/w/cpp/language/pimpl) idiom for hiding everything related to graphics in source files.

#### Header (`HorizontalIconButton.hpp`):
```c++
#include <QAbstractButton>

#include <memory> // for std::unique_ptr<T>

/*  ┌──────────────────┐
    │ ┌────┐           │
    │ │icon│    Text   │
    │ └────┘           │
    └──────────────────┘   */

class HorizontalIconButton : public QAbstractButton
{
    Q_OBJECT

    // PIMPL
    class Gfx;
    std::unique_ptr<Gfx> gfx;

    // Default methods disallowed (here, in private section) to prevent miss-usage
    using QAbstractButton::setText;
    using QAbstractButton::text;

    using QAbstractButton::setIcon;
    using QAbstractButton::icon;

    using QAbstractButton::setIconSize;
    using QAbstractButton::iconSize;

public:

    explicit HorizontalIconButton(QWidget *parent = nullptr);
    virtual ~HorizontalIconButton(); // Needed for std::unique_ptr

    // ---------------------------------------------

    void setText(const QString& text);
    QString getText() const;

    // ---------------------------------------------

    void setIcon(const QIcon& icon);

    // ---------------------------------------------

    QSize minimumSizeHint() const override; // For mimimum size restrictnment

protected:
    void paintEvent(QPaintEvent *) override; // Major place - drawing 
};
```
#### Source (`HorizontalIconButton.cpp`):

```c++
#include "HorizontalIconButton.hpp"

#include "QPaintedWidgets/components/Icon.hpp"
#include "QPaintedWidgets/components/TextStatic.hpp"
#include "QPaintedWidgets/components/RectFilledRounded.hpp"
#include "QPaintedWidgets/components/RectFilledRoundedWithBorder.hpp"

#include "QPaintedWidgets/composed/generic/ComponentsPair.hpp"
#include "QPaintedWidgets/composed/generic/tuple_aligned/TupleHorizontalStretched.hpp"
#include "QPaintedWidgets/composed/generic/WithPadding.hpp"
#include "QPaintedWidgets/composed/generic/WithSpacing.hpp"
#include "QPaintedWidgets/composed/generic/WithMinSize.hpp"
#include "QPaintedWidgets/composed/generic/Nested.hpp"

using namespace QPaintedWidgets;

// Icon placed in rounded rectangle
using Gfx_Icon_in_Rect
    = Nested < ComponentsPair <
        WithMinSize< components::RectFilledRoundedWithBorder >,
        components::Icon
    > >;

// Icon on left side, Text on right side (filling all space)
using Gfx_Items
    = TupleHorizontalStretched < WithSpacing < ComponentsPair <
        Gfx_Icon_in_Rect,
        components::TextStatic
    > >, 0, 1>;

// All items displayed over rounded rectangle
using GfxView
    = Nested < ComponentsPair <
        components::RectFilledRounded,
        WithPadding < Gfx_Items >
    > >;

struct HorizontalIconButton::Gfx : public GfxView
{
    using base_t = GfxView;
    
    explicit Gfx(QWidget* widget)
        : base_t(widget)
    {
        item_bg()->setBrush( QColor(Qt::red) ); // Custom styling
    }

    // -------------------
    // Convenient aliases for easier access

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
inline std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

HorizontalIconButton::HorizontalIconButton(QWidget *parent)
    : QAbstractButton(parent)
{
    gfx = make_unique<Gfx>(this);

    // Example of usage - restyling
    gfx->item_items()->setContentPadding({4, 4, 4, 4});
    gfx->item_items()->setSpacing(8);

    gfx->item_icon()->setSize({32, 32});
    gfx->item_icon_rect()->setCustomMinSize({60, 60});
}

HorizontalIconButton::~HorizontalIconButton()
{ }

// -----------------------------------------------------------------------------

void HorizontalIconButton::setText(const QString &text)
{
    gfx->item_text()->setText(text);
}

QString HorizontalIconButton::getText() const
{
    return gfx->item_text()->getText();
}

// -----------------------------------------------------------------------------

void HorizontalIconButton::setIcon(const QIcon &icon)
{
    gfx->item_icon()->setIcon(icon);
}

// -----------------------------------------------------------------------------

QSize HorizontalIconButton::minimumSizeHint() const
{
    return gfx->minimumSize();
}

#include <QPainter>

void HorizontalIconButton::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    gfx->draw(p, this->rect());
}
```

### Complex aliases

```c++
template <typename ComponentT, std::size_t STRETCH = 0>
struct Stretch
{
    using component_t = ComponentT;
    static constexpr std::size_t stretch = STRETCH;
};

// { Stretch<ComponentT, StretchT> ... } unpacked as { ComponentT ... , StretchT ... }
template <template <typename ...> class BaseT, typename ... StretchesT>
struct MyHBox : public
    TupleHorizontalStretched <
        BaseT<typename StretchesT::component_t ...>,
        StretchesT::stretch ...
    >
{
    // Same as above, sorry for duplicate :/
    using base_t
        = TupleHorizontalStretched <
            BaseT<typename StretchesT::component_t ...>,
            StretchesT::stretch ...
        >;

    using base_t::base_t;
};
```

To write:

```c++
MyHBox < ComponentsTuple,

    Stretch< components::Text, 2>,
    Stretch< components::Text, 3>,
    Stretch< components::Text, 5>

>
```
instead of:

```c++
TupleHorizontalStretched < ComponentsTuple
<
    components::Text,
    components::Text,
    components::Text

>, 2, 3, 5>
```

#### Fixme
- cannot be combined with additional attributes
    - so:
        `TupleHorizontalStretched < WithSpacing < ComponentsTuple`
    - cannot be:
        `MyHBox < WithSpacing<ComponentsTuple>, Stretches... >`

-----

## Currently unresolved issues

- `TupleHorizontal` & `TupleVertical` currently not handle zero-sizes (aka hidden components via `MayBeHidden`) (have no time, fix it later, sorry)
- `Text` component `size()` always works in **multiline** text mode
- `WithMaxMargin` - not implemented. Flexible wrapper, same as `WithMargin` but margin-offset may be shrinked, if space not enought
- `widgets/TextWidget` & `widgets/StaticTextWidget` must use pimpl idiom
- Implement `Pixmap` & `PixmapAspectRatio` & `Circle` & `Triangles`

## End

Feel free to fork & hack :) If this was useful to you, please add :star: on github :)
