#include "book_database.hpp"
#include <gtest/gtest.h>

using namespace bookdb;

TEST(TestBookDb, Fill_via_initializer_list) {
    BookDatabase book_db{{"1984", "George Orwell", 1949, Genre::SciFi, 4., 190},
                         {"The Hobbit", "J.R.R. Tolkien", 1937, Genre::Fiction, 4.9, 203},
                         {"Pride and Prejudice", "Jane Austen", 1813, Genre::Fiction, 4.7, 178}};

    ASSERT_EQ(book_db.size(), 3);
    ASSERT_EQ(book_db.at(0).title, "1984");
    ASSERT_EQ(book_db.at(1).title, "The Hobbit");
    ASSERT_EQ(book_db.at(2).title, "Pride and Prejudice");
    ASSERT_TRUE(book_db.GetAuthors().contains("George Orwell"));
    ASSERT_TRUE(book_db.GetAuthors().contains("J.R.R. Tolkien"));
    ASSERT_TRUE(book_db.GetAuthors().contains("Jane Austen"));
}

TEST(TestBookDb, Fill_via_EmplaceBack) {
    BookDatabase book_db;

    book_db.EmplaceBack("1984", "George Orwell", 1949, Genre::SciFi, 4., 190);
    book_db.EmplaceBack("Animal Farm", "George Orwell", 1945, Genre::Fiction, 4.4, 143);
    book_db.EmplaceBack("The Great Gatsby", "F. Scott Fitzgerald", 1925, Genre::Fiction, 4.5, 120);

    ASSERT_EQ(book_db.size(), 3);
    ASSERT_EQ(book_db.GetAuthors().size(), 2);
    ASSERT_EQ(book_db.at(0).title, "1984");
    ASSERT_EQ(book_db.at(1).title, "Animal Farm");
    ASSERT_EQ(book_db.at(2).title, "The Great Gatsby");
    ASSERT_TRUE(book_db.GetAuthors().contains("George Orwell"));
    ASSERT_TRUE(book_db.GetAuthors().contains("F. Scott Fitzgerald"));
}

TEST(TestBookDb, Fill_via_PushBack) {
    BookDatabase book_db;

    Book book1("1984", "George Orwell", 1949, Genre::SciFi, 4., 190);
    Book book2("Animal Farm", "George Orwell", 1945, Genre::Fiction, 4.4, 143);
    Book book3("The Great Gatsby", "F. Scott Fitzgerald", 1925, Genre::Fiction, 4.5, 120);
    book_db.PushBack(book1);
    book_db.PushBack(book2);
    book_db.PushBack(book3);

    ASSERT_EQ(book_db.size(), 3);
    ASSERT_EQ(book_db.GetAuthors().size(), 2);
    ASSERT_EQ(book_db.at(0).title, "1984");
    ASSERT_EQ(book_db.at(1).title, "Animal Farm");
    ASSERT_EQ(book_db.at(2).title, "The Great Gatsby");
    ASSERT_TRUE(book_db.GetAuthors().contains("George Orwell"));
    ASSERT_TRUE(book_db.GetAuthors().contains("F. Scott Fitzgerald"));
}

TEST(TestBookDb, Authors_is_unique) {
    BookDatabase book_db{{"1984", "George Orwell", 1949, Genre::SciFi, 4., 190},
                         {"The Hobbit", "J.R.R. Tolkien", 1937, Genre::Fiction, 4.9, 203},
                         {"Pride and Prejudice", "Jane Austen", 1813, Genre::Fiction, 4.7, 178},
                         {"Lord of the Flies", "William Golding", 1954, Genre::Fiction, 4.2, 89},
                         {"Animal Farm", "George Orwell", 1945, Genre::Fiction, 4.4, 143}};

    ASSERT_EQ(book_db.size(), 5);
    ASSERT_EQ(book_db.GetAuthors().size(), 4);
    ASSERT_TRUE(book_db.GetAuthors().contains("George Orwell"));
    ASSERT_TRUE(book_db.GetAuthors().contains("J.R.R. Tolkien"));
    ASSERT_TRUE(book_db.GetAuthors().contains("William Golding"));
    ASSERT_TRUE(book_db.GetAuthors().contains("Jane Austen"));
}

TEST(TestBookDb, Empty_db) {
    BookDatabase book_db;

    ASSERT_TRUE(book_db.empty());
    ASSERT_TRUE(book_db.GetAuthors().empty());

    book_db.EmplaceBack("1984", "George Orwell", 1949, Genre::SciFi, 4., 190);

    ASSERT_FALSE(book_db.empty());
    ASSERT_FALSE(book_db.GetAuthors().empty());
}

TEST(TestBookDb, Clear_db) {
    BookDatabase book_db;

    book_db.EmplaceBack("1984", "George Orwell", 1949, Genre::SciFi, 4., 190);
    ASSERT_FALSE(book_db.empty());
    ASSERT_FALSE(book_db.GetAuthors().empty());

    book_db.Clear();
    ASSERT_TRUE(book_db.empty());
    ASSERT_TRUE(book_db.GetAuthors().empty());
}

TEST(TestBookDb, Iterate) {
    BookDatabase book_db{{"1984", "George Orwell", 1949, Genre::SciFi, 4., 190},
                         {"The Hobbit", "J.R.R. Tolkien", 1937, Genre::Fiction, 4.9, 203},
                         {"Pride and Prejudice", "Jane Austen", 1813, Genre::Fiction, 4.7, 178}};

    auto it = book_db.begin();
    ASSERT_NE(it, book_db.end());
    ASSERT_EQ(it->title, "1984");
    it++;
    ASSERT_EQ(it->title, "The Hobbit");
    it++;
    ASSERT_EQ(it->title, "Pride and Prejudice");
    it++;
    ASSERT_EQ(it, book_db.end());
}

TEST(TestBookDb, Formatter_returns_book_friendly_text) {
    BookDatabase book_db{{"1984", "George Orwell", 1949, Genre::SciFi, 4., 190},
                         {"The Hobbit", "J.R.R. Tolkien", 1937, Genre::Fiction, 4.9, 203},
                         {"Pride and Prejudice", "Jane Austen", 1813, Genre::Fiction, 4.7, 178}};

    ASSERT_EQ(std::format("{}", book_db),
              "BookDatabase (size = 3): Books:\n- George Orwell '1984' [year:1949, genre:'SciFi', rating:4.0, "
              "reads:190]\n- J.R.R. Tolkien 'The Hobbit' [year:1937, genre:'Fiction', rating:4.9, reads:203]\n- Jane "
              "Austen 'Pride and Prejudice' [year:1813, genre:'Fiction', rating:4.7, reads:178]\nAuthors:\n- Jane "
              "Austen\n- J.R.R. Tolkien\n- George Orwell\n");
}