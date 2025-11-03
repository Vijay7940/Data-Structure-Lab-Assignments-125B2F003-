#include <iostream>
#include <fstream>
using namespace std;

int main() {
    float temp[50];
    int n = 0; // Array to store temperatures
    // Counter for number of readings

    // Open the input file for reading
    ifstream read("temperatures.txt");
    if (!read) { // Check whether file is opened successfully or not
        cout << "Unable to open 'temperatures.txt' file\n";
        return 1;
    }
    else {
        // Read temperature values from file
        while (read >> temp[n]) {
            n++;
            if (n >= 50) {
                cout << "Only 1st 50 readings are considered.\n";
                break;
            }
        }
        read.close();
        cout << "\nTotal no of temperatures read: " << n << endl;
    }

    // Applied Bubble Sort for sorting temperatures
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (temp[j] > temp[j + 1]) {
                float t = temp[j];
                PRN No : 125B2F003 Name : Vijay Jathare
                temp[j] = temp[j + 1];
                temp[j + 1] = t;
            }
        }
    }

    // Display Sorted Temperatures
    cout << "\n===== Sorted Temperatures =====\n";
    for (int i = 0; i < n; i++) {
        cout << temp[i] << "°C" << endl;
    }

    // Write Sorted Data to Output File
    ofstream write("sorted_temperatures.txt");
    if (!write) { // Check whether file is created successfully or not
        cout << "Unable to create 'sorted_temperatures.txt' file\n";
        return 1;
    }

    // Write sorted temperatures to file
    for (int i = 0; i < n; i++) {
        write << temp[i] << endl;
    }

    write.close();
    cout << "\nSorted temperatures saved to 'sorted_temperatures.txt'\n";

    return 0;
}
