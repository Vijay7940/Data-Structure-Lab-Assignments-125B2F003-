#include <iostream>
#include <string>
using namespace std;

#define MAX 100  

struct Product {
    int id;             
    string name;        
    int quantity;      
    float price;       
    Product* related;   
};

class Inventory {
private:
    Product items[MAX]; // Array to store products
    int count;          // No of product

public:
    // To initialize product count to 0
    Inventory() { count = 0; }

    // Method to Adda a new product
    void addProduct(int id, string name, int qty, float price) {
        if (count < MAX) { 
            items[count].id = id;
            items[count].name = name;
            items[count].quantity = qty;
            items[count].price = price;
            items[count].related = NULL; 
            count++;
            cout << "Product added: " << name << endl;
        } else {
            cout << "Inventory full, Cannot add more products\n";
        }
    }

    // Method to Update quantity of product
    void updateQuantity(int id, int newQty) {
        for (int i = 0; i < count; i++) {
            if (items[i].id == id) {  
                items[i].quantity = newQty;
                cout << "Quantity updated for " << items[i].name << " to " << newQty << endl;
                return;
            }
        }
        cout << "Product ID not found!\n";
    }

    // Method to Link two products
    void linkRelated(int id1, int id2) {
        Product* p1 = NULL;
        Product* p2 = NULL;

        // Searching for both products
        for (int i = 0; i < count; i++) {
            if (items[i].id == id1) p1 = &items[i];
            if (items[i].id == id2) p2 = &items[i];
        }

        // Link if exist
        if (p1 != NULL && p2 != NULL && p1 != p2) {
            p1->related = p2;
            p2->related = p1;
            cout << "Linked " << p1->name << " <-> " << p2->name << endl;
        } 
        else {
            cout << "Invalid product IDs for linking\n";
        }
    }

    // Method to Display all products
    void displayProducts() {
        if (count == 0) {
            cout << "No products in inventory.\n";
            return;
        }

        cout << "\nCurrent Inventory:\n";

        for (int i = 0; i < count; i++) {
            // Display product details
            cout << items[i].id << " | "
                 << items[i].name << " | "
                 << items[i].quantity << " | $"
                 << items[i].price << " | ";

            // Display related product if exists
            if (items[i].related != NULL)
                cout << "Related: " << items[i].related->name;

            cout << '\n';
        }
    }

    // Method to calculate total inventory value
    void totalInventoryValue() {
        float total = 0;
        for (int i = 0; i < count; i++)
            total += items[i].quantity * items[i].price;

        cout << "Total Inventory Value = $" << total << "\n";
    }
};

int main() {
    Inventory warehouse; 
    int choice;

    do {
        //Menu 
        cout << "\nINVENTORY MENU\n";
        cout << "1. Add New Product\n2. Update Product Quantity\n";
        cout << "3. Link Related Products\n4. Display All Products\n";
        cout << "5. Show Total Inventory Value\n6. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            int id, qty; 

        case 1: { 
            string name;
            float price;
            cout << "Enter Product ID: ";
            cin >> id;
            cin.ignore(); 
            cout << "Enter Product Name: ";
            getline(cin, name);
            cout << "Enter Quantity: ";
            cin >> qty;
            cout << "Enter Price: ";
            cin >> price;
            warehouse.addProduct(id, name, qty, price);
            break;
        }

        case 2: { 
            cout << "Enter Product ID to Update: ";
            cin >> id;
            cout << "Enter New Quantity: ";
            cin >> qty;
            warehouse.updateQuantity(id, qty);
            break;
        }

        case 3: {
            int id1, id2;
            cout << "Enter first Product ID: ";
            cin >> id1;
            cout << "Enter second Product ID: ";
            cin >> id2;
            warehouse.linkRelated(id1, id2);
            break;
        }

        case 4:
            warehouse.displayProducts();
            break;

        case 5:
            warehouse.totalInventoryValue();
            break;

        case 6: 
            cout << "Exiting... Thank you!\n";
            break;

        default:
            cout << "Invalid choice! Please try again\n";
        }
    } while (choice != 6);

    return 0;
}

