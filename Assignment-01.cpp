#include <iostream>
#include <cstring>
using namespace std;
struct Contact {
char name[50];
char phone[20];
char email[50];
};

Contact* linearSearch(Contact phonebook[], int n, const char searchName[]) {
  for (int i = 0; i < n; i++) {
    if (strcmp(phonebook[i].name, searchName) == 0) {
      return &phonebook[i];
    }
  }
  return NULL;
}

int main() {
Contact phonebook[100];
int n = 0;
int choice;
do {
  cout << "\nPhonebook Menu:\n";
  cout << "1. Add Contact\n";
  cout << "2. Show All Contacts\n";
  cout << "3. Search Contact\n";
  cout << "4. Exit\n";
  cout << "Enter Your Choice: ";
  cin >> choice;
  cin.ignore(); // clear newline
  if (choice == 1) {
    cout << "Name: ";
    cin.getline(phonebook[n].name, 50);
    cout << "Phone: ";
    cin.getline(phonebook[n].phone, 20);
    cout << "Email: ";
    cin.getline(phonebook[n].email, 50);
    n++;
  }
  else if (choice == 2) {
    if (n == 0) cout << "No contacts.\n";
    else {
      cout << "\nContacts List:\n";
      for (int i = 0; i < n; i++) {
        cout << i+1 << "." << phonebook[i].name << " | " <<phonebook[i].phone << " | " << phonebook[i].email << "\n";
      }
    }
  }
  else if (choice == 3) {
    char name[50];
    cout << "Enter name to search: ";
    cin.getline(name, 50);
    Contact* c = linearSearch(phonebook, n, name);
    if (c) {
      cout << "Contact Found:\n";
      cout << "Name: " << c->name << "\nPhone: " << c->phone << "\nEmail:" << c->email << "\n";
    } 
    else {
      cout << "Contact not found.\n";
    }
  }
}
  else if (choice == 4) {
  cout << "Goodbye!\n";
  else {
    cout << "Invalid choice.\n";
  }
} while (choice != 4);
  return 0;
}
