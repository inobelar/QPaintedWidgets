#include "StaticTextWidget.hpp"

QPaintedWidgets::StaticTextWidget::StaticTextWidget(QWidget *parent)
    : base_t(parent)
{

}

QPaintedWidgets::StaticTextWidget::StaticTextWidget(const QString &text_, QWidget *parent)
    : StaticTextWidget(parent)
{
    text.setText(text_);
}

// -----------------------------------------------------------------------------

QSize QPaintedWidgets::StaticTextWidget::minimumSizeHint() const
{
    return text.minimumSize();
}

// -----------------------------------------------------------------------------

void QPaintedWidgets::StaticTextWidget::setText(const QString &text_)
{
    text.setText(text_);
}

QString QPaintedWidgets::StaticTextWidget::getText() const
{
    return text.getText();
}

// -----------------------------------------------------------------------------

#include <QPainter>

void QPaintedWidgets::StaticTextWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    text.draw(p, this->rect());
}
