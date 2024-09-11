/*
PA5
Faculty.cpp
Drew Floyd
2429112
afloyd@chapman.edu
creates Faculty object

*/

#include "Faculty.h"
#include <sstream>
Faculty::Faculty() {
    facultyId = 0;
    name = "";
    level = "";
    department = "";
}

Faculty::Faculty(int id) {
    facultyId = id; // int
    name = ""; // any string
    level = ""; // lecturer, assistant prof, associate prof, professor
    department = ""; // any string
}

Faculty::Faculty(int id, std::string n, std::string lvl, std::string dept) {
    facultyId = id;
    name = n;
    level = lvl;
    department = dept;
}

int Faculty::getFacultyId() {
    return facultyId;
}

std::string Faculty::getName() {
    return name;
}

std::string Faculty::getLevel() {
    return level;
}

std::string Faculty::getDepartment() {
    return department;
}

 DblList<int> Faculty::getAdvisees() {
    return advisees;
}

void Faculty::addAdvisee(int studentId) {
    advisees.addBack(studentId);
}

int Faculty::removeAdvisee(int studentId) {
    return advisees.remove(studentId); // advisees use dblList
}

bool Faculty::operator==(const Faculty& other) const {
    return facultyId == other.facultyId;
}

bool Faculty::operator<(const Faculty& other) const {
    return facultyId < other.facultyId;
}

bool Faculty::operator>(const Faculty& other) const {
    return facultyId > other.facultyId;
}

bool Faculty::operator!=(const Faculty& other) const {
    return facultyId != other.facultyId;
}

bool Faculty::operator<=(const Faculty& other) const {
    return facultyId <= other.facultyId;
}

bool Faculty::operator>=(const Faculty& other) const {
    return facultyId >= other.facultyId;
}

string Faculty::toString() {
    // Using stringstream to build the string
    stringstream ss;

    // Append each field with a label
    ss << "Faculty ID: " << facultyId << endl;
    ss << "Name: " << name << endl;
    ss << "Level: " << level << endl;
    ss << "Department: " << department << endl;

    // Get the advisees and append to the string
   int current;
    ss << "Advisees: ";
    int n = 0;
  for (int i = 0; i < advisees.size(); i++) {
           current = advisees.get(i);
           ss << current << " ";
  }
    ss << endl;

    // Convert stringstream to string and return
    return ss.str();
}