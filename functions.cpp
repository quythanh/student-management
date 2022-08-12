#include "functions.h"

// Global Variable
ListStudent list;

/* ================================== STRUCT & CLASS ================================== */

/* Format Section */
Format::Format(string s, int w) {
    str = s;
    width = w;
    padding_left = padding_right = "";
}

Format::Format(double d, int w) {
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

string Format::Center() {
    int pw = width-str.length();

    for (int i = 0; i < pw/2; i++) {
        padding_left += " ";
        padding_right += " ";
    }

    return padding_left + str + padding_right;
}

string Format::Left(int p) {
    int pw = width-str.length()-p;

    for (int i = 0; i < pw; i++)
        padding_right += " ";
    for (int i = 0; i < p; i++)
        padding_left += " ";
    
    return padding_left + str + padding_right;
}

string Format::Right(int p) {
    int pw = width-str.length()-p;

    for (int i = 0; i < pw; i++)
        padding_left += " ";
    for (int i = 0; i < p; i++)
        padding_right += " ";
    
    return padding_left + str + padding_right;
}
/* End Format Section */


/* Student Section */
void Student::getInfo() {
    cout << "Nhap thong tin sinh vien:" << endl;
    cout << " - Ma so sinh vien: ";
    getString(ID);
    // ID = Format(ID).getStr();

    cout << " - Nhap ho ten sinh vien:\n";
    cout << "   + Ho sinh vien: ";
    getString(lastName);
    // lastName = Format(lastName).getStr();
    cout << "   + Ten sinh vien: ";
    getString(firstName);
    // firstName = Format(firstName).getStr();

    cout << " - Nhap diem mon 1: ";
    cin >> midtermMark;
    cin.ignore();
    
    cout << " - Nhap diem mon 2: ";
    cin >> finalMark;
    cin.ignore();
}

void Student::Print() {
    cout << "|" << setw(14) << Format(ID, 14).Center();
    cout << "|" << setw(22) << Format(lastName, 22).Left(3);
    cout << "|" << setw(13) << Format(firstName, 13).Left(3);
    cout << "|" << setw(12) << Format(midtermMark, 12).Right(3);
    cout << "|" << setw(12) << Format(finalMark, 12).Right(3);
    cout << "|" << setw(17) << Format((midtermMark + finalMark)/2, 17).Right(3);
    cout << "|" << endl;
    cout << "-------------------------------------------------------------------------------------------------" << endl;
}
/* End Student Section */


/* ListStudent Section */
ListStudent::ListStudent() {
    StudentHead = nullptr;
}

ListStudent::~ListStudent() {
    while (StudentHead != nullptr) {
        Node *pCur = StudentHead;
        StudentHead = StudentHead->next;
        delete pCur;
    }
}

Node *ListStudent::GetStudentHead() {
    return StudentHead;
}

void ListStudent::ReadData() {
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

bool ListStudent::isEmpty() {
    return StudentHead ? false : true;
}

void ListStudent::WriteStudentsToFile() {
    ofstream f("students.txt");
    Node *p = StudentHead;

    if (p == nullptr)
        f << "";

    while (p != nullptr) {
        Student student = p->info;
        f << student.ID << "-" << student.lastName << "-" << student.firstName << "-" << student.midtermMark << "-" << student.finalMark << endl;
        p = p->next;
    }

    f.close();
}

void ListStudent::InsertBeginning(Student newStudent) {
    StudentHead = new Node(newStudent, StudentHead);
}

void ListStudent::InsertEnd(Student newStudent, int write) {
    if (StudentHead == nullptr)
        StudentHead = new Node(newStudent);
    else {
        Node *p = StudentHead;
        while (p->next != nullptr)
            p = p->next;
        p->next = new Node(newStudent);
    }

    if (write)
        WriteStudentsToFile();
}

Node *ListStudent::SearchStudent(string ID) {
    Node *student = StudentHead;
    while (student != nullptr && student->info.ID != ID)
        student = student->next;       
    return student;
}

bool ListStudent::SwapStudents(Student A, Student B) {
    Node *StudentA = SearchStudent(A.ID);
    Node *StudentB = SearchStudent(B.ID);

    if (StudentA == nullptr || StudentB == nullptr)
        return false;

    StudentA->info = B;
    StudentB->info = A;
    return true;
}

bool ListStudent::DeleteStudent(string ID) {
    Node *pCur = StudentHead;
    Node *pPrev;
    while (pCur != nullptr && pCur->info.ID != ID) {
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

void ListStudent::PrintStudent(Node *student, int amount) {
    if (StudentHead == nullptr) {
        cout << "Danh sach rong!\n";
        return;
    }

    cout << "-------------------------------------------------------------------------------------------------" << endl;
    cout << "|     MSSV     |          Ho          |     Ten     | Diem mon 1 | Diem mon 2 | Diem trung binh |" << endl;
    cout << "-------------------------------------------------------------------------------------------------" << endl;

    Node *pCur = student ? student : StudentHead;
    if (!amount) {
        while (pCur != nullptr) {
            pCur->info.Print();
            pCur = pCur->next;
        }
        cout << endl;
        return;
    }

    while (amount-- && pCur != nullptr) {
        pCur->info.Print();
        pCur = pCur->next;
    }
    cout << endl;
}

bool ListStudent::UpdateStudent(string ID, Student newInfo) {
    Node *student = SearchStudent(ID);
    if (newInfo.ID != ID && SearchStudent(newInfo.ID))
        return false;
    student->info = newInfo;
    WriteStudentsToFile();
    return true;
}

ListStudent ListStudent::GetPassedStudents() {
    Node *student = StudentHead;
    ListStudent ListPassedStudents;

    while (student != nullptr) {
        double totalMark = (student->info.midtermMark + student->info.finalMark)/2;
        if (totalMark >= 5)
            ListPassedStudents.InsertEnd(student->info);
        student = student->next;
    }

    return ListPassedStudents;
}

ListStudent ListStudent::GetFailedStudents() {
    Node *student = StudentHead;
    ListStudent ListFailedStudents;

    while (student != nullptr) {
        double totalMark = (student->info.midtermMark + student->info.finalMark)/2;
        if (totalMark < 5)
            ListFailedStudents.InsertEnd(student->info);
        student = student->next;
    }

    return ListFailedStudents;
}

ListStudent ListStudent::SortByName() {
    ListStudent newList;
    newList.ReadData();
    
    Node *pCur = newList.GetStudentHead();

    while (pCur != nullptr) {
        Node *next = pCur->next;
        
        while (next != nullptr) {
            if (pCur->info.firstName > next->info.firstName)
                newList.SwapStudents(pCur->info, next->info);
            next = next->next;
        }
        pCur = pCur->next;
    }

    return newList;
}

ListStudent ListStudent::SortByMarks() {
    ListStudent newList;
    newList.ReadData();

    Node *pCur = newList.GetStudentHead();

    while (pCur != nullptr) {
        double maxMark = pCur->info.midtermMark + pCur->info.finalMark;
        Node *max = pCur;
        Node *pNext = pCur->next;
        
        while (pNext != nullptr) {
            double nextMark = pNext->info.midtermMark + pNext->info.finalMark;
            if (nextMark > maxMark) {
                max = pNext;
                maxMark = nextMark;
            }
            pNext = pNext->next;
        }

        if (max != pCur)
            newList.SwapStudents(pCur->info, max->info);

        pCur = pCur->next;
    }

    return newList;
}
/* End ListStudent Section */

/* ================================== FUNCTIONS ================================== */

void start() {
    system("cls");
    list.ReadData();
    Menu();
}

void pause() {
    char tmp;
    cout << endl << "Nhan Enter de tiep tuc...";
    getchar();
    system("cls");
}

void getString(string &s) {
    getline(cin, s);

    int start = 0, end = s.length() - 1;
    while (s[end] == ' ')
        end--;
    while (s[start] == ' ')
        start++;

    for (int i = start; i < end;)
        if (s[i] == ' ' && s[i + 1] == ' ') {
            s.erase(i, 1);
            end--;
        }
        else
            i++;
    s = s.substr(start, end - start + 1);
}

void Menu() {
    char c;
    string id;
    int option;

    while (true) {
        cout << "***-------------     QUAN LY DANH SACH SINH VIEN     --------------***" << endl;
        cout << "1. Tim kiem thong tin sinh vien theo MSSV" << endl;
        cout << "2. Them sinh vien moi" << endl;
        cout << "3. Xoa sinh vien theo MSSV" << endl;
        cout << "4. Sua thong tin sinh vien" << endl;
        cout << "5. In danh sach sinh vien" << endl;
        cout << "6. Thoat" << endl;
        cout << "Nhap lua chon cua ban:\t";
        cin >> option;
        cin.ignore();
        system("cls");

        switch (option) {
            case 1:
                MenuSearch();
                pause();
                break;
            
            case 2:
                MenuInsert();
                pause();
                break;
            
            case 3:
                MenuDelete();
                pause();
                break;
            
            case 4:
                MenuUpdate();
                pause();
                break;
            
            case 5:
                MenuPrint();
                pause();
                break;
            
            case 6:
                exit(0);
                break;
            
            default:
                cout << "Loi! Vui long nhap lai!\n";
                break;
        }
    }
}

void HandlePrint(char option) {
    system("cls");
    ListStudent newList;
    switch (option) {
        case 'a':
            cout << Format("***--------------     DANH SACH SINH VIEN SAP XEP THEO TEN    --------------***", 97).Center() << endl;
            list.SortByName().PrintStudent();
            break;

        case 'b':
            cout << Format("***--------------     DANH SACH SINH VIEN SAP XEP THEO DIEM    --------------***", 97).Center() << endl;
            list.SortByMarks().PrintStudent();
            break;

        case 'c':
            cout << Format("***--------------     DANH SACH SINH VIEN DAU    --------------***", 97).Center() << endl;
            list.GetPassedStudents().PrintStudent();

            cout << Format("***--------------     DANH SACH SINH VIEN ROT    --------------***", 97).Center() << endl;
            list.GetFailedStudents().PrintStudent();
            break;

        default:
            cout << Format("***--------------     DANH SACH SINH VIEN    --------------***", 97).Center() << endl;
            list.PrintStudent();
            break;
    }
}

// Menu Handle Functions
void MenuSearch() {
    string ID;
    cout << "Nhap ma sinh vien muon tim:\t";
    getline(cin, ID);
    
    Node *student = list.SearchStudent(ID);
    
    if (student)
        list.PrintStudent(student, 1);
    else
        cout << "Khong ton tai sinh vien co ma so " << ID << endl;
}

void MenuInsert() {
    Student student;
    student.getInfo();

    Node *pStudent = list.SearchStudent(student.ID);
    if (pStudent == nullptr)
        list.InsertEnd(student, 1);
    else
        cout << "Loi! Ma sinh vien da ton tai." << endl;
}

void MenuDelete() {
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

void MenuUpdate() {
    string ID;
    char option;

    cout << "Nhap ma sinh vien muon chinh sua: ";
    getline(cin, ID);
    Node *p = list.SearchStudent(ID);
    if (p == nullptr) {
        cout << "Khong ton tai sinh vien co ma " << ID << endl;
        return;
    }
    Student student = p->info;
    
    system("cls");
    cout << "***-------------     CAP NHAT THONG TIN SINH VIEN     --------------***" << endl;
    cout << "a. Chinh sua MSSV" << endl;
    cout << "b. Chinh sua ho ten" << endl;
    cout << "c. Chinh sua diem" << endl;
    cout << "d. Chinh sua toan bo" << endl;
    cout << "e. Thoat" << endl;
    cout << "Nhap lua chon cua ban:\t";
    while (cin >> option && (option < 'a' || option > 'e') && (option < 'A' || option > 'E'))
        cout << "Loi! Vui long nhap lua chon hop le:\t";
    cin.ignore();
    
    
    system("cls");

    switch (option)
    {
        case 'a':
            cout << " - Nhap MSSV moi: ";
            getString(student.ID);
            break;

        case 'b':
            cout << " - Nhap ho ten sinh vien:\n";
            cout << "   + Ho sinh vien: ";
            getString(student.lastName);
            cout << "   + Ten sinh vien: ";
            getString(student.firstName);
            break;

        case 'c':
            cout << " - Chinh sua diem:\n";
            cout << "   + Nhap diem mon 1: ";
            cin >> student.midtermMark;
            cin.ignore();
            cout << "   + Nhap diem mon 2: ";
            cin >> student.finalMark;
            cin.ignore();
            break;

        case 'd':
            student.getInfo();
            break;

        default:
            break;
    }

    if (list.UpdateStudent(ID, student))
        cout << "Cap nhat thong tin sinh vien thanh cong!\n";
    else
        cout << "Cap nhat that bai! Ma sinh vien da ton tai, vui long nhap ma khac.\n";
}

void MenuPrint() {
    char c;

    cout << "***-------------     IN DANH SACH SINH VIEN     --------------***" << endl;
    cout << "a. Theo ten tang dan" << endl;
    cout << "b. Theo diem trung binh giam dan" << endl;
    cout << "c. Theo cac sinh vien Dau, Rot" << endl;
    cout << "Nhap lua chon cua ban:\t";
    while (cin >> c && (c < 'a' || c > 'c') && (c < 'A' || c > 'C'))
        cout << "Loi! Vui long nhap lua chon hop le:\t";
    cin.ignore();
    HandlePrint(c);
}