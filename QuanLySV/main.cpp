#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include<fstream>
#include<sstream>
using namespace std;


template <class T>
class LinkedList {
private:
	struct Node {
		T data;
		Node* next;

		Node(T value) : data(value), next(nullptr) {}
	};

	Node* head;
	Node* tail;

public:
	LinkedList() : head(nullptr), tail(nullptr) {}
	//them dau 
	void push_front(T value) {
		Node* newNode = new Node(value);
		newNode->next = head;
		head = newNode;
		if (tail == nullptr) {
			tail = head;
		}
	}
	//them cuoi 
	void push_back(T value) {
		Node* newNode = new Node(value);
		if (tail == nullptr) {
			head = tail = newNode;
		}
		else {
			tail->next = newNode;
			tail = newNode;
		}
	}
	//them bat ky
	void push_by_position(T value, int position)
	{
		if (position < 1)
		{
			cout << "Khong hop le" << endl;
		}
		Node* newNode = new Node(value);
		if (position == 1)
		{
			newNode->next = head;
			head = newNode;
			if (tail == nullptr)
			{
				tail = newNode;
			}
			else 
			{
				Node* current = head;
				for (int i = 1; i < position && current != nullptr; i++)
				{
					current = current->next;
				}

				if (current == nullptr)
				{
					cout << "Khong co vi tri hop le";
					delete newNode;
					return;
				}
				newNode->next = current->next;
				current->next = newNode;
				if (newNode->next == nullptr)
				{
					tail = newNode;
				}
			}
		}
	}

	T front() const {
		return head->data;
	}

	T back() const {
		return tail->data;
	}


	void pop_front() {
		if (head == nullptr) {
			return;
		}

		Node* nodeToDelete = head;
		head = head->next;
		delete nodeToDelete;

		if (head == nullptr) {
			tail = nullptr;
		}
	}

	void pop_back() {
		if (tail == nullptr) {
			return;
		}

		Node* current = head;
		while (current->next != tail) {
			current = current->next;
		}

		Node* nodeToDelete = tail;
		tail = current;
		tail->next = nullptr;
		delete nodeToDelete;
	}

	T at(int index) const {
		if (index < 0 || index >= size()) {
			throw out_of_range("Index out of range");
		}

		Node* current = head;
		for (int i = 0; i < index; i++) {
			current = current->next;
		}

		return current->data;
	}

	void erase(int index) {
		if (index < 0 || index >= size()) {
			throw out_of_range("Index out of range");
		}

		if (index == 0) {
			pop_front();
			return;
		}

		if (index == size() - 1) {
			pop_back();
			return;
		}

		Node* previous = head;
		for (int i = 0; i < index - 1; i++) {
			previous = previous->next;
		}

		Node* current = previous->next;
		previous->next = current->next;
		delete current;
	}

	void reverse() {
		Node* prev = nullptr;
		Node* current = head;
		Node* next = nullptr;

		while (current != nullptr) {
			next = current->next;
			current->next = prev;
			prev = current;
			current = next;
		}

		tail = head;
		head = prev;
	}

	void concat(LinkedList<T> otherList) {
		if (head == nullptr) {
			head = otherList.head;
			tail = otherList.tail;
		}
		else {
			tail->next = otherList.head;
			tail = otherList.tail;
		}
	}

	void bubbleSort() {
		bool swapped;

		do {
			swapped = false;
			Node* curr = head;
			Node* prev = nullptr;

			while (curr->next) {
				if (curr->data.score1 < curr->next->data.score1) {
					if (!prev) {
						head = curr->next;
					}
					else {
						prev->next = curr->next;
					}

					Node* temp = curr->next;
					curr->next = temp->next;
					temp->next = curr;

					curr = temp;
					swapped = true;
				}

				prev = curr;
				curr = curr->next;
			}
		} while (swapped);
	}

