#include "testing_structs.h"
using namespace std;

template<typename T>
void printAllElements(const vector<T>& elements) {
    cout << "All elements in the tree: ";
    for (const auto& element : elements) {
        cout << element << " ";
    }
    cout << endl;
}

void printMenu() {
    cout << "1. Insert Element\n";
    cout << "2. Search Element\n";
    cout << "3. Perform Breadth-First Traversal\n";
    cout << "4. Perform Postorder Traversal\n";
    cout << "5. Build a New Tree by Applying Function to Each Element (map)\n";
    cout << "6. Perform Element Filtering (where)\n";
    cout << "7. Extract Subtree\n";
    cout << "8. Print All Elements\n";
    cout << "9. Delete Element\n";
    cout << "10. Enter Student\n";
    cout << "11. Search Student\n";
    cout << "12. Perform Breadth-First Traversal (Students)\n";
    cout << "13. Perform Postorder Traversal (Students)\n";
    cout << "14. Build a New Student Tree by Applying Function to Each Element (map)\n";
    cout << "15. Perform Student Filtering (where)\n";
    cout << "16. Extract Student Subtree\n";
    cout << "17. Print All Students\n";
    cout << "18. Delete Student\n";
    cout << "19. Exit\n";
    cout << "Choose an action: ";
}


void menu() {
    BST<int> bst;
    BST<Student> student_bst;

    int choice;
    do {
        printMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                int val;
                cout << "Enter the value to insert: ";
                cin >> val;
                bst.insert(val);
                break;
            }
            case 2: {
                int val;
                cout << "Enter the value to search: ";
                cin >> val;
                if (bst.search(val) != nullptr) {
                    cout << "Element found.\n";
                } else {
                    cout << "Element not found.\n";
                }
                break;
            }
            case 3: {
                vector<int> result = bst.bfs();
                cout << "Breadth-First Traversal: ";
                for (int val : result) {
                    cout << val << " ";
                }
                cout << endl;
                break;
            }
            case 4: {
                vector<int> result = bst.postorderTraversal();
                cout << "Postorder Traversal: ";
                for (int val : result) {
                    cout << val << " ";
                }
                cout << endl;
                break;
            }
            case 5: {
                BST<int> squaredTree = bst.map<int>([](int x) { return x * x; });
                vector<int> result = squaredTree.inorderTraversal();
                cout << "New tree after applying function (squaring): ";
                for (int val : result) {
                    cout << val << " ";
                }
                cout << endl;
                break;
            }
            case 6: {
                BST<int> filteredTree = bst.where([](int x) { return x % 2 == 0; });
                vector<int> result = filteredTree.inorderTraversal();
                cout << "New tree after filtering (even elements): ";
                for (int val : result) {
                    cout << val << " ";
                }
                cout << endl;
                break;
            }
            case 7: {
                int val;
                cout << "Enter the value to extract subtree: ";
                cin >> val;
                BST<int> extractedTree = bst.extractSubtree(val);
                vector<int> result = extractedTree.inorderTraversal();
                cout << "Extracted subtree: ";
                for (int val : result) {
                    cout << val << " ";
                }
                cout << endl;
                break;
            }
            case 8: {
                vector<int> result = bst.inorderTraversal();
                printAllElements(result);
                break;
            }
            case 9: {
                int val;
                cout << "Enter the value to delete: ";
                cin >> val;
                bst.delete_element(val);
                cout << "Element deleted.\n";
                break;
            }
            case 10: {
                Student student;
                string name, surname, lastname;
                int age, id;
                cout << "Enter the student's name: ";
                cin >> name;
                cout << "Enter the student's surname: ";
                cin >> surname;
                cout << "Enter the student's lastname: ";
                cin >> lastname;
                cout << "Enter the student's age: ";
                cin >> age;
                cout << "Enter the student's ID: ";
                cin >> id;
                student.student_id = id;
                student.Name = name;
                student.Surname = surname;
                student.Lastname = lastname;
                student.age = age;
                student_bst.insert(student);
                break;
            }
            case 11: {
                int student_id;
                cout << "Enter the student ID to search: ";
                cin >> student_id;
                Student search_student;
                search_student.student_id = student_id;
                if (student_bst.search(search_student) != nullptr) {
                    cout << "Student found.\n";
                } else {
                    cout << "Student not found.\n";
                }
                break;
            }
            case 12: {
                vector<Student> result = student_bst.bfs();
                cout << "Breadth-First Traversal of Students: ";
                for (const auto& student : result) {
                    cout << student.Name << " " << student.Surname << " ";
                }
                cout << endl;
                break;
            }
            case 13: {
                vector<Student> result = student_bst.postorderTraversal();
                cout << "Postorder Traversal of Students: ";
                for (const auto& student : result) {
                    cout << student.Name << " " << student.Surname << " ";
                }
                cout << endl;
                break;
            }
            case 14: {
                BST<Student> mapTree = student_bst.map<Student>([](Student s) {
                    s.age += 1;
                    return s;
                });
                vector<Student> result = mapTree.inorderTraversal();
                cout << "New student tree after applying function (increment age): ";
                for (const auto& student : result) {
                    cout << student.Name << " " << student.Surname << " " << student.age << " ";
                }
                cout << endl;
                break;
            }
            case 15: {
                BST<Student> filteredTree = student_bst.where([](Student s) { return s.age > 20; });
                vector<Student> result = filteredTree.inorderTraversal();
                cout << "Filtered student tree (age > 20): ";
                for (const auto& student : result) {
                    cout << student.Name << " " << student.Surname << " " << student.age << " ";
                }
                cout << endl;
                break;
            }
            case 16: {
                int student_id;
                cout << "Enter the student ID to extract subtree: ";
                cin >> student_id;
                Student student;
                student.student_id = student_id;
                BST<Student> extractedTree = student_bst.extractSubtree(student);
                vector<Student> result = extractedTree.inorderTraversal();
                cout << "Extracted student subtree: ";
                for (const auto& student : result) {
                    cout << student.Name << " " << student.Surname << " " << student.age << " ";
                }
                cout << endl;
                break;
            }
            case 17: {
                vector<Student> result = student_bst.inorderTraversal();
                cout << "All student elements: ";
                for (const auto& student : result) {
                    cout << student.Name << " " << student.Surname << " " << student.age << " ";
                }
                cout << endl;
                break;
            }
            case 18: {
                int student_id;
                cout << "Enter the student ID to delete: ";
                cin >> student_id;
                Student student;
                student.student_id = student_id;
                student_bst.delete_element(student);
                cout << "Student deleted.\n";
                break;
            }
            case 19: {
                cout << "Exiting the program.\n";
                break;
            }
            default: {
                cout << "Invalid input. Please try again.\n";
                break;
            }
        }
    } while (choice != 19);
}




