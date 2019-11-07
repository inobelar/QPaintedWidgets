#ifndef HICONBUTTON_HPP
#define HICONBUTTON_HPP

#include <QAbstractButton>

#include <memory>

class HIconButton : public QAbstractButton
{
    Q_OBJECT

    // PIMPL
    struct Gfx;
    std::unique_ptr<Gfx> gfx;

    // Default methods disabled
    using QAbstractButton::setText;
    using QAbstractButton::text;

    using QAbstractButton::setIcon;
    using QAbstractButton::icon;

    using QAbstractButton::setIconSize;
    using QAbstractButton::iconSize;

    bool _activated = false;

public:

    using base_t = QAbstractButton;
    explicit HIconButton(QWidget *parent = nullptr);
    virtual ~HIconButton();

    // ---------------------------------------------

    void setText(const QString& text);
    QString getText() const;

    // ---------------------------------------------

    void setIcon(const QIcon& icon);

    // ---------------------------------------------

    void setActivated(bool activated);
    bool isActivated() const;

    // ---------------------------------------------

    QSize minimumSizeHint() const override;

protected:
    void paintEvent(QPaintEvent*) override;
};

#endif // HICONBUTTON_HPP
