// Student.h
#ifndef STUDENT_H
#define STUDENT_H

#include <string>  // Add this line

using namespace std;

class Student {
public:
    Student();
    Student(int id);
    Student(int id, string name, string level, string major, double gpa, int advisor);

    int getStudentId();  // Add const to getter functions
    string getName();
    string getLevel();
    string getMajor();
    double getGPA();
    int getAdvisor();
    string toString();
    void setAdvisor(int newAdvisor);
    

    bool operator==(const Student& other);
    bool operator<(const Student& other);
    bool operator>(const Student& other);
    bool operator!=(const Student& other);
    bool operator<=(const Student& other);
    bool operator>=(const Student& other);
    

private:
    int studentId;
    string name;
    string level; // freshman sophomore junior senior
    string major;
    double gpa;
    int advisorId;
};

#endif
