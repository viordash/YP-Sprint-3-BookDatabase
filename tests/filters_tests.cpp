#include "book_database.hpp"
#include "filters.hpp"
#include <gtest/gtest.h>

using namespace bookdb;

TEST(TestFilters, YearBetween) {
    BookDatabase book_db{{"1984", "George Orwell", 1949, Genre::SciFi, 4.0, 190},
                         {"The Hobbit", "J.R.R. Tolkien", 1937, Genre::Fiction, 9, 203},
                         {"Pride and Prejudice", "Jane Austen", 1813, Genre::Fiction, 7, 178},
                         {"Lord of the Flies", "William Golding", 1954, Genre::Mystery, 4.2, 89},
                         {"Animal Farm", "George Orwell", 1945, Genre::Fiction, 3, 143},
                         {"Jane Eyre", "Charlotte Brontë", 1847, Genre::Fiction, 1, 110}};

    auto filtered_0 = filterBooks(book_db.begin(), book_db.end(), YearBetween(2900, 2999));
    ASSERT_EQ(filtered_0.size(), 0);

    auto filtered_1 = filterBooks(book_db.begin(), book_db.end(), YearBetween(1937, 1937));
    ASSERT_EQ(filtered_1.size(), 1);
    ASSERT_EQ(filtered_1[0].get().title, "The Hobbit");

    auto filtered_3 = filterBooks(book_db.begin(), book_db.end(), YearBetween(1800, 1937));
    ASSERT_EQ(filtered_3.size(), 3);
    ASSERT_EQ(filtered_3[0].get().title, "The Hobbit");
    ASSERT_EQ(filtered_3[1].get().title, "Pride and Prejudice");
    ASSERT_EQ(filtered_3[2].get().title, "Jane Eyre");

    auto filtered_10 = filterBooks(book_db.begin(), book_db.end(), YearBetween(0, 3000));
    ASSERT_EQ(filtered_10.size(), 6);
}

TEST(TestFilters, RatingAbove) {
    BookDatabase book_db{{"1984", "George Orwell", 1949, Genre::SciFi, 4.0, 190},
                         {"The Hobbit", "J.R.R. Tolkien", 1937, Genre::Fiction, 9, 203},
                         {"Pride and Prejudice", "Jane Austen", 1813, Genre::Fiction, 7, 178},
                         {"Lord of the Flies", "William Golding", 1954, Genre::Mystery, 4.2, 89},
                         {"Animal Farm", "George Orwell", 1945, Genre::Fiction, 3, 143},
                         {"Jane Eyre", "Charlotte Brontë", 1847, Genre::Fiction, 1, 110}};

    auto filtered_0 = filterBooks(book_db.begin(), book_db.end(), RatingAbove(100));
    ASSERT_EQ(filtered_0.size(), 0);

    auto filtered_1 = filterBooks(book_db.begin(), book_db.end(), RatingAbove(9));
    ASSERT_EQ(filtered_1.size(), 1);
    ASSERT_EQ(filtered_1[0].get().title, "The Hobbit");

    auto filtered_3 = filterBooks(book_db.begin(), book_db.end(), RatingAbove(4.2));
    ASSERT_EQ(filtered_3.size(), 3);
    ASSERT_EQ(filtered_3[0].get().title, "The Hobbit");
    ASSERT_EQ(filtered_3[1].get().title, "Pride and Prejudice");
    ASSERT_EQ(filtered_3[2].get().title, "Lord of the Flies");

    auto filtered_10 = filterBooks(book_db.begin(), book_db.end(), RatingAbove(0));
    ASSERT_EQ(filtered_10.size(), 6);
}

TEST(TestFilters, GenreIs) {
    BookDatabase book_db{{"1984", "George Orwell", 1949, Genre::SciFi, 4.0, 190},
                         {"The Hobbit", "J.R.R. Tolkien", 1937, Genre::Fiction, 9, 203},
                         {"Pride and Prejudice", "Jane Austen", 1813, Genre::Fiction, 7, 178},
                         {"Lord of the Flies", "William Golding", 1954, Genre::Mystery, 4.2, 89},
                         {"Animal Farm", "George Orwell", 1945, Genre::Fiction, 3, 143},
                         {"Jane Eyre", "Charlotte Brontë", 1847, Genre::SciFi, 1, 110}};

    auto filtered_0 = filterBooks(book_db.begin(), book_db.end(), GenreIs(Genre::Unknown));
    ASSERT_EQ(filtered_0.size(), 0);

    auto filtered_1 = filterBooks(book_db.begin(), book_db.end(), GenreIs(Genre::Mystery));
    ASSERT_EQ(filtered_1.size(), 1);
    ASSERT_EQ(filtered_1[0].get().title, "Lord of the Flies");

    auto filtered_3 = filterBooks(book_db.begin(), book_db.end(), GenreIs(Genre::Fiction));
    ASSERT_EQ(filtered_3.size(), 3);
    ASSERT_EQ(filtered_3[0].get().title, "The Hobbit");
    ASSERT_EQ(filtered_3[1].get().title, "Pride and Prejudice");
    ASSERT_EQ(filtered_3[2].get().title, "Animal Farm");
}

