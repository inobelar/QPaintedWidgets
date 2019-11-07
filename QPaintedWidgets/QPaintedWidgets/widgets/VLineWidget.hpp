#ifndef Q_PAINTED_WIDGETS___WIDGETS___V_LINE_WIDGET_HPP
#define Q_PAINTED_WIDGETS___WIDGETS___V_LINE_WIDGET_HPP

#include <QWidget>

#include <memory>

namespace QPaintedWidgets {

class VLineWidget : public QWidget
{
    Q_OBJECT

    // PIMPL
    struct Gfx;
    std::unique_ptr<Gfx> _line;

public:

    using base_t = QWidget;

    explicit VLineWidget(QWidget *parent = nullptr);
    explicit VLineWidget(const QPen& pen, QWidget* parent = nullptr);
    virtual ~VLineWidget();

    virtual QSize minimumSizeHint() const override;

    // -------------------------------------------------------------------------

    void setPen(const QPen& pen);
    QPen getPen() const;

protected:
    virtual void paintEvent(QPaintEvent *) override;
};

} // namespace QPaintedWidgets

#endif // Q_PAINTED_WIDGETS___WIDGETS___V_LINE_WIDGET_HPP
