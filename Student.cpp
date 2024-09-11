/*
PA5
Student.cpp
Drew Floyd
2429112
afloyd@chapman.edu
creates Student object

*/
#include "Student.h"
#include <iostream>
#include <sstream>
using namespace std;
// Constructors

Student::Student() {
    studentId = 0; // int
    name = ""; // any string
    level = ""; // Freshman, Sophomore, Junior, Senior
    major = ""; // any string
    gpa = 0.0; // double from 0-4
    advisorId = 0; // int
}

Student::Student(int id) {
    studentId = id;
    name = "";
    level = "";
    major = "";
    gpa = 0.0;
    advisorId = 0;
}

Student::Student(int id, string n, string lvl, string mjr, double g, int adv) {
    studentId = id;
    name = n;
    level = lvl;
    major = mjr;
    gpa = g;
    advisorId = adv;
}

// Getter functions
int Student::getStudentId() {
    return studentId;
}

string Student::getName() {
    return name;
}

string Student::getLevel() {
    return level;
}

string Student::getMajor() {
    return major;
}

double Student::getGPA() {
    return gpa;
}

int Student::getAdvisor() {
    return advisorId;
}

void Student::setAdvisor(int newAdvisor) {
    advisorId = newAdvisor;
}

// Overloaded operators
bool Student::operator==(const Student& other) {
    return studentId == other.studentId;
}

bool Student::operator<(const Student& other) {
    return studentId < other.studentId;
}

bool Student::operator>(const Student& other) {
    return studentId > other.studentId;
}

bool Student::operator!=(const Student& other) {
    return studentId != other.studentId;
}

bool Student::operator<=(const Student& other) {
    return studentId <= other.studentId;
}

bool Student::operator>=(const Student& other) {
    return studentId >= other.studentId;
}


string Student::toString() {
    // Using stringstream to build the string
    std::stringstream ss;

    // Append each field with a label
    ss << "Student ID: " << studentId << endl;
    ss << "Name: " << name << endl;
    ss << "Level: " << level << endl;
    ss << "Major: " << major << endl;
    ss << "GPA: " << gpa << endl;
    ss << "Advisor ID: " << advisorId << endl;

    // Convert stringstream to string and return
    return ss.str();
}