TEST(TestFilters, all_of) {
    BookDatabase book_db{{"1984", "George Orwell", 1949, Genre::SciFi, 4.0, 190},
                         {"The Hobbit", "J.R.R. Tolkien", 1937, Genre::Fiction, 9, 203},
                         {"Pride and Prejudice", "Jane Austen", 1813, Genre::Fiction, 7, 178},
                         {"Lord of the Flies", "William Golding", 1954, Genre::Mystery, 4.2, 89},
                         {"Animal Farm", "George Orwell", 1945, Genre::Fiction, 3, 143},
                         {"Jane Eyre", "Charlotte Brontë", 1847, Genre::Fiction, 1, 110}};

    auto filtered_0_Year =
        filterBooks(book_db.begin(), book_db.end(), all_of(YearBetween(2900, 2999), RatingAbove(4.5)));
    ASSERT_EQ(filtered_0_Year.size(), 0);
    auto filtered_0_Rating =
        filterBooks(book_db.begin(), book_db.end(), all_of(YearBetween(0, 3000), RatingAbove(100)));
    ASSERT_EQ(filtered_0_Rating.size(), 0);

    auto filtered_1_Year =
        filterBooks(book_db.begin(), book_db.end(), all_of(YearBetween(1937, 1937), RatingAbove(4.0)));
    ASSERT_EQ(filtered_1_Year.size(), 1);
    ASSERT_EQ(filtered_1_Year[0].get().title, "The Hobbit");
    auto filtered_1_Rating =
        filterBooks(book_db.begin(), book_db.end(), all_of(YearBetween(0, 3000), RatingAbove(9.0)));
    ASSERT_EQ(filtered_1_Rating.size(), 1);
    ASSERT_EQ(filtered_1_Rating[0].get().title, "The Hobbit");

    auto filtered_3 = filterBooks(book_db.begin(), book_db.end(), all_of(YearBetween(1800, 1937), RatingAbove(1)));
    ASSERT_EQ(filtered_3.size(), 3);
    ASSERT_EQ(filtered_3[0].get().title, "The Hobbit");
    ASSERT_EQ(filtered_3[1].get().title, "Pride and Prejudice");
    ASSERT_EQ(filtered_3[2].get().title, "Jane Eyre");

    auto filtered_10 = filterBooks(book_db.begin(), book_db.end(), all_of(YearBetween(0, 3000), RatingAbove(0)));
    ASSERT_EQ(filtered_10.size(), 6);
}

TEST(TestFilters, any_of) {
    BookDatabase book_db{{"1984", "George Orwell", 1949, Genre::SciFi, 4.0, 190},
                         {"The Hobbit", "J.R.R. Tolkien", 1937, Genre::Fiction, 9, 203},
                         {"Pride and Prejudice", "Jane Austen", 1813, Genre::Fiction, 7, 178},
                         {"Lord of the Flies", "William Golding", 1954, Genre::Mystery, 4.2, 89},
                         {"Animal Farm", "George Orwell", 1945, Genre::Fiction, 3, 143},
                         {"Jane Eyre", "Charlotte Brontë", 1847, Genre::Fiction, 1, 110}};

    auto filtered_0 = filterBooks(book_db.begin(), book_db.end(), any_of(YearBetween(2900, 2999), RatingAbove(100)));
    ASSERT_EQ(filtered_0.size(), 0);

    auto filtered_1 = filterBooks(book_db.begin(), book_db.end(), any_of(YearBetween(1937, 1937), RatingAbove(9.0)));
    ASSERT_EQ(filtered_1.size(), 1);
    ASSERT_EQ(filtered_1[0].get().title, "The Hobbit");

    auto filtered_3_Year =
        filterBooks(book_db.begin(), book_db.end(), any_of(YearBetween(1800, 1937), RatingAbove(10)));
    ASSERT_EQ(filtered_3_Year.size(), 3);
    ASSERT_EQ(filtered_3_Year[0].get().title, "The Hobbit");
    ASSERT_EQ(filtered_3_Year[1].get().title, "Pride and Prejudice");
    ASSERT_EQ(filtered_3_Year[2].get().title, "Jane Eyre");
    auto filtered_3_Rating =
        filterBooks(book_db.begin(), book_db.end(), any_of(YearBetween(2900, 2999), RatingAbove(4.2)));
    ASSERT_EQ(filtered_3_Rating.size(), 3);
    ASSERT_EQ(filtered_3_Rating[0].get().title, "The Hobbit");
    ASSERT_EQ(filtered_3_Rating[1].get().title, "Pride and Prejudice");
    ASSERT_EQ(filtered_3_Rating[2].get().title, "Lord of the Flies");

    auto filtered_10_Year = filterBooks(book_db.begin(), book_db.end(), any_of(YearBetween(0, 3000), RatingAbove(100)));
    ASSERT_EQ(filtered_10_Year.size(), 6);
    auto filtered_10_Rating =
        filterBooks(book_db.begin(), book_db.end(), any_of(YearBetween(2900, 2999), RatingAbove(0)));
    ASSERT_EQ(filtered_10_Rating.size(), 6);
}