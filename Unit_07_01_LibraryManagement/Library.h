#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include <vector>
#include <string>
#include <optional>
using namespace std;

class Library
{
public:
    void add_book(const Book &book);
    bool remove_book(const string &title);

    optional<Book> find_book(const string &title) const;

    vector<Book> get_books_by_author(const string &author) const;

    vector<Book> get_books_by_genre(const string &genre) const;

    vector<Book> books_published_after(int year) const;

    vector<Book> genre_sorted_by_year(const string &genre, bool ascending = true) const;

    void print_all_iterator() const;

    void sort_by_year(bool ascending = true);

private:
    vector<Book> books_;
};

#endif
