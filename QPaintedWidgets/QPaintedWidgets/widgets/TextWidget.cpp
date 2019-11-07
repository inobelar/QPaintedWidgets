#include "TextWidget.hpp"

QPaintedWidgets::TextWidget::TextWidget(QWidget *parent)
    : base_t(parent)
{

}

QPaintedWidgets::TextWidget::TextWidget(const QString &text_, QWidget *parent)
    : TextWidget(parent)
{
    text.setText(text_);
}

// -----------------------------------------------------------------------------

QSize QPaintedWidgets::TextWidget::minimumSizeHint() const
{
    return text.minimumSize();
}

// -----------------------------------------------------------------------------

void QPaintedWidgets::TextWidget::setText(const QString &text_)
{
    text.setText(text_);
}

QString QPaintedWidgets::TextWidget::getText() const
{
    return text.getText();
}

// -----------------------------------------------------------------------------

#include <QPainter>

void QPaintedWidgets::TextWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    text.draw(p, this->rect());
}
