// Student_Record_Management_System.cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <conio.h>  // For _getch()

using namespace std;

// ------------------------
// ABSTRACT BASE CLASS
// ------------------------
class Person {
public:
    virtual void displayBasic() const = 0; 
};

// ------------------------
// STUDENT CLASS
// ------------------------
class Student : public Person {
private:
    string id;
    string name;
    int age;

public:
    Student() { id = ""; age = 0; name = ""; }
    Student(string i, string n, int a) { id = i; name = n; age = a; }

    void setId(string i) { id = i; }
    void setName(string n) { name = n; }
    void setAge(int a) { age = a; }

    string getId() const { return id; }
    string getName() const { return name; }
    int getAge() const { return age; }

    void displayBasic() const {
        cout << "ID: " << id << " | Name: " << name << " | Age: " << age;
    }
};

// ------------------------
// ACADEMIC RECORD CLASS
// ------------------------
class AcademicRecord : public Student {
private:
    string department;
    double gpa;
    int enrollmentYear;
    string batch;

public:
    AcademicRecord() { department = ""; gpa = 0.0; enrollmentYear = 0; batch = ""; }
    AcademicRecord(string id, string n, int a, string dep, double g, int ey, string b)
        : Student(id, n, a) { department = dep; gpa = g; enrollmentYear = ey; batch = b; }

    void setDepartment(string d) { department = d; }
    void setGPA(double g) { gpa = g; }
    void setEnrollmentYear(int ey) { enrollmentYear = ey; }
    void setBatch(string b) { batch = b; }

    string getDepartment() const { return department; }
    double getGPA() const { return gpa; }
    int getEnrollmentYear() const { return enrollmentYear; }
    string getBatch() const { return batch; }

    void display() const {
        displayBasic();
        cout << " | Department: " << department
             << " | GPA: " << gpa
             << " | Enrollment Year: " << enrollmentYear
             << " | Batch: " << batch
             << endl;
    }

    // FILE SAVE
    void saveToFile(ofstream &out) const {
        out << getId() << endl
            << getName() << endl
            << getAge() << endl
            << department << endl
            << gpa << endl
            << enrollmentYear << endl
            << batch << endl;
    }

    // FILE LOAD
    void loadFromFile(ifstream &in) {
        string n, dep, b, id;
        int age, ey;
        double g;

        getline(in, id);
        getline(in, n);
        in >> age;
        in.ignore();
        getline(in, dep);
        in >> g >> ey;
        in.ignore();
        getline(in, b);

        setId(id);
        setName(n);
        setAge(age);
        department = dep;
        gpa = g;
        enrollmentYear = ey;
        batch = b;
    }
};

// ------------------------
// STUDENT MANAGEMENT SYSTEM
// ------------------------
class StudentManagement {
private:
    vector<AcademicRecord> list;

public:
    StudentManagement() { 
        loadAll(); 
    }

    void addStudent() {
        string id, name, dept, batch;
        int age, enrollmentYear;

        cout << "Enter ID (e.g., S25CSC018): "; cin >> id;
        cin.ignore();
        cout << "Enter Name: "; getline(cin, name);
        cout << "Enter Age: "; cin >> age;

        // DEPARTMENT MENU
        int depChoice;
        cout << "\nSelect Department:\n1. BSCS\n2. Artificial Intelligence\n3. PharmD\nEnter choice: ";
        cin >> depChoice;

        switch (depChoice) {
            case 1: dept = "BSCS"; break;
            case 2: dept = "Artificial Intelligence"; break;
            case 3: dept = "PharmD"; break;
            default: dept = "Unknown";
        }

        cout << "Enter Enrollment Year (e.g., 2023, 2024, 2025): "; cin >> enrollmentYear;

        batch = to_string(enrollmentYear);
        AcademicRecord s(id, name, age, dept, 0.0, enrollmentYear, batch);
        list.push_back(s);

        saveAll();
        cout << "\nStudent added successfully!\n";
    }

    void displayByDepartment() const {
        if (list.empty()) {
            cout << "No records found." << endl;
            return;
        }

        // Collect unique departments
        vector<string> departments;
        for (auto &s : list) {
            if (find(departments.begin(), departments.end(), s.getDepartment()) == departments.end())
                departments.push_back(s.getDepartment());
        }

        cout << "\n===== STUDENTS BY DEPARTMENT =====\n";
        for (auto &dept : departments) {
            cout << "\n--- " << dept << " ---\n";
            for (auto &s : list) {
                if (s.getDepartment() == dept) s.display();
            }
        }

        // Enrollment year count
        vector<int> years;
        for (auto &s : list) {
            if (find(years.begin(), years.end(), s.getEnrollmentYear()) == years.end())
                years.push_back(s.getEnrollmentYear());
        }

        cout << "\n===== TOTAL ENROLLED STUDENTS BY ENROLLMENT YEAR =====\n";
        for (auto &y : years) {
            int count = 0;
            for (auto &s : list) if (s.getEnrollmentYear() == y) count++;
            cout << "Year " << y << ": " << count << " students\n";
        }
        cout << "Total Students: " << list.size() << endl;
    }

    void searchStudent() const {
        string id;
        cout << "Enter ID to search: "; cin >> id;

        for (auto &s : list) {
            if (s.getId() == id) {
                cout << "\nRecord Found:\n";
                s.display();
                return;
            }
        }
        cout << "Student not found.\n";
    }

