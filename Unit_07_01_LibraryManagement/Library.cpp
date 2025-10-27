#include "Library.h"
#include <algorithm>
#include <ranges>
#include <iostream>
#include <optional>

using namespace std;
using namespace std::views;

void Library::add_book(const Book &book)
{
    books_.push_back(book);
}

bool Library::remove_book(const string &title)
{
    auto old_size = books_.size();
    auto it = remove_if(books_.begin(), books_.end(),
                        [&](const Book &b)
                        { return b.title() == title; });
    books_.erase(it, books_.end());
    return books_.size() != old_size;
}

optional<Book> Library::find_book(const string &title) const
{

    if (auto it = ranges::find(books_, title, &Book::title); it != books_.end())
    {
        return *it;
    }
    return nullopt;
}

vector<Book> Library::get_books_by_author(const string &author) const
{

    vector<Book> result;
    for (auto it = books_.begin(); it != books_.end(); ++it)
    {
        if (it->author() == author)
            result.push_back(*it);
    }
    return result;
}

vector<Book> Library::get_books_by_genre(const string &genre) const
{

    vector<Book> result;
    for (const auto &b : books_ | filter([&](const Book &bk)
                                         { return bk.genre() == genre; }))
    {
        result.push_back(b);
    }
    return result;
}

vector<Book> Library::books_published_after(int year) const
{

    vector<Book> result;
    for (const auto &b : books_ | filter([&](const Book &bk)
                                         { return bk.year() > year; }))
    {
        result.push_back(b);
    }
    return result;
}

vector<Book> Library::genre_sorted_by_year(const string &genre, bool ascending) const
{

    vector<Book> filtered;
    for (const auto &b : books_ | filter([&](const Book &bk)
                                         { return bk.genre() == genre; }))
    {
        filtered.push_back(b);
    }
    ranges::sort(filtered, [&](const Book &a, const Book &b)
                 { return ascending ? a.year() < b.year() : a.year() > b.year(); });
    return filtered;
}

void Library::print_all_iterator() const
{

    for (auto it = books_.begin(); it != books_.end(); ++it)
    {
        it->display();
        cout << '\n';
    }
}

void Library::sort_by_year(bool ascending)
{
    ranges::sort(books_, [&](const Book &a, const Book &b)
                 { return ascending ? a.year() < b.year() : a.year() > b.year(); });
}
