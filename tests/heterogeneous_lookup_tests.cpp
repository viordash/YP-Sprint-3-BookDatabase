#include "heterogeneous_lookup.hpp"
#include <concepts>
#include <gtest/gtest.h>

using namespace bookdb;

TEST(TestComparators, TransparentStringLess) {
    TransparentStringLess comp;

    static_assert(requires { typename TransparentStringLess::is_transparent; });

    ASSERT_TRUE(comp("book1", "book3"));
    ASSERT_FALSE(comp("book1", "book1"));
    ASSERT_FALSE(comp("book3", "book1"));
}

TEST(TestComparators, TransparentStringEqual) {
    TransparentStringEqual comp;

    static_assert(requires { typename TransparentStringEqual::is_transparent; });

    ASSERT_FALSE(comp("book1", "book3"));
    ASSERT_TRUE(comp("book1", "book1"));
    ASSERT_FALSE(comp("book3", "book1"));
}

TEST(TestComparators, TransparentStringHash) {
    TransparentStringHash comp;

    static_assert(requires { typename TransparentStringHash::is_transparent; });

    ASSERT_EQ(comp("book1"), std::hash<std::string_view>{}("book1"));
}