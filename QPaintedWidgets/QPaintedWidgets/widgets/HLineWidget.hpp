#ifndef Q_PAINTED_WIDGETS___WIDGETS___H_LINE_WIDGET_HPP
#define Q_PAINTED_WIDGETS___WIDGETS___H_LINE_WIDGET_HPP

#include <QWidget>

#include <memory>

namespace QPaintedWidgets {

class HLineWidget : public QWidget
{
    Q_OBJECT

    // PIMPL
    struct Gfx;
    std::unique_ptr<Gfx> _line;

public:

    using base_t = QWidget;

    explicit HLineWidget(QWidget *parent = nullptr);
    explicit HLineWidget(const QPen& pen, QWidget* parent = nullptr);
    virtual ~HLineWidget();

    virtual QSize minimumSizeHint() const override;

    // -------------------------------------------------------------------------

    void setPen(const QPen& pen);
    QPen getPen() const;

protected:
    virtual void paintEvent(QPaintEvent *) override;
};

} // namespace QPaintedWidgets

#endif // Q_PAINTED_WIDGETS___WIDGETS___H_LINE_WIDGET_HPP
