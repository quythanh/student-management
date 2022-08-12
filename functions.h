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
    Format(string s, int w);

    Format(double d, int w);

    string Center();

    string Left(int p = 1);

    string Right(int p = 1);
};

struct Student {
    string ID; // MSSV
    string firstName; // Ten
    string lastName; // Ho
    double midtermMark; // Diem mon 1
    double finalMark; // Diem mon 2

    void getInfo();
    void Print();
};

struct Node {
    Student info;
    Node *next;
    
    Node() = default;
    Node(Student info, Node *next = nullptr) {
        this->info = info;
        this->next = next;
    }
};

class ListStudent {
private:
    Node *StudentHead;

public:
    ListStudent();

    ~ListStudent();

    Node *GetStudentHead();

    void ReadData();

    bool isEmpty();

    void WriteStudentsToFile();

    void InsertBeginning(Student newStudent);

    void InsertEnd(Student newStudent, int write = 0);

    Node *SearchStudent(string ID);

    bool SwapStudents(Student A, Student B);

    bool DeleteStudent(string ID);

    void PrintStudent(Node *student = nullptr, int amount = 0);

    bool UpdateStudent(string ID, Student newInfo);

    ListStudent GetPassedStudents();

    ListStudent GetFailedStudents();

    ListStudent SortByName();

    ListStudent SortByMarks();
};

// ========================= FUNCTIONS SECTION =========================

void start();

/* Tạm dừng chương trình để người dùng xem danh sách được in */
void pause();

/* Nhập vào chuỗi tự định dạng lại */
void getString(string &s);

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
void HandlePrint(char option);

// Menu Handle Functions
void MenuSearch();
void MenuInsert();
void MenuDelete();
void MenuUpdate();
void MenuPrint();