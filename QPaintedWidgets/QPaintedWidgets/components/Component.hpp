#ifndef Q_PAINTED_WIDGETS___COMPONENTS___COMPONENT_HPP
#define Q_PAINTED_WIDGETS___COMPONENTS___COMPONENT_HPP

#include <QWidget>

namespace QPaintedWidgets {

namespace components {

class Component
{
    // Non-Copyable
    Component (const Component&) = delete; // non construction-copyable
    Component& operator = (const Component&) = delete; // non copyable

protected:

    // Stored for calling:
    // - QWidget::updateGeometry()
    // - QWidget::update()
    // on component properties change, which may cause resize/redraw
    QWidget* widget = nullptr;

    void update();

    // Common helper
    bool hovered_by_cursor() const;

public:

    using self_t = Component;

    explicit Component(QWidget* w);
    virtual ~Component();

    // -------------------------------------------------------------------------

    virtual QSize minimumSize() const;

    virtual void draw(QPainter& p, const QRect& rect) = 0;

};

} // namespace components

} // namespace QPaintedWidgets

#endif // Q_PAINTED_WIDGETS___COMPONENTS___COMPONENT_HPP
