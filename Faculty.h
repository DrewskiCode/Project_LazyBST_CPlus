// Faculty.h
#ifndef FACULTY_H
#define FACULTY_H
using namespace std;
#include "DblList.h"
#include <string>
#include <list>

class Faculty {
public:
    //constructors
    Faculty();
    Faculty(int id);
    Faculty(int id, string name, string level, string department);
    // getters
    int getFacultyId();
    string getName();
    string getLevel();
    string getDepartment();
    DblList<int> getAdvisees();
    // to string
    string toString();
    // add/remove for DblList
    void addAdvisee(int studentId);
    int removeAdvisee(int studentId);

    // overloaded operators
    bool operator==(const Faculty& other) const;
    bool operator<(const Faculty& other) const;
    bool operator>(const Faculty& other) const;
    bool operator!=(const Faculty& other) const;
    bool operator<=(const Faculty& other) const;
    bool operator>=(const Faculty& other) const;

private:
    int facultyId;
    string name;
    string level;
    string department;
    DblList<int> advisees;
};

#endif
