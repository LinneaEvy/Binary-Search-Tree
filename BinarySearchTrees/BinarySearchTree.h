#pragma once
#include <iostream>

#include <queue>
#include <iostream>
#include <vector>
using namespace std;
template<typename E>


class BinarySearchTree
{

protected:
    struct Node {
        E data;
        Node* parent;
        Node* left;
        Node* right;
        Node(E data) : data(data), parent(NULL), left(NULL), right(NULL) { }
    };
private:
    int NumberOfNodes = 0;
    bool rotated = false;
    int currentLeftHeight;
    int currentRightHeight;
    Node* mostRecentlyAdded;
public:
    Node* mRoot;
    BinarySearchTree(E data) {
        //numberOfTrees++; 
        mRoot = new Node(data);
        NumberOfNodes++;
    }
    ~BinarySearchTree();
    void destroyRecursive(Node* root);

    void insertNodeHelper(E data, Node* root);
    void insertNode(E data, Node* root);
    void preorderBalance(Node* v);
    void balanceValue(Node* v);
    int bf(Node* v) {
        height(v, v->data);
        //std::cout << "currentLeft" << currentLeftHeight << "    currentRight" << currentRightHeight << std::endl;
        return (currentRightHeight - currentLeftHeight);
    }
    int findHeightUtil(Node* root, E x, int& height);
    void height(Node* v, E x);

    void inorderTraversal(Node* v);
    void preorder(Node* v);
    void LevelOrder(Node* root);
    int getNumberOfNodes() { return NumberOfNodes; }

    void leftLeftCase(Node* v);
    void leftRightCase(Node* v);
    void rightLeftCase(Node* v);
    void rightRightCase(Node* v);
    void rightRotation(Node* v);
    void leftRotation(Node* v);

    int recursiveTree(int v1, int y1, int c, Node* v, int depth);
    void printTree();
    void printSubTree(Node* p);
    void printSubTree(std::string& prefix, Node* p, bool isLeft);
};

template<typename E>
inline BinarySearchTree<E>::~BinarySearchTree()
{
    destroyRecursive(mRoot);


}

template<typename E>
inline void BinarySearchTree<E>::destroyRecursive(Node* root)
{
    if (root->left != NULL)                    // traverse left subtree
        destroyRecursive(root->left);
    if (root->right != NULL)                    // traverse right subtree
        destroyRecursive(root->right);
    delete root;
    root = nullptr;
}

template<typename E>
inline void BinarySearchTree<E>::insertNode(E data, Node* root)
{
    insertNodeHelper(data, root);
    printTree();
    preorderBalance(mRoot);
    if (rotated) { 
        printTree(); 
        rotated = false;
    }
}

template<typename E>
inline void BinarySearchTree<E>::insertNodeHelper(E data, Node* root)
{
    if (root->data == NULL) {
        return;
    }
    if (root->data == data) {
        return;
    }if (root->data >= data) {
        if (root->left == NULL) {
            Node* v = new Node(data);
            root->left = v;
            v->parent = root;
            mostRecentlyAdded = v;
        }
        else { insertNode(data, root->left); }
    }if (root->data <= data) {
        if (root->right == NULL) {
            Node* v = new Node(data);
            root->right = v;
            v->parent = root;
            mostRecentlyAdded = v;
        }
        else { insertNode(data, root->right); }
    }

}

template<typename E>
inline void BinarySearchTree<E>::preorderBalance(Node* v)
{

    if (v->left != NULL)                    // traverse left subtree
        preorderBalance(v->left);
    if (v->right != NULL)                    // traverse right subtree
        preorderBalance(v->right);
    if (v->left != NULL || v->right != NULL) {
        balanceValue(v);
    }
}

template<typename E>
inline void BinarySearchTree<E>::balanceValue(Node* v)
{
    if (bf(v) == -2)
    {
        if (bf(v->left) <= 0) {
            leftLeftCase(v);
            rotated = true;
        }
        else {
            leftRightCase(v);
            rotated = true;
        }
    }
    else if (bf(v) == 2)
    {
        if (bf(v->right) >= 0) {
            rightRightCase(v);
            rotated = true;
        }
        else {
            rightLeftCase(v);
            rotated = true;
        }
    }
}

template<typename E>
inline int BinarySearchTree<E>::findHeightUtil(Node* root, E x, int& height)
{
    if (root == NULL) {
        return -1;
    }
    int leftHeight = findHeightUtil(root->left, x, height);

    int rightHeight = findHeightUtil(root->right, x, height);

    // Update height of the current node
    int ans = max(leftHeight, rightHeight) + 1;

    // If current node is the required node
    if (root->data == x)
        height = ans;
    currentLeftHeight = leftHeight;
    currentRightHeight = rightHeight;
    return ans;
}

template<typename E>
inline void BinarySearchTree<E>::height(Node* v, E x)
{
    int height = -1;
    int maxHeight = findHeightUtil(v, x, height);
}



template<typename E>
inline void BinarySearchTree<E>::inorderTraversal(Node* v)
{
    if (v->left != NULL)                    // traverse left subtree
        inorderTraversal(v->left);
    std::cout << v->data;
    std::cout << endl;
    if (v->right != NULL)                    // traverse right subtree
        inorderTraversal(v->right);
    
}

template<typename E>
void BinarySearchTree<E>::preorder(Node* v) {
    std::cout << v->data;
    if (v->left != NULL)                    // traverse left subtree
        preorder(v->left);
    if (v->right != NULL)                    // traverse right subtree
        preorder(v->right);
    std::cout << std::endl;
}

