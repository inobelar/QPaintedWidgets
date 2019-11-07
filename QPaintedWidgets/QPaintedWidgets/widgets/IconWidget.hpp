#ifndef Q_PAINTED_WIDGETS___WIDGETS___ICON_WIDGET_HPP
#define Q_PAINTED_WIDGETS___WIDGETS___ICON_WIDGET_HPP

#include <QWidget>

#include <memory>

namespace QPaintedWidgets {

class IconWidget : public QWidget
{
    Q_OBJECT

    // PIMPL
    struct Gfx;
    std::unique_ptr<Gfx> _icon;

public:

    using base_t = QWidget;

    explicit IconWidget(QWidget *parent = nullptr);
    explicit IconWidget(const QIcon& icon_, QWidget* parent = nullptr);
    virtual ~IconWidget();

    virtual QSize minimumSizeHint() const override;

    // -------------------------------------------------------------------------

    void setIcon(const QIcon& icon);
    QIcon getIcon() const;

    void setIconSize(const QSize& size);
    QSize getIconSize() const;

protected:
    virtual void paintEvent(QPaintEvent *) override;
};

} // namespace QPaintedWidgets

#endif // Q_PAINTED_WIDGETS___WIDGETS___ICON_WIDGET_HPP
