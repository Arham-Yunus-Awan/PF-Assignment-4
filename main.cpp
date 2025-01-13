#include <iostream>
#include <sstream>
#include<fstream>
#include<string>
#include <iomanip>
using namespace std;

struct Patient {
    int patient_id;
    string patient_name;
    int age;
    string disease;
    string room_number;
};

// global variables
string filename = "patients_data.txt";
const int MAX_PATIENTS = 100;
int patient_count = 0;
Patient patients[MAX_PATIENTS] = {};

string truncateString(const string& str, int width) {
    if (str.length() > width) {
        return str.substr(0, width - 3) + "...";
    }
    return str;
}

void display_patients(){
    if (patient_count == 0) {
        cout << "There are no patients to display..." << endl;
    }

    else {
        cout << string(90, '-') << endl;
        cout << left << setw(15)  << "Patient ID"
            << setw(25) << "Patient Name"
            << setw(10)  << "Age"
            << setw(25) << "Disease"
            << setw(15)  << "Room Number" << endl;
        cout << string(90, '-') << endl;

        for (int i = 0; i < patient_count; i++) {
            cout << left << setw(15)  << patients[i].patient_id
                << setw(25) << truncateString(patients[i].patient_name, 24)
                << setw(10) << patients[i].age
                << setw(25) << truncateString(patients[i].disease, 24)
                << setw(15)  << truncateString(patients[i].room_number, 14) << endl;
        }
        cout << string(90, '-') << endl << endl;
    }
}

void add_patient_to_file(string data){
    ifstream infile(filename);
    if (!infile) {
        ofstream newFile(filename);
        if (newFile) {
            newFile << data << endl;
        } else {
            cerr << "Failed to create the file: " << filename << endl;
        }
    }
    else {
        ofstream file(filename, ios::app);
    
        if (file.is_open()) {
            file << data << endl;
            file.close();
        } else {
            cout << "Error: Unable to open the file " << filename << endl;
        }
    }
}

void add_patient() {
    string patient_data = "";
    patients[patient_count].patient_id = patient_count + 1;
    
    cout << "Enter the name of patient: ";
    getline(cin, patients[patient_count].patient_name);
    while(patients[patient_count].patient_name == "") {
        cout << "Patient's name can't be empty, enter again: ";
        getline(cin, patients[patient_count].patient_name);
    } 

    cout << "Enter the age of patient: ";
    cin >> patients[patient_count].age;
    while(patients[patient_count].age <= 0) {
        cout << "Kindly enter a positive age: ";
        cin >> patients[patient_count].age;
    }
    cin.ignore();

    cout << "Enter the disease of patient: ";
    getline(cin, patients[patient_count].disease);
    while(patients[patient_count].disease == "") {
        cout << "Patient's disease can't be empty, enter again: ";
        getline(cin, patients[patient_count].disease);
    } 

    cout << "Enter the room number of patient: ";
    getline(cin, patients[patient_count].room_number);
    while(patients[patient_count].room_number == "") {
        cout << "Patient's room number can't be empty, enter again: ";
        getline(cin, patients[patient_count].room_number);
    } 

    patient_data += to_string(patients[patient_count].patient_id);
    patient_data += ",";
    patient_data += patients[patient_count].patient_name;
    patient_data += ",";
    patient_data += to_string(patients[patient_count].age);
    patient_data += ",";
    patient_data += patients[patient_count].disease;
    patient_data += ",";
    patient_data += patients[patient_count].room_number;

    add_patient_to_file(patient_data);

    patient_count++;
}

