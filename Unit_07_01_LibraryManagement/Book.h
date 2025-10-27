#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>
#include <utility>
using namespace std;

class Book
{
public:
    Book() = default;
    Book(string title, string author, int year, string genre)
        : title_(std::move(title)),
          author_(std::move(author)),
          year_(year),
          genre_(std::move(genre)) {}

    const string &title() const { return title_; }
    const string &author() const { return author_; }
    int year() const { return year_; }
    const string &genre() const { return genre_; }

    void display(ostream &os = cout) const
    {
        os << title_ << " by " << author_ << " (" << year_ << ") [" << genre_ << "]";
    }

private:
    string title_;
    string author_;
    int year_ = 0;
    string genre_;
};

inline ostream &operator<<(ostream &os, const Book &b)
{
    b.display(os);
    return os;
}

#endif
