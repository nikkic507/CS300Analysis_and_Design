//============================================================================
// Name Nicholle Caudy        : ABCUProject.cpp
// Author      : Nicholle Caudy
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <time.h>

using namespace std;





struct Course{

	string courseId;

	string courseTitle;

	string prerequisite1;

	string prerequisite2;

	vector<string> prequisites;

};



//structure for tree node



struct Node{



	Course course;
	Node *left;
	Node *right;



	//constructor
	Node(){

		left = nullptr;
		right = nullptr;
	}

	//initialize with a course
	Node (Course acourse){

		left = nullptr;
		right = nullptr;
		course = acourse;
	}
};
//bst class
//implement bst
class BinarySearchTree{

private:

	Node *root;

	void addNode(Node *node, Course course);
	void inOrder (Node *node);

public:

  	BinarySearchTree();
	virtual ~BinarySearchTree();
	void InOrder();
	void Insert(Course course);
	Course Search (string courseId);
};

//constructor
BinarySearchTree::BinarySearchTree(){

	root = nullptr;
}
//traverse tree in order
void BinarySearchTree::InOrder(){
	//call inOrder function and pass root
	this -> inOrder(root);
}

//insert course
void BinarySearchTree::Insert(Course course){

	if (root == nullptr){

		root = new Node(course);
	}

	else {

		//add node root and course
		this -> addNode(root, course);
	}
}

//search for a course
Course BinarySearchTree::Search(string courseId) {

	//set current node equal to root
	Node *current = root;

	//loop downward until bottom is reached or match is found
	while (current != nullptr){

		//if current node matches return it
		if (current->course.courseId.compare(courseId)==0){

			return current -> course;
		}

		//if course is smaller traverse left subtree
		if (courseId.compare(current -> course.courseId)<0) {

			current = current ->left;
		}

		//else larger traverse right
		else {

			current = current -> right;
		}
	}

	Course course;

	return course;
}
//add course to node
void BinarySearchTree::addNode(Node *node, Course course){

	//if node is larger add to left
	if (node ->course.courseId.compare(course.courseId)>0) {

		//node become left if no left node
		if (node -> left == nullptr){

			node ->left = new Node(course);
		}

	//else recurse down left node
	else {

		this ->addNode (node -> left, course);
	}
}

else {
	//if no right node this node becomes right
	if (node ->right == nullptr){

		node ->right = new Node(course);
	}

	//else recurse down right node
	else {

		this ->addNode(node->right, course);
	}
  }
}

void BinarySearchTree::inOrder(Node *node) {

	//if node is not equal to nullptr
	//inOrder node left and output courseId, and courseTitle
	if (node != nullptr) {

		inOrder(node->left); //traverse left side first
		cout << node -> course.courseId << ", " << node-> course.courseTitle<<endl;

		inOrder (node ->right); //traverse right side after each level checked
	}
}

//Display information to console

void displayCourse (Course &course){

	cout << course.courseId << ", " << course.courseTitle <<endl;

	if (!(course.prerequisite2 == " ")){

		cout << "Prerequisites: " << course.prerequisite1 << ", " << course.prerequisite2;
	}

	else {

		cout << "Prerequisites: " << course.prerequisite1;
	}
}

//load csv file
void loadCourses(string csvPath, BinarySearchTree *bst) {

	Course course;
	cout <<"Loading CSV file" << csvPath << endl;

	ifstream file;
	string line;

	try{
		file.open(csvPath);

		if (file.is_open()) {

			while (file.good()){

				cout << line << endl;

				while (getline(file, line)) {

					stringstream ss(line);
					string courseId;
					string courseTitle;
					string prerequisite1;
					string prerequisite2;

					getline(ss, courseId, ',');
					getline(ss, courseId, ',');
					getline(ss, prerequisite1, ',');
					getline(ss, prerequisite2, ',');

					course.courseId = courseId;
					course.courseTitle = courseTitle;
					course.prerequisite1 = prerequisite1;
					course.prerequisite2 = prerequisite2;

					bst ->Insert(course);
					ss.clear();
				}
			}
		}
	}

	catch (exception &e) {

		cerr << e.what() << endl;
	}
}

int main(int argc, char *argv[]){

	string csvPath, courseKey;
	Course course;

	switch (argc) {

	case 2:

		csvPath = argv [1];

		break;

	case 3:

		csvPath = argv [1];

		break;

	default:

		csvPath = "ABCUInput.csv";
	}

	//Define a bst to hold all courses
	BinarySearchTree *bst();

	bst = new BinarySearchTree();

	int choice = 0;
	while (choice !=9) {

		if (!(choice <=3) && (choice >0)) {

			cout << endl;
			cout << choice << " is not a valid choice.";
			cout << endl;
		}

		cout << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
		cout << "Welcome to the course planner." << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << endl;
		cout << "1.Load Data Structure" << endl;
		cout << "2.Print Course List" << endl;
		cout << "3.Print Course" << endl;
		cout << "9.Exit" << endl;
		cout << endl;
		cout << "What would you like to do?";
		cin >> choice;
		cout << endl;

		switch (choice) {

		case 1:

			loadCourses(csvPath, bst);

			break;

		case 2:

			if (bst == NULL) {

				cout << "Data not loaded.";
			}

			else

				cout << "Here is a sample schedule:\n"

				<<endl;

			bst -> InOrder(); //print course in order by courseId

			break;

		case 3:

			cout << "What course do you want to know about?";
			cin >> courseKey;

			transform(courseKey.begin(), courseKey.end(), courseKey.begin(), ::toupper);

			course = bst ->Search(courseKey);

			if (!course.courseId.empty()) {

				displayCourse(course);
			}

			else {

				cout << "Course " << courseKey << " not found." << endl;
			}

			break;
		}
	}

	cout << "Good bye." << endl;

	return 0;
}
