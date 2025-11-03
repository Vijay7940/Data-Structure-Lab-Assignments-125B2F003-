#include <iostream>
#include <string>
using namespace std;
#define MAX 5 

class Order {
public:
    int orderID;
    string customerName;
    string items;

    // Constructor with default values
    Order(int id = 0, string name = "", string it = "") {
        orderID = id;
        customerName = name;
        items = it;
    }

    void display() {
        cout << "Order ID: " << orderID << ", Customer: " << customerName << ", Items: " << items << endl;
    }
};


class CircularQueue {
private:
    Order orders[MAX];  //Array to stroe orders
    int front;
    int rear;
    int count; // Number of current orders in queue

public:
	// Constructor to initialize queue
    CircularQueue() {
        front = 0;
        rear = -1;
        count = 0;
    }

    // Method check if queue is full or not 
    bool isFull() {
        return count == MAX;
    }

    // Method to check if queue is empty or not
    bool isEmpty() {
        return count == 0;
    }

    // Method to Add a new order
    void addOrder(int id, string name, string items) {
        if (isFull()) {
            cout << "Drive-thru lane is full. Cannot add more orders.\n";
            return;
        }
        rear = (rear + 1) % MAX;   // To move the rear pointer circularly
        orders[rear] = Order(id, name, items);
        count++;
        cout << "Order added for " << name << endl;
    }

    // Method to process the next order
    void processOrder() {
        if (isEmpty()) {
            cout << "No orders to process!\n";
            return;
        }
        cout << "Processing order:\n";
        orders[front].display();
        front = (front + 1) % MAX;     // To move front pointer circularly
        count--;
    }

    // Method for displaying all pending orders
    void displayOrders() {
        if (isEmpty()) {
            cout << "No pending orders.\n";
            return;
        }

        cout << "Pending Orders:\n";
        int idx = front;
        for (int i = 0; i < count; i++) {
            orders[idx].display();
            idx = (idx + 1) % MAX;
        }
    }
};

// Main function - menu driven
int main() {
    CircularQueue driveThru;
    int choice;

    // Initial orders
    driveThru.addOrder(101, "Rahul Sharma", "Burger, Fries, Drink");
    driveThru.addOrder(102, "Priya Patel", "Chicken Sandwich, Salad, Drink");
    driveThru.addOrder(103, "Aarav Gupta", "Pizza, Wings, Drink");

    do {
        cout << "\n===== DRIVE-THRU MENU =====\n";
        cout << "1. Add New Order\n";
        cout << "2. Process Next Order\n";
        cout << "3. Display Pending Orders\n";
        cout << "4. Exit\n";
        cout << "============================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); 

        switch (choice) {
            case 1: {
                int id;
                string name, items;
                cout << "Enter Order ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Customer Name: ";
                getline(cin, name);
                cout << "Enter Items: ";
                getline(cin, items);
                driveThru.addOrder(id, name, items);
                break;
            }
            case 2:
                driveThru.processOrder();
                break;
            case 3:
                driveThru.displayOrders();
                break;
            case 4:
                cout << "Exiting... Thank you!\n";
                break;
            default:
                cout << "Invalid choice! Try again\n";
        }
    } while (choice != 4);

    return 0;
}

