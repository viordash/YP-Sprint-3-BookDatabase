#include "heterogeneous_lookup.hpp"
#include <gtest/gtest.h>

using namespace bookdb;

TEST(TestHeterogeneous_Lookup, TransparentStringLess) {
    TransparentStringLess comp;

    static_assert(requires { typename TransparentStringLess::is_transparent; });

    ASSERT_TRUE(comp("book1", "book3"));
    ASSERT_FALSE(comp("book1", "book1"));
    ASSERT_FALSE(comp("book3", "book1"));
}

TEST(TestHeterogeneous_Lookup, TransparentStringEqual) {
    TransparentStringEqual comp;

    static_assert(requires { typename TransparentStringEqual::is_transparent; });

    ASSERT_FALSE(comp("book1", "book3"));
    ASSERT_TRUE(comp("book1", "book1"));
    ASSERT_FALSE(comp("book3", "book1"));
}

TEST(TestHeterogeneous_Lookup, TransparentStringHash) {
    TransparentStringHash comp;

    static_assert(requires { typename TransparentStringHash::is_transparent; });

    ASSERT_EQ(comp("book1"), std::hash<std::string_view>{}("book1"));
}