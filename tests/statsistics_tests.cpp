#include "statsistics.hpp"
#include <gtest/gtest.h>

using namespace bookdb;

TEST(TestStatsistics, AuthorHistogram) {
    BookDatabase book_db{{"1984", "George Orwell", 1949, Genre::SciFi, 4., 190},
                         {"The Hobbit", "J.R.R. Tolkien", 1937, Genre::Fiction, 4.9, 203},
                         {"Pride and Prejudice", "Jane Austen", 1813, Genre::Fiction, 4.7, 178},
                         {"Lord of the Flies", "William Golding", 1954, Genre::Fiction, 4.2, 89},
                         {"Animal Farm", "George Orwell", 1945, Genre::Fiction, 4.4, 143}};

    auto histogram = buildAuthorHistogramFlat(book_db);
    ASSERT_EQ(histogram.size(), 4);
    ASSERT_EQ(histogram["George Orwell"], 2);
    ASSERT_EQ(histogram["J.R.R. Tolkien"], 1);
    ASSERT_EQ(histogram["Jane Austen"], 1);
    ASSERT_EQ(histogram["William Golding"], 1);
}

TEST(TestStatsistics, GenreRatings) {
    BookDatabase book_db{{"1984", "George Orwell", 1949, Genre::SciFi, 4., 190},
                         {"The Hobbit", "J.R.R. Tolkien", 1937, Genre::Fiction, 9, 203},
                         {"Pride and Prejudice", "Jane Austen", 1813, Genre::Fiction, 7, 178},
                         {"Lord of the Flies", "William Golding", 1954, Genre::Mystery, 4.2, 89},
                         {"Animal Farm", "George Orwell", 1945, Genre::Fiction, 3, 143},
                         {"Jane Eyre", "Charlotte Brontë", 1847, Genre::Fiction, 1, 110}};

    auto genreRatings = calculateGenreRatings(book_db.begin(), book_db.end());
    ASSERT_EQ(genreRatings.size(), 3);
    ASSERT_FLOAT_EQ(genreRatings[Genre::SciFi], 4.0);
    ASSERT_FLOAT_EQ(genreRatings[Genre::Fiction], 5);
    ASSERT_FLOAT_EQ(genreRatings[Genre::Mystery], 4.2);
    ASSERT_FLOAT_EQ(genreRatings[Genre::NonFiction], 0);
    ASSERT_FLOAT_EQ(genreRatings[Genre::Biography], 0);
    ASSERT_FLOAT_EQ(genreRatings[Genre::Unknown], 0);
}
