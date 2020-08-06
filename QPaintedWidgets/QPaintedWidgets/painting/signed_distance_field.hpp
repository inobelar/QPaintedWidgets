#ifndef Q_PAINTED_WIDGETS___PAINTING___SIGNED_DISTANCE_FIELD_HPP
#define Q_PAINTED_WIDGETS___PAINTING___SIGNED_DISTANCE_FIELD_HPP

#include <vector>     // for std::vector<T>
#include <functional> // for std::function<R(Args)>

namespace QPaintedWidgets {
namespace sdf {

using comparator_func_t = std::function<bool(int x, int y)>;

/**
    @brief make_field
    @param searchDistance - lookup distance. smaller values -> faster lookup
    @param width  - resulting field width
    @param height - resulting field height
    @param comparator - predicate, that must return true for pixels, for which distance must be calculated
    @return 1-dimentional array (with size: @a width x @a height) of normalized distances
 */
std::vector<float> make_field(int searchDistance, int width, int height, const comparator_func_t& comparator);

} // namespace sdf
} // namespace QPaintedWidgets

#endif // Q_PAINTED_WIDGETS___PAINTING___SIGNED_DISTANCE_FIELD_HPP
