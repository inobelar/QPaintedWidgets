#include "Component.hpp"

void QPaintedWidgets::components::Component::update()
{
    widget->update();
}

bool QPaintedWidgets::components::Component::hovered_by_cursor() const
{
    return widget->rect().contains( widget->mapFromGlobal(QCursor::pos()) ); // Mouse over widget (hovered)
}

// -----------------------------------------------------------------------------

QPaintedWidgets::components::Component::Component(QWidget *w)
    : widget(w)
{}

QPaintedWidgets::components::Component::~Component()
{}

// -----------------------------------------------------------------------------

QSize QPaintedWidgets::components::Component::minimumSize() const
{
    return {0, 0};
}
