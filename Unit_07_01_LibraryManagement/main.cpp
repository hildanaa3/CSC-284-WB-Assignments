#include "Library.h"
#include <iostream>
#include <ranges>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
using namespace std::views;

int main()
{
    Library lib;

    lib.add_book(Book{"The Hobbit", "J. R. R. Tolkien", 1937, "Fantasy"});
    lib.add_book(Book{"Dune", "Frank Herbert", 1965, "Sci-Fi"});
    lib.add_book(Book{"Foundation", "Isaac Asimov", 1951, "Sci-Fi"});
    lib.add_book(Book{"The Fellowship of the Ring", "J. R. R. Tolkien", 1954, "Fantasy"});
    lib.add_book(Book{"Pride and Prejudice", "Jane Austen", 1813, "Romance"});

    cout << "All books (iterator traversal):\n";
    lib.print_all_iterator();

    vector<string> titles;

    for (const auto &t : lib.get_books_by_genre("Sci-Fi") | transform([](const Book &b)
                                                                      { return b.title(); }))
    {
        titles.push_back(t);
    }
    if (auto it = find(titles.begin(), titles.end(), "Dune"); it != titles.end())
    {
        cout << "\nFound title with std::find: " << *it << "\n";
    }

    if (auto b = lib.find_book("The Hobbit"))
    {
        cout << "\nfind_book: " << *b << "\n";
    }
    else
    {
        cout << "\nfind_book: not found\n";
    }

    bool removed = lib.remove_book("Foundation");
    cout << "\nRemoved Foundation? " << (removed ? "yes" : "no") << "\n";

    auto tolkien = lib.get_books_by_author("J. R. R. Tolkien");
    cout << "\nBooks by Tolkien:\n";
    for (const auto &b : tolkien)
        cout << "  " << b << "\n";

    auto modern = lib.books_published_after(1950);
    cout << "\nBooks after 1950:\n";
    for (const auto &b : modern)
        cout << "  " << b << "\n";

    auto fantasy_sorted = lib.genre_sorted_by_year("Fantasy", true);
    cout << "\nFantasy sorted by year:\n";
    for (const auto &b : fantasy_sorted | transform([](const Book &x)
                                                    { return x; }))
    {
        cout << "  " << b << "\n";
    }

    lib.sort_by_year(false);
    cout << "\nLibrary sorted by year (desc):\n";
    lib.print_all_iterator();

    return 0;
}
