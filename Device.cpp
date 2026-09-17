#include "Device.h"
#include <iostream>

Device::Device(int id, const std::string& title, const std::string& location)
    : Item(id, title), location(location) {}

std::string Device::getLocation() const {
    return location;
}

std::string Device::getType() const {
    return "Device";
}

void Device::display() const {
    std::cout << "[Device] " << getId() << " | " << getTitle() << " | " << location << " | "
              << (isBorrowed() ? "borrowed" : "available") << std::endl;
}