#include "book.hpp"
#include <gtest/gtest.h>

using namespace bookdb;

TEST(TestBook, GenreFromString_returns_Genre) {
    ASSERT_EQ(GenreFromString("Fiction"), Genre::Fiction);
    ASSERT_EQ(GenreFromString("NonFiction"), Genre::NonFiction);
    ASSERT_EQ(GenreFromString("SciFi"), Genre::SciFi);
    ASSERT_EQ(GenreFromString("Biography"), Genre::Biography);
    ASSERT_EQ(GenreFromString("Mystery"), Genre::Mystery);

    static_assert(GenreFromString("Fiction") == Genre::Fiction);
    static_assert(GenreFromString("NonFiction") == Genre::NonFiction);
    static_assert(GenreFromString("SciFi") == Genre::SciFi);
    static_assert(GenreFromString("Biography") == Genre::Biography);
    static_assert(GenreFromString("Mystery") == Genre::Mystery);
}

TEST(TestBook, GenreFromString_returns_Unknown_for_unknown_genres_or_with_incorrect_case) {
    ASSERT_EQ(GenreFromString("Unknown"), Genre::Unknown);
    ASSERT_EQ(GenreFromString(""), Genre::Unknown);
    ASSERT_EQ(GenreFromString("fiction"), Genre::Unknown);
    ASSERT_EQ(GenreFromString("nonfiction"), Genre::Unknown);
    ASSERT_EQ(GenreFromString("scifi"), Genre::Unknown);
    ASSERT_EQ(GenreFromString("biography"), Genre::Unknown);
    ASSERT_EQ(GenreFromString("mystery"), Genre::Unknown);

    static_assert(GenreFromString("Unknown") == Genre::Unknown);
}
