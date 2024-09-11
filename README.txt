Programming Assignment 5: 
lazyily Balanced Trees
Created By:
Drew Floyd
ID: 2429112
afloyd@chapman.edu

How to run:
type g++ *.cpp -o e.exe
then ./e.exe
follow prompts given by the program

Files:
LazyBST.h: A Templated Lazyily Balanced Binary Search Trees
TreeNode.h: Creates TreeNodes implemented by LazyBST.h
DblList.h: A Templated Doubly Linked List used for the advisees List
ListNode.h: Creates ListNodes implemented by DblList.h
Student.h & Student.cpp: Creates Student Object for the database
Faculty.h & Faculty.cpp: creates Faculty Object for the database
runLog.txt: Prints out the dtatabases when program is exited
main.cpp: prints the menu, handles exceptions, and manages the two databases

KNOWN PROBLEMS: 
DblList advisees doesn't work as intended
Option 8 will result in a Segmentation Fault because of this

The Database works as described in the prompt of the assignment however I ran into an issue trying to add/delete/update advisees and advisor values