	LinkedList<T> cloneList() {
		LinkedList<T> clonedList;

		if (head == nullptr) {
			return clonedList;
		}

		clonedList.head = new typename LinkedList<T>::Node(head->data);
		typename LinkedList<T>::Node* originalCurrent = head->next;
		typename LinkedList<T>::Node* clonedCurrent = clonedList.head;

		while (originalCurrent != nullptr) {
			clonedCurrent->next = new typename LinkedList<T>::Node(originalCurrent->data);
			originalCurrent = originalCurrent->next;
			clonedCurrent = clonedCurrent->next;
		}

		clonedList.tail = clonedCurrent;

		return clonedList;
	}

	int size() const {
		int size = 0;
		Node* current = head;
		while (current != nullptr) {
			size++;
			current = current->next;
		}
		return size;
	}

	class Iterator {
	private:
		Node* current;

	public:
		Iterator(Node* node) : current(node) {}

		T& operator*() {
			return current->data;
		}

		Iterator& operator++() {
			current = current->next;
			return *this;
		}

		bool operator!=(const Iterator& other) {
			return current != other.current;
		}
	};

	Iterator begin() const {
		return Iterator(head);
	}

	Iterator end() const {
		return Iterator(nullptr);
	}
};


class Student {
public:
	string name;
	string studentID;
	string subject1;
	int score1;
	string subject2;
	int score2;
	Student(string n, string id, string s1, int scr1, string s2, int scr2) : name(n), studentID(id), subject1(s1), score1(scr1), subject2(s2), score2(scr2) {}
};

class Class {
public:
	string name;
	string classID;
	LinkedList<Student> studentList;
	int size;
public:
	Class(string n, string c) : name(n), classID(c) , size(0){}

	//Them hs vao dau
	void addStudentFront(const Student& student) {
		studentList.push_front(student);
		size++;
	}
	//Them hs vao cuoi
	void addStudent(const Student& student) {
		studentList.push_back(student);
		size++;
	}
	//Them hs vao bat ki vi tri
	void addStudentByPosition(const Student& student, int position) {
		studentList.push_by_position(student, position);
		size++;
	}
	//Xoa hs o dau 
	void deleteStudentFront() {
		studentList.pop_front();
		size--;
	}
	//Xoa hs o cuoi
	void deleteStudentBack() {
		studentList.pop_back();
		size--;
	}
	//Xoa hs o vi tri bat ky
	void deleteStudentByPosition(int position) {
		if (position < 1 || position > studentList.size()) {
			throw out_of_range("Vi tri khong hop le");
		}

		studentList.erase(position - 1);
		size--;
	}

	void inStudent() const {
		for (const Student& student : studentList) {
			cout << "\n---------------------------------------------------------------------";
			cout << "\n MSSV: " << student.studentID;
			cout << "\n Ho va ten: " << student.name;
			cout << "\n Ten mon hoc 1: " << student.subject1;
			cout << "\n Diem mon hoc 1: " << student.score1;
			cout << "\n Ten mon hoc 2: " << student.subject2;
			cout << "\n Diem mon hoc 2: " << student.score2;
		}
	}
};


class LISTClass
{
public:

	LinkedList<Class> classList;


	void addClass(const Class& Class) {
		classList.push_back(Class);
	}

	int findClass(const string& classID) {
		int dem = 0;
		for (Class& classObj : classList) {
			if (classObj.classID == classID) {
				return dem;
			}
			else dem++;
		}
		return -1;
	}

