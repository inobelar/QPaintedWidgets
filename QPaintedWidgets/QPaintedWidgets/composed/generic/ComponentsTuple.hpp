#ifndef Q_PAINTED_WIDGETS___COMPOSED___GENERIC___COMPONENTS_TUPLE_HPP
#define Q_PAINTED_WIDGETS___COMPOSED___GENERIC___COMPONENTS_TUPLE_HPP

#include "QPaintedWidgets/components/Component.hpp"

#include "QPaintedWidgets/meta/tuple_for_each.hpp"

namespace QPaintedWidgets {

template <typename ... ComponentsT>
class ComponentsTuple : public components::Component
{

// TODO:
//    static_assert ((std::is_base_of<components::Component, ComponentsT>::value == true) && ...,
//                   "ComponentFirst must be derived from components::Component");

    /**
        Lambda-like class. In c++11 we cannot write `auto` lambda param, like:
        @code{.cpp}
            detail::for_each_in_tuple(components, [](auto* component) {
                delete component;
                component = nullptr;
            });
        @endcode

        only:
        @code
            detail::for_each_in_tuple(components, geterogen_deleter() );
        @endcode
     */
    struct geterogen_deleter
    {
        // Call-operator
        template <typename ComponentT>
        void operator () (ComponentT* component) const {
            delete component;
            component = nullptr;
        }
    };

public:

    using base_t = components::Component;

    // -------------------------------------------------------------------------

    using tuple_t = std::tuple< ComponentsT* ... >;

    tuple_t components; // = { nullptr };

    // -------------------------------------------------------------------------

    explicit ComponentsTuple(QWidget *w)
        : base_t(w)
    {
        components = std::tuple<ComponentsT* ...>( new ComponentsT(w) ...);
    }

    virtual ~ComponentsTuple()
    {
        meta::for_each_in_tuple(components, geterogen_deleter() ); // TODO: make sure that this is work ok
    }

    // -------------------------------------------------------------------------
    // Convenient helpers

    /*
        Note: next line:
            using nth_item_t = typename std::tuple_element<N, tuple_t>::type;
        used to NOT write return type like:
            auto get() -> decltype( std::get<N>(components) ) { ... }
        which REQUIRES RTTI, which is bad :)
    */
    template <std::size_t N>
    using nth_item_t = typename std::tuple_element<N, tuple_t>::type;

    template <std::size_t N>
    nth_item_t<N> get() {
        return std::get<N>(components);
    }

    template <std::size_t N>
    constexpr nth_item_t<N> get() const {
        return std::get<N>(components);
    }

    // -----------------------------------------------------

    template <typename F>
    void for_each(F&& func) {
        meta::for_each_in_tuple(components, func);
    }

    template <typename F>
    void for_each(const F&& func) const {
        meta::for_each_in_tuple(components, func);
    }

    // -----------------------------------------------------

    static constexpr std::size_t count() {
        return std::tuple_size<tuple_t>::value;
    }

    // -------------------------------------------------------------------------
    // Required override's in derived classes

    virtual QSize minimumSize() const = 0;

    virtual void draw(QPainter& p, const QRect& rect) = 0;

};

} // namespace QPaintedWidgets

#endif // Q_PAINTED_WIDGETS___COMPOSED___GENERIC___COMPONENTS_TUPLE_HPP
