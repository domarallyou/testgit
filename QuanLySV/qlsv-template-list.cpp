	#include <iostream>
	#include <string>
	#include <vector>
	#include <algorithm>
	#include <stdexcept>
	#include <iterator>
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
	        } else {
	            tail->next = newNode;
	            tail = newNode;
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
	            throw std::out_of_range("Index out of range");
	        }
	
	        Node* current = head;
	        for (int i = 0; i < index; i++) {
	            current = current->next;
	        }
	
	        return current->data;
	    }
	
	    void erase(int index) {
	        if (index < 0 || index >= size()) {
	            throw std::out_of_range("Index out of range");
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
	
	    LinkedList<T> reverse() const {
	        LinkedList<T> reversedList;
	        Node* current = head;
	        while (current != nullptr) {
	            reversedList.push_back(current->data);
	            current = current->next;
	        }
	
	        return reversedList;
	    }
	
	    LinkedList<T> concat(const LinkedList<T>& otherList) const {
	        LinkedList<T> newList;
	        newList.push_back(front());
	        newList.concat(otherList);
	
	        return newList;
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
	
	    Iterator begin() const{
	        return Iterator(head);
	    }
	
	    Iterator end() const{
	        return Iterator(nullptr);
	    }
	};
	    
	
	
	
	
	class Student {
	public:
		int STT;
	    string name;
	    int grades;
	    int studentID;
	
	    Student(int stt,string n, int g, int s) :STT(stt), name(n), grades(g), studentID(s) {}
	};
	
	class Class {
	public:
	    string name;
	    string classID;
	    LinkedList<Student> studentList;
		int size=0; 

	    Class(string n, string c) : name(n), classID(c) {}
	
	    void addStudent(const Student& student) {	    	
	        studentList.push_back(student);
	    }
	    
	    void addStudentFront(const Student& student) {	    	
	        studentList.push_front(student);
	    }
	    
	    void deleteStudentFront() {	    	
	        studentList.pop_front();
	    }
	     void deleteStudentBack() {	    	
	        studentList.pop_back();
	    }
	    
		void inStudent() const {
    	for (const Student& student : studentList) {
		cout <<"\n---------------------------------------------------------------------";
		cout << "\n So Thu Tu : " << student.STT ;
		cout << "\n MSSV : " << student.studentID ;
        cout <<"\n ho va ten : "<< student.name ;
        cout << "\n Diem mon hoc : " <<student.grades ;
    }
}
	};
	
	
	class LISTClass {
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
		//them hs vao cuoi
		void updateClass(const string& classID, const int& gradeStu, const string& nameStu,const int& idStu) {
    	int index = findClass(classID);
    	if (index != -1) {
        	LinkedList<Class>::Iterator it = classList.begin();
        	for (int i = 0; i < index; i++) {
            	++it;
        	}
        Class& classToUpdate = *it;
        classToUpdate.size+=1;
        Student tempstudent(classToUpdate.size,nameStu,gradeStu,idStu);
        classToUpdate.addStudent(tempstudent) ;
 
    }
}
		//them hs vao dau
		void updateClass1(const string& classID, const int& gradeStu, const string& nameStu,const int& idStu) {
    	int index = findClass(classID);
    	if (index != -1) {
        	LinkedList<Class>::Iterator it = classList.begin();
        	for (int i = 0; i < index; i++) {
            	++it;
        	}
        Class& classToUpdate = *it;
        classToUpdate.size+=1;
        Student tempstudent(classToUpdate.size,nameStu,gradeStu,idStu);
        classToUpdate.addStudentFront(tempstudent) ;
 
    }
}
		//xoa hs dau tien
		void updateClass2(const string& classID) {
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
		void updateClass3(const string& classID) {
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

		void inclass()
		{
			
	    for (const Class& Class : classList) {
	    cout << Class.name << " - ";
	    cout << Class.classID<<endl;
			}
		 } 
		 
		 
		void inStudentofclass(const string& classid)
		{
			
	    for (const Class& Class : classList) {
	    	if (Class.classID==classid)
	    		{
   					cout <<"\n---------------------------------------------------------------------";
	    			cout<<"\nLop danh sach sinh vien lop "<<Class.name<<"  : "<<endl;
	    			Class.inStudent();
				}
	    	
			}
		} 
		
		void inAllStudent()
		{
	    for (const Class& Class : classList) {
	    		{
	    			cout <<"\n---------------------------------------------------------------------";
	    			cout<<"\nLop danh sach sinh vien lop "<<Class.name<<"  : "<<endl;
	    			Class.inStudent();
				}
	    	
			}
		} 
		
	};
	
	
	int main() {

		LISTClass admin;
	    
	    int Select;
		while (true)
		{
	
				system("CLS");
				cout << "1. Tao lop hoc : " << endl;
				cout << "2. Them sinh vien vao lop hoc : " << endl;
				cout << "3. Xoa sinh vien khoi lop hoc : " << endl;
				cout << "8. Xuat thong tin sinh vien the lop : " << endl;
				cout << "9. Xuat thong tin sinh vien tat ca cac lop : " << endl;

				cin >> Select;
			if(Select==1)
			{
				string classname,classid;
				cout << "\nMoi nhap ten lop hoc : ";
				cin >> classname;
				cout << "\nMoi nhap ma lop hoc : ";
				cin >> classid;
				Class tempclass(classname,classid);
				
				admin.addClass(tempclass);
				admin.inclass();
				cout << "Nhap phim bat ky de quay lai menu";
				system("PAUSE>NULL");
			}
			else if(Select==2)
			{
				string classid="";
				cout << "\n Ban muon them vao lop hoc nao : ";
				cin >> classid;
				
				int tem;
					cout << "\n1/them sinh vien vao cuoi cung : ";
					cout << "\n2/them sinh vien vao dau tien : "<<endl;
					cin>>tem;
				
				int test=admin.findClass(classid);	
				if( test!=-1)
				{
					string name;
					int grade,id;
					cout<<"Nhap thong tin sing vien : ";
					cout<<"\nNhap ID : ";
					cin >> id;
					cout<<"\nNhap ten sinh vien : ";
					cin >> name;
					cout<<"\nNhap diem : ";
					cin >> grade;
					if (cin.fail()) {
    				cout << "\nNhap sai vui long nhap lai !!!" << endl;
    				cin.clear(); 
    				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
					
						if(tem==1)
					{
						admin.updateClass(classid,grade,name,id);
					}
					else if(tem==2)
					{
						admin.updateClass1(classid,grade,name,id);
					}
				}
				cout << "Nhap phim bat ky de quay lai menu";
				system("PAUSE>NULL");
	
			}
			else if(Select==3)
			{
				string classid="";
				cout << "\n Ban muon xoa sinh vien thuoc lop hoc nao : ";
				cin >> classid;
				int test=admin.findClass(classid);	
				if( test!=-1)
				{
					int tem;
					cout << "\n1/xoa sinh vien dau tien : ";
					cout << "\n2/xoa sinh vien cuoi cung : ";
					cin>>tem;
					if(tem==1)
					{
						admin.updateClass2(classid);
					}
					else if(tem==2)
					{
						admin.updateClass3(classid);
					}
					
				}
				cout << "Nhap phim bat ky de quay lai menu";
				system("PAUSE>NULL");
	
			}
			else if(Select==8)
			{
				string classid;
				cout << "\n Ban muon them vao lop hoc nao : ";
				cin >> classid;
				admin.inStudentofclass(classid);
			
			cout << "Nhap phim bat ky de quay lai menu";
			system("PAUSE>NULL");
			}    
			else if(Select==9)
			{
				string classid;
		
				admin.inAllStudent();
			
			cout << "Nhap phim bat ky de quay lai menu";
			system("PAUSE>NULL");
			}    
		}
	}

