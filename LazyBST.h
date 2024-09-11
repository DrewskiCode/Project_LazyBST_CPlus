/*
PA5
LazyBST.h
Drew Floyd
2429112
afloyd@chapman.edu
Creates Lazily Balanced Tree
*/

#ifndef LazyBST_H
#define LazyBST_H
#include <sstream>
#include <string>
#include "TreeNode.h"

template <typename T>
class LazyBST{
    public:
        LazyBST();
        virtual ~LazyBST();
        bool isEmpty(); // is empty?
        bool contains(T d); // recursive version that uses recContainsHelper
        void printInOrder(); // least to greatest 
        void printTreePostOrder(); // left tree then right tree then root 
        std::string saveInOrder();
        bool isBalanced(); // check to see if tree is balanced (Lazy)
        void insert(T d); // insert into Tree
        int size(); // size of tree
        T max(); // right most child
        T min(); // left most child 
        T median(); // will only work if tree is balanced 
        void remove (T d); // remove from Tree
        T root(); // get root of tree
        void rebalance(); // Rebalance the Tree (Lazy)
        T get(T data); // get T data from Tree
         
    private: 
        TreeNode<T>* m_root;
        int m_size;
        void saveIOHelper(TreeNode<T>* n, std::stringstream& ss);
        bool recContainsHelper(TreeNode<T>* n, T d); 
        void printIOHelper(TreeNode<T>* n);
        void updateHeights(TreeNode<T>* subTreeRoot);
        void printTreePostOrderHelper(TreeNode<T>* subTreeRoot);
        T getHelper(TreeNode<T>* subTreeRoot, T data);
        bool isBalancedHelper(TreeNode<T>* subTreeRoot);
        bool isBalancing = false;
        void insertHelper(TreeNode<T>*& subTreeRoot, T& d);
        T getMaxHelper(TreeNode<T>* n);
        T getMinHelper(TreeNode<T>* n);
        void findTarget(T key, TreeNode<T>*& target, TreeNode<T>*& parent);
        TreeNode<T>* getSuccessor (TreeNode<T>* rightChild);
        void getSortedValues(TreeNode<T>* subTreeRoot, T* values, int& index);
        void buildBalancedTree(T* values, int startIndex, int size);
        int findSize(TreeNode<T>* subTreeRoot);
};

   template <typename T>
        LazyBST<T>::LazyBST(){
        m_root = NULL;
        m_size = 0;
    }

    template <typename T>
    LazyBST<T>::~LazyBST(){
    }

    // RECURSIVE CONTAINS
    template <typename T>
    bool LazyBST<T>::contains(T d){
        return recContainsHelper(m_root, d);
    }

    template <typename T>
bool LazyBST<T>::isEmpty() {
    return m_root == nullptr;
}

    // RECURSIVE CONTAINS HELPER
    template <typename T>
    bool LazyBST<T>::recContainsHelper(TreeNode<T>* n, T d){
        if (n == NULL){ // if it is null then d is not in tree 
            return false;
        } 
        if (n -> m_data == d) { // if it is not null, is it here? 
            return true;
             std::cout << n -> m_data.toString() << std::endl; 
        }
        if (d > n -> m_data){ // it's not null but it's also not here, check if it is > or <
            return recContainsHelper( n -> m_right, d);
        } else {
            return recContainsHelper( n -> m_left, d);
        }
    }

    template <typename T>
    std::string LazyBST<T>::saveInOrder() {
        std::stringstream ss;  // Create a stringstream to build the string representation
        saveIOHelper(m_root, ss);  // Pass the stringstream to the helper function
        return ss.str();  // Return the built string
}

