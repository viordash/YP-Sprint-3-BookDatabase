#pragma once

#include "book.hpp"
#include "concepts.hpp"

namespace bookdb {

inline auto YearBetween(int min, int max) {
    return [min, max](const Book &book) { return book.year >= min && book.year <= max; };
}

inline auto RatingAbove(double min_rating) {
    return [min_rating](const Book &book) { return book.rating >= min_rating; };
}

inline auto GenreIs(Genre genre) {
    return [genre](const Book &book) { return book.genre == genre; };
}

template <BookPredicate... Preds>
auto all_of(Preds... preds) {
    return [... ps = std::move(preds)](const Book &book) { return (ps(book) && ...); };
}

template <BookPredicate... Preds>
auto any_of(Preds... preds) {
    return [... ps = std::move(preds)](const Book &book) { return (ps(book) || ...); };
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