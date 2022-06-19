#include "functions.h"

void start() {
    Menu();
}

void cls() {
    system("cls");
}

void pause() {
    char tmp;
    cout << endl << "Nhan Enter de tiep tuc...";
    cin.ignore();
    getchar();
    Menu();
}

void Menu() {
    cls();

    int option;

    cout << "***-------------     QUAN LY DANH SACH SINH VIEN     --------------***" << endl;
    cout << "1. Tim kiem thong tin sinh vien theo MSSV" << endl;
    cout << "2. Them sinh vien moi" << endl;
    cout << "3. Xoa sinh vien theo MSSV" << endl;
    cout << "4. In danh sach sinh vien" << endl;
    cout << "5. Thoat" << endl;

    HandleOption();
}

void HandleOption() {
    int option;
    char c;
    string ID;
    Node *pStudentsListHead = nullptr;

    while (true) {
        cout << "Nhap lua chon cua ban:\t";
        cin >> option;
        cin.ignore();

        switch (option) {
            case 1:
                FindStudent();
                pause();
                break;
            
            case 2:
                InsertStudent();
                pause();
                break;
            
            case 3:
                DeleteStudent();
                pause();
                break;
            
            case 4:
                system("cls");
                cout << "***-------------     IN DANH SACH SINH VIEN     --------------***" << endl;
                cout << "a. Theo ten tang dan" << endl;
                cout << "b. Theo diem trung binh giam dan" << endl;
                cout << "c. Theo cac sinh vien Dau, Rot" << endl;
                cout << "Nhap lua chon cua ban:\t";
                while (cin >> c && (c < 'a' || c > 'e') && (c < 'A' || c > 'C'))
                    cout << "Loi! Vui long nhap lua chon hop le:\t";
                HandlePrintStudents(c);
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

bool ReadFile(Node *&pStudentsListHead) {
    ifstream f("students.txt");

    if (pStudentsListHead != nullptr)
        return false;
    else
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
                InsertEnd(pStudentsListHead, student);
        }
    
    f.close();
    return true;
}

void WriteFile(Node *pStudentsListHead) {
    ofstream f("students.txt");

    if (pStudentsListHead == nullptr)
        f << "";

    while (pStudentsListHead != nullptr) {
        Student student = pStudentsListHead->student;
        f << student.ID << "-" << student.lastName << "-" << student.firstName << "-" << student.midtermMark << "-" << student.finalMark << endl;
        pStudentsListHead = pStudentsListHead->pNext;
    }

    f.close();
}

void HandlePrintStudents(char option, string ID) {
    Node *pStudentsListHead = nullptr;
    Node *pPassedStudents = nullptr;
    Node *pFailedStudents = nullptr;
    ReadFile(pStudentsListHead);

    switch (option) {
        case 'a':
            SortStudentsByName(pStudentsListHead);
            
            cls();
            cout << "***-------------     DANH SACH SINH VIEN SAP XEP THEO TEN    --------------***" << endl;
            PrintStudents(pStudentsListHead);
            
            break;
        
        case 'b':
            SortStudentsByMarks(pStudentsListHead);
            
            cls();
            cout << "***-------------     DANH SACH SINH VIEN SAP XEP THEO DIEM    --------------***" << endl;
            PrintStudents(pStudentsListHead);
            
            break;
        
        case 'c':
            pPassedStudents = SeperatePassedStudents(pStudentsListHead);
            pFailedStudents = SeperateFailedStudents(pStudentsListHead);

            cls();
            cout << "***-------------     DANH SACH SINH VIEN DAU    --------------***" << endl;
            PrintStudents(pPassedStudents);
            
            cout << "***-------------     DANH SACH SINH VIEN ROT    --------------***" << endl;
            PrintStudents(pFailedStudents);

            Delete(pPassedStudents);
            Delete(pFailedStudents);
            break;
        
        default:
            cls();
            cout << "***-------------     DANH SACH SINH VIEN    --------------***" << endl;
            PrintStudents(pStudentsListHead);
            break;
    }

    
    Delete(pStudentsListHead);
}

void PrintStudents(Node *pStudentsListHead) {    
    cout << "-------------------------------------------------------------------------------------------------" << endl;
    cout << "|     MSSV     |          Ho          |     Ten     | Diem mon 1 | Diem mon 2 | Diem trung binh |" << endl;
    cout << "-------------------------------------------------------------------------------------------------" << endl;

    while (pStudentsListHead != nullptr) {
        Student s = pStudentsListHead->student;
        
        cout << "|" << setw(14) << Format(s.ID, 14).Center();
        cout << "|" << setw(22) << Format(s.lastName, 22).Left(3);
        cout << "|" << setw(13) << Format(s.firstName, 13).Left(3);
        cout << "|" << setw(12) << Format(s.midtermMark, 12).Right(3);
        cout << "|" << setw(12) << Format(s.finalMark, 12).Right(3);
        cout << "|" << setw(17) << Format((s.midtermMark + s.finalMark)/2, 17).Right(3);
        cout << "|" << endl;
        cout << "-------------------------------------------------------------------------------------------------" << endl;

        pStudentsListHead = pStudentsListHead->pNext;
    }
    cout << endl;
}

// Linked List Functions
void InsertBeginning(Node *&pStudentsListHead, Student student) {
    if (pStudentsListHead == nullptr) {
        pStudentsListHead = new Node;
        pStudentsListHead->student = student;
        pStudentsListHead->pNext = nullptr;
    } else {
        Node *pNew = new Node;
        pNew->student = student;
        pNew->pNext = pStudentsListHead;
        
        pStudentsListHead = pNew;
    }
}

void InsertEnd(Node *&pStudentsListHead, Student student) {
    Node *pCur = pStudentsListHead;

    if (pStudentsListHead == nullptr) {
        pCur = new Node;
        pCur->student = student;
        pCur->pNext = nullptr;

        pStudentsListHead = pCur;
    } else {
        while (pCur->pNext != nullptr)
            pCur = pCur->pNext;

        Node *pNew = new Node;
        pNew->student = student;
        pNew->pNext = nullptr;
        
        pCur->pNext = pNew;
    }
}

Node *FindNode(Node *pStudentsListHead, string ID) {
    while (pStudentsListHead != nullptr && pStudentsListHead->student.ID != ID)
        pStudentsListHead = pStudentsListHead->pNext;
    
    Node *pNew = nullptr;
    if (pStudentsListHead != nullptr) {
        pNew = new Node;
        pNew->student = pStudentsListHead->student;
        pNew->pNext = nullptr;
    }

    return pNew;
}

bool swapNode(Node *&pStudentsListHead, Student A, Student B) {
    Node *pStudentA = pStudentsListHead;
    while (pStudentA != nullptr && pStudentA->student.ID != A.ID)
        pStudentA = pStudentA->pNext;
    
    Node *pStudentB = pStudentsListHead;
    while (pStudentB != nullptr && pStudentB->student.ID != B.ID)
        pStudentB = pStudentB->pNext;

    if (pStudentA == nullptr || pStudentB == nullptr)
        return false;

    pStudentA->student = B;
    pStudentB->student = A;
    
    return true;
}

bool DeleteNode(Node *&pStudentsListHead, string ID) {
    Node *pCur = pStudentsListHead;
    Node *pPrev;
    while (pCur != nullptr && pCur->student.ID != ID) {
        pPrev = pCur;
        pCur = pCur->pNext;
    }
    
    if (pCur == nullptr)
        return false;

    pPrev->pNext = pCur->pNext;
    delete pCur;
    return true;
}

bool Delete(Node *&pStudentsListHead) {
    if (pStudentsListHead == nullptr)
        return false;

    while (pStudentsListHead != nullptr) {
        Node *pCur = pStudentsListHead;
        pStudentsListHead = pStudentsListHead->pNext;
        delete pCur;
    }
    return true;
}

// Student's Functions
void FindStudent() {
    string ID;
    Node *pStudentsListHead = nullptr;
    Node *pStudent = nullptr;

    cout << "Nhap ma sinh vien muon tim:\t";
    getline(cin, ID);
    
    ReadFile(pStudentsListHead);
    
    pStudent = FindNode(pStudentsListHead, ID);
    if (pStudent != nullptr)
        PrintStudents(pStudent);
    else
        cout << "Khong ton tai sinh vien co ma so " << ID << endl;
    delete pStudent;
    
    Delete(pStudentsListHead);
}

void InsertStudent() {
    Node *pStudentsListHead = nullptr;
    Student student;
    
    ReadFile(pStudentsListHead);

    student.getInfo();
    Node *pStudent = FindNode(pStudentsListHead, student.ID);
    if (pStudent == nullptr) {
        InsertEnd(pStudentsListHead, student);
        WriteFile(pStudentsListHead);
    }
    else
        cout << "Loi! Ma sinh vien da ton tai." << endl;

    delete pStudent;
    Delete(pStudentsListHead);
}

void SortStudentsByName(Node *&pStudentsListHead) {
    Node *pCur = pStudentsListHead;

    while (pCur != nullptr) {
        Node *pNext = pCur->pNext;
        
        while (pNext != nullptr) {
            if (pCur->student.firstName > pNext->student.firstName)
                swapNode(pStudentsListHead, pCur->student, pNext->student);
            pNext = pNext->pNext;
        }
        pCur = pCur->pNext;
    }
}

void SortStudentsByMarks(Node *&pStudentsListHead) {
    Node *pCur = pStudentsListHead;

    while (pCur != nullptr) {
        double curMark = (pCur->student.midtermMark + pCur->student.finalMark)/2;
        Node *pNext = pCur->pNext;
        
        while (pNext != nullptr) {
            double nextMark = (pNext->student.midtermMark + pNext->student.finalMark)/2;
            if (curMark < nextMark)
                swapNode(pStudentsListHead, pCur->student, pNext->student);

            pNext = pNext->pNext;
        }
        pCur = pCur->pNext;
    }
}

Node *SeperatePassedStudents(Node *pStudentsListHead) {
    Node *pPassedStudents = nullptr;

    while (pStudentsListHead != nullptr) {
        double totalMark = (pStudentsListHead->student.midtermMark + pStudentsListHead->student.finalMark)/2;
        if (totalMark >= 5)
            InsertEnd(pPassedStudents, pStudentsListHead->student);
        pStudentsListHead = pStudentsListHead->pNext;
    }

    return pPassedStudents;
}

Node *SeperateFailedStudents(Node *pStudentsListHead) {
    Node *pFailedStudents = nullptr;

    while (pStudentsListHead != nullptr) {
        double totalMark = (pStudentsListHead->student.midtermMark + pStudentsListHead->student.finalMark)/2;
        if (totalMark < 5)
            InsertEnd(pFailedStudents, pStudentsListHead->student);
        pStudentsListHead = pStudentsListHead->pNext;
    }

    return pFailedStudents;
}

void DeleteStudent() {
    char c;
    string ID;
    Node *pStudentsListHead = nullptr;

    cout << "Nhap ma sinh vien muon xoa:\t";
    getline(cin, ID);
    ReadFile(pStudentsListHead);
    
    if (DeleteNode(pStudentsListHead, ID)) {
        WriteFile(pStudentsListHead);
        cout << "Da xoa thanh cong sinh vien co ma so " << ID << endl;
        cout << "Ban co muon xem danh sach sinh vien khong (y/n)?\t";
        cin >> c;
        cin.ignore();
        if (c == 'y' || c == 'Y')
            HandlePrintStudents('d');
    } else
        cout << "Ma sinh vien khong ton tai!" << endl;
    
    Delete(pStudentsListHead);
}