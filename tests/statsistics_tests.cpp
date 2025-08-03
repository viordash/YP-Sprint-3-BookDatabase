#include "statsistics.hpp"
#include <gmock/gmock.h>
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

    auto genre_ratings = calculateGenreRatings(book_db.begin(), book_db.end());
    ASSERT_EQ(genre_ratings.size(), 3);
    ASSERT_FLOAT_EQ(genre_ratings[Genre::SciFi], 4.0);
    ASSERT_FLOAT_EQ(genre_ratings[Genre::Fiction], 5);
    ASSERT_FLOAT_EQ(genre_ratings[Genre::Mystery], 4.2);
    ASSERT_FLOAT_EQ(genre_ratings[Genre::NonFiction], 0);
    ASSERT_FLOAT_EQ(genre_ratings[Genre::Biography], 0);
    ASSERT_FLOAT_EQ(genre_ratings[Genre::Unknown], 0);
}

TEST(TestStatsistics, AverageRating) {
    BookDatabase book_db{{"1984", "George Orwell", 1949, Genre::SciFi, 4.0, 190},
                         {"The Hobbit", "J.R.R. Tolkien", 1937, Genre::Fiction, 9, 203},
                         {"Pride and Prejudice", "Jane Austen", 1813, Genre::Fiction, 7, 178},
                         {"Lord of the Flies", "William Golding", 1954, Genre::Mystery, 4.2, 89},
                         {"Animal Farm", "George Orwell", 1945, Genre::Fiction, 3, 143},
                         {"Jane Eyre", "Charlotte Brontë", 1847, Genre::Fiction, 1, 110}};

    auto avg_ratings = calculateAverageRating(book_db);
    ASSERT_FLOAT_EQ(avg_ratings, 4.7);
}

TEST(TestStatsistics, SampleRandomBooks) {
    BookDatabase book_db{{"1984", "George Orwell", 1949, Genre::SciFi, 4.0, 190},
                         {"The Hobbit", "J.R.R. Tolkien", 1937, Genre::Fiction, 9, 203},
                         {"Pride and Prejudice", "Jane Austen", 1813, Genre::Fiction, 7, 178},
                         {"Lord of the Flies", "William Golding", 1954, Genre::Mystery, 4.2, 89},
                         {"Animal Farm", "George Orwell", 1945, Genre::Fiction, 3, 143},
                         {"Jane Eyre", "Charlotte Brontë", 1847, Genre::Fiction, 1, 110}};

    auto random_books_0 = sampleRandomBooks(book_db, 0);
    ASSERT_EQ(random_books_0.size(), 0);

    auto random_books_1 = sampleRandomBooks(book_db, 1);
    ASSERT_EQ(random_books_1.size(), 1);
    ASSERT_THAT(book_db, testing::Contains(testing::Eq(random_books_1[0].get())));

    auto random_books_3 = sampleRandomBooks(book_db, 3);
    ASSERT_EQ(random_books_3.size(), 3);
    ASSERT_THAT(book_db, testing::Contains(testing::Eq(random_books_3[0].get())));
    ASSERT_THAT(book_db, testing::Contains(testing::Eq(random_books_3[1].get())));
    ASSERT_THAT(book_db, testing::Contains(testing::Eq(random_books_3[2].get())));

    auto random_books_10 = sampleRandomBooks(book_db, 10);
    ASSERT_EQ(random_books_10.size(), 6);
}
