// Mac Grier
// CS 300 Project Two.cpp 
// 10/19/2025
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>

using namespace std;

// Struct to hold course information
struct Course {
	string courseID;
	string courseName;
	vector<string> prerequisites;
};

// Node to hold courses in BST
struct Node {
	Course course;
	Node* right;
	Node* left;

	Node() : right{}, left{} {}

	Node(Course newCourse) : course(newCourse), right(nullptr), left(nullptr) {}
};


Node* insert(Node* root, const Course& newCourse) {
	// Root empty
	if (root == nullptr) {
		return new Node(newCourse);
	}
	// Search for insert left
	if (newCourse.courseID < root->course.courseID) {
		root->left = insert(root->left, newCourse);
	}
	// Search for insert right
	else if (newCourse.courseID > root->course.courseID) {
		root->right = insert(root->right, newCourse);
	}
	return root;
}

// Prints tree in order
void inOrder(Node* root) {
	// checks if no course exists
	if (root == nullptr) {
		return;
	}
	// Check for lesser node
	inOrder(root->left);
	
	// Print node
	cout << root->course.courseID << ", " << root->course.courseName << endl;

	// Check for greater node
	inOrder(root->right);
}

Node* loadCourses(const string& filename, Node* root) {
	ifstream file(filename);
	if (!file.is_open()) {
		cout << "Error opening file" << endl;
		return root;
	}
	// Loops through file
	string line;
	while (getline(file, line)) {
		if (line.empty()) continue;
		cout << "in loop" << endl;
		stringstream ss(line);
		string id;
		string name;
		string prerequisitesRaw;

		//Get course data
		getline(ss, id, ',');
		getline(ss, name, ',');
		getline(ss, prerequisitesRaw, '\n');

		//Loop through prereqs
		vector<string> prerequisites;
		stringstream prereqStream(prerequisitesRaw);
		string prereq;
		while (prereqStream >> prereq) {
			prerequisites.push_back(prereq);
		}
		Course course{ id, name, prerequisites };
		root = insert(root, course);
	}
	file.close();
	return root;
}

Course search(Node* root, string courseID) {
	Node* currNode = root;
	// search loop
	while (currNode != nullptr) {
		// found match
		if (currNode->course.courseID == courseID) {
			return currNode->course;
		}
		// move left 
		else if (courseID < currNode->course.courseID) {
			currNode = currNode->left;
		}
		// move right
		else{
			currNode = currNode->right;
			
		}
	}
	// Fail case
	Course course;
	return course;
}

int main() {
	Node* root = nullptr;

	string filename = "CS 300 ABCU_Advising_Program_Input.csv";
	Course searchCourse;
	string searchID;
	int choice = 0;
	// Main Menu Loop
	
	while (choice != 9) {
		cout << "Course Binary Search Tree" << endl;
		cout << "What would you like to do?" << endl;
		cout << "1: Load Courses" << endl;
		cout << "2: Print All Courses" << endl;
		cout << "3: Print a Specific Course" << endl;
		cout << "9: Exit" << endl;
		try {
			cin >> choice;
		}
		catch(int err){
			cout << "Double check your input." << endl;
		}
		switch (choice) {
		case 1:
			root = loadCourses(filename, root);
			cout << "Courses Read" << endl;
			if (root) {
				cout << "b";
			}
			break;

		case 2:
			inOrder(root);
			cout << "Done!" << endl;
			break;

		case 3:
			cout << "Enter the course ID you would like to print: " << endl;
			cin >> searchID;
			searchCourse = search(root, searchID);
			if (searchCourse.courseID.empty()) {
				cout << "Course not found." << endl;
			}
			else {
				cout << searchCourse.courseID << ": " << searchCourse.courseName << endl;
				if (!searchCourse.prerequisites.empty()) {
					cout << "Prerequisites: ";
					for (int i = 0; i < searchCourse.prerequisites.size(); i++) {
						cout << searchCourse.prerequisites.at(i) << "  ";
					}
					cout << endl;
				}
			}
		case 9:
			exit;
			break;

		default:
			break;
		}
		// Clears cin to avoid input errors
		cin.clear();
		cin.ignore();
	}
	cout << "Exiting program..." << endl;
	return 0;
}