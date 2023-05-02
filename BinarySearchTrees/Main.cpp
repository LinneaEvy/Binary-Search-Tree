#include <iostream>
#include "BinarySearchTree.h"

int main()
{
    BinarySearchTree<int>* tom = new BinarySearchTree<int>(10);
    tom->insertNode(20, tom->mRoot);
    tom->insertNode(6, tom->mRoot);
    tom->insertNode(-3, tom->mRoot);
    tom->insertNode(40, tom->mRoot);
    tom->insertNode(30, tom->mRoot);
    tom->insertNode(2, tom->mRoot);
    tom->insertNode(7, tom->mRoot);
    tom->insertNode(15, tom->mRoot);
    tom->insertNode(1, tom->mRoot);
    tom->insertNode(-4, tom->mRoot);
    tom->insertNode(0, tom->mRoot);
    tom->inorderTraversal(tom->mRoot);
}