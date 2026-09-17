#pragma once
#include "Item.h"

class Device : public Item {
    std::string location;

public:
    Device(int id, const std::string& title, const std::string& location);
    std::string getLocation() const;
    
    std::string getType() const override;
    void display() const override;
};