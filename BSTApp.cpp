#include <iostream>
#include <vector>
#include <time.h>

#include "BinarySearchTree.h"
#include "AvlTree.h"
#include "BinaryTreeChecker.h"
#include "BinaryTreePrinter.h"

using namespace std;

const bool DUMP = false;

void testBST(long n);
void testAVL(long n);

void buildAndSearchTree(BinarySearchTree& tree,
               BinaryTreeChecker& checker,
               BinaryTreePrinter& printer,
               string kind,long size);
void buildAndSearchTree(BinarySearchTree& treebst, BinarySearchTree& treeavl, long size);

void dismantleTree(BinarySearchTree& tree,
                   BinaryTreeChecker& checker,
                   BinaryTreePrinter& printer);

/**
 * Main.
 */
static const long VALUES[] = {
   5000,10000,15000,20000,25000,30000,35000,40000,45000,50000
};

int main( )
{
    BinarySearchTree bst;
    bst.reset();
    //BinaryTreeChecker checkerbst(bst);
    //BinaryTreePrinter printerbst(bst); 
    AvlTree avl;
    avl.reset();
    //BinaryTreeChecker checkeravl(avl);
    //BinaryTreePrinter printeravl(avl);
    
    for (long n: VALUES){
        n=n*2;
        cout<<endl<<endl<<"n= "<<n<<endl;
        cout<<right<<setw(30)<<"PROBE COUNT"<<right<<setw(30)<<"COMPARE COUNT"<<right<<setw(33)<<"ELAPSED TIME"<<endl;
        buildAndSearchTree(bst, avl, n);
    }
    
    //testBST();
    //testAVL();
}

/**
 * Run the test with a binary search tree.
 */
void testBST()
{
    cout << endl;
    cout << "* BINARY SEARCH TREE *" << endl;
    
    BinarySearchTree  tree;
    BinaryTreeChecker checker(tree);
    BinaryTreePrinter printer(tree); 
 

    //buildTree(tree, checker, printer, "BST");
   // dismantleTree(tree, checker, printer);
}

/**
 * Run the test with an AVL tree.
 */
void testAVL()
{
    cout << endl;
    cout << "************" << endl;
    cout << "* AVL TREE *" << endl;
    cout << "************" << endl;

    AvlTree tree;
    BinaryTreeChecker checker(tree);
    BinaryTreePrinter printer(tree);

    //buildTree(tree, checker, printer, "AVL");
    //dismantleTree(tree, checker, printer);
}


/**
 * Build a binary search tree containing unique random integer data items.
 * @param tree the tree to make.
 * @param maxNodes the maximum number of nodes to generate.
 * @param checker the binary tree checker to use.
 * @param printer the binary tree printer to use.
 * @param insertPrint true iff print a message after each node insertion
 */
void buildAndSearchTree(BinarySearchTree& tree,
              BinaryTreeChecker& checker,
              BinaryTreePrinter& printer,
              string kind,long size)
{
    //insert
    for (long i =1;i<=size;i++)
    {
        tree.insert(i);  // insert into tree
        checker.add(i);  // store with the tree checker
    }
    if(kind=="BST")
       cout<<"BST insert"<<right<<setw(10)<<tree.probeCount<<right<<setw(30)<<tree.compareCount<<right<<setw(30)<<tree.elapsedTime<<" us"<<endl;
    else
       cout<<"AVL insert"<<right<<setw(10)<<tree.probeCount<<right<<setw(30)<<tree.compareCount<<right<<setw(30)<<tree.elapsedTime<<" us"<<endl; 
    tree.reset();
    
    //search
    for (long i=1;i<=size;i++){
       tree.contains(i);  
    }
    if(kind=="BST")
       cout<<"BST search"<<right<<setw(10)<<tree.probeCount<<right<<setw(30)<<tree.compareCount<<right<<setw(30)<<tree.elapsedTime<<" us"<<endl;
    else
       cout<<"AVL search"<<right<<setw(10)<<tree.probeCount<<right<<setw(30)<<tree.compareCount<<right<<setw(30)<<tree.elapsedTime<<" us"<<endl; 
    tree.reset();
}

void buildAndSearchTree(BinarySearchTree& treebst, BinarySearchTree& treeavl, long size){
    srand(time(0));
    for (long i =1;i<=size;i++)
    {
        
        long k = (rand()%100000000)+1;
        treebst.insert(k);  // insert into tree
        treeavl.insert(k);  // store with the tree checker
    }
  
       cout<<"BST insert"<<right<<setw(20)<<treebst.probeCount<<right<<setw(30)<<treebst.compareCount<<right<<setw(30)<<treebst.elapsedTime/1000<<" ms"<<endl;
   
       cout<<"AVL insert"<<right<<setw(20)<<treeavl.probeCount<<right<<setw(30)<<treeavl.compareCount<<right<<setw(30)<<treeavl.elapsedTime/1000<<" ms"<<endl; 
       treebst.reset();
       treeavl.reset();
       //BinaryTreePrinter printer(treebst);
       //printer.print();
    
    //search
    for (long i=1;i<=size;i++){
      
       long k = (rand()%100000000)+1;
       treebst.contains(k); 
       treeavl.contains(k);
    }
  
       cout<<"BST search"<<right<<setw(20)<<treebst.probeCount<<right<<setw(30)<<treebst.compareCount<<right<<setw(30)<<treebst.elapsedTime/1000<<" ms"<<endl;
       cout<<"AVL search"<<right<<setw(20)<<treeavl.probeCount<<right<<setw(30)<<treeavl.compareCount<<right<<setw(30)<<treeavl.elapsedTime/1000<<" ms"<<endl; 
       treebst.reset();
       treeavl.reset();
       
       treebst.clear();
       treeavl.clear();
}

/**
 * Dismantle a binary tree.
 * @param tree the tree to test.
 * @param checker the binary tree checker to use.
 * @param printer the binary tree printer to use.
 */
void dismantleTree(BinarySearchTree& tree,
                   BinaryTreeChecker& checker,
                   BinaryTreePrinter& printer)
{
    int status = BinaryTreeChecker::NO_ERROR;

    // Delete the root node each time through the loop.
    // Print the tree after each deletion.
    while (!tree.isEmpty())
    {
        BinaryNode *root = tree.getRoot();
        int data = root->data;
        cout << endl << "Deleted root node " << data << ":" << endl;

        tree.remove(data);
        checker.remove(data);

        cout << endl;
        printer.print();

        status = checker.check(DUMP);
        if (status != BinaryTreeChecker::NO_ERROR) break;
    }

    // What was the status?
    string msg;
    switch (status)
    {
        case BinaryTreeChecker::NO_ERROR:
        {
            msg = ">>>>> The tree is now empty.";
            break;
        }
        case BinaryTreeChecker::DATA_MISMATCH:
        {
            msg =  ">>>>> Data mismatch.";
            break;
        }
        case BinaryTreeChecker::INSUFFICIENT_DATA:
        {
            msg =  ">>>>> Data missing from tree.";
            break;
        }
        case BinaryTreeChecker::REMAINING_DATA:
        {
            msg =  ">>>>> Data remaining in tree.";
            break;
        }
    }
    cout << msg << endl;
}
