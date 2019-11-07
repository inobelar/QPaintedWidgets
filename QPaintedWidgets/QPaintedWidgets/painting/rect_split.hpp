#ifndef Q_PAINTED_WIDGETS___PAINTING___RECT_SPLIT_HPP
#define Q_PAINTED_WIDGETS___PAINTING___RECT_SPLIT_HPP

#include <QRectF>
#include <QRect>

#include <array>
#include <numeric> // for std::accumulate

template <std::size_t N>
inline std::array<qreal, N> split(const qreal length, std::array<qreal, N> ratios)
{
    const qreal sum = std::accumulate(ratios.begin(), ratios.end(), 0.0);
    const qreal multiplier = length / sum;

    for(auto& ratio : ratios)
        ratio *= multiplier;

    return ratios;
}

template <std::size_t N>
inline std::array<QRectF, N> split_vertically(const QRectF& rect, const std::array<qreal, N>& ratios)
{
    const auto sizes = split(rect.height(), ratios);

    std::array<QRectF, N> rects;

    qreal offset = 0.0;
    for(std::size_t i = 0; i < rects.size(); ++i)
    {
        QRectF& r = rects[i];

        const qreal top = rect.top() + offset;
        r = QRectF(rect.left(), top, rect.width(), sizes[i]);

        offset += top;
    }
    return rects;
}

template <std::size_t N>
inline std::array<QRectF, N> split_horizontally(const QRectF& rect, const std::array<qreal, N>& ratios)
{
    const auto sizes = split(rect.width(), ratios);

    std::array<QRectF, N> rects;

    qreal offset = 0.0;
    for(std::size_t i = 0; i < rects.size(); ++i)
    {
        QRectF& r = rects[i];

        const qreal left = rect.left() + offset;
        r = QRectF(left, rect.top(), sizes[i], rect.height());

        offset += left;
    }
    return rects;
}

// -----------------------------------------------------------------------------

template <typename T, std::size_t N>
inline T calc_total(const std::array<T, N>& data)
{
    return std::accumulate(data.begin(), data.end(), T{0});
}

template <std::size_t N>
inline qreal calc_total_size(const std::array<qreal, N>& sizes, const qreal spacing)
{
    const qreal total_sizes   = calc_total(sizes);
    const qreal total_spacing = spacing * static_cast<qreal>(N - 1);
    return total_sizes + total_spacing;
}

template <std::size_t N>
inline std::array<qreal, N> make_ranges(const qreal length, std::array<qreal, N> sizes, const qreal spacing)
{
    static_assert (N >= 1, "Must contains at least one element");

    // TODO: handle empty components (zero size[i])

    const qreal total = calc_total_size(sizes, spacing);

    if(total < length) // Extra space available
    {
        const qreal extra_space = length - total;
        const qreal extra_per_size = extra_space / static_cast<qreal>(N);

        for(auto& s : sizes)
            s += extra_per_size;
        return sizes;
    }
    else // No extra space
    {
        return sizes;
    }
}

template <std::size_t N>
inline std::array<QRectF, N> make_rects_horizontal(const QRectF& rect, const std::array<qreal, N>& sizes, const qreal spacing)
{
    const auto expanded_sizes = make_ranges(rect.width(), sizes, spacing);

    std::array<QRectF, N> rects;

    qreal offset = 0.0;
    for(std::size_t i = 0; i < expanded_sizes.size(); ++i)
    {
        const auto& size = expanded_sizes[i];
        QRectF& r = rects[i];

        const qreal left = rect.left() + offset;
        r = QRectF(left, rect.top(), size, rect.height());

        offset += (size + spacing);
    }

    return rects;
}

