#ifndef Q_PAINTED_WIDGETS___COMPONENTS___ABSTRACT_LINE_HPP
#define Q_PAINTED_WIDGETS___COMPONENTS___ABSTRACT_LINE_HPP

#include "Component.hpp"

#include <QPen>

namespace QPaintedWidgets {

namespace components {

class AbstractLine : public Component
{
protected:

    QPen _pen = QPen(Qt::black, 1.0);

public:

    using self_t = AbstractLine;

    using base_t = Component;

    using base_t::base_t;

    // -------------------------------------------------------------------------

    self_t& setPen(const QPen& pen);
    QPen getPen() const;
};

} // namespace components

} // namespace QPaintedWidgets

#endif // Q_PAINTED_WIDGETS___COMPONENTS___ABSTRACT_LINE_HPP
