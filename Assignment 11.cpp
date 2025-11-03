#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

struct Student {
    string name;
    int age;
    string course;
};

class StudentInfo {
private:
    unordered_map<int, Student> studentTable;

public:
    void addStudent(int id, const Student& stu) {
        studentTable[id] = stu;
        cout << "Student Added Successfully\n";
    }

    void getStudentById(int id) {
        auto it = studentTable.find(id);
        if (it != studentTable.end()) {
        	cout << "-----Student Profile-----" << endl;
        	cout << "-------------------------" << endl;
            cout << "Student ID: " << id << endl;
            cout << "Name: " << it->second.name << endl;
            cout << "Age: " << it->second.age << endl;
            cout << "Course: " << it->second.course << endl;
            cout << "-------------------------" << endl;
        } 
		else {
            cout << "Student Not Found" << endl;
        }
    }

    void removeStudent(int id) {
        if (studentTable.erase(id)) {
            cout << "Student Removed" << endl;
        } 
		else {
            cout << "Student Not Found" << endl;
        }
    }

    void display() {
        for (const auto& pair : studentTable) {
        	cout << "-----------------------" << endl;
            cout << "Student ID: " << pair.first << endl;
            cout << "Name: " << pair.second.name << endl;
            cout << "Age: " << pair.second.age << endl;
            cout << "Course: " << pair.second.course << endl; 
        }
        cout << "-----------------------" << endl;
    }
};

int main() {
    StudentInfo sis;
    int choice, id, age;
    string name, course;

    while (true) {
    	cout << "\n";
    	cout << "----------MENU-----------";
        cout << "\n1. Add Student\n2. Get Student by ID\n3. Remove Student\n4. Display All Students\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cout << endl;

        if (choice == 1) {
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter Name: ";
            cin.ignore();  
            getline(cin, name);
            cout << "Enter Age: ";
            cin >> age;
            cout << "Enter Course: ";
            cin.ignore();
            getline(cin, course);
            sis.addStudent(id, {name, age, course});
        } 
		else if (choice == 2) {
            cout << "Enter ID: ";
            cin >> id;
            sis.getStudentById(id);
        } 
		else if (choice == 3) {
            cout << "Enter ID to Remove: ";
            cin >> id;
            sis.removeStudent(id);
        } 
		else if (choice == 4) {
            sis.display();
        }
		 else if (choice == 5) {
            cout << "Exiting Program Thanks!!!" << endl;
            break;
        } 
		else {
            cout << "Invalid choice\n";
        }
    }
    return 0;
}


