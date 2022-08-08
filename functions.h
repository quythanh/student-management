#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdio> // getchar

using namespace std;

// ========================= STRUCTS SECTION =========================
class Format {
private:
    string str;
    int width;
    string padding_left;
    string padding_right;

public:
    Format(string s, int w) {
        str = s;
        width = w;
        padding_left = padding_right = "";
    }

    Format(double d, int w) {
        str = to_string(d);
        if (str[2] == '0' && str[3] == '0')
            str = str.substr(0, str.find("."));
        else if (str[3] == '0')
            str = str.substr(0, str.find(".")+2);
        else
            str = str.substr(0, str.find(".")+3);
        width = w;
        padding_left = padding_right = "";
    }

    string Center() {
        int pw = width-str.length();
        
        for (int i = 0; i < pw/2; i++) {
            padding_left += " ";
            padding_right += " ";
        }
        
        return padding_left + str + padding_right;
    }

    string Left(int p = 1) {
        int pw = width-str.length()-p;
        
        for (int i = 0; i < pw; i++)
            padding_right += " ";
        for (int i = 0; i < p; i++)
            padding_left += " ";
        
        return padding_left + str + padding_right;
    }

    string Right(int p = 1) {
        int pw = width-str.length()-p;
        
        for (int i = 0; i < pw; i++)
            padding_left += " ";
        for (int i = 0; i < p; i++)
            padding_right += " ";
        
        return padding_left + str + padding_right;
    }
};

struct Student {
    string ID; // MSSV
    string firstName; // Ten
    string lastName; // Ho
    double midtermMark;
    double finalMark;

    void getInfo() {
        cout << "Nhap thong tin sinh vien:" << endl;
        cout << " - Ma so sinh vien: ";
        getline(cin, ID);

        cout << " - Nhap ho ten sinh vien:\n";
        cout << "   + Ho sinh vien: ";
        getline(cin, lastName);
        cout << "   + Ten sinh vien: ";
        getline(cin, firstName);

        cout << " - Nhap diem mon 1: ";
        cin >> midtermMark;
        cin.ignore();
        
        cout << " - Nhap diem mon 2: ";
        cin >> finalMark;
        cin.ignore();
    }

    void Print() {
        cout << "|" << setw(14) << Format(ID, 14).Center();
        cout << "|" << setw(22) << Format(lastName, 22).Left(3);
        cout << "|" << setw(13) << Format(firstName, 13).Left(3);
        cout << "|" << setw(12) << Format(midtermMark, 12).Right(3);
        cout << "|" << setw(12) << Format(finalMark, 12).Right(3);
        cout << "|" << setw(17) << Format((midtermMark + finalMark)/2, 17).Right(3);
        cout << "|" << endl;
        cout << "-------------------------------------------------------------------------------------------------" << endl;
    }
};

struct Node {
    Student student;
    Node *next;
    
    Node() = default;
    Node(Student student, Node *next = nullptr) {
        this->student = student;
        this->next = next;
    }
};

class ListStudent {
private:
    Node *StudentHead;

public:
    ListStudent() {
        StudentHead = nullptr;   
    }

    ~ListStudent() {
        while (StudentHead != nullptr) {
            Node *pCur = StudentHead;
            StudentHead = StudentHead->next;
            delete pCur;
        }
    }

    Node *GetStudentHead() {
        return StudentHead;
    }

    void ReadData() {
        ifstream f("students.txt");
        while (!f.eof()) {
            Student student;

            getline(f, student.ID, '-');
            getline(f, student.lastName, '-');
            getline(f, student.firstName, '-');
            f >> student.midtermMark;
            f.ignore();
            f >> student.finalMark;
            f.ignore();

            if (student.ID != "")
                InsertEnd(student);
        }  
        f.close();
    }

    bool isEmpty() {
        return StudentHead ? false : true;
    }

    void WriteStudentsToFile() {
        ofstream f("students.txt");
        Node *pCur = StudentHead;

        if (pCur == nullptr)
            f << "";

        while (pCur != nullptr) {
            Student student = pCur->student;
            f << student.ID << "-" << student.lastName << "-" << student.firstName << "-" << student.midtermMark << "-" << student.finalMark << endl;
            pCur = pCur->next;
        }

        f.close();
    }

    void InsertBeginning(Student newStudent) {
        StudentHead = new Node(newStudent, StudentHead);
    }