	//them hs vao dau
	void addFirstStudent(const string& classID, Student student) {
		int index = findClass(classID);
		if (index != -1) {
			LinkedList<Class>::Iterator it = classList.begin();
			for (int i = 0; i < index; i++) {
				++it;
			}
			Class& classToUpdate = *it;
			classToUpdate.addStudentFront(student);
			classToUpdate.size += 1;
		}
	}
	//them hs vao cuoi
	void addFinalStudent(const string& classID, Student student) {
		int index = findClass(classID);
		if (index != -1) {
			LinkedList<Class>::Iterator it = classList.begin();
			for (int i = 0; i < index; i++) {
				++it;
			}
			Class& classToUpdate = *it;
			classToUpdate.addStudent(student);
			classToUpdate.size += 1;

		}
	}
	//them hs theo vi tri
	void addByPositionStudent(const string& classID, Student student, int position) {
		int index = findClass(classID);
		if (index != -1) {
			LinkedList<Class>::Iterator it = classList.begin();
			for (int i = 0; i < index; i++) {
				++it;
			}
			Class& classToUpdate = *it;
			classToUpdate.size += 1;
			classToUpdate.addStudentByPosition(student, position);

		}
	}
	//xoa hs dau tien
	void deleteFirstStudent(const string& classID) {
		int index = findClass(classID);
		if (index != -1) {
			LinkedList<Class>::Iterator it = classList.begin();
			for (int i = 0; i < index; i++) {
				++it;
			}
			Class& classToUpdate = *it;

			classToUpdate.deleteStudentFront();

		}
	}
	//xoa hs cuoi cung
	void deleteFinalStudent(const string& classID) {
		int index = findClass(classID);
		if (index != -1) {
			LinkedList<Class>::Iterator it = classList.begin();
			for (int i = 0; i < index; i++) {
				++it;
			}
			Class& classToUpdate = *it;

			classToUpdate.deleteStudentBack();

		}
	}
	//xoa hs theo vi tri bat ky
	void deleteByPositionStudent(const string& classID, int position) {
		int index = findClass(classID);
		if (index != -1) {
			LinkedList<Class>::Iterator it = classList.begin();
			for (int i = 0; i < index; i++) {
				++it;
			}
			Class& classToUpdate = *it;
			classToUpdate.deleteStudentByPosition(position);
		}
	}
	//Tim vi tri hoc sinh
	int findStudentPositionById(string classId, string studentId) {
		int index = findClass(classId);
		if (index != -1) {
			LinkedList<Class>::Iterator it = classList.begin();
			for (int i = 0; i < index; i++) {
				++it;
			}
			Class& classToUpdate = *it;

			LinkedList<Student>::Iterator st = classToUpdate.studentList.begin();
			for (int j = 0; j < classToUpdate.size; j++) {
				Student& tempSt = *st;
				if (tempSt.studentID == studentId) {
					return j;
				}
				++st;
			}
		}
		return -1;
	}
	void inclass()
	{

		for (const Class& Class : classList) {
			cout << Class.name << " - ";
			cout << Class.classID << endl;
		}
	}


	void inStudentofclass(const string& classid)
	{

		for (const Class& Class : classList) {
			if (Class.classID == classid)
			{
				cout << "\n---------------------------------------------------------------------";
				cout << "\nLop danh sach sinh vien lop " << Class.name << "  : " << endl;
				Class.inStudent();
			}

		}
	}

	void inAllStudent()
	{
		for (const Class& Class : classList) {
			{
				cout << "\n---------------------------------------------------------------------";
				cout << "\nLop danh sach sinh vien lop " << Class.name << "  : " << endl;
				Class.inStudent();
			}

		}
	}

	LinkedList<Student> sortByDM1() {
		LinkedList<Student> students;
		for (const Class& Class : classList) {
			{
				LinkedList<Student> studentList = Class.studentList;
				LinkedList<Student> tempList = studentList.cloneList();
				students.concat(tempList);
			}
		}
		LinkedList<Student> newList = students.cloneList();
		newList.bubbleSort();
		return newList;
	}

	void printStudentsByDM1Desc()
	{
		LinkedList<Student> sortedStudents = sortByDM1();

		for (const Student& student : sortedStudents) {
			cout << "\n---------------------------------------------------------------------";
			cout << "\n MSSV: " << student.studentID;
			cout << "\n Ho va ten: " << student.name;
			cout << "\n Diem mon hoc 1: " << student.score1;
		}
	}

