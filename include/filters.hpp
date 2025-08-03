#pragma once

#include "book.hpp"
#include "concepts.hpp"
#include <functional>

namespace bookdb {

inline auto YearBetween(int min, int max) {
    return [min, max](const Book &book) { return book.year >= min && book.year <= max; };
}

template <BookIterator I, BookSentinel<I> S, BookPredicate P>
auto filterBooks(I first, S last, P pred) {
    std::vector<std::reference_wrapper<const Book>> result;
    for (; first != last; ++first) {
        if (pred(*first)) {
            result.emplace_back(*first);
        }
    }
    return result;
}

}  // namespace bookdb