    void InsertEnd(Student newStudent, int write = 0) {
        if (StudentHead == nullptr)
            StudentHead = new Node(newStudent);
        else {
            Node *pCur = StudentHead;
            while (pCur->next != nullptr)
                pCur = pCur->next;
            pCur->next = new Node(newStudent);
        }

        if (write)
            WriteStudentsToFile();
    }

    Node *SearchStudent(string ID) {
        Node *pCur = StudentHead;
        while (pCur != nullptr && pCur->student.ID != ID)
            pCur = pCur->next;       
        return pCur;
    }

    bool SwapStudents(Student A, Student B) {
        Node *pStudentA = SearchStudent(A.ID);
        Node *pStudentB = SearchStudent(B.ID);

        if (pStudentA == nullptr || pStudentB == nullptr)
            return false;

        pStudentA->student = B;
        pStudentB->student = A;
        return true;
    }

    bool DeleteStudent(string ID) {
        Node *pCur = StudentHead;
        Node *pPrev;
        while (pCur != nullptr && pCur->student.ID != ID) {
            pPrev = pCur;
            pCur = pCur->next;
        }
        
        if (pCur == nullptr)
            return false;

        pPrev->next = pCur->next;
        delete pCur;
        WriteStudentsToFile();
        
        return true;
    }

    void PrintStudent(Node *student = nullptr, int amount = 0) {
        cout << "-------------------------------------------------------------------------------------------------" << endl;
        cout << "|     MSSV     |          Ho          |     Ten     | Diem mon 1 | Diem mon 2 | Diem trung binh |" << endl;
        cout << "-------------------------------------------------------------------------------------------------" << endl;

        Node *pCur = student ? student : StudentHead;
        if (!amount)
            while (pCur != nullptr) {
                pCur->student.Print();
                pCur = pCur->next;
            }

        while (amount-- && pCur != nullptr) {
            pCur->student.Print();
            pCur = pCur->next;
        }

        cout << endl;
    }

    ListStudent GetPassedStudents() {
        Node *student = StudentHead;
        ListStudent ListPassedStudents;

        while (student != nullptr) {
            double totalMark = (student->student.midtermMark + student->student.finalMark)/2;
            if (totalMark >= 5)
                ListPassedStudents.InsertEnd(student->student);
            student = student->next;
        }

        return ListPassedStudents;
    }

    ListStudent GetFailedStudents() {
        Node *student = StudentHead;
        ListStudent ListFailedStudents;

        while (student != nullptr) {
            double totalMark = (student->student.midtermMark + student->student.finalMark)/2;
            if (totalMark < 5)
                ListFailedStudents.InsertEnd(student->student);
            student = student->next;
        }

        return ListFailedStudents;
    }

    ListStudent SortByName() {
        ListStudent newList;
        newList.ReadData();
        
        Node *pCur = newList.GetStudentHead();

        while (pCur != nullptr) {
            Node *next = pCur->next;
            
            while (next != nullptr) {
                if (pCur->student.firstName > next->student.firstName)
                    newList.SwapStudents(pCur->student, next->student);
                next = next->next;
            }
            pCur = pCur->next;
        }

        return newList;
    }

    ListStudent SortByMarks() {
        ListStudent newList;
        newList.ReadData();

        Node *pCur = newList.GetStudentHead();

        while (pCur != nullptr) {
            double curMark = (pCur->student.midtermMark + pCur->student.finalMark)/2;
            Node *next = pCur->next;
            
            while (next != nullptr) {
                double nextMark = (next->student.midtermMark + next->student.finalMark)/2;
                if (curMark < nextMark)
                    newList.SwapStudents(pCur->student, next->student);
                next = next->next;
            }
            pCur = pCur->next;
        }

        return newList;
    }
};

// ========================= FUNCTIONS SECTION =========================

void start();

/* Tạm dừng chương trình để người dùng xem danh sách được in */
void pause();

/* In menu */
void Menu();

/*
    Hàm nhận vào 2 tham số: list, option
        ListStudent list: Danh sách sinh viên
        char option: Các lựa chọn để in sinh viên
            - Các giá trị:
                a: Tên đã được sắp xếp theo thứ tự tăng dần
                b: Điểm đã sắp xếp theo thứ tự tăng dần
                c: Lọc ra sinh viên đậu, rớt
                default: In theo thứ tự trong file
*/
void HandlePrint(ListStudent list, char option);


// Menu Handle Functions
void FindStudent(ListStudent list);
void InsertStudent(ListStudent &list);
void DeleteStudent(ListStudent &list);