	void printStudentsByDM1Asc() {
		LinkedList<Student> sortedStudentsDesc = sortByDM1();
		sortedStudentsDesc.reverse();
		for (const Student& student : sortedStudentsDesc) {
			cout << "\n---------------------------------------------------------------------";
			cout << "\n MSSV: " << student.studentID;
			cout << "\n Ho va ten: " << student.name;
			cout << "\n Diem mon hoc 1: " << student.score1;
		}
	}

	void exportStudentByClassIdToCSV(string filePath, string classId)
	{
		for (const Class& Class : classList) {
			if (Class.classID == classId)
			{
				ofstream outFile(filePath);
				if (!outFile.is_open()) {
					cout << "Khong the mo file de ghi du lieu.\n";
					return;
				}

				outFile << Class.classID << "," << Class.name << "\n";
				outFile << "Id,Ho va ten,Ma mon hoc 1,Diem mon hoc 1,Ma mon hoc 2,Diem mon hoc 2\n";
				for (const Student& student : Class.studentList) {
					outFile << student.studentID << "," << student.name << ","
						<< student.subject1 << "," << student.score1 << "," << student.subject2 << "," << student.score2 << "\n";
				}
				outFile.close();
				cout << "Xuat du lieu thanh cong.\n";
			}
		}
	}

	void exportAllStudentToCSV(string filePath)
	{
		ofstream outFile(filePath);
		if (!outFile.is_open()) {
			cout << "Khong the mo file de ghi du lieu.\n";
			return;
		}

		for (const Class& Class : classList) {
			{
				outFile << Class.classID << "," << Class.name << "\n";
				outFile << "Id,Ho va ten,Ma mon hoc 1,Diem mon hoc 1,Ma mon hoc 2,Diem mon hoc 2\n";
				for (const Student& student : Class.studentList) {
					outFile << student.studentID << "," << student.name << ","
						<< student.subject1 << "," << student.score1 << "," << student.subject2 << "," << student.score2 << "\n";
				}
				outFile << "\n\n";
			}
		}

		outFile.close();
		cout << "Xuat du lieu thanh cong.\n";
	}

	void importClassfromCSV(string filename) {		
		ifstream file(filename);

		if (!file.is_open()) {
			cerr << "Khong the mo duoc file." << endl;
			return;
		}

		string line;
		bool isFirstLine = true;

		while (getline(file, line)) {
			if (isFirstLine) {
				isFirstLine = false;
				continue;
			}

			stringstream ss(line);
			string classID, className;

			getline(ss, classID, ',');
			getline(ss, className, ',');

			Class newClass = Class(className, classID);
			classList.push_back(newClass);
		}

		file.close();

		return;
	}
	
	void importStudentsfromCSV(string filename) {
		ifstream file(filename);

		if (!file.is_open()) {
			cerr << "Khong the mo duoc file." << endl;
			return;
		}

		string line;
		bool isFirstLine = true;

		while (getline(file, line)) {
			if (isFirstLine) {
				isFirstLine = false;
				continue;
			}

			stringstream ss(line);
			string classID, studentId, studentName, subject1, sc1, subject2, sc2;

			getline(ss, classID, ',');
			getline(ss, studentId, ',');
			getline(ss, studentName, ',');
			getline(ss, subject1, ',');
			getline(ss, sc1, ',');
			getline(ss, subject2, ',');
			getline(ss, sc2, ',');
			int score1 = ParseInt(sc1);
			int score2 = ParseInt(sc2);

			int test = findClass(classID);
			if (test != -1)
			{
				Student newStudent = Student(studentName, studentId, subject1, score1, subject2, score2);
				addFinalStudent(classID, newStudent);
			}
		}

		file.close();

		return;
	}

