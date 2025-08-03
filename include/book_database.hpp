#pragma once

#include "book.hpp"
#include "concepts.hpp"
#include "heterogeneous_lookup.hpp"
#include <print>
#include <string>
#include <unordered_set>
#include <vector>

namespace bookdb {

template <BookContainerLike BookContainer = std::vector<Book>>
class BookDatabase {
public:
    using value_type = typename BookContainer::value_type;
    using iterator = typename BookContainer::iterator;
    using const_iterator = typename BookContainer::const_iterator;
    using size_type = typename BookContainer::size_type;
    using reference = typename BookContainer::reference;
    using const_reference = typename BookContainer::const_reference;

    using AuthorContainer = std::unordered_set<std::string, TransparentStringHash, TransparentStringEqual>;

    BookDatabase() = default;

    void Clear() {
        books_.clear();
        authors_.clear();
    }

    // Standard container interface methods

    // Ваш код здесь

    BookDatabase(std::initializer_list<Book> init) {
        for (const auto &book : init) {
            PushBack(book);
        }
    }

    void PushBack(const Book &book) {
        books_.push_back(book);
        authors_.insert(std::string(book.author));
    }

    template <typename... Args>
    void EmplaceBack(Args &&...args) {
        books_.emplace_back(std::forward<Args>(args)...);
        authors_.insert(std::string(books_.back().author));
    }

    iterator begin() { return books_.begin(); }
    const_iterator begin() const { return books_.begin(); }
    iterator end() { return books_.end(); }
    const_iterator end() const { return books_.end(); }
    size_type size() const { return books_.size(); }
    bool empty() const { return books_.empty(); }
    reference operator[](size_type pos) { return books_[pos]; }
    const_reference operator[](size_type pos) const { return books_[pos]; }
    reference at(size_type pos) { return books_.at(pos); }
    const_reference at(size_type pos) const { return books_.at(pos); }

    const BookContainer &GetBooks() const { return books_; }
    const AuthorContainer &GetAuthors() const { return authors_; }

private:
    BookContainer books_;
    AuthorContainer authors_;
};

}  // namespace bookdb

namespace std {
template <>
struct formatter<bookdb::BookDatabase<std::vector<bookdb::Book>>> {
    template <typename FormatContext>
    auto format(const bookdb::BookDatabase<std::vector<bookdb::Book>> &db, FormatContext &fc) const {
        /*
        Раскомментируйте, когда bookdb::BookDatabase поддержит интерфейсы, доступные стандартным контейнерам
        (size/begin/...)*/

        format_to(fc.out(), "BookDatabase (size = {}): ", db.size());

        format_to(fc.out(), "Books:\n");
        for (const auto &book : db.GetBooks()) {
            format_to(fc.out(), "- {}\n", book);
        }

        format_to(fc.out(), "Authors:\n");
        for (const auto &author : db.GetAuthors()) {
            format_to(fc.out(), "- {}\n", author);
        }

        return fc.out();
    }

    constexpr auto parse(format_parse_context &ctx) {
        return ctx.begin();  // Просто игнорируем пользовательский формат
    }
};
}  // namespace std