template <typename T>
    void LazyBST<T>::saveIOHelper(TreeNode<T>* n, std::stringstream& ss) {
        if (n != nullptr) {  // Check if the node is null
            saveIOHelper(n->m_left, ss);  // Traverse left
            ss << n->m_data.toString() << "\n";  // Append the key of the current node to the stringstream
            saveIOHelper(n->m_right, ss);  // Traverse right
    }
}

    template <typename T>
    void LazyBST<T>::printInOrder(){
        printIOHelper(m_root);
    }

    template <typename T>
    void LazyBST<T>::printIOHelper(TreeNode<T>* n){
        if (n != NULL){ // is the node null? 
            printIOHelper(n -> m_left); // if not then print the left thing 
            std::cout << n -> m_data.toString() << std::endl; // then print the key of the curr node 
            printIOHelper(n -> m_right); // then print the right thing 
        } 
    }

    template <typename T>
    void LazyBST<T>::printTreePostOrder(){
        printTreePostOrderHelper(m_root);
    }

    template <typename T>
    void LazyBST<T>::printTreePostOrderHelper(TreeNode<T>* subTreeRoot){
        if(subTreeRoot != NULL){
            printTreePostOrderHelper(subTreeRoot->m_left);
            printTreePostOrderHelper(subTreeRoot->m_right);
            std::cout << subTreeRoot->m_data << std::endl;
        }
    }

    // INSERT RECURSIVETY 
    template <typename T>
    void LazyBST<T>::insert(T d){
        insertHelper(m_root, d);
        ++m_size;
        if (isBalancing) {
            return;
        }
        updateHeights(m_root);
        if (isBalanced()) {
                cout << "balanced" << endl;
            } else {
                cout << "NOT balanced" << endl;
                rebalance();
                cout << "Rebalance COMPLETE" << endl; // doesnt get to this line
            }
    }
    // INSERT HELPER SO WE DO NOT HAVE TO PASS IN ROOT 
    // pass in by reference so that you don't have to manually mess with pointers (r & l children)
    template <typename T>
    void LazyBST<T>::insertHelper(TreeNode<T>*& subTreeRoot, T& d){
        if(subTreeRoot == NULL){
            subTreeRoot =  new TreeNode<T>(d); // insert here  & stop recursive call 
        } else if(d > subTreeRoot->m_data){
            insertHelper(subTreeRoot->m_right, d);

        } else{ // Less than or = to so we will have repeats in this tree. 
								// Some say duplicates are not allowed in trees but you can alternatively 
								// choose whether to put them to left or right as long as you're consistent
            insertHelper(subTreeRoot->m_left, d);
        }
    }

    // HELPER METHODS 

    // GET SIZE 
    template <typename T>
    int LazyBST<T>::size(){
       return m_size;
    }

    // GET ROOT
    template <typename T>
    T LazyBST<T>::root(){
       return m_root->getData();
    }

    
    // GET MAX 
    template <typename T>
    T LazyBST<T>::max(){
       return getMaxHelper(m_root);
    }

    template <typename T>
    T LazyBST<T>::getMaxHelper(TreeNode<T>* n){
       if(n -> m_right == NULL){
        return n -> m_data;
       } else {
            return getMaxHelper(n -> m_right);
       }
       
    }

    // GET MIN 
    template <typename T>
    T LazyBST<T>::min(){
       return getMinHelper(m_root);
    }

    template <typename T>
    T LazyBST<T>::getMinHelper(TreeNode<T>* n){
       if(n -> m_left == NULL){
            return n -> m_data;
       } else {
            return getMinHelper(n -> m_left);
       }
       
    }


    // GET MEDIAN - ONTY WORKS IF TREE IS BALANCED! 
    template <typename T>
    T LazyBST<T>::median(){
        return m_root->m_data;
    }

    // HELPER METHODS 
    template <typename T>
    void LazyBST<T>::findTarget(T key, TreeNode<T>*& target, TreeNode<T>*& parent){ // passing in the actual object target so no need to return or set to when the function is called
        // FIND THE NODE WE WANT TO DELETE AND ITS PARENT NODE 
        while (target != NULL && target -> m_data != key){ // while target still has children and it is not our actual target
            parent = target; 
            if (key < target -> m_data){ // data greater than target, go left
                target = target -> m_left; 
            } else { // otherwise go right because key is greater
                target = target -> m_right;
            }
        }
    }

    template <typename T>
    TreeNode<T>* LazyBST<T>::getSuccessor (TreeNode<T>* rightChild){ // VERIFIES IF RIGHT CHILD IS SUCESSOR OR IF RIGHT CHILD HAS A LEFT CHILD WHICH WOULD BE SUCESSOR OF TARGET
        while (rightChild -> m_left != NULL){ // If the node coming in (rightChild) doesn't have a left child then this is our successor and we're done, else:
            rightChild = rightChild -> m_left; // getting the right childs leftmost child, go down the family tree
        }
        return rightChild; // not really (necessarily) a right child, this is the successor! 
    }

    template <typename T>
    void LazyBST<T>::remove(T d){
        // check if tree is empty 
        // we assume the tree is non-empty 
        TreeNode<T>* target = NULL; 
        TreeNode<T>* parent = NULL; 
        target = m_root;

        // find the target 
        findTarget(d, target, parent); // no need save under any variables, target and parent are redefined bc we passed them in by reference  
        
        // target value was not found - it does not exist in our tree
        if (target == NULL){
            return;
        }

        // SCENARIO 1: TARGET IS A LEAF (INCLUDING ROOT)
        if (target -> m_left == NULL && target -> m_right == NULL){
            if (target == m_root){ // THE ONLY THING IN THE TREE IS A LEAF ROOT
                m_root = NULL;
            } else { // if it's a leaf but not the root 
                // check if target is its parent's left or right child 
                if (target == parent -> m_left){ // if target is a left child
                    parent -> m_left = NULL;
                } else { // target is a right child 
                    parent -> m_right = NULL;
                }
            }
            delete target;
						--m_size;
        } 

        // SCENARIO 3: TARGET HAS TWO CHILDREN 
        else if (target -> m_left != NULL && target -> m_right != NULL){  // both children pointers are not null
            TreeNode<T>* suc = getSuccessor(target -> m_right); // find sucessor of target
            T value = suc -> m_data; // get sucessor data
            remove(value); // remove the sucessor, this can call scenario 1 or 2 DO NOT DELETE target or REMOVE size because its done inside here
            target -> m_data = value; // set sucessor data to target
        } 

        // SCENARIO 2: TARGET HAS 1 CHILD 
        else { 
            TreeNode<T>* child;
            // check whether target has a left or right child 
            if (target -> m_left != NULL){ // target has a left child 
                child = target -> m_left;
            } else{                        // target has a right child 
                child = target -> m_right;
            }

            if (target == m_root){
                m_root = child; // if deleting the root set the m_root to the chid to set the newRoot to the only child of the old m_root
            } else {
                if (target == parent -> m_left){ // our target is a left child 
                    parent -> m_left = child; // make the parent's left child the target's child 
                } else {                       // our target is a right child 
                    parent -> m_right = child; // make the parent's right child the target's child 
                }
            }
						target -> m_left = NULL;
						target -> m_right = NULL;

            delete target;
						-- m_size;
        }
             if (isBalancing) {
            return;
        }
            updateHeights(m_root); // updates the heights in the tree before balance check
                        if (isBalanced()) { // balance check
                cout << "balanced" << endl;
            } else {
                cout << "NOT balanced" << endl;
                rebalance(); // if not balanced rebalance
                cout << "Rebalance COMPLETE" << endl;
            }
    }

