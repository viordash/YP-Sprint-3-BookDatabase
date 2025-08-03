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
