#pragma once

#include <concepts>
#include <iterator>

#include "book.hpp"

namespace bookdb {

template <typename C>
concept BookContainerLike = std::ranges::input_range<C> && std::same_as<std::ranges::range_value_t<C>, Book>;

template <typename T>
concept BookIterator = std::input_iterator<T> && std::same_as<std::iter_value_t<T>, Book>;

template <typename S, typename I>
concept BookSentinel = std::sentinel_for<S, I>;

template <typename P>
concept BookPredicate = std::predicate<P, Book>;

template <typename C>
concept BookComparator = std::predicate<C, const Book&, const Book&>;

}  // namespace bookdb