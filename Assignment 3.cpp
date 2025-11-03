#include<iostream>
using namespace std;

struct patient{
	
	string name;
	int id;
	string condition;
	patient *next;
	
};

class ERQueue{
	patient *head = NULL;
	
	public:
		ERQueue(){
			head = NULL;
		}
		
	// Method to add the patient to End OF Queue	
	void addToEnd(string Name, string Condition, int ID){
		patient *newPatient = new patient();
		newPatient->name = Name;
		newPatient->condition = Condition;
		newPatient->id = ID;
		newPatient->next = NULL;
		
		//Check if the Queue is Empty
		if(head == NULL){
			head = newPatient;
		}
		
		else{
			patient *temp = head;
			while(temp->next != NULL){
				temp = temp->next;
			}
			temp->next = newPatient;
		}
		cout <<"------------------------------------------" << endl;
		cout <<"New patient " << Name << " Added To Queue" <<endl;
		cout <<"------------------------------------------";
	}
	
	// Method to remove the Patient from Front[Doctor]
	void removePatient(){  
	    // Check if Queue is Empty
		if(!head){
			cout << "Queue is Empty"<< endl;
			return;
		}
		
		patient *temp = head;
		cout <<"------------------------------------------" << endl;
		cout <<"Patient " << temp->name <<" Removed\n";
		cout <<"------------------------------------------";
		head = head->next;
		delete temp;
	}
	
	// Method to update priority of patient
	void movetoPriority(string name){
		
		if(!head){
			cout << "Queue is Empty" <<endl;
			return;
		}
		
		if(head->name == name){
			cout << "Patient is Already at Front" <<endl;
			return;
		}
		
		patient* temp = head;
		patient* prev = NULL;
		
		// Searching the patient by name
		while (temp != NULL && temp->name != name) {
			prev = temp;
            temp = temp->next;
		}

        // Check If patient exists
        if (temp == NULL) {
        	cout << "\nPatient not found!\n"; 
            return;
		}
		
		prev->next = temp->next; 
        // Move the patient to the front of the queue
        temp->next = head; 
        head = temp; 
        cout <<"------------------------------------------" << endl;
        cout <<"\n"<<temp->name<<" moved to priority!\n";
        cout <<"------------------------------------------";
        
        // Renumbering all patient IDs & Assigning ID as 1 to the patient
        patient* current = head;
        int newId = 1;
        while (current != NULL) {
            current->id = newId;
            newId++;
            current = current->next;
        }
	}
	
	// Display the current queue
    void displayQueue() {
        if (head == NULL) {
            cout << "\nNo patients are in the queue\n";
            return;
        }

        cout << "\n===== Current Patient Queue =====\n";
        patient* temp = head;
        
        while (temp != NULL) {
            cout << "ID: " << temp->id<< " | Name: " << temp->name << " | Condition: " << temp->condition << endl;
            temp = temp->next;
        }
    }
    
    // Method to Search patient
    void searchPatient(string name) {
        patient* temp = head;
        
        while (temp != NULL) {
            if (temp->name == name) {
            	cout <<"------------------------------------------" << endl;
                cout << "Found: " << temp->name << " | Condition: " << temp->condition << endl;
                return;
            }
            temp = temp->next;
        }
        cout <<"------------------------------------------";
        
        cout << "Patient not found\n";
    }
    
    // Method to Update patient information 
    void updatePatient(int id, string newCondition) { 
        patient* temp = head; 
         
        while (temp != NULL) { 
            if (temp->id == id) { 
                temp->condition = newCondition; 
                cout <<"------------------------------------------" << endl;
                cout << "\nPatient condition updated!\n"; 
                cout <<"------------------------------------------";
                return; 
            } 
            temp = temp->next; 
        } 
        cout << "\nPatient not found!\n"; 
    }
    
};
		
// Driver Code
int main() {
    ERQueue er;  
    int choice;

    do {
    	cout <<"\n";
    	cout << "======Hospital Management System Menu======";
        cout << "\n1. Add Patient\n2. Remove Patient\n3. Move To Priority\n";
        cout << "4. Search Patient\n5. Update Patient\n6. Display Queue\n7. Exit\n";
        cout << "Enter your choice:";
        cin >> choice; 
		cin.ignore();

        string name, condition;
        int id;

        switch(choice) {
            case 1:
                cout << "Name: "; getline(cin, name);
                cout << "Condition: "; getline(cin, condition);
                cout << "ID: "; cin >> id; cin.ignore();
                er.addToEnd(name, condition, id);
                break;
                
            case 2: er.removePatient(); break;
            
            case 3:
                cout << "Patient name to move to priority: "; getline(cin, name);
                er.movetoPriority(name);
                break;
                
            case 4:
                cout << "Patient name to search: "; getline(cin, name);
                er.searchPatient(name);
                break;
                
            case 5:
                cout << "Patient ID to update: "; cin >> id; cin.ignore();
                cout << "Enter new condition: "; getline(cin, condition);
                er.updatePatient(id, condition);
                break;
                
            case 6: er.displayQueue(); break;
            
            case 7: cout << "Exiting...\n"; break;
            
            default: cout << "Invalid choice.\n";
        }
    } while(choice != 7);

    return 0;
}

