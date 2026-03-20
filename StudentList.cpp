	#include "StudentList.h"
//DONE!
	// Define a constructor to initialize the list. The list starts with no Students
    StudentList::StudentList() {
		head = nullptr;
		tail = nullptr;
		numStudents = 0;
	}
//DONE!
	// return the number of students currently in the list
	int StudentList::listSize() {
		return numStudents;
	}
//DONE!
	//add a Node with a student to the front (head) of the list.
	void StudentList::addFront(Student s) {
		Node* newNode = new Node(s, head, nullptr);
		if(numStudents == 0){
			head = newNode;
			tail = newNode;
		}
		else{
			head->prev = newNode;
			head = newNode;
		}
		numStudents++;
	}
//DONE!
	//add a Node with a student to the back (tail) of the list.
	void StudentList::addBack(Student s) {
		Node* newNode = new Node(s, nullptr, tail);
		if(numStudents == 0){
			head = newNode;
			tail = newNode;
		}
		else{
			tail->next = newNode;
			tail = newNode;
		}
		numStudents++;
	}

	//Print out the names of each student in the list.
	void StudentList::printList() {
		if(head == nullptr){
			cout << "Empty";
			return;
		}
		Node* temp = head;
		while(temp != nullptr){
			cout << "Name: " << temp->data.name << endl;
			temp = temp->next;
		}
	}

	// Remove the Node with the student at the back (tail) of the list
	// should not fail if list is empty! Print an error message if this occurs
	// Don't forget that your head and tail pointers will be null pointers if the list is empty
	void StudentList::popBack() {
		if(numStudents == 0){
			cout << "Error: Empty!";
			return;
		}
		Node* temp = tail;
		if(numStudents == 1){
			head = nullptr;
			tail = nullptr;
		}
		else{
			tail = tail->prev;
			tail->next = nullptr;
		}
		delete temp;
		numStudents--;
	}

	// Remove the Node with the student at the front (head) of the list
	// should not fail if list is empty! Print an error message if this occurs
	// Don't forget that your head and tail pointers will be null pointers if the list is empty
	void StudentList::popFront() {
		if(numStudents == 0){
			cout << "Error: Empty!";
			return;
		}
		Node* temp = head;
		if(numStudents == 1){
			head = nullptr;
			tail = nullptr;
		}
		else{
			head = head->next;
			head->prev = nullptr;
		}
		delete temp;
		numStudents--;
	}

	//insert a student at the position "index".
	// for this list, count head as index 0
	// if index is outside of current list range, 
	// print a message and insert the student at the back of the list
	// the previous Node at your target index should be moved forward. "For exampe, Node with student at index i, becomes index i+1" 
	// Remember that you already have methods that can add students to the front or back of list if needed! Don't repeat this code.
	void StudentList::insertStudent(Student s, int index) {
		if(index<=0){
			addFront(s);
			return;
		}
		if(numStudents <= index){
			cout << "Out of range... \nadding to back";
			addBack(s);
			return;
		}
		Node* temp = head;
		int currentIndex = 0;
		int i=0;
		while(i<index){
			temp = temp->next;
			currentIndex++;
			i++;
		}
		Node* newNode = new Node(s, temp, temp->prev);
		temp->prev->next = newNode;
		temp->prev = newNode;
		numStudents++;
	}

	//find the student with the given id number and return them
	// if no student matches, print a message 
	// and create and return a dummy student object
	Student StudentList::retrieveStudent(int idNum) {
		Node* temp = head;
		while(temp!=nullptr){
			if(temp->data.id == idNum){
				return temp->data;
			}
			temp = temp->next;
		}
		cout<<"Not found!";
		Student dummy;
		return dummy;
	}

	// Remove a Node with a student from the list with a given id number
	// If no student matches, print a message and do nothing
	void StudentList::removeStudentById(int idNum) {
		Node* temp = head;
		while(temp!=nullptr){
			if(temp->data.id == idNum){
				if(temp == head){
					popFront();
				}
				else if(temp == tail){
					popBack();
				}
				else{
					temp->prev->next = temp->next;
					temp->next->prev = temp->prev;
					delete temp;
					numStudents--;
				}
				return;
			}
			temp = temp->next;
		}
		cout<<"Student ID: " << idNum << "\nnot found...";
	}

	//Change the gpa of the student with given id number to newGPA
	void StudentList::updateGPA(int idNum, float newGPA) {
		Node* temp = head;
		while(temp!=nullptr){
			if(temp->data.id == idNum){
				temp->data.GPA = newGPA;
				return;
			}
			temp = temp->next;
		}		
	}

	//Add all students from otherList to this list.
	//otherlist should be empty after this operation.
	/*
	For example, if the list has 3 students:
	s1 <-> s2 <-> s3
	and otherList has 2 students
	s4 <-> s5
	then after mergeList the currently list should have all 5 students
	s1 <-> s2 <-> s3 <-> s4 <-> s5
	and otherList should be empty and have zero students.
	*/
	void StudentList::mergeList(StudentList &otherList) {
		if(otherList.head == nullptr){
			return;
		}
		if(this->head == nullptr){
			this->head = otherList.head;
			this->tail = otherList.tail;
		}
		else{
			this->tail->next = otherList.head;
			otherList.head->prev = this->tail;
			this->tail = otherList.tail;
		}
		this->numStudents += otherList.numStudents;
		otherList.head = nullptr;
		otherList.tail = nullptr;
		otherList.numStudents = 0;
	}

	//create a StudentList of students whose gpa is at least minGPA.
	//Return this list.  The original (current) list should
	//not be modified (do not remove the students from the original list).
	StudentList StudentList::honorRoll(float minGPA) {
		StudentList honor;
		Node* temp = head;
		while(temp!=nullptr){
			if(temp->data.GPA >= minGPA){
				honor.addBack(temp->data);
			}
			temp = temp->next;
		}
		return honor;
	}

	//remove all students whose GPA is below a given threshold.
	// For example, if threshold = 3.0, all students with GPA less than 3.0
	// should be removed from the list. 
	// Be sure to correctly update both head and tail pointers when removing 
	// from the front or back, and adjust numStudents accordingly.
	// If the list is empty, print a message and do nothing.
	void StudentList::removeBelowGPA(float threshold) {
		if(numStudents == 0){
			cout<<"Empty";
			return;
		}
		Node* current = head;
		while(current!=nullptr){
			Node* nextNode = current->next;
			if(current->data.GPA < threshold){
				if(current==head){
					popFront();
				}
				else if(current == tail){
					popBack();
				}
				else{
					current->prev->next = current->next;
					current->next->prev = current->prev;
					delete current;
					numStudents--;
				}
			}
			current = nextNode;
		}
	}
