//============================================================================
// Name        : Advising Assistance Prgram
// Author      : Benjamin Cleary
// Version     : 1.0
// Description : Program to pull course data including course ID, name, and 
// up to two prerequisites and store them in a spanning tree structure for 
// display and lookup
//============================================================================

#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>



using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// structure defined to hold information of a single course
struct Course {
    string courseId; // unique identifier
    string title;
    string prereq1;
    string prereq2;
    Course() {
        courseId = "";
        title = "";
        prereq1 = "";
        prereq2 = "";
    }
};

// Internal structure for tree node
struct Node {
    Course course;
    Node* left;
    Node* right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a bid
    Node(Course aCourse) :
        Node() {
        course = aCourse;
        left = nullptr;
        right = nullptr;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root = nullptr;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    void deleteTree(Node* node);


public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void DisplayTree();
    void Insert(Course course);
    Course Search(string courseId);
    void printCourse(Course course);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // Default constuctor
    Node* root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
    deleteTree(root);
}

/**
 * Method to remove the nodes of the tree when the destructor is called
 */
void BinarySearchTree::deleteTree(Node* node) {
    if (node == nullptr) {
        return;
    }

    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}
/**
 * Traverse the tree in order
 */
void BinarySearchTree::DisplayTree() {
    // call inOrder fuction and pass root 
    inOrder(root);
}

/**
*Display course information to stdout
*
* @param Node node containing the course data
*/
void printCourse(Course course, BinarySearchTree tree) {
    if (course.courseId != "") {
        cout << "+++++Course:" << course.courseId << " Data+++++" << endl;
        cout << "ID: " << course.courseId << endl;
        cout << "Title: " << course.title << endl;
        if (course.prereq1 != "") {
            cout << "First Prerequisite: " << course.prereq1 << endl;
        }
        if (course.prereq2 != "") {
            cout << "Second Prerequisite: " << course.prereq2 << endl;
        }
        //Course prereq1course = tree.Search(course.prereq1);
        //printCourse(prereq1course, tree);
        //Course prereq2course = tree.Search(course.prereq2);
        //printCourse(prereq2course, tree);
    }
    return;
}

/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Course course) {
    if (root == nullptr) {
        // root is equal to new node bid
        root = new Node(course);
    }
    // else
    else {
        // add Node root and bid
        addNode(root, course);
    }

}

/**
 * Search for a bid
 */
Course BinarySearchTree::Search(string courseId) {
    Node* current = root;
    // keep looping downwards until bottom reached or matching bidId found
    while (current != nullptr) {
        // if match found, return current bid
        if (current->course.courseId == courseId) {
            return current->course;
        }
        // if bid is smaller than current node then traverse left
        if (courseId < current->course.courseId) {
            current = current->left;
        }
        // else larger so traverse right
        else {
            current = current->right;
        }
    }
    //Returns a empty bid if not found
    Course course;
    return course;
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param course Course to be added
 */
void BinarySearchTree::addNode(Node* node, Course course) {
    if (course.courseId < node->course.courseId) {
        // if no left node
        if (node->left == nullptr) {
            // this node becomes left
            node->left = new Node(course);
        }
        else {
            // else recurse down the left node
            addNode(node->left, course);
        }
    }
    // else
    else {
        // if no right node
        if (node->right == nullptr) {
            // this node becomes right
            node->right = new Node(course);
        }
        //else
        else {
            // recurse down the right node
            addNode(node->right, course);
        }
    }
}

void BinarySearchTree::inOrder(Node* node) {
    //if node is not equal to null ptr
    if (node != nullptr) {
        //InOrder not left
        inOrder(node->left);
        //output course details
        cout << "+++++Course:" << node->course.courseId << " Data+++++" << endl;
        cout << "ID: " << node->course.courseId << endl;
        cout << "Title: " << node->course.title << endl;
        if (node->course.prereq1 != "") {
            cout << "First Prerequisite: " << node->course.prereq1 << endl;
        }
        if (node->course.prereq2 != "") {
            cout << "Second Prerequisite: " << node->course.prereq2 << endl;
        }
        //InOder right
        inOrder(node->right);
    }
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, BinarySearchTree* bst) {
    ifstream inputFile;
    inputFile.open(csvPath);
    string inputLine;
    if (!inputFile.is_open()) {
        cout << "Error reading file" << endl;
        return;
    }
    while (getline(inputFile, inputLine))
    {
        string temp1, temp2, temp3, temp4;
        int slot = 0;
        for (unsigned int i = 0; i < inputLine.size(); i++) {
            if (inputLine[i] == ',') {
                slot += 1;
            }
            if (slot == 0 && inputLine[i] != ',') {
                temp1.push_back(inputLine[i]);
            }
            if (slot == 1 && inputLine[i] != ',') {
                temp2.push_back(inputLine[i]);
            }
            if (slot == 2 && inputLine[i] != ',') {
                temp3.push_back(inputLine[i]);
            }
            if (slot == 3 && inputLine[i] != ',') {
                temp4.push_back(inputLine[i]);
            }
            if (slot > 3) {
                continue;
            }
        }

        if (temp1 == "" || temp2 == "") {
            cout << "Course data input format error, skipping...." << endl;
            continue;
        }
        //if (temp3 == "") {
        //    continue;
        //}
 /*       if (temp3 != "") {
           bool exists = false;
           Course course = bst->Search(temp3);
            if (temp3 == course.courseId) {
                exists = true;
            }
            if (exists == false) {
                cout << "Prerequisite one is not loaded into database skipping course: " << temp1 << endl;
                continue;
            }
        }*/
 /*       if (temp4 != "") {
            bool exists = false;
            Course course = bst->Search(temp4);
            if (temp4 == course.courseId) {
                exists = true;
            }
            if (exists == false) {
                cout << "Prerequisite two is not loaded into database skipping course: " << temp1 << endl;
                continue;
            }
        }*/
        Course newCourse;
        newCourse.courseId = temp1;
        newCourse.title = temp2;
        newCourse.prereq1 = temp3;
        newCourse.prereq2 = temp4;
        bst->Insert(newCourse);
    }
    inputFile.close();
    cout << "Successfully read file into structure" << endl;
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
//    case 3:
 //       csvPath = argv[1];
 //       break;
    default:
        csvPath = "CS 300 ABCU_Advising_Program_Input.csv";
    }

    // Define a binary search tree to hold all bids
    BinarySearchTree* courseList;
    courseList = new BinarySearchTree();
    string crseID;
    Course course;
    int choice = 0;

    //while loop for menu implementation
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Courses" << endl;
        cout << "  2. Display All Courses" << endl;
        cout << "  3. Find Course" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:

            // Complete the method call to load the courses
            //cout << "Please specify the absolute file path to the file containing course data" << endl;

            loadBids(csvPath, courseList);
            break;

        case 2:
            //call to display the courses in order
            courseList->DisplayTree();
            break;

        case 3:
            // call to get course ID from user and print out class and prerequisite data
            cout << "Enter Course ID (Case Sensitive):" << endl;
            cin >> crseID;
            course = courseList->Search(crseID);
            if (course.courseId != "") {
                printCourse(course, *courseList);
            }
            else {
                cout << "====Course Not found=====" << endl;
            }
            break;

        default:
            cout << choice << " is not a valid option";

        }
    }

    cout << "Good bye." << endl;

    return 0;
}
