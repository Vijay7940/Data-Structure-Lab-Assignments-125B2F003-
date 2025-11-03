#include <iostream>
using namespace std;

struct GradeEntry {
    int student;   
    int subject;   
    int marks;     
};

int main() {
    int numStudents, numSubjects, totalGrades, choice;

    cout << "Enter number of students: ";
    cin >> numStudents;
    cout << "Enter number of subjects: ";
    cin >> numSubjects;

    string subjects[50]; // Array to store Subject names
    cout << "\nEnter subject names:\n";
    for (int i = 0; i < numSubjects; i++) {
        cout << "Subject " << i << ": ";
        cin >> subjects[i];
    }

    cout << "\nEnter total number of grades to input (non-zero entries): ";
    cin >> totalGrades;

    GradeEntry grades[100]; // Array to store non-zero grades

    cout << "\nEnter student grades (student_index, subject_index, marks):\n";
    for (int i = 0; i < totalGrades; i++) {
        cout << "Entry " << i + 1 << ": ";
        cin >> grades[i].student >> grades[i].subject >> grades[i].marks;
    }

    // Menu Driven Code
    while (true) {
        cout << "\n===== Student Grades System =====\n";
        cout << "1. Show All Grades\n";
        cout << "2. Subject Averages\n";
        cout << "3. Student Report\n";
        cout << "4. Top Performers\n";
        cout << "5. Exit\n";
        cout << "Enter your Choice: ";
        cin >> choice;

        // Displaying All Grades
        if (choice == 1) {
            cout << "\n--- All Grades ---\n";
            for (int i = 0; i < totalGrades; i++) {
                cout << "Student " << (grades[i].student + 1) << " | "
                     << subjects[grades[i].subject] << ": "
                     << grades[i].marks << endl;
            }
        }
        
        // Displaying Subject Averages
        else if (choice == 2) {
            cout << "\n--- Subject Averages ---\n";
            for (int sub = 0; sub < numSubjects; sub++) {
                int sum = 0, count = 0;
                for (int i = 0; i < totalGrades; i++) {
                    if (grades[i].subject == sub) {
                        sum += grades[i].marks;
                        count++;
                    }
                }
                if (count > 0) {
                    float avg = (float)sum / count;
                    cout << subjects[sub] << ": " << avg
                         << " (" << count << " students)\n";
                }
                else {
                    cout << subjects[sub] << ": No grades\n";
                }
            }
        }
        
        // Displaying Student Report
        else if (choice == 3) {
            int id;
            cout << "Enter Student ID: ";
            cin >> id;
            
            if (id < 0 || id >= numStudents) {
                cout << "Invalid ID!\n";
                continue;
            }
            
            cout << "\n--- Student " << id + 1 << " Report ---\n";
            bool found = false;
            for (int i = 0; i < totalGrades; i++) {
                if (grades[i].student == id) {
                    cout << subjects[grades[i].subject] << ": " << grades[i].marks << endl;
                    found = true;
                }
            }
            if (!found) {
            	cout << "No grades found!\n";
			}
        }
        
        // Displaying Top performer
        else if (choice == 4) {
            cout << "\n--- Top Performers ---\n";
            for (int sub = 0; sub < numSubjects; sub++) {
                int maxGrade = -1, topStudent = -1;
                for (int i = 0; i < totalGrades; i++) {
                    if (grades[i].subject == sub && grades[i].marks > maxGrade) {
                        maxGrade = grades[i].marks;
                        topStudent = grades[i].student;
                    }
                }
                if (topStudent != -1) {
                    cout << subjects[sub] << ": Student " << (topStudent + 1)
                         << " with " << maxGrade << " marks\n";
                } else {
                    cout << subjects[sub] << ": No grades\n";
                }
            }
        }
        
        else if (choice == 5) {
            cout << "\nGoodbye!\n";
            break;
        }
        else {
            cout << "\nInvalid choice!\n";
        }
    }

    return 0;
}

