#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

class Person {
protected:
    char name[50];
    int age;
public:
    Person() { age = 0; strcpy(name, ""); }
    void setData(const char n[], int a) {
        strcpy(name, n);
        age = a;
    }
    void showData() {
        cout << "Name: " << name << "\nAge: " << age << endl;
    }
};

class Student : public Person {
private:
    int rollNo;
    char branch[30];
    float marks;
    static int count;

public:
    Student() {
        rollNo = 0;
        strcpy(branch, "");
        marks = 0.0;
    }

    Student(int r, const char n[], int a, const char b[], float m) {
        rollNo = r;
        strcpy(name, n);
        age = a;
        strcpy(branch, b);
        marks = m;
        count++;
    }

    inline void setMarks(float m) { marks = m; }

    void input() {
        cout << "\nEnter Roll No: ";
        cin >> rollNo;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Age: ";
        cin >> age;
        cout << "Enter Branch: ";
        cin >> branch;
        cout << "Enter Marks: ";
        cin >> marks;
        count++;
    }

    void display() {
        cout << "\nRoll No: " << rollNo;
        cout << "\nName: " << name;
        cout << "\nAge: " << age;
        cout << "\nBranch: " << branch;
        cout << "\nMarks: " << marks << endl;
    }

    friend void updateMarks(Student &s, float bonus);

    static void showCount() {
        cout << "\nTotal Students Added: " << count << endl;
    }

    void writeToFile() {
        ofstream fout("students.txt", ios::app);
        fout << rollNo << " " << name << " " << age << " " << branch << " " << marks << endl;
        fout.close();
    }

    static void readFromFile() {
        ifstream fin("students.txt");
        if (!fin) {
            cout << "\nNo file found!";
            return;
        }
        int r, a;
        char n[50], b[30];
        float m;
        cout << "\n--- Student Records ---\n";
        while (fin >> r >> n >> a >> b >> m) {
            cout << "\nRoll No: " << r;
            cout << "\nName: " << n;
            cout << "\nAge: " << a;
            cout << "\nBranch: " << b;
            cout << "\nMarks: " << m << endl;
        }
        fin.close();
    }

    Student operator+(Student s2) {
        Student temp;
        temp.marks = (marks + s2.marks) / 2;
        return temp;
    }

    ~Student() {
        // cout << "Destructor called for Roll No: " << rollNo << endl;
    }
};

int Student::count = 0;

void updateMarks(Student &s, float bonus) {
    s.marks = s.marks + bonus;
}

class Scholar : public Student {
private:
    int researchScore;
public:
    Scholar() : Student() { researchScore = 0; }
    Scholar(int r, const char n[], int a, const char b[], float m, int rs)
        : Student(r, n, a, b, m) { researchScore = rs; }

    void showScholar() {
        cout << "\nScholar Info -> ";
        display();
        cout << "Research Score: " << researchScore << endl;
    }
};

template <class T>
T findMax(T a, T b) {
    return (a > b) ? a : b;
}

void divideMarks(float total, float subjects) {
    try {
        if (subjects == 0)
            throw 1;
        cout << "\nAverage Marks: " << total / subjects << endl;
    }
    catch (int) {
        cout << "\nError: Division by zero not allowed!\n";
    }
}

int main() {
    Student s[100];
    int n = 0, choice;

    do {
        cout << "\n=== STUDENT MANAGEMENT SYSTEM ===";
        cout << "\n1. Add Student";
        cout << "\n2. Display All Students";
        cout << "\n3. Save to File";
        cout << "\n4. Read from File";
        cout << "\n5. Update Marks (Friend Function)";
        cout << "\n6. Inheritance Demo";
        cout << "\n7. Operator Overloading Demo";
        cout << "\n8. Template Demo";
        cout << "\n9. Exception Handling Demo";
        cout << "\n10. Show Count";
        cout << "\n11. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            s[n].input();
            n++;
        }
        else if (choice == 2) {
            for (int i = 0; i < n; i++)
                s[i].display();
        }
        else if (choice == 3) {
            for (int i = 0; i < n; i++)
                s[i].writeToFile();
            cout << "\nSaved successfully!\n";
        }
        else if (choice == 4) {
            Student::readFromFile();
        }
        else if (choice == 5) {
            if (n > 0) {
                updateMarks(s[0], 5);
                cout << "\nMarks Updated using Friend Function!\n";
                s[0].display();
            }
        }
        else if (choice == 6) {
            Scholar sch(101, "Ravi", 20, "CSE", 80, 15);
            sch.showScholar();
        }
        else if (choice == 7) {
            if (n >= 2) {
                Student avg = s[0] + s[1];
                cout << "\nAverage Marks (using + operator): ";
                avg.display();
            }
        }
        else if (choice == 8) {
            cout << "\nMax of 5 and 9 is: " << findMax(5, 9) << endl;
        }
        else if (choice == 9) {
            divideMarks(250, 0);
        }
        else if (choice == 10) {
            Student::showCount();
        }

    } while (choice != 11); 

    cout << "\nProgram Ended.\n";
    return 0;
}

