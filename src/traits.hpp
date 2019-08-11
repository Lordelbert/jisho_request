#ifndef __TRAITS_H__
#define __TRAITS_H__
#include <type_traits>
template <typename T, typename = void> struct is_iterable : std::false_type {
};
template <typename T>
struct is_iterable<T, std::void_t<decltype(std::declval<T>().begin()),
                                  decltype(std::declval<T>().end())>> : std::true_type {
};
template <class T> inline constexpr bool is_iterable_v = is_iterable<T>::value;

template <typename T, typename = void> struct has_emplace : std::false_type {
};
template <typename T>
struct has_emplace<T, std::void_t<decltype(std::declval<T>().emplace())>>
    : std::true_type {
};
template <class T> inline constexpr bool has_emplace_v = has_emplace<T>::value;
#endif