template<typename E>
void BinarySearchTree<E>::LevelOrder(Node* root) {
    if (root == NULL) return;
    std::queue<Node*> Q;//remove from front add to back
    Q.push(root);
    //while there is at least one discovered node
    int i = 0;
    while (!Q.empty()) {
        i++;
        Node* current = Q.front();//das element was als erstes rermoved wird ist current
        Q.pop(); // removing the element at front
        cout << "Data, Layer" << current->data << "," << i << endl;
        queue<Node> T = Q;
        cout << "Inside que";
        while (!T.empty()) {
            cout << T.front()->data << "  "; // die que beeinhaltet alles was in dem Layer ist zu dem zeitpunkt
            T.pop();
        }cout << endl;
        if (current->left != NULL) Q.push(current->left);//das nächste linke und rechte wird hinzugefügt das linke wird im nächsten verlauf gelöscht links und rechts werden hinzugefügt
        if (current->right != NULL) Q.push(current->right);//im verlauf danach wird rschts gelöscht und links und rechts davon hinzugefügt.
    }
}



template<typename E>
inline void BinarySearchTree<E>::leftLeftCase(Node* v)
{
    std::cout << "leftLeftCase " << v->data << std::endl;
    rightRotation(v);
}

template<typename E>
inline void BinarySearchTree<E>::leftRightCase(Node* v)
{
    std::cout << "LeftRightCase " << v->data << std::endl;
    leftRotation(v->left);
    leftLeftCase(v);
}

template<typename E>
inline void BinarySearchTree<E>::rightLeftCase(Node* v)
{
    std::cout << "RightLeftCase " << v->data << std::endl;
    rightRotation(v->right);
    rightRightCase(v);
}

template<typename E>
inline void BinarySearchTree<E>::rightRightCase(Node* v)
{
    std::cout << "rightRightCase " << v->data << std::endl;
    leftRotation(v);
}

template<typename E>
inline void BinarySearchTree<E>::rightRotation(Node* v)
{
    std::cout << "RightRotation around " << v->data << std::endl;
    Node* oldParent = v->parent;
    Node* oldLeft = v->left;
    v->left = oldLeft->right;//A zu E
    if (oldLeft->right != NULL) {
        oldLeft->right->parent = v;
    }
    oldLeft->right = v;
    v->parent = oldLeft;
    oldLeft->parent = oldParent;
    if (oldParent != NULL) {
        if (oldParent->left == v) {
            oldParent->left = oldLeft;
        }
        else {
            oldParent->right = oldLeft;
        }
    }

}

template<typename E>
inline void BinarySearchTree<E>::leftRotation(Node* v)
{
    std::cout << "LeftRotation around " << v->data << std::endl;
    Node* oldParent = v->parent;
    Node* oldRight = v->right;
    v->right = oldRight->left;//A zu E
    if (oldRight->left != NULL) {
        oldRight->left->parent = v;
    }
    oldRight->left = v;
    v->parent = oldRight;
    oldRight->parent = oldParent;
    if (oldParent != NULL) {
        if (oldParent->right == v) {
            oldParent->right = oldRight;
        }
        else {
            oldParent->left = oldRight;
        }
    }
}



template<typename E>
int BinarySearchTree<E>::recursiveTree(int v1, int y1, int c, Node* v, int depth) // this is used to draw the tree in open frameworks
{
    /*if (depth == 0) {
        return 0;
    }
    ofSetColor(155, 29, 227);
    ofSetLineWidth(3);

    ofDrawLine(v1, y1, 0, v1 / 2, y1 + ofGetHeight() / pow(2, c), 0);
    ofDrawLine(v1, y1, 0, v1 + (v1 / 2), y1 + ofGetHeight() / pow(2, c), 0);

    ofSetColor(244, 244, 244);
    ofDrawBitmapString(v->data, v1, y1 + 10);
    ofSetColor(155, 29, 227);
    if (v->left != NULL /* && v->right != NULL / ) {
        ofSetColor(244, 244, 244);
        ofDrawBitmapString(v->left->data, v1 / 2, (y1 + (ofGetHeight() / pow(2, c))) + 10);
        ofSetColor(155, 29, 227);
        recursiveTree(v1 / 2, y1 + (ofGetHeight() / pow(2, c)), c + 1, v->left, depth - 1);
    }
    else { return 0; }
    if (/*v->left != NULL && /v->right != NULL) {
        ofPushMatrix();
        ofTranslate(v1, 0);
        ofSetColor(244, 244, 244);
        ofDrawBitmapString(v->right->data, v1 / 2, (y1 + (ofGetHeight() / pow(2, c))) + 10);
        ofSetColor(155, 29, 227);
        recursiveTree(v1 / 2, y1 + (ofGetHeight() / pow(2, c)), c + 1, v->right, depth - 1);
        ofPopMatrix();
    }
    else { return 0; }*/
}

template <typename E>
void BinarySearchTree<E>::printTree() {
    printSubTree(mRoot);
}

template <typename E>
void BinarySearchTree<E>::printSubTree(Node* p) {
    std::string tom = "";
    printSubTree(tom, p, false);
}

template <typename E>
void BinarySearchTree<E>::printSubTree(std::string& prefix, Node* p, bool isLeft) {
    std::cout << prefix;
    Node* v = p;//p.v
    if (v->parent == nullptr) std::cout << "---- ";
    else
        if (isLeft) std::cout << " |--- ";
        else
            std::cout << " '--- ";

    // print the value of the node
    std::cout << v->data << std::endl;

    // enter the next tree level - left and right branch
    std::string tom = prefix + (isLeft ? " |  " : "    ");
    std::string thomas = prefix + (isLeft ? " |  " : "    ");
    if (v->left != nullptr) { printSubTree(tom, p->left, true); }
    if (v->right != nullptr) { printSubTree(thomas, p->right, false); }
}


