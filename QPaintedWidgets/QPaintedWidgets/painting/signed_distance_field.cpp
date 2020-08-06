#include "signed_distance_field.hpp"

#include <cmath>  // for std::sqrt()
#include <limits> // for std::numeric_limits<T>::max()

namespace detail {

float distance(int x1, int y1, int x2, int y2) {
    const float xd = x1 - x2;
    const float yd = y1 - y2;
    return std::sqrt((xd * xd) + (yd * yd));
}

// via: https://en.cppreference.com/w/cpp/algorithm/clamp
template <typename T>
const T& clamp(const T& v, const T& low, const T& high) {
    return (v < low) ? low : (high < v) ? high : v;
}

} // namespace detail

// Based on https://stackoverflow.com/q/11891887
std::vector<float> QPaintedWidgets::sdf::make_field(int searchDistance, int width, int height, const comparator_func_t& comparator)
{
    constexpr auto F_MAX = std::numeric_limits<float>::max();

    // Make distances field, filled by inifity distance
    std::vector<float> field( (width * height) , F_MAX );

    for(int x = 0; x < width; ++x)
    {
        for(int y = 0; y < height; ++y)
        {
            // Distance to closest pixel which is the inverse of a
            // start on float::max() so we can be sure we found something
            float distance = F_MAX;

            // Search coordinates, x::min/max and y::min/max
            const int fxMin = std::max(x - searchDistance, 0);
            const int fxMax = std::min(x + searchDistance, width);
            const int fyMin = std::max(y - searchDistance, 0);
            const int fyMax = std::min(y + searchDistance, height);

            for (int fx = fxMin; fx < fxMax; ++fx)
            {
                for (int fy = fyMin; fy < fyMax; ++fy)
                {
                    // Checking that the current pixel is such that the distance
                    // needs to be calculated
                    if ( comparator(fx, fy) )
                    {
                        const float d = detail::distance(x, y, fx, fy);

                        // Compare absolute distance values, and if smaller replace distance with the new one
                        if ( std::abs(d) < std::abs(distance) )
                        {
                            distance = d;
                        }
                    }
                }
            }

            // If new distance was found - normalize & invert it
            if (distance != F_MAX)
            {
                // Clamp distance to -/+
                distance = detail::clamp<float>(distance, -searchDistance, +searchDistance);

                // Convert from -search,+search to 0,+search*2 and then convert to 0.0, 1.0 and invert
                const float a = 1.0f - detail::clamp<float>((distance + searchDistance) / (searchDistance + searchDistance), 0, 1);

                const int idx = (x + (y * width));
                field[idx] = a;
            }

        }
    }

    return field;
}
