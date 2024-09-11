// TreeNode.h
#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <cstdlib>
#include <iostream>
using namespace std;

template <typename T>
class TreeNode {
public:
    TreeNode(T d);
    virtual ~TreeNode();
    T getData();
    bool isBalanced();
    void updateNode();

    template <typename S>
    friend class LazyBST;

private:
    T m_data;
    double m_leftHeight;
    double m_rightHeight;
    TreeNode<T>* m_left;
    TreeNode<T>* m_right;
};

template <typename T>
TreeNode<T>::TreeNode(T d)
{
    m_data = d;
    m_left = nullptr;
    m_right = nullptr;
    m_leftHeight = 1;
    m_rightHeight = 1;
}

template <typename T>
TreeNode<T>::~TreeNode() {
    if (m_left != nullptr) {
        delete m_left;
    }
    if (m_right != nullptr) {
        delete m_right;
    }
}

template <typename T>
T TreeNode<T>::getData() {
    return m_data;
}

template <typename T>
void TreeNode<T>::updateNode() {
    m_leftHeight = (m_left == nullptr) ? 1 : max(m_left->m_leftHeight, m_left->m_rightHeight) + 1;
    m_rightHeight = (m_right == nullptr) ? 1 : max(m_right->m_leftHeight, m_right->m_rightHeight) + 1;
}

#endif // TREE_NODE_H
