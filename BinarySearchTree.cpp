#include <string>
#include "BinarySearchTree.h"
#include <chrono>
#include <iostream>
using namespace std;
using namespace std::chrono;

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() : root(nullptr)
{
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree()
{
    clear();
}

/**
 * @return pointer to the root of the tree.
 */
BinaryNode *BinarySearchTree::getRoot() const
{
    return root;
}

void BinarySearchTree::reset(){
    probeCount=0;
    compareCount=0;
    elapsedTime=0;
}

/**
 * Public method to return the height of a subtree.
 * @return the height.
 */
int BinarySearchTree::height() 
{
    return height(root);
}

/**
 * Protected method to compute the height of a subtree.
 * @param ptr pointer to the root node of the subtree.
 * @return the height.
 */
int BinarySearchTree::height(const BinaryNode *ptr)
{
    probeCount++;
    return ptr == nullptr ? -1
                          : 1 + max(height(ptr->left),
                                    height(ptr->right));
}

/**
 * Public method to find the minimum data item in a subtree.
 * @return the minimum data item in the tree
 *         or nullptr if the tree is empty.
 */
int BinarySearchTree::findMin() const throw(string)
{
    if (isEmpty()) throw(string("Empty tree"));
    return findMin(root)->data;
}

/**
 * Private method to find the minimum data item in a subtree.
 * @param ptr pointer to the root node of the subtree.
 * @return pointer to the node containing the smallest data item
 *         or nullptr if the subtree is empty.
 */
BinaryNode *BinarySearchTree::findMin(BinaryNode *ptr) const
{
    if (ptr != nullptr)
    {
        while(ptr->left != nullptr) {ptr = ptr->left;}
    }

    return ptr;
}

/**
 * Public method to find the maximum data item in a subtree.
 * @return pointer to the maximum data item in the tree
 *         or nullptr if the tree is empty.
 */
int BinarySearchTree::findMax() const throw(string)
{
    if (isEmpty()) throw(string("Empty tree"));
    return findMax(root)->data;
}

/**
 * Private method to find the maximum data item in a subtree.
 * @param ptr pointer to the root node of the subtree.
 * @return pointer to the node containing the largest data item
 *         or nullptr if the subtree is empty.
 */
BinaryNode *BinarySearchTree::findMax(BinaryNode *ptr) const
{
    if (ptr != nullptr)
    {
        while(ptr->right != nullptr) {ptr = ptr->right;}
    }

    return ptr;
}

/**
 * Public method to empty a subtree.
 */
void BinarySearchTree::clear()
{
    clear(root);
}

/**
 * Private method to empty a subtree.
 * @param ptr pointer to the root node of the subtree.
 */
void BinarySearchTree::clear(BinaryNode* &ptr)
{   probeCount++;
    if (ptr != nullptr)
    {
        clear(ptr->left);
        clear(ptr->right);
        delete ptr;
        ptr = nullptr;
    }
}

/**
 * @return true if and only if the tree is empty.
 */
bool BinarySearchTree::isEmpty() const
{
    return root == nullptr;
}

/**
 * Public method to search for a data item in the tree.
 * @param data the data to search for.
 * @return true if and only if data is in the tree.
 */

bool BinarySearchTree::contains(const int data) 
{
    auto start = chrono::steady_clock::now();
    bool res= contains(data, root);
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    elapsedTime+=chrono::duration <double, micro> (diff).count();
    return res;
}

/**
 * Private method to search for a data item in a subtree.
 * @param data the data to search for.
 * @param ptr pointer to the root node of the subtree.
 * @return true if and only if data is in the tree.
 */
bool BinarySearchTree::contains(const int data, BinaryNode *ptr) 
{ 
    while (ptr != nullptr)
    {
        probeCount++;
        if (data < ptr->data)
        {
            compareCount++;
            ptr = ptr->left;
        }
        else if (data > ptr->data)
        {
            compareCount++;
            ptr = ptr->right;
        }
        else
        {
            compareCount++;
            return true;  // found
        }
    }

    return false;         // not found
}

/**
 * Public method to insert a data item into a subtree
 * and set the new root of the subtree.
 * @param data the data to insert into the tree.
 */

void BinarySearchTree::insert(const int data)
{
    auto start = chrono::steady_clock::now();
    insert(data, root);
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    elapsedTime+=chrono::duration <double, micro> (diff).count();
}

/**
 * Protected method to insert a data item into a subtree
 * and set the new root of the subtree.
 * @param data the data to insert.
 * @param ptr pointer to the root node of the subtree.
 */
void BinarySearchTree::insert(const int data, BinaryNode* &ptr)
{   probeCount++;
    if (ptr == nullptr)
    {
        ptr = new BinaryNode(data);
    }
    else if (data < ptr->data)
    {
        compareCount++;
        insert(data, ptr->left);
    }
    else if (data > ptr->data)
    {
        compareCount++;
        insert(data, ptr->right);
    }
    else{
        compareCount++;
        cout<<"";
    }
}

/**
 * Public method to remove a data item from a subtree
 * and set the new root of the subtree.
 * Do nothing if the data item is not found.
 * @param data the data to remove.
 */
void BinarySearchTree::remove(const int data)
{
    remove(data, root);
}

/**
 * Protected method to remove a data item from a subtree
 * and set the new root of the subtree.
 * Do nothing if the data item is not found.
 * @param data the data to remove.
 * @param ptr pointer to the root node of the subtree.
 */
void BinarySearchTree::remove(const int data, BinaryNode* &ptr)
{
    probeCount++;
    if (ptr == nullptr) return;   // not found, so do nothing

    // First search for the target node to remove.
    if (data < ptr->data)
    {
        compareCount++;
        remove(data, ptr->left);
    }
    else if (data > ptr->data)
    {
        compareCount++;
        remove(data, ptr->right);
    }

    // Remove a target node with two children.
    else if (   (ptr->left  != nullptr)
             && (ptr->right != nullptr))
    {
        compareCount++;
        // Replace the target node's data with the successor node's data.
        ptr->data = findMin(ptr->right)->data;

        // Search for and remove the successor node.
        remove(ptr->data, ptr->right);
    }

    // Remove a target node with one or no children.
    else
    {
        BinaryNode *oldNode = ptr;
        probeCount++;
        ptr = (ptr->left != nullptr) ? ptr->left
                                     : ptr->right;
        delete oldNode;
    }
}