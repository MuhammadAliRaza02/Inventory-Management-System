#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// Product Structure
struct Product {
    int id;
    string name;
    int quantity;
    double price;
};

vector<Product> inventory; // List to store products

// Function to load data from file
void loadInventory() {
    ifstream file("inventory.txt");
    if (file) {
        Product p;
        while (file >> p.id >> p.name >> p.quantity >> p.price) {
            inventory.push_back(p);
        }
    }
    file.close();
}

// Function to save data to file
void saveInventory() {
    ofstream file("inventory.txt");
    for (Product p : inventory) {
        file << p.id << " " << p.name << " " << p.quantity << " " << p.price << endl;
    }
    file.close();
}

// Function to authenticate user
bool authenticate() {
    string username, password;
    cout << "Enter username: "; cin >> username;
    cout << "Enter password: "; cin >> password;
    return (username == "admin" && password == "1234");
}

// Function to add a new product
void addProduct() {
    Product p;
    cout << "Enter Product ID: "; cin >> p.id;
    cout << "Enter Product Name: "; cin >> p.name;
    cout << "Enter Quantity: "; cin >> p.quantity;
    cout << "Enter Price: "; cin >> p.price;
    inventory.push_back(p);
    saveInventory();
    cout << "Product Added Successfully!\n";
}

// Function to view product list
void viewProducts() {
    cout << "\nID\tName\tQuantity\tPrice\n";
    for (Product p : inventory) {
        cout << p.id << "\t" << p.name << "\t" << p.quantity << "\t" << p.price << "\n";
    }
}

// Function to update a product
void updateProduct() {
    int id, newQuantity;
    double newPrice;
    cout << "Enter Product ID to Update: "; cin >> id;
    for (Product &p : inventory) {
        if (p.id == id) {
            cout << "Enter New Quantity: "; cin >> newQuantity;
            cout << "Enter New Price: "; cin >> newPrice;
            p.quantity = newQuantity;
            p.price = newPrice;
            saveInventory();
            cout << "Product Updated Successfully!\n";
            return;
        }
    }
    cout << "Product Not Found!\n";
}

// Function to delete a product
void deleteProduct() {
    int id;
    cout << "Enter Product ID to Delete: "; cin >> id;
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if (it->id == id) {
            inventory.erase(it);
            saveInventory();
            cout << "Product Deleted Successfully!\n";
            return;
        }
    }
    cout << "Product Not Found!\n";
}

// Function to check stock
void checkStock() {
    cout << "Low Stock Products (less than 5 units):\n";
    for (Product p : inventory) {
        if (p.quantity < 5)
            cout << p.id << " " << p.name << " " << p.quantity << "\n";
    }
}

int main() {
    loadInventory();
    if (!authenticate()) {
        cout << "Access Denied!\n";
        return 0;
    }
    int choice;
    do {
        cout << "\n1. Add Product\n2. View Products\n3. Update Product\n4. Delete Product\n5. Check Stock\n6. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addProduct(); break;
            case 2: viewProducts(); break;
            case 3: updateProduct(); break;
            case 4: deleteProduct(); break;
            case 5: checkStock(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 6);
    return 0;
}
