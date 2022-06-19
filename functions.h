#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdio> // getchar

using namespace std;

// ========================= STRUCTS SECTION =========================
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
};

struct Node {
    Student student;
    Node *pNext;
};

class Format {
private:
    string str;
    int width;

public:
    Format(string s, int w) {
        str = s;
        width = w;
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
    }

    string Center() {
        string padding_left = "";
        string padding_right = "";
        int pw = width-str.length();
        
        for (int i = 0; i < pw/2; i++) {
            padding_left += " ";
            padding_right += " ";
        }
        
        return padding_left + str + padding_right;
    }

    string Left(int p = 1) {
        string padding_left = "";
        string padding_right = "";
        int pw = width-str.length()-p;
        
        for (int i = 0; i < pw; i++)
            padding_right += " ";
        for (int i = 0; i < p; i++)
            padding_left += " ";
        
        return padding_left + str + padding_right;
    }

    string Right(int p = 1) {
        string padding_left = "";
        string padding_right = "";
        int pw = width-str.length()-p;
        
        for (int i = 0; i < pw; i++)
            padding_left += " ";
        for (int i = 0; i < p; i++)
            padding_right += " ";
        
        return padding_left + str + padding_right;
    }
};

// ========================= FUNCTIONS SECTION =========================

// General Functions
void start();
void pause();
void cls();
void Menu();
void HandleOption();

// File
bool ReadFile(Node *&pStudentsListHead);
void WriteFile(Node *pStudentsListHead);

// Print & Format
void HandlePrintStudents(char option, string ID = "") ;
void PrintStudents(Node *pStudentsListHead);

// Linked List Functions
void InsertBeginning(Node *&pStudentsListHead, Student student);
void InsertEnd(Node *&pStudentsListHead, Student student);

Node *FindNode(Node *pStudentsListHead, string ID);

bool swapNode(Node *&pStudentsListHead, Student A, Student B);

bool DeleteNode(Node *&pStudentsListHead, string ID);
bool Delete(Node *&pStudentsListHead);

// Student's Functions
void FindStudent();
void InsertStudent();
void SortStudentsByName(Node *&pStudentsListHead);
void SortStudentsByMarks(Node *&pStudentsListHead);
Node *SeperatePassedStudents(Node *pStudentsListHead);
Node *SeperateFailedStudents(Node *pStudentsListHead);
void DeleteStudent();