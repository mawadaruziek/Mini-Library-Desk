#pragma once
#include "Item.h"

class Book : public Item {
    std::string author;

public:
    Book(int id, const std::string& title, const std::string& author);
    std::string getAuthor() const;
    
    std::string getType() const override;
    void display() const override;
};