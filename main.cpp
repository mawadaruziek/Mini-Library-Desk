/*
 * Course: Eduvera - Intro to Programming using C++
 * Task: Mini Library Desk - Final Project
 * Name: Mawada Rabie
 * Student ID: 2500910
 */


#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Book.h"
#include "Device.h"

using namespace std;

Item* findById(const vector<Item*>& shelf, int id) {
    for (Item* item : shelf) {
        if (item->getId() == id) {
            return item;
        }
    }
    return nullptr;
}

void freeShelf(vector<Item*>& shelf) {
    for (Item* item : shelf) {
        delete item;
    }
    shelf.clear();
}

int main() {
    vector<Item*> shelf;
    int choice = -1;

    while (choice != 0) {
        cout << "=====Mini Library Desk=====\n"
             << "1. Add book\n"
             << "2. Add device\n"
             << "3. List all\n"
             << "4. Find by ID\n"
             << "5. Borrow\n"
             << "6. Return\n"
             << "7. Delete\n"
             << "8. Save\n"
             << "9. Load\n"
             << "0. Quit\n"
             << "Choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            string ignore;
            cin >> ignore;
            cout << "Invalid choice." << endl;
            continue;
        }

        switch (choice) {
            case 1: {
                int id;
                string title, author;
                cout << "ID: ";
                cin >> id;
                if (findById(shelf, id) != nullptr) {
                    cout << "ID already exists" << endl;
                    break;
                }
                cout << "Title: ";
                cin >> title;
                cout << "Author: ";
                cin >> author;

                shelf.push_back(new Book(id, title, author));
                cout << "Added." << endl;
                break;
            }
            case 2: {
                int id;
                string title, location;
                cout << "ID: ";
                cin >> id;
                if (findById(shelf, id) != nullptr) {
                    cout << "ID already exists" << endl;
                    break;
                }
                cout << "Title: ";
                cin >> title;
                cout << "Location: ";
                cin >> location;

                shelf.push_back(new Device(id, title, location));
                cout << "Added." << endl;
                break;
            }
            case 3: {
                if (shelf.empty()) {
                    cout << "Shelf is empty." << endl;
                } else {
                    for (const Item* item : shelf) {
                        item->display();
                    }
                }
                break;
            }
            case 4: {
                int id;
                cout << "ID: ";
                cin >> id;
                Item* item = findById(shelf, id);
                if (item != nullptr) {
                    item->display();
                } else {
                    cout << "ID not found" << endl;
                }
                break;
            }
            case 5: {
                int id;
                cout << "ID: ";
                cin >> id;
                Item* item = findById(shelf, id);
                if (item == nullptr) {
                    cout << "ID not found" << endl;
                } else if (item->isBorrowed()) {
                    cout << "Already borrowed" << endl;
                } else {
                    item->borrow();
                    cout << "Borrowed." << endl;
                }
                break;
            }
            case 6: {
                int id;
                cout << "ID: ";
                cin >> id;
                Item* item = findById(shelf, id);
                if (item == nullptr) {
                    cout << "ID not found" << endl;
                } else if (!item->isBorrowed()) {
                    cout << "Not borrowed" << endl;
                } else {
                    item->giveBack();
                    cout << "Returned." << endl;
                }
                break;
            }
            case 7: {
                int id;
                cout << "ID: ";
                cin >> id;
                bool found = false;
                for (auto it = shelf.begin(); it != shelf.end(); ++it) {
                    if ((*it)->getId() == id) {
                        delete *it;
                        shelf.erase(it);
                        cout << "Removed." << endl;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "ID not found" << endl;
                }
                break;
            }
            case 8: { 
                ofstream outFile("library.csv");
                if (outFile.is_open()) {
                    for (Item* item : shelf) {
                        
                        if (item->getType() == "Book") {
                            Book* b = (Book*)item; 
                            outFile << "B," << b->getId() << "," << b->getTitle() << ","
                                    << b->getAuthor() << "," << (b->isBorrowed() ? 1 : 0) << "\n";
                        } else if (item->getType() == "Device") {
                            Device* d = (Device*)item; 
                            outFile << "D," << d->getId() << "," << d->getTitle() << ","
                                    << d->getLocation() << "," << (d->isBorrowed() ? 1 : 0) << "\n";
                        }
                    }
                    outFile.close();
                    cout << "Saved." << endl;
                }
                break;
            }
            case 9: {
                freeShelf(shelf);
                ifstream inFile("library.csv");
                if (!inFile.is_open()) {
                    cout << "No library file yet." << endl;
                } else {
                    string line;
                    while (getline(inFile, line)) {
                        if (line.empty()) continue;
                        stringstream ss(line);
                        string type, idStr, title, extra, borrowedStr;

                        if (getline(ss, type, ',') &&
                            getline(ss, idStr, ',') &&
                            getline(ss, title, ',') &&
                            getline(ss, extra, ',') &&
                            getline(ss, borrowedStr, ',')) {

                            int id = stoi(idStr);
                            int borrowed = stoi(borrowedStr);

                            if (type == "B") {
                                Book* b = new Book(id, title, extra);
                                if (borrowed == 1) b->borrow();
                                shelf.push_back(b);
                            } else if (type == "D") {
                                Device* d = new Device(id, title, extra);
                                if (borrowed == 1) d->borrow();
                                shelf.push_back(d);
                            }
                        }
                    }
                    inFile.close();
                    cout << "Loaded." << endl;
                }
                break;
            }
            case 0:
                freeShelf(shelf);
                break;

            default:
                cout << "Invalid choice." << endl;
                break;
        }
    }

    return 0;
}
