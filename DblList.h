#ifndef DBL_LIST_H
#define DBL_LIST_H
#include <cstdlib>

#include "ListNode.h"
#include <iostream>
using namespace std;

template <typename T>
class DblList{
    public:
        DblList();
        virtual ~DblList();
        int size();
        bool isEmpty();
        void addFront(T data);
        void addBack(T data);
        void add(int pos, T data);
        T get(int pos);
        T removeFront();
        T removeBack();
        T remove(int pos);

    private:
        ListNode<T>* m_front;
        ListNode<T>* m_back;
        int m_size;
};

template<typename T>
DblList<T>::DblList(){
    m_front = NULL;
    m_back = NULL;
    m_size = 0;
}

template<typename T>
DblList<T>::~DblList(){
    m_front = NULL;
    m_back = NULL;
    m_size = 0;
}

template<typename T>
int DblList<T>::size(){
    return m_size;
}

template<typename T>
bool DblList<T>::isEmpty(){
    return (m_size == 0);
}

template <typename T>
void DblList<T>::addFront(T data){
    ListNode<T>* newNode = new ListNode<T>(data); // create new node (aka newNode)
		// set newNode’s prev pointer to NULL (done in constructor)
    if (!isEmpty()){ // if linked list is not empty 
        newNode -> m_next = m_front; 
        // set newNode’s next pointer to the old front (aka oldFront)
        m_front -> m_prev = newNode; 
        // set oldFront’s prev pointer to newNode 
    } else { // if list is empty (newNode is 1st node) 
        m_back = newNode; // then set back to newNode too
    }
    m_front = newNode; // set front to newNode regardless 
    ++m_size; // add one to size 
}

template<typename T>
void DblList<T>::addBack(T data){
    // create a new node
    ListNode<T>* newNode = new ListNode<T>(data);
    if(!isEmpty()){ // check if our list is currently empty, if it is not them
        // we need to set the new nodes prev pointer to the back
        newNode->m_prev = m_back;
        // then we need to change the back node's next ptr to newNode
        m_back->m_next = newNode;
    }else{
        m_front = newNode;
        // if it is empty just set m_front to new node cuz its the only one in there
    }
    m_back = newNode;
    // then no matter what the new nopde will become the back node
    ++m_size;
    // add one to count
}

template<typename T>
void DblList<T>::add(int pos, T data){
    if(isEmpty()){
        addFront(data);
    }else if(pos == 0){
        addFront(data);
    }else if(pos >= m_size){
        addBack(data);
    }else{
        ListNode<T>* current = m_front;
        int cPos = 0;
        while(cPos != pos){
            current = current->m_next;
            ++cPos;
        }
        ListNode<T>* newNode = new ListNode<T>(data);
        current->m_prev->m_next = newNode; // change the Node prev to currentPos's NEXT to the new node
        newNode->m_prev = current->m_prev; // set newNode prev to currentPosNode's old prev because it took that spot
        current->m_prev = newNode; // set currentPosNode prev to newNode
        newNode->m_next = current; // set newNode next to currentPosNode
        ++m_size;
    }
}

template<typename T>
T DblList<T>::removeFront(){
    if(isEmpty()){
        cout << "Nuh uh its empty stop trying to remove" << endl;
    }
    //make sure not empty
    T data = m_front->m_data; // save data from old front so we can return it
    if(m_size == 1){
        delete m_front;
        m_front = NULL;
        m_back = NULL;
    }else{
        ListNode<T>* oldFront = m_front;
        m_front = m_front->m_next;
        m_front->m_prev = NULL;
        delete oldFront;
    }
    --m_size;
    return data;
}

template<typename T>
T DblList<T>::removeBack(){
    if(isEmpty()){
        cout << "Nuh uh its empty stop trying to remove" << endl;
    }
    //make sure not empty
     T data = m_back->m_data;
     if(m_size == 1){
        delete m_back;
        m_front = NULL;
        m_back = NULL;
     }else{
        ListNode<T>* currBack = m_back;
        m_back = m_back->m_prev;
        m_back->m_next = NULL;
        delete currBack;
     }
     --m_size;
     return data;
}

template<typename T>
T DblList<T>::remove(int pos){
    //make sure not empty
    if(isEmpty()){
        cout << "Nuh uh its empty stop trying to remove" << endl;
    }
    T data;
    if(pos == 0){
        data = removeFront();
    }else if(pos >= m_size -1){
        data = removeBack();
    }else{
        ListNode<T>* current = m_front;
        int cPos = 0;
        while(cPos != pos){
            current = current->m_next;
            ++cPos;
        }
        data = current->m_data;
        current->m_prev->m_next = current->m_next;
        current->m_next->m_prev = current->m_prev;
        delete current;
        --m_size;
    }
    return data;
}

template<typename T>
T DblList<T>::get(int pos){
    //is pos in range, etc.
    ListNode<T>* current = m_front; // keep track of the current Node you are visiting (If you wanted to optimize you could check if its first half or second half and then start at front or back)
    for (int i = 0; i < pos; ++i) {
        current = current -> m_next; // FOR LOOP OR WHILE LOOP WORKS DANIEL POINTED OUT FOR TEACHER
    }
    // int cPos = 0;
    // while(cPos != pos){ // while the current position is not the wanted postion
    //     current = current->m_next; // set current to next node
    //     ++cPos; // add one to position
    // }
    return current->m_data; // return wanted position node
}


#endif