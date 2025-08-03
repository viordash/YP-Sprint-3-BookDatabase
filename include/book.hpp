#pragma once

#include <flat_map>
#include <format>
#include <stdexcept>
#include <string_view>

namespace bookdb {

enum class Genre { Fiction, NonFiction, SciFi, Biography, Mystery, Unknown };

// Ваш код для constexpr преобразования строк в enum::Genre и наоборот здесь

constexpr Genre GenreFromString(std::string_view s) {
    if (s == "Fiction") {
        return Genre::Fiction;
    }
    if (s == "NonFiction") {
        return Genre::NonFiction;
    }
    if (s == "SciFi") {
        return Genre::SciFi;
    }
    if (s == "Biography") {
        return Genre::Biography;
    }
    if (s == "Mystery") {
        return Genre::Mystery;
    }
    return Genre::Unknown;
}

struct Book {
    // string_view для экономии памяти, чтобы ссылаться на оригинальную строку, хранящуюся в другом контейнере
    std::string_view author;
    std::string title;

    int year;
    Genre genre;
    double rating;
    int read_count;

    // Ваш код для конструкторов здесь
    Book(std::string_view title, std::string_view author, int year, std::string_view genre_str, double rating,
         int read_count)
        : author(author), title(title), year(year), genre(GenreFromString(genre_str)), rating(rating),
          read_count(read_count) {}

    Book(std::string_view title, std::string_view author, int year, Genre genre, double rating, int read_count)
        : author(author), title(title), year(year), genre(genre), rating(rating), read_count(read_count) {}

    bool operator==(const Book &) const = default;
};
}  // namespace bookdb

namespace std {
template <>
struct formatter<bookdb::Genre, char> {
    template <typename FormatContext>
    auto format(const bookdb::Genre g, FormatContext &fc) const {
        std::string genre_str;

        // clang-format off
        using bookdb::Genre;
        switch (g) {
            case Genre::Fiction:    genre_str = "Fiction"; break;
            case Genre::Mystery:    genre_str = "Mystery"; break;
            case Genre::NonFiction: genre_str = "NonFiction"; break;
            case Genre::SciFi:      genre_str = "SciFi"; break;
            case Genre::Biography:  genre_str = "Biography"; break;
            case Genre::Unknown:    genre_str = "Unknown"; break;
            default:
                throw logic_error{"Unsupported bookdb::Genre"};
            }
        // clang-format on
        return format_to(fc.out(), "{}", genre_str);
    }

    constexpr auto parse(format_parse_context &ctx) {
        return ctx.begin();  // Просто игнорируем пользовательский формат
    }
};

// Ваш код для std::formatter<Book> здесь
template <>
struct formatter<bookdb::Book, char> {
    template <typename FormatContext>
    auto format(const bookdb::Book &book, FormatContext &fc) const {
        return format_to(fc.out(), "{} '{}' [year:{}, genre:'{}', rating:{:.1f}, reads:{}]", book.author, book.title,
                         book.year, book.genre, book.rating, book.read_count);
    }

    constexpr auto parse(format_parse_context &ctx) {
        return ctx.begin();  // Просто игнорируем пользовательский формат
    }
};

template <>
struct formatter<flat_map<bookdb::Genre, double>> {
    template <typename FormatContext>
    auto format(const flat_map<bookdb::Genre, double> &genre_map, FormatContext &fc) const {
        auto out = fc.out();

        for (auto it = genre_map.begin(); it != genre_map.end(); ++it) {
            const auto &[genre, rating] = *it;
            out = format_to(out, "{}: {:.1f}", genre, rating);
            bool put_delimeter = std::next(it) != genre_map.end();
            if (put_delimeter) {
                out = format_to(out, ", ");
            }
        }
        return out;
    }

    constexpr auto parse(format_parse_context &ctx) { return ctx.begin(); }
};
}  // namespace std
