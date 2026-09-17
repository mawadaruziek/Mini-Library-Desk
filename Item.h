#pragma once
#include <iostream>
#include <string>

class Item {
    int id;
    std::string title;
    bool borrowed;

public:
    Item(int id, const std::string& title);
    virtual ~Item() {}

    int getId() const;
    std::string getTitle() const;
    bool isBorrowed() const;

    void borrow();
    void giveBack();
    
    virtual std::string getType() const = 0;
    virtual void display() const = 0;
};