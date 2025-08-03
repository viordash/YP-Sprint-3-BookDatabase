#include "book.hpp"
#include "book_database.hpp"
#include "statsistics.hpp"
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

TEST(TestBook, Genre_formatter_returns_genre_name) {
    ASSERT_EQ(std::format("{}", Genre::Fiction), "Fiction");
    ASSERT_EQ(std::format("{}", Genre::NonFiction), "NonFiction");
    ASSERT_EQ(std::format("{}", Genre::SciFi), "SciFi");
    ASSERT_EQ(std::format("{}", Genre::Biography), "Biography");
    ASSERT_EQ(std::format("{}", Genre::Mystery), "Mystery");
    ASSERT_EQ(std::format("{}", Genre::Unknown), "Unknown");
}

TEST(TestBook, Book_formatter_returns_string_about_book) {
    ASSERT_EQ(std::format<bookdb::Book>("{}", {"1984", "George Orwell", 1949, Genre::SciFi, 4., 190}),
              "George Orwell '1984' [year:1949, genre:'SciFi', rating:4.0, reads:190]");
    ASSERT_EQ(std::format<bookdb::Book>("{}", {"The Hobbit", "J.R.R. Tolkien", 1937, Genre::Fiction, 4.9, 203}),
              "J.R.R. Tolkien 'The Hobbit' [year:1937, genre:'Fiction', rating:4.9, reads:203]");
}

TEST(TestBook, GenreRatings_formatter_returns_string_about_book) {
    BookDatabase book_db{{"1984", "George Orwell", 1949, Genre::SciFi, 4., 190},
                         {"The Hobbit", "J.R.R. Tolkien", 1937, Genre::Fiction, 9, 203},
                         {"Pride and Prejudice", "Jane Austen", 1813, Genre::Fiction, 7, 178}};

    auto genre_ratings = calculateGenreRatings(book_db.begin(), book_db.end());
    ASSERT_EQ(std::format("{}", genre_ratings), "Fiction: 8.0, SciFi: 4.0");
}
