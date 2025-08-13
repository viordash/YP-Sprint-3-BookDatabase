#include "comparators.hpp"
#include <gtest/gtest.h>

using namespace bookdb;
using namespace bookdb::comp;

TEST(TestComparators, LessByAuthor_compare) {
    Book book1{"title", "author1", 2025, Genre::SciFi, 1, 1};
    Book book2{"title", "author2", 2025, Genre::SciFi, 1, 1};
    Book book3{"title", "author3", 2025, Genre::SciFi, 1, 1};

    LessByAuthor lessByAuthor;

    ASSERT_TRUE(lessByAuthor(book1, book3));
    ASSERT_TRUE(lessByAuthor(book2, book3));
    ASSERT_FALSE(lessByAuthor(book2, book1));
    ASSERT_FALSE(lessByAuthor(book3, book1));
}

TEST(TestComparators, LessByRating_compare) {
    Book book1{"title", "author1", 2025, Genre::SciFi, 1, 1};
    Book book2{"title", "author2", 2025, Genre::SciFi, 2, 1};
    Book book3{"title", "author3", 2025, Genre::SciFi, 3, 1};

    LessByRating lessByRating;

    ASSERT_TRUE(lessByRating(book1, book3));
    ASSERT_TRUE(lessByRating(book2, book3));
    ASSERT_FALSE(lessByRating(book2, book1));
    ASSERT_FALSE(lessByRating(book3, book1));
}

TEST(TestComparators, LessByPopularity_compare) {
    Book book1{"title", "author1", 2025, Genre::SciFi, 1, 1};
    Book book2{"title", "author2", 2025, Genre::SciFi, 1, 2};
    Book book3{"title", "author3", 2025, Genre::SciFi, 1, 3};

    LessByPopularity lessByPopularity;

    ASSERT_TRUE(lessByPopularity(book1, book3));
    ASSERT_TRUE(lessByPopularity(book2, book3));
    ASSERT_FALSE(lessByPopularity(book2, book1));
    ASSERT_FALSE(lessByPopularity(book3, book1));
}