template <std::size_t N>
inline std::array<QRectF, N> make_rects_vertical(const QRectF& rect, const std::array<qreal, N>& sizes, const qreal spacing)
{
    const auto expanded_sizes = make_ranges(rect.height(), sizes, spacing);

    std::array<QRectF, N> rects;

    qreal offset = 0.0;
    for(std::size_t i = 0; i < expanded_sizes.size(); ++i)
    {
        const auto& size = expanded_sizes[i];
        QRectF& r = rects[i];

        const qreal top = rect.top() + offset;
        r = QRectF(rect.left(), top, rect.width(), size);

        offset += (size + spacing);
    }

    return rects;
}

// -----------------------------------------------------------------------------

template <std::size_t N, typename RangeT = std::pair<qreal /*begin*/, qreal /*length*/> >
inline std::array<RangeT, N>
make_stretched_sizes(const qreal length,
                 const std::array<qreal, N>& sizes,
                 std::array<std::size_t, N> stretch_factors,
                 const qreal spacing)
{
    // Important step: components with size equal to zero (typicaly it means: hidden)
    // have zero stretch factor and dont waste space
    int empty_count = 0;
    for(std::size_t i = 0; i < stretch_factors.size(); ++i)
    {
        if( qFuzzyIsNull(sizes[i]) ) {
            stretch_factors[i] = 0;
            empty_count++;
        }
    }

    // -------------------------------------------------------------------------

    const qreal total_lenght = calc_total(sizes);

    int N_SPACES = (N-1) - empty_count;
    if(N_SPACES < 0) { N_SPACES = 0; } // Prevent case, when all components is 'hidden' (may cause 'negative spacing')

    const qreal total_spacing = static_cast<qreal>(N_SPACES) * spacing;
    const qreal total_size = (total_lenght + total_spacing);

    // -------------------------------------------------------------------------

    const qreal extra_size = (length - total_size);

    std::size_t total_stretch = calc_total(stretch_factors);
    if(total_stretch == 0) { total_stretch = 1; } // Prevent division by zero, if all stretches are zeroes

    const qreal expand_coef = (extra_size / total_stretch);

    // -------------------------------------------------------------------------

    std::array<RangeT, N> ranges;

    qreal offset = 0.0;
    for(std::size_t i = 0; i < N; ++i)
    {
        if( qFuzzyIsNull(sizes[i]) ) // Component lenght equal to zero (typicaly it means: hidden)
        {
            ranges[i] = RangeT{offset, 0};
        }
        else
        {
            const qreal len = sizes[i] + (stretch_factors[i] * expand_coef);
            ranges[i] = RangeT{offset, len};

            offset += (len + spacing);
        }
    }

    return ranges;

}

template <std::size_t N>
inline std::array<QRectF, N> make_stretched_rects_horizontal(
        const QRectF& rect,
        const std::array<qreal, N>& sizes,
        const std::array<std::size_t, N>& stretch_factors,
        const qreal spacing)
{
    const auto ranges = make_stretched_sizes(rect.width(), sizes, stretch_factors, spacing);

    std::array<QRectF, N> rects;

    for(std::size_t i = 0; i < ranges.size(); ++i)
    {
        const qreal& left  = ranges[i].first;
        const qreal& width = ranges[i].second;

        rects[i] = QRectF(rect.left() + left, rect.top(), width, rect.height());
    }

    return rects;
}

template <std::size_t N>
inline std::array<QRectF, N> make_stretched_rects_vertical(
        const QRectF& rect,
        const std::array<qreal, N>& sizes,
        const std::array<std::size_t, N>& stretch_factors,
        const qreal spacing)
{
    const auto ranges = make_stretched_sizes(rect.height(), sizes, stretch_factors, spacing);

    std::array<QRectF, N> rects;

    for(std::size_t i = 0; i < ranges.size(); ++i)
    {
        const qreal& top    = ranges[i].first;
        const qreal& height = ranges[i].second;

        rects[i] = QRectF(rect.left(), rect.top() + top, rect.width(), height);
    }

    return rects;
}

#endif // Q_PAINTED_WIDGETS___PAINTING___RECT_SPLIT_HPP
