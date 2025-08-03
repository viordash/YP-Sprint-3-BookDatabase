#include "concepts.hpp"
#include <gtest/gtest.h>
#include <iterator>
#include <list>

using namespace bookdb;

TEST(TestConcepts, BookContainerLike) {
    static_assert(BookContainerLike<std::vector<Book>>);
    static_assert(BookContainerLike<std::list<Book>>);

    static_assert(!BookContainerLike<std::vector<std::string>>);
    static_assert(!BookContainerLike<Book>);
}

TEST(TestConcepts, BookIterator) {
    static_assert(BookIterator<std::vector<Book>::iterator>);
    static_assert(BookIterator<std::vector<Book>::const_iterator>);
    static_assert(BookIterator<std::vector<Book>::reverse_iterator>);
    static_assert(BookIterator<std::list<Book>::iterator>);
    static_assert(BookIterator<std::list<Book>::const_iterator>);
    static_assert(BookIterator<std::list<Book>::reverse_iterator>);

    static_assert(BookIterator<Book *>);
    static_assert(BookIterator<const Book *>);

    static_assert(!BookIterator<std::vector<int>::iterator>);
    static_assert(!BookIterator<int *>);
    static_assert(!BookIterator<Book>);
}

TEST(TestConcepts, BookSentinel) {
    static_assert(BookSentinel<std::vector<Book>::iterator, std::vector<Book>::iterator>);
    static_assert(BookSentinel<std::vector<Book>::const_iterator, std::vector<Book>::const_iterator>);
    static_assert(BookSentinel<std::vector<Book>::const_iterator, std::vector<Book>::iterator>);
    static_assert(BookSentinel<std::vector<Book>::iterator, std::vector<Book>::const_iterator>);

    static_assert(BookSentinel<Book *, Book *>);
    static_assert(BookSentinel<const Book *, const Book *>);
    static_assert(BookSentinel<const Book *, Book *>);

    static_assert(!BookSentinel<std::vector<Book>::iterator, std::vector<int>::iterator>);
    static_assert(!BookSentinel<std::vector<Book>::iterator, Book>);
    static_assert(!BookSentinel<Book *, void *>);
}

TEST(TestConcepts, BookPredicate) {
    static_assert(BookPredicate<decltype([](const Book &b) { return true; })>);
    static_assert(BookPredicate<decltype([](Book b) { return true; })>);
    static_assert(BookPredicate<decltype([](const Book b) { return 1; })>);
    static_assert(BookPredicate<decltype([](Book b) { return 1; })>);

    static_assert(!BookPredicate<decltype([](Book b, int i) { return true; })>);
    static_assert(!BookPredicate<decltype([](int b) { return 1; })>);
}

TEST(TestConcepts, BookComparator) {
    static_assert(BookComparator<decltype([](const Book &b1, const Book &b2) { return true; })>);
    static_assert(BookComparator<decltype([](const Book &b1, const Book &b2) { return 1; })>);

    static_assert(!BookComparator<decltype([](Book &b1, Book &b2) { return true; })>);
    static_assert(!BookComparator<decltype([](const Book &b1, const Book &b2, int i) { return true; })>);
}