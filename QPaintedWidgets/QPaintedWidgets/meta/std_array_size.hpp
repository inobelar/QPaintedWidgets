#ifndef Q_PAINTED_WIDGETS___META___STD_ARRAY_SIZE_HPP
#define Q_PAINTED_WIDGETS___META___STD_ARRAY_SIZE_HPP

#include <array>   // for: std::array<T, SIZE>
#include <cstddef> // for: std::size_t

namespace QPaintedWidgets {

namespace meta {

// -----------------------------------------------------------------------------
// Based on: https://stackoverflow.com/a/16866128/

template <typename>
struct get_array_size;

template <typename T, std::size_t N>
struct get_array_size< std::array<T, N> >
{
    static constexpr std::size_t size = N;
};

// -----------------------------------------------------------------------------

/* Suitable for the next case:

    const std::array<int, 3> arr { 1, 2, 3 };

    1) static_assert( get_array_size< decltype(arr) >::size == 3, "Test failed" );
        - In that case compiler produces error:
            incomplete type 'get_array_size< const std::array<int, 3> >' used in nested name specifier
          Error means: we have no specialization for 'const std::array<T, SIZE>' (because we have only for 'std::array<T, SIZE>').

    2) static_assert( array_size< decltype(arr) >::size == 3, "Test failed" );
        - In that case we 'decay' (clear const-ness, reference, etc from type), so this works ok.

    Reference: https://stackoverflow.com/a/29587307/
*/
template <typename T>
using array_size = get_array_size< typename std::decay<T>::type >;

} // namespace meta

} // namespace QPaintedWidgets

#endif // Q_PAINTED_WIDGETS___META___STD_ARRAY_SIZE_HPP
