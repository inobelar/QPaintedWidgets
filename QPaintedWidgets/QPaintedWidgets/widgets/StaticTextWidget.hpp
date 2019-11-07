#ifndef Q_PAINTED_WIDGETS___WIDGETS___STATIC_TEXT_WIDGET_HPP
#define Q_PAINTED_WIDGETS___WIDGETS___STATIC_TEXT_WIDGET_HPP

#include <QWidget>

#include "QPaintedWidgets/components/TextStatic.hpp"

namespace QPaintedWidgets {

class StaticTextWidget : public QWidget
{
    Q_OBJECT

public:

    components::TextStatic text { this };

    using base_t = QWidget;

    explicit StaticTextWidget(QWidget *parent = nullptr);
    explicit StaticTextWidget(const QString& text_, QWidget* parent = nullptr);

    virtual QSize minimumSizeHint() const override;

    // Convenient helpers
    void setText(const QString& text_);
    QString getText() const;

protected:
    virtual void paintEvent(QPaintEvent *) override;
};

} // namespace QPaintedWidgets

#endif // Q_PAINTED_WIDGETS___WIDGETS___STATIC_TEXT_WIDGET_HPP