	int ParseInt(const string& str) {
		try {
			int result = stoi(str);

			if (result < 0 || result > 10) {
				return 0;
			}

			return result;
		}
		catch (const invalid_argument&) {
			return 0;
		}
		catch (const out_of_range&) {
			return 0;
		}
	}
};

int main() {

	LISTClass admin;
	admin.importClassfromCSV("class.csv");
	admin.importStudentsfromCSV("student.csv");

	int Select;
	while (true)
	{

		system("CLS");
		cout << "1. Tao lop hoc: " << endl;
		cout << "2. Them sinh vien vao lop hoc: " << endl;
		cout << "3. Xoa sinh vien khoi lop hoc: " << endl;
		cout << "4. Nhap danh sach lop tu file: " << endl;
		cout << "5. Nhap danh sach sinh vien tu file: " << endl;
		cout << "6. Xuat danh sach sinh vien ra file theo lop: " << endl;
		cout << "7. Xuat tat ca sinh vien ra file: " << endl;
		cout << "8. Xuat thong tin sinh vien theo lop: " << endl;
		cout << "9. Xuat thong tin sinh vien tat ca cac lop: " << endl;
		cout << "10. Xuat thong tin sinh vien theo diem mon hoc 1 tu cao den thap: " << endl;
		cout << "11. Xuat thong tin sinh vien theo diem mon hoc 1 tu thap den cao: " << endl;
		cout << "\nNhap lua chon" << endl;
		cin >> Select;
		if (Select == 1)
		{
			string classname, classid;
			cout << "\nMoi nhap ten lop hoc: ";
			cin >> classname;
			cout << "\nMoi nhap ma lop hoc: ";
			cin >> classid;
			Class tempclass(classname, classid);

			admin.addClass(tempclass);
			admin.inclass();
			cout << "\nNhap phim bat ky de quay lai menu";
			system("PAUSE>NULL");
		}
		else if (Select == 2)
		{
			string classid = "";
			cout << "\nBan muon them vao lop hoc nao: ";
			cin >> classid;

			int tem;
			cout << "1.Them sinh vien vao dau tien: " << endl;
			cout << "2.Them sinh vien vao cuoi cung: " << endl;
			cout << "3.Them sinh vien vao vi tri bat ky: " << endl;
			cin >> tem;

			int test = admin.findClass(classid);
			if (test != -1)
			{
				string name, id, subject1, subject2;
				int score1, score2, position;
				cout << "Nhap thong tin sinh vien: ";
				cout << "\nNhap ID: ";
				cin >> id;
				cout << "\nNhap ten sinh vien: ";
				cin >> name;
				cout << "\nNhap ten mon hoc 1: ";
				cin >> subject1;
				cout << "\nNhap diem mon hoc 1: ";
				cin >> score1;
				cout << "\nNhap ten mon hoc 2: ";
				cin >> subject2;
				cout << "\nNhap diem mon hoc 2: ";
				cin >> score2;
				if (cin.fail()) {
					cout << "\nNhap sai vui long nhap lai" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				if (tem == 1)
				{
					Student tempstudent(name, id, subject1, score1, subject2, score2);
					admin.addFirstStudent(classid, tempstudent);
				}
				else if (tem == 2)
				{
					Student tempstudent(name, id, subject1, score1, subject2, score2);
					admin.addFinalStudent(classid, tempstudent);
				}
				else if (tem == 3)
				{
					cout << "\nNhap vi tri: ";
					cin >> position;

					if (cin.fail()) {
						cout << "\nNhap sai vui long nhap lai" << endl;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
					Student tempstudent(name, id, subject1, score1, subject2, score2);
					admin.addByPositionStudent(classid, tempstudent, position);
				}
			}
			cout << "\nNhap phim bat ky de quay lai menu\n";
			system("PAUSE>NULL");

		}
		else if (Select == 3)
		{
			string classid = "";
			cout << "\nBan muon xoa sinh vien thuoc lop hoc nao: ";
			cin >> classid;
			int test = admin.findClass(classid);
			if (test != -1)
			{
				int tem;
				cout << "\n1.Xoa sinh vien dau tien: ";
				cout << "\n2.Xoa sinh vien cuoi cung: ";
				cout << "\n3.Xoa sinh vien o vi tri bat ky: ";
				cout << "\n4.Xoa sinh vien theo MSSV: ";
				cin >> tem;
				if (tem == 1)
				{
					admin.deleteFirstStudent(classid);
				}
				else if (tem == 2)
				{
					admin.deleteFinalStudent(classid);
				}
				else if (tem == 3)
				{
					int position;
					cout << "\nNhap vi tri sinh vien can xoa: ";
					cin >> position;
					try {
						admin.deleteByPositionStudent(classid, position);
						cout << "\nXoa sinh vien tai vi tri " << position << " thanh cong.";
					}
					catch (const out_of_range& e) {
						cout << "\nLoi: " << e.what();
					}
				}
				else if (tem == 4) {
					string mssv;
					cout << "\nNhap mssv can xoa: ";
					cin >> mssv;
					try {
						int position = admin.findStudentPositionById(classid, mssv);
						if (position == -1) {
							cout << "\nKhong tim thay mssv";
						}
						else {
							admin.deleteByPositionStudent(classid, position);
							cout << "\nXoa sinh vien voi mssv: " << mssv << " thanh cong.";
						}
					}
					catch (const out_of_range& e) {
						cout << "\nLoi: " << e.what();
					}
				}
			}
			cout << "\nNhap phim bat ky de quay lai menu";
			system("PAUSE>NULL");

		}
		else if (Select == 4)
		{
			string fileName;
			cout << "\n vui long nhap ten file: ";
			cin >> fileName;
			admin.importClassfromCSV(fileName);

			cout << "\nNhap phim bat ky de quay lai menu";
			system("PAUSE>NULL");
		}
		else if (Select == 5)
		{
			string fileName;
			cout << "\nVui long nhap ten file: ";
			cin >> fileName;
			admin.importStudentsfromCSV(fileName);

			cout << "\nNhap phim bat ky de quay lai menu";
			system("PAUSE>NULL");
		}
		else if (Select == 6)
		{
			string classid = "";
			cout << "\nBan muon export sinh vien thuoc lop hoc nao: ";
			cin >> classid;
			int test = admin.findClass(classid);
			if (test != -1)
			{
				string fileName;
				cout << "\nVui long nhap duong dan cua file: ";
				cin >> fileName;
				admin.exportStudentByClassIdToCSV(fileName, classid);
			}

			cout << "\n Khong tim thay lop hoc : ";
			cout << "Nhap phim bat ky de quay lai menu";
			system("PAUSE>NULL");
		}
		else if (Select == 7)
		{
			string fileName;
			cout << "\nVui long nhap duong dan cua file: ";
			cin >> fileName;
			admin.exportAllStudentToCSV(fileName);

			cout << "Nhap phim bat ky de quay lai menu";
			system("PAUSE>NULL");
		}
		else if (Select == 8)
		{
			string classid;
			cout << "\n Ban muon them vao lop hoc nao: ";
			cin >> classid;
			admin.inStudentofclass(classid);

			cout << "Nhap phim bat ky de quay lai menu";
			system("PAUSE>NULL");
		}
		else if (Select == 9)
		{
			admin.inAllStudent();

			cout << "\nNhap phim bat ky de quay lai menu";
			system("PAUSE>NULL");
		}
		else if (Select == 10)
		{
			admin.printStudentsByDM1Desc();
			cout << "\nNhap phim bat ky de quay lai menu";
			system("PAUSE>NULL");
		}
		else if (Select == 11)
		{
			admin.printStudentsByDM1Asc();
			cout << "\nNhap phim bat ky de quay lai menu";
			system("PAUSE>NULL");
		}
	}
}

