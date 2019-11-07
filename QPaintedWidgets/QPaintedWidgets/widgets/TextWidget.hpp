#ifndef Q_PAINTED_WIDGETS___WIDGETS___TEXT_WIDGET_HPP
#define Q_PAINTED_WIDGETS___WIDGETS___TEXT_WIDGET_HPP

#include <QWidget>

#include "QPaintedWidgets/components/Text.hpp"

namespace QPaintedWidgets {

class TextWidget : public QWidget
{
    Q_OBJECT

public:

    components::Text text { this };

    using base_t = QWidget;

    explicit TextWidget(QWidget* parent = nullptr);
    explicit TextWidget(const QString& text_, QWidget* parent = nullptr);

    virtual QSize minimumSizeHint() const override;

    // Convenient helpers
    void setText(const QString& text_);
    QString getText() const;

protected:
    virtual void paintEvent(QPaintEvent *) override;
};

} // namespace QPaintedWidgets

#endif // Q_PAINTED_WIDGETS___WIDGETS___TEXT_WIDGET_HPP
