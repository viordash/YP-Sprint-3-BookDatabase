#pragma once

#include "book_database.hpp"
#include <algorithm>
#include <flat_map>
#include <iterator>
#include <print>
#include <random>
#include <string_view>

namespace bookdb {

template <BookContainerLike T, typename Comparator = TransparentStringLess>
auto buildAuthorHistogramFlat(const BookDatabase<T> &cont) {
    std::flat_map<std::string_view, int, Comparator> histogram;
    for (const auto &book : cont.GetBooks()) {
        auto [iterator, inserted] = histogram.insert({book.author, 0});
        iterator->second++;
    }
    return histogram;
}

template <BookIterator I, BookSentinel<I> S>
auto calculateGenreRatings(I first, S last) {
    std::flat_map<Genre, std::pair<double, int>> genreStats;
    for (; first != last; ++first) {
        auto &stats = genreStats[first->genre];
        stats.first += first->rating;
        stats.second++;
    }

    std::flat_map<Genre, double> result;
    for (const auto &[genre, stats] : genreStats) {
        result.insert({genre, stats.first / stats.second});
    }
    return result;
}

}  // namespace bookdb
