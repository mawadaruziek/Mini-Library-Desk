#include "Item.h"

Item::Item(int id, const std::string& title)
    : id(id), title(title), borrowed(false) {}

int Item::getId() const {
    return id;
}

std::string Item::getTitle() const {
    return title;
}

bool Item::isBorrowed() const {
    return borrowed;
}

void Item::borrow() {
    borrowed = true;
}

void Item::giveBack() {
    borrowed = false;
}