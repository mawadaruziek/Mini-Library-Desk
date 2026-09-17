#include "Book.h"
#include <iostream>

Book::Book(int id, const std::string& title, const std::string& author)
    : Item(id, title), author(author) {}

std::string Book::getAuthor() const {
    return author;
}

std::string Book::getType() const {
    return "Book";
}

void Book::display() const {
    std::cout << "[Book] " << getId() << " | " << getTitle() << " | " << author << " | "
              << (isBorrowed() ? "borrowed" : "available") << std::endl;
}