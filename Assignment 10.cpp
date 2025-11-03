#include <iostream>
#include <string>
#include <cmath>
using namespace std;

struct Contact {
    int id;
    string name;
    string phone;
    string email;
    Contact* left;
    Contact* right;
    int height;
};

class AVLContactTree {
private:
    Contact* root;

    // Method to create new contact node
    Contact* createContact(int id, string name, string phone, string email) {
        Contact* newContact = new Contact;
        newContact->id = id;
        newContact->name = name;
        newContact->phone = phone;
        newContact->email = email;
        newContact->left = NULL;
        newContact->right = NULL;
        newContact->height = 1;
        return newContact;
    }

    // Method to get height of a node
    int getHeight(Contact* node) {
        if (node == NULL) return 0;
        return node->height;
    }

    // Method to get balance factor of a node
    int getBalance(Contact* node) {
        if (node == NULL) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    // Helper method to get max of two integers
    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    // Method to perform right rotation
    Contact* rightRotate(Contact* y) {
        Contact* x = y->left;
        Contact* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    // Method to perform left rotation
    Contact* leftRotate(Contact* x) {
        Contact* y = x->right;
        Contact* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    // Recursive method to insert a contact into AVL tree
    Contact* insertNode(Contact* node, int id, string name, string phone, string email) {
        if (node == NULL) return createContact(id, name, phone, email);

        if (id < node->id)
            node->left = insertNode(node->left, id, name, phone, email);
        else if (id > node->id)
            node->right = insertNode(node->right, id, name, phone, email);
        else {
            cout << "Contact ID already exists" << endl;
            return node;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        if (balance > 1 && id < node->left->id) return rightRotate(node);
        if (balance < -1 && id > node->right->id) return leftRotate(node);
        if (balance > 1 && id > node->left->id) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && id < node->right->id) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    // Method to search contact by ID
    Contact* searchById(Contact* node, int id) {
        if (node == NULL) return NULL;
        if (id == node->id) return node;
        else if (id < node->id) return searchById(node->left, id);
        else return searchById(node->right, id);
    }

    // Method to search contact by name
    void searchByName(Contact* node, string name) {
        if (node == NULL) return;
        searchByName(node->left, name);
        if (node->name == name) displayContact(node);
        searchByName(node->right, name);
    }

    // Method to search contact by phone
    void searchByPhone(Contact* node, string phone) {
        if (node == NULL) return;
        searchByPhone(node->left, phone);
        if (node->phone == phone) displayContact(node);
        searchByPhone(node->right, phone);
    }

    // Method to search contact by email
    void searchByEmail(Contact* node, string email) {
        if (node == NULL) return;
        searchByEmail(node->left, email);
        if (node->email == email) displayContact(node);
        searchByEmail(node->right, email);
    }

    // Method to display a single contact
    void displayContact(Contact* contact) {
        cout << "Contact ID: " << contact->id << endl;
        cout << "Name: " << contact->name << endl;
        cout << "Phone: " << contact->phone << endl;
        cout << "Email: " << contact->email << endl;
        cout << endl;
    }

    // Method for inorder traversal to display all contacts
    void inorderDisplay(Contact* node) {
        if (node != NULL) {
            inorderDisplay(node->left);
            displayContact(node);
            inorderDisplay(node->right);
        }
    }

    // Method to display AVL tree structure
    void displayTreeStructure(Contact* node, string prefix, bool isLeft) {
        if (node == NULL) return;
        cout << prefix;
        cout << (isLeft ? "+--" : "+--");
        cout << node->name << "(" << node->id << ")" << " [H:" << node->height << "]" << endl;
        displayTreeStructure(node->left, prefix + (isLeft ? "¦   " : "    "), true);
        displayTreeStructure(node->right, prefix + (isLeft ? "¦   " : "    "), false);
    }

    // Method to destroy all nodes recursively (destructor)
    void destroyTree(Contact* node) {
        if (node != NULL) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    AVLContactTree() : root(NULL) {}
    ~AVLContactTree() { destroyTree(root); }

    // Method to add contact
    void addContact(int id, string name, string phone, string email) {
        root = insertNode(root, id, name, phone, email);
        cout << "Contact added: " << name << endl;
    }

    // Methods to search contact
    void searchContactById(int id) {
        Contact* result = searchById(root, id);
        if (result != NULL) {
            cout << "Contact found:" << endl;
            displayContact(result);
        } else {
            cout << "Contact not found" << endl;
        }
    }

    void searchContactByName(string name) {
        cout << "Contact found: " << name << endl;
        searchByName(root, name);
    }

    void searchContactByPhone(string phone) {
        cout << "Contact found: " << phone << endl;
        searchByPhone(root, phone);
    }

    void searchContactByEmail(string email) {
        cout << "Contact found: " << email << endl;
        searchByEmail(root, email);
    }

    // Method to update a contact
    void updateContact(int id, string newName, string newPhone, string newEmail) {
        Contact* contact = searchById(root, id);
        if (contact != NULL) {
            if (!newName.empty()) contact->name = newName;
            if (!newPhone.empty()) contact->phone = newPhone;
            if (!newEmail.empty()) contact->email = newEmail;
            cout << "Contact updated successfully" << endl;
            displayContact(contact);
        } else {
            cout << "Contact not found" << endl;
        }
    }

    // Method to display all contacts
    void displayAllContacts() {
        cout << "=== All Contacts ===" << endl;
        inorderDisplay(root);
    }

    // Method to display AVL tree structure
    void displayTree() {
        cout << "=== AVL Tree Structure ===" << endl;
        if (root == NULL) {
            cout << "Tree is empty" << endl;
            return;
        }
        displayTreeStructure(root, "", false);
    }

    // Method to check balance only at root
    void checkBalance() {
        cout << "Tree height: " << getHeight(root) << endl;
        cout << "Tree is balanced: " << (abs(getBalance(root)) <= 1 ? "Yes" : "No") << endl;
    }
};

// ------------------ MAIN MENU ------------------
int main() {
    AVLContactTree contacts;
    int choice;

    cout << "\n===== Contact Management Menu =====" << endl;
    cout << "1. Add Contact\n2. Search Contact by ID\n3. Search Contact by Name\n";
    cout << "4. Search Contact by Phone\n5. Search Contact by Email\n6. Update Contact\n";
    cout << "7. Display All Contacts\n8. Display AVL Tree Structure\n9. Check Tree Balance\n";
    cout << "10. Exit" << endl;

    do {
        cout << "Enter your choice: ";
        cin >> choice;

        int id;
        string name, phone, email;

        switch (choice) {
        case 1:
            cout << "Enter ID: "; cin >> id;
            cin.ignore();
            cout << "Enter Name: "; getline(cin, name);
            cout << "Enter Phone: "; getline(cin, phone);
            cout << "Enter Email: "; getline(cin, email);
            contacts.addContact(id, name, phone, email);
            break;
        case 2:
            cout << "Enter ID to search: "; cin >> id;
            contacts.searchContactById(id);
            break;
        case 3:
            cin.ignore();
            cout << "Enter Name to search: "; getline(cin, name);
            contacts.searchContactByName(name);
            break;
        case 4:
            cin.ignore();
            cout << "Enter Phone to search: "; getline(cin, phone);
            contacts.searchContactByPhone(phone);
            break;
        case 5:
            cin.ignore();
            cout << "Enter Email to search: "; getline(cin, email);
            contacts.searchContactByEmail(email);
            break;
        case 6:
            cout << "Enter ID to update: "; cin >> id;
            cin.ignore();
            cout << "Enter new Name (leave blank to skip): "; getline(cin, name);
            cout << "Enter new Phone (leave blank to skip): "; getline(cin, phone);
            cout << "Enter new Email (leave blank to skip): "; getline(cin, email);
            contacts.updateContact(id, name, phone, email);
            break;
        case 7:
            contacts.displayAllContacts();
            break;
        case 8:
            contacts.displayTree();
            break;
        case 9:
            contacts.checkBalance();
            break;
        case 10:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice! Try again." << endl;
        }

    } while (choice != 10);

    return 0;
}

