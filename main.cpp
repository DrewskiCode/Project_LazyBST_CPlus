/*
PA5
main.cpp
Drew Floyd
2429112
afloyd@chapman.edu
prints the menu, handles exceptions, and manages the two databases

*/

#include <iostream>
#include <fstream>
#include <cctype>
#include <limits>
#include "LazyBST.h"
#include "Student.h"
#include "Faculty.h"

using namespace std;

bool isInteger(const string& str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

void printMenu() {
    cout << "1. Print all students and their information (sorted by ascending id #)\n"
         << "2. Print all faculty and their information (sorted by ascending id #)\n"
         << "3. Find and display student information given the student id\n"
         << "4. Find and display faculty information given the faculty id\n"
         << "5. Add a new student\n"
         << "6. Delete a student given the id\n"
         << "7. Add a new faculty member\n"
         << "8. Delete a faculty member given the id\n"
         << "9. Change a student’s advisor given the student id and the new faculty id\n"
         << "10. Remove an advisee from a faculty member given the ids\n"
         << "11. Exit\n";
}

void executeCommand(int choice, LazyBST<Student>& studentTree, LazyBST<Faculty>& facultyTree) {
    string id;
    string studentIdStr, name, level, major, gpaStr, advisorIdStr, department, adviseeIdStr;
    double gpa;
    int studentId, advisorId, adviseeId;
    switch (choice) {
        case 1:
            // Print all students
            cout << "Printing all students (sorted by Acending ID):\n";
            studentTree.printInOrder(); 
            // Use print in order function
            // Implement the functionality to print all students
            break;
        case 2:
            // Print all faculty
             cout << "Printing all faculty (sorted by Acending ID):\n";
             facultyTree.printInOrder();
            // use print in order function
            // Implement the functionality to print all faculty
            break;
        case 3:
            // Find and display student information given the student id
            cout << "Enter a Valid Student ID: ";
            cin >> id;
            if (isInteger(id)) {
                Student temp(stoi(id));
               if (studentTree.contains(temp)) {
                   cout << studentTree.get(temp).toString() << endl;
               } else {
                    cout << "Student Not Found" << endl;
                    break;
               }
            } else {
                cout << "Please Enter A Valid Number" << endl;
                break;
            }


            // findTarget on the student ID, getData of that ID
            // Implement the functionality to find and display student information
            break;
        case 4: {
            // Find and display faculty information given the faculty id
             cout << "Enter a Valid Faculty ID: ";
            cin >> id;
            if (isInteger(id)) {
                Faculty temp(stoi(id));
               if (facultyTree.contains(temp)) {
                   cout << facultyTree.get(temp).toString() << endl;
               } else {
                    cout << "Faculty Not Found" << endl;
                    break;
               }
            } else {
                cout << "Please Enter A Valid Number" << endl;
                break;
            }
            // findTarget on the faculty ID, getData of that ID
            // Implement the functionality to find and display faculty information
            break;
        }
        case 5: {
            // Add a new student

            // Input Student ID with validation
            cout << "Enter New Student ID: ";
            cin >> studentIdStr;

            if (!isInteger(studentIdStr)) {
                cout << "Invalid input. Please enter a valid integer for Student ID: " << endl;
                cin >> studentIdStr;
            }

            // Convert the validated input to an integer
            studentId = stoi(studentIdStr);

            Student temp(studentId);

            while (studentTree.contains(temp)) {
                cout << "Student ID already exists. Please enter a different Student ID: ";
                cin >> studentIdStr;

                while (!isInteger(studentIdStr)) {
                    cout << "Invalid input. Please enter a valid integer for Student ID: " << endl;
                    cin >> studentIdStr;
                }

                studentId = stoi(studentIdStr);
                temp = Student(studentId); // Update the existing 'temp' variable with the new student ID
            }
                    // Input Name
                    cout << "Enter Name: ";
                    cin >> name;

                    // Input Level with validation
                    cout << "Enter Level (Freshman, Sophomore, Junior, Senior): ";
                    while (!(cin >> level) || (level != "Freshman" && level != "Sophomore" &&
                        level != "Junior" && level != "Senior")) {
                        cout << "Invalid input. Please enter a valid level: ";
                        }
                    // Input Major
                    cout << "Enter Major: ";
                    cin >> major;

                    // Input GPA
                    cout << "Enter GPA: ";
                    cin >> gpaStr;

            // Validate if the input is a valid double between 0 and 4
            while (true) {
                try {
                    size_t pos;
                    gpa = stod(gpaStr, &pos);

                    if (pos == gpaStr.length() && gpa >= 0.0 && gpa <= 4.0) {
                        break; // Valid input, exit the loop
                    } else {
                        throw invalid_argument("Invalid GPA");
                    }
                } catch (const invalid_argument& e) {
                    // Clear input buffer and ignore remaining characters


                    // Prompt the user for valid input
                    cout << "Invalid input. Please enter a valid double for GPA between 0 and 4: ";
                    cin >> gpaStr;
                }
            }

                    // Input Advisor ID
                cout << "Enter Advisor ID: ";
                cin >> advisorIdStr;

            // Validate if the input is a valid integer
            while (true) {
                try {
                    size_t pos;
                    advisorId = stoi(advisorIdStr, &pos);

                    if (pos == advisorIdStr.length()) {
                        // Valid integer, check if it exists in facultyTree
                        Faculty temp2(advisorId);
                        if (!facultyTree.contains(temp2)) {
                            // Advisor does not exist in the database
                            cout << "Advisor Does Not Exist In Database. ";
                            cin >> advisorIdStr;
                            continue; // Skip the rest of the loop and re-validate the new input
                        } 

                        if (facultyTree.contains(temp2)) {
                            // Update the student's advisor in the student tree
                            studentTree.get(temp).setAdvisor(advisorId);

                            // Find the actual Faculty object inside the tree
                            Faculty actualAdvisor = facultyTree.get(temp2);

                            // Add the student to the new advisor's advisees
                            actualAdvisor.addAdvisee(temp.getStudentId()); // Adding or Removing Advisees doesnt work

                        } else {
                            cout << "New Advisor does not exist in the database." << endl;
                        }

                        break;
                    } else {
                        throw invalid_argument("Invalid Advisor ID");
                    }
                } catch (const invalid_argument& e) {
                    // Clear input buffer and ignore remaining characters

                    // Prompt the user for valid input
                    cout << "Invalid input. Please enter a valid integer for Advisor ID: ";
                    cin >> advisorIdStr;
                }
            }
                    // Create the new student using the overloaded constructor
                    Student newStudent(studentId, name, level, major, gpa, stoi(advisorIdStr));
                    studentTree.insert(newStudent);

                    // ADD METHOD TO CREATE AND 

                    // Display the entered student information
                    cout << "Entered Student Information:" << endl;
                    cout << newStudent.toString() << endl;

                    // insert a new student object to the student tree
                    // takes in variables: student name, student ID, major, GPA, level, advisor Id
                    // Implement the functionality to add a new student
                    break;
                }
        case 6: {
            // Delete a student given the id
            if (studentTree.isEmpty()){
                cout << "No Students in Tree" << endl;
                break;
            }
            cout << "Enter a Student ID to Delete: ";
            cin >> studentIdStr;
             while (!isInteger(studentIdStr)) {
                    cout << "Invalid input. Please enter a valid integer for Student ID: ";
                    cin >> studentIdStr;
                }
            studentId = stoi(studentIdStr);

            Student temp(studentId);

            while (!studentTree.contains(temp)) {
                cout << "Student ID doesnt exist. Please enter a different Student ID: ";
                cin >> studentIdStr;

                 while (!isInteger(studentIdStr)) {
                    cout << "Invalid input. Please enter a valid integer for Student ID: ";
                    cin >> studentIdStr;
                }

                studentId = stoi(studentIdStr);
                temp = Student(studentId); // Update the existing 'temp' variable with the new student ID
            }

            studentTree.remove(temp);
            // remove student ID from tree
            // takes in variables: studentId
            // Implement the functionality to delete a student
            break;
        }
        case 7: {
             // Input Faculty ID with validation
            cout << "Enter New Faculty ID: ";
            cin >> advisorIdStr;

            while (!isInteger(advisorIdStr)) {
                cout << "Invalid input. Please enter a valid integer for Faculty ID: " << endl;
                cin >> advisorIdStr;
            }

            // Convert the validated input to an integer
            advisorId = stoi(advisorIdStr);

            Faculty temp3(advisorId);

            while (facultyTree.contains(temp3)) {
                cout << "Faculty ID already exists. Please enter a different Faculty ID: ";
                cin >> advisorIdStr;

                while (!isInteger(advisorIdStr)) {
                    cout << "Invalid input. Please enter a valid integer for Faculty ID: " << endl;
                    cin >> advisorIdStr;
                }

                advisorId = stoi(advisorIdStr);
                temp3 = Faculty(advisorId); // Update the existing 'temp' variable with the new Faculty ID
            }
                    // Input Name
                    cout << "Enter Name: ";
                    cin >> name;

                    // Input Level with validation
                    cout << "Enter Level (Lecturer, Assistant Prof, Associate Prof, Professor: ";
                    while (!(cin >> level) || (level != "Lecturer" && level != "Assistant Prof" &&
                        level != "Associate Prof" && level != "Professor")) {
                        cout << "Invalid input. Please enter a valid level: ";
                        }
                    // Input Department
                    cout << "Enter Department: ";
                    cin >> department;
                     // Create the new faculty using the overloaded constructor
                    Faculty newFaculty(advisorId, name, level, department);

                    while (true) {
                        // Input Advisee ID as string with initial validation
                        cout << "Enter Advisee ID (or type 'Done' to finish): ";
                        cin >> adviseeIdStr;

                        // Check if the user wants to finish
                        if (adviseeIdStr == "Done" || adviseeIdStr == "done") {
                            break;
                        }

                        // Validate if the input is a valid integer
                        try {
                            size_t pos;
                            adviseeId = stoi(adviseeIdStr, &pos);

                            if (pos == adviseeIdStr.length()) {
                                // Valid integer, check if it exists in studentTree
                                Student temp(adviseeId);
                                if (!studentTree.contains(temp)) {
                                    // Advisee does not exist in the database
                                    cout << "Advisee Does Not Exist In Database. ";
                                    continue; // Skip the rest of the loop and re-validate the new input
                                }
                                    newFaculty.addAdvisee(adviseeId);
                                    cout << "Advisee Added to List. ";
                            } else {
                                throw invalid_argument("Invalid Advisee ID");
                            }
                        } catch (const invalid_argument& e) {
                            // Clear input buffer and ignore remaining characters
                            cin.clear();
                            // Prompt the user for valid input
                            cout << "Invalid input. Please enter a valid integer for Advisee ID: ";
                        }
                    }

                   // add faculty to tree
                    
                    facultyTree.insert(newFaculty);

                    // Display the entered student information
                    cout << "Entered Faculty Information:" << endl;
                    cout << newFaculty.toString() << endl;

                    // insert a new student object to the student tree
                    // takes in variables: student name, student ID, major, GPA, level, advisor Id
                    // Implement the functionality to add a new student
                    break;
                }
            break;
        case 8:  {
            // Delete a faculty given the id
            if (facultyTree.isEmpty()){
                cout << "No Faculty in Tree" << endl;
                break;
            }
            cout << "Enter a Faculty ID to Delete: ";
            cin >> advisorIdStr;
            while (!isInteger(advisorIdStr)) {
                    cout << "Invalid input. Please enter a valid integer for Faculty ID: ";
                    cin >> advisorIdStr;
                }
            advisorId = stoi(advisorIdStr);

            Faculty temp2(advisorId);

            while (!facultyTree.contains(temp2)) {
                cout << "Faculty ID doesnt exist. Please enter a different Faculty ID: ";
                cin >> advisorIdStr;

                while (!isInteger(advisorIdStr)) {
                    cout << "Invalid input. Please enter a valid integer for Faculty ID: ";
                    cin >> advisorIdStr;
                }

                advisorId = stoi(advisorIdStr);
                temp2 = Faculty(advisorId); // Update the existing 'temp' variable with the new student ID
            }
            int i =0;
            DblList<int> relocateAdvisees = facultyTree.get(temp2).getAdvisees();
            int adviseeId;
            for (int i = 0; i < relocateAdvisees.size(); ++i) {
                adviseeId = facultyTree.get(temp2).removeAdvisee(relocateAdvisees.get(i));
                cout << "Advisee With Student ID: " << adviseeId << " needs to be relocated to another Advisor, Please Enter A Valid Advisor ID: ";
                
                    cin >> advisorIdStr;

                while (!isInteger(advisorIdStr)) {
                    cout << "Invalid input. Please enter a valid integer for Faculty ID: " << endl;
                    cin >> advisorIdStr;
                }

                // Convert the validated input to an integer
                advisorId = stoi(advisorIdStr);

                Faculty temp5(advisorId);

                while (!facultyTree.contains(temp5)) {
                    cout << "Faculty ID doesnt exist. Please enter a different Faculty ID: ";
                    cin >> advisorIdStr;

                    while (!isInteger(advisorIdStr)) {
                        cout << "Invalid input. Please enter a valid integer for Faculty ID: " << endl;
                        cin >> advisorIdStr;
                    }
                    advisorId = stoi(advisorIdStr);
                    temp5 = Faculty(advisorId); // Update the existing 'temp' variable with the new Faculty ID
                }
                facultyTree.get(temp5).addAdvisee(adviseeId);
            }
            facultyTree.remove(temp2);
            // remove student ID from tree
            // takes in variables: studentId
            // Implement the functionality to delete a student
            break;
        }
        case 9: {
            // Change a student’s advisor given the student id and the new faculty id
            cout << "Enter a Student ID to Change Advisor: ";
            cin >> studentIdStr;
            while (!isInteger(studentIdStr)) {
                    cout << "Invalid input. Please enter a valid integer for Student ID: ";
                    cin >> studentIdStr;
                }

            studentId = stoi(studentIdStr);

            Student temp(studentId);
            Faculty temp2(temp.getAdvisor());

            while (!studentTree.contains(temp)) {
                cout << "Student ID doesnt exist. Please enter a different Student ID: ";
                cin >> studentIdStr;

                while (!isInteger(studentIdStr)) {
                    cout << "Invalid input. Please enter a valid integer for Student ID: ";
                    cin >> studentIdStr;
                }

                studentId = stoi(studentIdStr);
                temp = Student(studentId); // Update the existing 'temp' variable with the new student ID
            }

            cout << "Enter a Faculty ID to Change to: ";
            if (studentTree.contains(temp)) {
            

            cout << "Enter the new Advisor ID for the student: ";
            cin >> advisorIdStr;
            while (!isInteger(advisorIdStr)) {
                    cout << "Invalid input. Please enter a valid integer for Faculty ID: ";
                    cin >> advisorIdStr;
                }

            Faculty newAdvisor(stoi(advisorIdStr));
             while (!facultyTree.contains(newAdvisor)) {
                cout << "Faculty ID doesnt exist. Please enter a different Faculty ID: ";
                cin >> advisorIdStr;

                while (!isInteger(advisorIdStr)) {
                    cout << "Invalid input. Please enter a valid integer for Faculty ID: ";
                    cin >> advisorIdStr;
                }

                advisorId = stoi(advisorIdStr);
                newAdvisor = Faculty(advisorId); // Update the existing 'temp' variable with the new student ID
            }

            if (facultyTree.contains(newAdvisor)) {
                // Update the student's advisor in the student tree
                studentTree.get(temp).setAdvisor(advisorId);

                // Add the student to the new advisor's advisees
                facultyTree.get(newAdvisor).addAdvisee(studentId);


                // Remove the student from the old advisor's advisees
              //  facultyTree.get(temp2).removeAdvisee(temp.getStudentId());

            } else {
                cout << "New Advisor does not exist in the database." << endl;
            }
        }
            break;
        }
        case 10: {
            // Remove an advisee from a faculty member given the ids
            // Change a student’s advisor given the student id and the new faculty id
            cout << "Enter the Advisor ID you would like to Remove from: ";
            cin >> advisorIdStr;
            while (!isInteger(advisorIdStr)) {
                    cout << "Invalid input. Please enter a valid integer for Faculty ID: ";
                    cin >> advisorIdStr;
                }
            advisorId = stoi(advisorIdStr);

            Faculty tempAdvisor(advisorId);

             while (!facultyTree.contains(tempAdvisor)) {
                cout << "Faculty ID doesnt exist. Please enter a different Faculty ID: ";
                cin >> advisorIdStr;
                while (!isInteger(advisorIdStr)) {
                    cout << "Invalid input. Please enter a valid integer for Faculty ID: ";
                    cin >> advisorIdStr;
                }
            advisorId = stoi(advisorIdStr);
                tempAdvisor = Faculty(advisorId);
             }
            cout << "Enter a Student ID to Remove: ";
            cin >> studentIdStr;
            while (!isInteger(studentIdStr)) {
                    cout << "Invalid input. Please enter a valid integer for Student ID: ";
                    cin >> studentIdStr;
                }

            studentId = stoi(studentIdStr);

            Student temp(studentId);
            Faculty temp2(temp.getAdvisor());

            while (!studentTree.contains(temp)) {
                cout << "Student ID doesnt exist. Please enter a different Student ID: ";
                cin >> studentIdStr;

                while (!isInteger(studentIdStr)) {
                    cout << "Invalid input. Please enter a valid integer for Student ID: ";
                    cin >> studentIdStr;
                }

                studentId = stoi(studentIdStr);
                temp = Student(studentId); // Update the existing 'temp' variable with the new student ID
            }

            DblList<int> advisees = facultyTree.get(tempAdvisor).getAdvisees();
            bool found = false;;
            for (int i = 0; i < advisees.size(); ++i) {
                if (advisees.get(i) == temp.getAdvisor()) {
                    found = true;
                }
            }
            if (found) {
                cout << "Student ID " << studentId << " removed from Faculty ID: " << tempAdvisor.getFacultyId() << endl;
                facultyTree.get(tempAdvisor).removeAdvisee(temp.getAdvisor());
            } else {
                 cout << "Student ID " << studentId << " is not a advisee of Faculty ID: " << tempAdvisor.getFacultyId() << endl;
            }
           // facultyTree.get(tempAdvisor).addAdvisee(temp.getStudentId());


            break;
        }
        case 11: {
            // Save information to runLog.txt and exit
            std::ofstream outputFile;
            outputFile.open("runLog.txt");

                // Check if the file is successfully opened
                if (!outputFile.is_open()) {
                    std::cerr << "Error: Unable to open runLog.txt for writing.\n";
                    return;
                }

                // Write Student information to the file DOESNT WORK
                outputFile << "Student Information:\n";
                outputFile << studentTree.saveInOrder() << endl;

                // Write Faculty information to the file
                outputFile << "Faculty Information:\n";
                outputFile << facultyTree.saveInOrder() << endl;
              //  outputFile << 
                // Close the file
                outputFile.close();
            

            cout << "Exiting the program. Information saved to runLog.txt.\n";


            // Implement the functionality to save information to runLog.txt and exit
            // run option 1 and 2 but output to a file instead of to terminal
            break;
    }
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
    }
}
int main() {
    LazyBST<Student> studentTree;
    LazyBST<Faculty> facultyTree;

    // SAMPLE DATA

    Faculty john(16, "John Garden", "Professor", "Math");
    Faculty paul(18, "Paul Holand", "Professor", "English");

    Student jake(15, "Jake Smith", "Junior", "Computer Science", 3.5, 16);
    Student jonny(10, "Jonny Johnson", "Sophomore", "Biology", 3.2, 16);
    Student drew(20, "Drew Davis", "Senior", "Electrical Engineering", 3.8, 16);
    Student mike(17, "Mike Miller", "Freshman", "Psychology", 3.0, 16);
    Student kim(12, "Kim Kim", "Junior", "Mathematics", 3.7, 16);
    Student nataniel(25, "Nataniel Nelson", "Sophomore", "Physics", 3.4, 16);
    Student sam(5, "Samuel Samuels", "Senior", "Chemistry", 3.9, 18);
    Student daniel(150, "Daniel Daniels", "Junior", "Mechanical Engineering", 4.0, 18);
    Student josh(180, "Josh Johnson", "Junior", "Computer Engineering", 3.9, 18);
    Student drake(190, "Drake Drake", "Sophomore", "Environmental Science", 3.6, 18);

    john.addAdvisee(jake.getStudentId());
    john.addAdvisee(jonny.getStudentId());
    john.addAdvisee(drew.getStudentId());
    john.addAdvisee(mike.getStudentId());
    john.addAdvisee(kim.getStudentId());
    john.addAdvisee(nataniel.getStudentId());
    paul.addAdvisee(sam.getStudentId());
    paul.addAdvisee(daniel.getStudentId());
    paul.addAdvisee(drake.getStudentId());
    paul.addAdvisee(josh.getStudentId());


    studentTree.insert(jake);
    studentTree.insert(jonny);
    studentTree.insert(drew);
    studentTree.insert(mike);
    studentTree.insert(kim);
    studentTree.insert(nataniel);
    studentTree.insert(sam);
    studentTree.insert(daniel);
    studentTree.insert(josh);


    facultyTree.insert(john);
    facultyTree.insert(paul);

    int choice;
    do {
        printMenu();
        cout << "Enter your choice (1-11): ";
        cin >> choice;
        if (cin.fail()) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clearing the input 
            continue;
        }

        executeCommand(choice, studentTree, facultyTree);
    } while (choice != 11);

    return 0;
}