    void updateStudent() {
        string id;
        cout << "Enter ID to update: "; cin >> id;

        for (auto &s : list) {
            if (s.getId() == id) {
                string name, dept, batch;
                int age, enrollmentYear;
                double gpa;

                cin.ignore();
                cout << "Enter new Name: "; getline(cin, name);
                cout << "Enter new Age: "; cin >> age;

                int depChoice;
                cout << "\nSelect Department:\n1. BSCS\n2. Artificial Intelligence\n3. PharmD\nEnter choice: ";
                cin >> depChoice;
                switch(depChoice) {
                    case 1: dept = "BSCS"; break;
                    case 2: dept = "Artificial Intelligence"; break;
                    case 3: dept = "PharmD"; break;
                    default: dept = "Unknown";
                }

                cout << "Enter new GPA: "; cin >> gpa;
                cout << "Enter new Enrollment Year: "; cin >> enrollmentYear;
                cout << "Enter new Batch: "; cin >> batch;

                s.setName(name); s.setAge(age); s.setDepartment(dept);
                s.setGPA(gpa); s.setEnrollmentYear(enrollmentYear); s.setBatch(batch);

                saveAll();
                cout << "Record Updated!\n";
                return;
            }
        }
        cout << "Student not found.\n";
    }

    void deleteStudent() {
        string id;
        cout << "Enter ID to delete: "; cin >> id;

        for (int i = 0; i < list.size(); i++) {
            if (list[i].getId() == id) {
                list.erase(list.begin() + i);
                saveAll();
                cout << "Record Deleted!\n";
                return;
            }
        }
        cout << "Student not found.\n";
    }

    void deleteAllRecords() {
        char confirm;
        cout << "Are you sure you want to delete ALL records? (Y/N): ";
        cin >> confirm;
        if (confirm == 'Y' || confirm == 'y') {
            list.clear();
            saveAll();
            cout << "All student records deleted!\n";
        } else {
            cout << "Operation cancelled.\n";
        }
    }

    void viewMyRecord() const {
        string id;
        cout << "Enter your Student ID: "; cin >> id;

        for (auto &s : list) {
            if (s.getId() == id) {
                cout << "\n===== YOUR RECORD =====\n";
                s.display();
                return;
            }
        }
        cout << "Student ID not found.\n";
    }

    void saveAll() const {
        ofstream out("students.txt");
        for (auto &s : list) s.saveToFile(out);
        out.close();
    }

    void loadAll() {
        ifstream in("students.txt");
        list.clear();
        if (!in) {
            cout << "\nStarting fresh. Total Students: 0\n";
            return;
        }

        while (!in.eof()) {
            AcademicRecord s;
            s.loadFromFile(in);
            if (in) list.push_back(s);
        }
        in.close();

        cout << "\nSuccessfully loaded " << list.size() << " student records from file.\n";
    }

    void adminMenu() {
        int choice;
        while (true) {
            cout << "\n===== ADMIN MENU =====\n";
            cout << "1. Add Student\n";
            cout << "2. Display Students by Department\n";
            cout << "3. Search Student\n";
            cout << "4. Update Student\n";
            cout << "5. Delete Student\n";
            cout << "6. Delete ALL Records\n";
            cout << "7. Back to Main Menu\n";
            cout << "Enter choice: "; cin >> choice;

            switch(choice) {
                case 1: addStudent(); break;
                case 2: displayByDepartment(); break;
                case 3: searchStudent(); break;
                case 4: updateStudent(); break;
                case 5: deleteStudent(); break;
                case 6: deleteAllRecords(); break;
                case 7: return;
                default: cout << "Invalid choice!\n";
            }
        }
    }

    void studentMenu() {
        int choice;
        while (true) {
            cout << "\n===== STUDENT MENU =====\n";
            cout << "1. View My Record\n";
            cout << "2. View All Students by Department\n";
            cout << "3. Back to Main Menu\n";
            cout << "Enter choice: "; cin >> choice;

            switch(choice) {
                case 1: viewMyRecord(); break;
                case 2: displayByDepartment(); break;
                case 3: return;
                default: cout << "Invalid choice!\n";
            }
        }
    }
};

// ------------------------
// MAIN MENU
// ------------------------
int main() {
    StudentManagement sm;
    int choice;
    string password;

    while (true) {
        cout << "\n===== STUDENT RECORD MANAGEMENT SYSTEM =====\n";
        cout << "1. Admin Login\n";
        cout << "2. Student Login\n";
        cout << "3. Exit\n";
        cout << "Enter choice: "; 
		cin >> choice;

	if (cin.fail()) {
    	cin.clear();                    
    	cin.ignore(10000, '\n');         // discard bad input
    	cout << "Invalid input! Enter 1, 2, or 3.\n";
    	continue;
		}


        switch(choice) {
            case 1:
                cout << "Enter Admin Password: ";
                password = "";
                char ch;
                while ((ch = _getch()) != 13) { // ENTER key
                    if (ch == 8) {
                        if (!password.empty()) {
                            password.pop_back();
                            cout << "\b \b";
                        }
                    } else {
                        password += ch;
                        cout << '*';
                    }
                }
                cout << endl;
                if (password == "admin123") {
                    cout << "Login Successful!\n";
                    sm.adminMenu();
                } else {
                    cout << "Incorrect Password!\n";
                }
                break;

            case 2:
                cout << "Student Login Successful!\n";
                sm.studentMenu();
                break;

            case 3:
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice!\n";
        }
    }
}