template <typename T>
bool LazyBST<T>::isBalanced() {
    return isBalancedHelper(m_root);
}

template <typename T>
bool LazyBST<T>::isBalancedHelper(TreeNode<T>* subTreeRoot) {
    if (subTreeRoot == nullptr) {
        return true; // An empty tree is considered balanced
    }

    int leftHeight = subTreeRoot->m_leftHeight;
    int rightHeight = subTreeRoot->m_rightHeight;
    double max_height = std::max(leftHeight, rightHeight);
    double min_height = std::min(leftHeight, rightHeight);
   // cout << "MAX: " << max_height << " DIVIDED BY MIN: " << min_height << endl;
    double balanceFactor = max_height / min_height;

    // Check if the balance factor is within the acceptable range (-1.5, 0, 1.5)
    if (balanceFactor > 1.5 && min_height > 1) {
        return false; // The tree is not balanced
    }

    return true;
}

template <typename T>
void LazyBST<T>::updateHeights(TreeNode<T>* subTreeRoot) { // fix update heights
    if (subTreeRoot != nullptr) {
        updateHeights(subTreeRoot->m_left);
        updateHeights(subTreeRoot->m_right);
        subTreeRoot->updateNode(); // Update the node's left and right heights FIX UPDATE NODE
    }
}

template <typename T>
void LazyBST<T>::rebalance() {
    isBalancing = true;

    // Get the number of values
    int size = findSize(m_root);

    // Build a new balanced tree
    LazyBST<T> balancedTree;
    T* sortedValues = new T[m_size]; // create Array for sorted values
    int index = 0;
    getSortedValues(m_root, sortedValues, index);

    while (m_size > 0) {
        remove(min()); // remove all from current BST after sortedValues are stored in sortedValues
    }

    buildBalancedTree(sortedValues, 0, size - 1); // build the balanced Tree

    delete[] sortedValues; 
    isBalancing = false;
}

template <typename T>
void LazyBST<T>::getSortedValues(TreeNode<T>* subTreeRoot, T* values, int& index) {
    if (subTreeRoot != nullptr) {
        getSortedValues(subTreeRoot->m_left, values, index);
        values[index++] = subTreeRoot->m_data;
        getSortedValues(subTreeRoot->m_right, values, index);
    }
}

template <typename T>
void LazyBST<T>::buildBalancedTree(T* values, int startIndex, int size) {
    if (size >= startIndex && size >= 0) {
        int midIndex = startIndex + (size - startIndex) / 2;

        // Choose the median value and insert into the new tree
        insert(values[midIndex]);

        // Recursively build the left subtree
        buildBalancedTree(values, startIndex, midIndex - 1);

        // Recursively build the right subtree
        buildBalancedTree(values, midIndex + 1, size);
    }
}

template <typename T>
int LazyBST<T>::findSize(TreeNode<T>* subTreeRoot) {
    if (subTreeRoot == nullptr) {
        return 0;
    }
    return 1 + findSize(subTreeRoot->m_left) + findSize(subTreeRoot->m_right);
}

template <typename T>
T LazyBST<T>::get(T data) {
    return getHelper(m_root, data);
}

template <typename T>
T LazyBST<T>::getHelper(TreeNode<T>* subTreeRoot, T data) {
    if (subTreeRoot == nullptr) {
        // case when the key is not found
        // return a default-constructed object of type T
        return T();
    }

    if (data < subTreeRoot->m_data) {
        return getHelper(subTreeRoot->m_left, data);
    } else if (data > subTreeRoot->m_data) {
        return getHelper(subTreeRoot->m_right, data);
    } else {
        return subTreeRoot->m_data;
    }
}

#endif