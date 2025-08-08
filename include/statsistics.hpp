#pragma once

#include "book_database.hpp"
#include <algorithm>
#include <flat_map>
#include <iterator>
#include <numeric>
#include <print>
#include <random>
#include <span>
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

template <BookContainerLike T>
double calculateAverageRating(const BookDatabase<T> &cont) {
    if (cont.empty()) {
        return 0.0;
    }
    auto total = std::transform_reduce(cont.begin(), cont.end(), 0.0, std::plus<>(),
                                       [](const auto &book) { return book.rating; });

    return total / cont.size();
}

template <BookContainerLike T>
auto sampleRandomBooks(const BookDatabase<T> &cont, size_t count) {
    std::vector<std::reference_wrapper<const Book>> result;
    count = std::min(count, cont.size());
    result.reserve(count);
    std::sample(cont.begin(), cont.end(), std::back_inserter(result), count, std::mt19937{std::random_device{}()});
    return result;
}

template <BookComparator C>
auto getTopNBy(std::span<Book> books, size_t n, C comp) {
    n = std::min(n, books.size());
    std::sort(books.begin(), books.end(), comp);
    std::vector<std::reference_wrapper<const Book>> res(books.rbegin(), books.rbegin() + n);
    return res;
}

}  // namespace bookdb
