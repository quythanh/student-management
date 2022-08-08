#include "functions.h"

void start() {
    system("cls");
    Menu();
}

void pause() {
    char tmp;
    cout << endl << "Nhan Enter de tiep tuc...";
    getchar();
    system("cls");
}

void Menu() {
    char c;
    int option;
    ListStudent list;
    list.ReadData();

    while (true) {
        cout << "***-------------     QUAN LY DANH SACH SINH VIEN     --------------***" << endl;
        cout << "1. Tim kiem thong tin sinh vien theo MSSV" << endl;
        cout << "2. Them sinh vien moi" << endl;
        cout << "3. Xoa sinh vien theo MSSV" << endl;
        cout << "4. In danh sach sinh vien" << endl;
        cout << "5. Thoat" << endl;
        cout << "Nhap lua chon cua ban:\t";
        cin >> option;
        cin.ignore();

        switch (option) {
            case 1:
                FindStudent(list);
                pause();
                break;
            
            case 2:
                InsertStudent(list);
                pause();
                break;
            
            case 3:
                DeleteStudent(list);
                pause();
                break;
            
            case 4:
                system("cls");
                cout << "***-------------     IN DANH SACH SINH VIEN     --------------***" << endl;
                cout << "a. Theo ten tang dan" << endl;
                cout << "b. Theo diem trung binh giam dan" << endl;
                cout << "c. Theo cac sinh vien Dau, Rot" << endl;
                cout << "Nhap lua chon cua ban:\t";
                while (cin >> c && (c < 'a' || c > 'c') && (c < 'A' || c > 'C'))
                    cout << "Loi! Vui long nhap lua chon hop le:\t";
                cin.ignore();
                HandlePrint(list, c);
                pause();
                break;
            
            case 5:
                exit(0);
                break;
            
            default:
                cout << "Loi! Vui long nhap lai!\n";
                break;
        }
    }
}

void HandlePrint(ListStudent list, char option) {
    system("cls");
    ListStudent newList;
    switch (option) {
        case 'a':
            cout << "***-------------     DANH SACH SINH VIEN SAP XEP THEO TEN    --------------***" << endl;
            list.SortByName().PrintStudent();
            break;

        case 'b':
            cout << "***-------------     DANH SACH SINH VIEN SAP XEP THEO DIEM    --------------***" << endl;
            list.SortByMarks().PrintStudent();
            break;

        case 'c':
            // Danh sach sinh vien dau
            newList = list.GetPassedStudents();
            if (!newList.isEmpty()) {
                cout << "***-------------     DANH SACH SINH VIEN DAU    --------------***" << endl;
                newList.PrintStudent();
            }

            // Danh sach sinh vien rot
            newList = list.GetFailedStudents();
            if (!newList.isEmpty()) {
                cout << "***-------------     DANH SACH SINH VIEN ROT    --------------***" << endl;
                newList.PrintStudent();
            }
            break;

        default:
            cout << "***-------------     DANH SACH SINH VIEN    --------------***" << endl;
            list.PrintStudent();
            break;
    }
}


// Menu Handle Functions
void FindStudent(ListStudent list) {
    string ID;
    cout << "Nhap ma sinh vien muon tim:\t";
    getline(cin, ID);
    
    Node *student = list.SearchStudent(ID);
    
    if (student)
        list.PrintStudent(student, 1);
    else
        cout << "Khong ton tai sinh vien co ma so " << ID << endl;
}

void InsertStudent(ListStudent &list) {
    Student student;
    student.getInfo();

    Node *pStudent = list.SearchStudent(student.ID);
    if (pStudent == nullptr)
        list.InsertEnd(student, 1);
    else
        cout << "Loi! Ma sinh vien da ton tai." << endl;
}

void DeleteStudent(ListStudent &list) {
    char c;
    string ID;

    cout << "Nhap ma sinh vien muon xoa:\t";
    getline(cin, ID);
    
    if (list.DeleteStudent(ID)) {
        cout << "Da xoa thanh cong sinh vien co ma so " << ID << endl;
        cout << "Ban co muon xem danh sach sinh vien khong (y/n)?\t";
        cin >> c;
        cin.ignore();
        if (c == 'y' || c == 'Y')
            list.PrintStudent();
    } else
        cout << "Ma sinh vien khong ton tai!" << endl;
}