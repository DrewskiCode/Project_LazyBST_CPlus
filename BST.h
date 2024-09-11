#ifndef BST_H
#define BST_H

#include "TreeNode.h"

template <typename T>
class BST{
    public:
				// lecture 17
        BST();
        virtual ~BST();
        bool iterContains(T d); 
        bool contains(T d); // recursive version that uses recContainsHelper
        void printInOrder(); // least to greatest 
        void printTreePostOrder(); // left tree then right tree then root 
				// lecture 18
        void insert(T d);
        int size(); 
        T max(); // right most child
        T min(); // left most child 
        T median(); // will only work if tree is balanced 
        // lecture 19
        void remove (T d); 
         
    private: 
				// lecture 17
        TreeNode<T>* m_root;
        int m_size;
        bool recContainsHelper(TreeNode<T>* n, T d); 
        void printIOHelper(TreeNode<T>* n);
        void printTreePostOrderHelper(TreeNode<T>* subTreeRoot); // do this as participation
				// lecture 18
        void insertHelper(TreeNode<T>*& subTreeRoot, T& d);
        T getMaxHelper(TreeNode<T>* n);
        T getMinHelper(TreeNode<T>* n);
            // lecture 19 
        void findTarget(T key, TreeNode<T>*& target, TreeNode<T>*& parent);
        TreeNode<T>* getSuccessor (TreeNode<T>* rightChild);
     
};



    // ***************************************************************** // 
    // ****************** LECTURE  17 ********************************** // 
    // ***************************************************************** // 


   template <typename T>
        BST<T>::BST(){
        m_root = NULL;
        m_size = 0;
    }

    template <typename T>
    BST<T>::~BST(){
        // TO DO: free up all memory 
    }


    // how do we find whether or not a tree contains a key?
        // navigate through the tree until we find it 
        // well it's not linear and each node has a left and right child potentially so... 

        // let's say we are at the root and we assume the root is not null
        // how do we know if the tree contains "d"?
        // let's try iteratively 
    template <typename T>
    bool BST<T>::iterContains(T d){
        if (m_root == NULL){ // tree is empty
            return false; 
        }
        if (m_root -> data == d){ // root is the key d
            return true;
        }

        // look for d 
        bool found = false; 
        TreeNode<T>* current = m_root;
        while (!found){
            // check if d is greater than current go right 
            if (d > current -> m_data){
                current = current -> m_right;
            } else { // if d is less than/ == current go left 
                current = current -> m_left;
            } 
            // check if current node is NULL -> we've reached a leaf and d was not found
            if (current == NULL){
                found =  false; 
                break;
            }

            // check if the current node's data is d -> we found d 
            if (current -> m_data == d){
                found = true;
            }
        }
        return found;
    }

    // RECURSIVE CONTAINS
    template <typename T>
    bool BST<T>::contains(T d){
        return recContainsHelper(m_root, d);
    }

    // RECURSIVE CONTAINS HELPER
    template <typename T>
    bool BST<T>::recContainsHelper( TreeNode<T>* n, T d){
        if (n == NULL){ // if it is null then d is not in tree 
            return false;
        } 
        if (n -> m_data == d) { // if it is not null, is it here? 
            return true;
        }
        if (d > n -> m_data){ // it's not null but it's also not here, check if it is > or <
            return recContainsHelper( n -> m_right, d);
        } else {
            return recContainsHelper( n -> m_left, d);
        }
    }

    template <typename T>
    void BST<T>::printInOrder(){
        printIOHelper(m_root);
    }

    template <typename T>
    void BST<T>::printIOHelper(TreeNode<T>* n){
        if (n != NULL){ // is the node null? 
            printIOHelper(n -> m_left); // if not then print the left thing 
            std::cout << n -> m_data << std::endl; // then print the key of the curr node 
            printIOHelper(n -> m_right); // then print the right thing 
        } 
    }


    template <typename T>
    void BST<T>::printTreePostOrder(){
        printTreePostOrderHelper(m_root);
    }

    template <typename T>
    void BST<T>::printTreePostOrderHelper(TreeNode<T>* subTreeRoot){
        if(subTreeRoot != NULL){
            printTreePostOrderHelper(subTreeRoot->m_left);
            printTreePostOrderHelper(subTreeRoot->m_right);
            std::cout << subTreeRoot->m_data << std::endl;
        }
    }

    // ***************************************************************** // 
    // ****************** LECTURE  18 ********************************** // 
    // ***************************************************************** // 

    // INSERT RECURSIVETY 
    template <typename T>
    void BST<T>::insert(T d){
        insertHelper(m_root, d);
        ++m_size;

    }
    // INSERT HELPER SO WE DO NOT HAVE TO PASS IN ROOT 
    // pass in by reference so that you don't have to manually mess with pointers (r & l children)
    template <typename T>
    void BST<T>::insertHelper(TreeNode<T>*& subTreeRoot, T& d){
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
    int BST<T>::size(){
       return m_size;
    }

    
    // GET MAX 
    template <typename T>
    T BST<T>::max(){
       return getMaxHelper(m_root);
    }

    template <typename T>
    T BST<T>::getMaxHelper(TreeNode<T>* n){
       if(n -> m_right == NULL){
        return n -> m_data;
       } else {
            return getMaxHelper(n -> m_right);
       }
       
    }

    // GET MIN 
    template <typename T>
    T BST<T>::min(){
       return getMinHelper(m_root);
    }

    template <typename T>
    T BST<T>::getMinHelper(TreeNode<T>* n){
       if(n -> m_left == NULL){
            return n -> m_data;
       } else {
            return getMinHelper(n -> m_left);
       }
       
    }


    // GET MEDIAN - ONTY WORKS IF TREE IS BALANCED! 
    template <typename T>
    T BST<T>::median(){
        //check if empty we assume it is a non-empty tree
        return m_root->m_data;
    }

    // ***************************************************************** // 
    // ****************** LECTURE  19 ********************************** // 
    // ***************************************************************** //

    // HELPER METHODS 
    template <typename T>
    void BST<T>::findTarget(T key, TreeNode<T>*& target, TreeNode<T>*& parent){ // passing in the actual object target so no need to return or set to when the function is called
        // FIND THE NODE WE WANT TO DELETE AND ITS PARENT NODE 
        while (target != NULL && target -> m_data != key){ // while target still has children and it is not our actual target
            parent = target; 
            if (key < target -> m_data){ // data greater than target, go left SHOULD I ADD AN IF STATEMENT BEFORE THIS ONE TO CHECK IF KEY IS EQUAL TO TARGET AND NOT MESS WITH IT ANS: NO I DONT NEED TO BECAUSE IT WILL CHECK AT THE START OF THE LOOP ONCE THE TARGET IS SET TO A NEW VALUE
                target = target -> m_left; 
            } else { // otherwise go right because key is greater
                target = target -> m_right;
            }
        }
    }

    template <typename T>
    TreeNode<T>* BST<T>::getSuccessor (TreeNode<T>* rightChild){ // VERIFIES IF RIGHT CHILD IS SUCESSOR OR IF RIGHT CHILD HAS A LEFT CHILD WHICH WOULD BE SUCESSOR OF TARGET
        while (rightChild -> m_left != NULL){ // If the node coming in (rightChild) doesn't have a left child then this is our successor and we're done, else:
            rightChild = rightChild -> m_left; // getting the right childs leftmost child, go down the family tree
        }
        return rightChild; // not really (necessarily) a right child, this is the successor! 
    }

    template <typename T>
    void BST<T>::remove(T d){
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
    }




#endif