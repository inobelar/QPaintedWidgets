#ifndef MY_VERTICAL_BUTTON_HPP
#define MY_VERTICAL_BUTTON_HPP

#include <QAbstractButton>

#include <memory>

class MyVerticalButton : public QAbstractButton
{
    Q_OBJECT

    // PIMPL
    class Gfx;
    std::unique_ptr<Gfx> gfx;

    // Default methods disabled
    using QAbstractButton::setText;
    using QAbstractButton::text;

    using QAbstractButton::setIcon;
    using QAbstractButton::icon;

    using QAbstractButton::setIconSize;
    using QAbstractButton::iconSize;

public:

    using base_t = QAbstractButton;
    explicit MyVerticalButton(QWidget *parent = nullptr);
    virtual ~MyVerticalButton();

    QSize minimumSizeHint() const override;

    void setIcon(const QIcon& icon);

protected:
    void paintEvent(QPaintEvent*) override;
};

#endif // MY_VERTICAL_BUTTON_HPP
