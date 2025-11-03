#include <iostream>
#include <queue>
#include <string>
using namespace std;

class ServiceRequest {
public:
    int requestID;
    string customerName;
    string serviceType;

    // Constructor to initialize values
    ServiceRequest(int id, string name, string type) {
        requestID = id;
        customerName = name;
        serviceType = type;
    }

    // Method to display attributes
    void display() {
        cout << "Request ID: " << requestID << ", Customer Name: " << customerName << ", Service Type: " << serviceType << endl;
    }
};


class CallCenter {
private:
    queue<ServiceRequest> requestQueue;

public:
	
    // Method to Add new request
    void addRequest(int id, string name, string type) {
        ServiceRequest req(id, name, type);
        requestQueue.push(req);
        cout << "Request added for " << name << endl;
    }

    // Method to process next request
    void processRequest() {
        if (!requestQueue.empty()) {
            cout << "Processing request:\n";
            ServiceRequest req = requestQueue.front();
            req.display();
            requestQueue.pop();
        } else {
            cout << "No pending requests!\n";
        }
    }

    // Method to Display all pending requests
    void displayRequests() {
        if (requestQueue.empty()) {
            cout << "No pending requests!\n";
            return;
        }

        cout << "Pending Requests:\n";
        queue<ServiceRequest> temp = requestQueue; // Copy to traverse
        while (!temp.empty()) {
            temp.front().display();
            temp.pop();
        }
    }
};

// Main function - menu driven
int main() {
    CallCenter center;
    int choice;

    // Initial requests
    center.addRequest(101, "John Doe", "Technical Support");
    center.addRequest(102, "Jane Smith", "Billing Inquiry");
    center.addRequest(103, "David Brown", "Product Information");

    do {
        cout << "\n===== CALL CENTER MENU =====\n";
        cout << "1. Add New Request\n";
        cout << "2. Process Next Request\n";
        cout << "3. Display All Pending Requests\n";
        cout << "4. Exit\n";
        cout << "============================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id;
                string name, type;
                cout << "Enter Request ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Customer Name: ";
                getline(cin, name);
                cout << "Enter Service Type: ";
                getline(cin, type);
                center.addRequest(id, name, type);
                break;
            }
            case 2:
                center.processRequest();
                break;
            case 3:
                center.displayRequests();
                break;
            case 4:
                cout << "Exiting... Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Try again\n";
        }

    } while (choice != 4);

    return 0;
}