void search_patient() {
    int choice;
    int found_index = -1;
    cout << "Do you want to search by Id, Patient Name or Room Number?\n"
         << "1. By Patient Id\n"
         << "2. By Patient Name\n"
         << "3. By Room Number\n"
         << "Your choice: ";
    cin >> choice;

    switch (choice) {
    case 1: {
        bool id_found = false;
        int id_to_search;

        cout << "Enter the Patient Id to search: ";
        cin >> id_to_search;
        for (int i = 0; i < patient_count; i++) {
            if (patients[i].patient_id == id_to_search) {
                id_found = true;
                found_index = i;
                break;
            }
        }
        if (id_found) {
            cout << string(90, '-') << endl;
            cout << left << setw(15)  << "Patient ID"
                 << setw(25) << "Patient Name"
                 << setw(10)  << "Age"
                 << setw(25) << "Disease"
                 << setw(15)  << "Room Number" << endl;
            cout << string(90, '-') << endl;

            cout << left << setw(15)  << patients[found_index].patient_id
                 << setw(25) << truncateString(patients[found_index].patient_name, 24)
                 << setw(10) << patients[found_index].age
                 << setw(25) << truncateString(patients[found_index].disease, 24)
                 << setw(15)  << truncateString(patients[found_index].room_number, 14) << endl;
            cout << string(90, '-') << endl << endl;
        } 
        else {
            cout << "No patient was found with the given Id." << endl;
        }
        break;
    }
    case 2: {
        bool name_found = false;
        string name_to_search;

        cin.ignore();
        cout << "Enter the Patient Name to search: ";
        getline(cin, name_to_search);
        for (int i = 0; i < patient_count; i++) {
            if (patients[i].patient_name == name_to_search) {
                name_found = true;
                found_index = i;
                break;
            }
        }
        if (name_found) {
            cout << string(90, '-') << endl;
            cout << left << setw(15)  << "Patient ID"
                 << setw(25) << "Patient Name"
                 << setw(10)  << "Age"
                 << setw(25) << "Disease"
                 << setw(15)  << "Room Number" << endl;
            cout << string(90, '-') << endl;

            cout << left << setw(15)  << patients[found_index].patient_id
                 << setw(25) << truncateString(patients[found_index].patient_name, 24)
                 << setw(10) << patients[found_index].age
                 << setw(25) << truncateString(patients[found_index].disease, 24)
                 << setw(15)  << truncateString(patients[found_index].room_number, 14) << endl;
            cout << string(90, '-') << endl << endl;
        } 
        else {
            cout << "No patient was found with the given Name." << endl;
        }
        break;
    }
    case 3: {
        bool room_found = false;
        string room_to_search;

        cin.ignore();
        cout << "Enter the Room Number to search: ";
        getline(cin,room_to_search);
        for (int i = 0; i < patient_count; i++) {
            if (patients[i].room_number ==room_to_search) {
                room_found = true;
                found_index = i;
                break;
            }
        }
        if (room_found) {
            cout << string(90, '-') << endl;
            cout << left << setw(15)  << "Patient ID"
                 << setw(25) << "Patient Name"
                 << setw(10)  << "Age"
                 << setw(25) << "Disease"
                 << setw(15)  << "Room Number" << endl;
            cout << string(90, '-') << endl;

            cout << left << setw(15)  << patients[found_index].patient_id
                 << setw(25) << truncateString(patients[found_index].patient_name, 24)
                 << setw(10) << patients[found_index].age
                 << setw(25) << truncateString(patients[found_index].disease, 24)
                 << setw(15)  << truncateString(patients[found_index].room_number, 14) << endl;
            cout << string(90, '-') << endl << endl;
        } 
        else {
            cout << "The given room number was not found." << endl;
        }
        break;
    }
    default:
        cout << "Invalid choice." << endl;
        break;
    }
}

void read_patients_from_file() {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line) && patient_count < MAX_PATIENTS) {
        stringstream ss(line);
        Patient newPatient;

        if (!(ss >> newPatient.patient_id)) {
            cerr << "Error: Invalid patient ID in file." << endl;
            continue;
        }
        ss.ignore();

        getline(ss, newPatient.patient_name, ',');
        if (!(ss >> newPatient.age) || newPatient.age <= 0) {
            cerr << "Error: Invalid age for patient ID " << newPatient.patient_id << endl;
            continue;
        }
        ss.ignore();

        getline(ss, newPatient.disease, ',');
        getline(ss, newPatient.room_number, ',');

        if (newPatient.patient_name.empty() || newPatient.disease.empty() || newPatient.room_number.empty()) {
            cerr << "Error: Missing fields for patient ID " << newPatient.patient_id << endl;
            continue;
        }

        patients[patient_count++] = newPatient;
    }
    file.close();
}

int main() {
    display_patients();
    read_patients_from_file();
    display_patients();
    search_patient();
    search_patient();
    // add_patient();
    // display_patients();

    return 0;
}