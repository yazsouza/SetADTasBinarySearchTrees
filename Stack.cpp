#include "BSTSet.h"
#include <iostream>
#include <vector>
using namespace std;

BSTSet::BSTSet()
{
	root = NULL; //empty tree
}

BSTSet::BSTSet(const std::vector<int>& input)
{
	if (input.size() == 0) return; //if input vector empty, return

	for (int i = 0; i < input.size(); i++) { //else add each element of vector to tree
		add(input[i]);
	}
}

BSTSet::~BSTSet()
{
	deletef(root);
}

void BSTSet::deletef(TNode* t)
{
    if (t == NULL) return; //if set empty return
    else {
        deletef(t->left); 
        deletef(t->right);
        free(t); //frees memory allocated for t
    }
}

bool BSTSet::isInRec(TNode* t, int v) const {

    if (t == NULL) //if set empty return false
        return false;
    
    else {
        if (v < t->element)  //if v is less than element, search left
            return isInRec(t->left, v);
        else if (v > t->element)
            return isInRec(t->right, v); //if v is greater, search right
        else
            return true;
    }
}

bool BSTSet::isIn(int v)
{
    return isInRec(root, v);
}

void BSTSet::addRec(TNode* t, int v) {

    if (root == NULL)  //empty set, add node
        root = new TNode(v, NULL, NULL);
    
    else if (isIn(v) == false) { //check to make sure node isnt in set alr

        if (v < t->element && t->left == NULL) //if smaller than t and t is leftmost node, add to left of t
            t->left = new TNode(v, NULL, NULL);

        else if (v > t->element && t->right == NULL) //if larger than t and t is rightmost node, add to right of t
            t->right = new TNode(v, NULL, NULL);

        else {
            if (v < t->element) //if v is less than t but t is not leftmost, iterate left
                addRec(t->left, v);

            else
                return addRec(t->right, v); // if v is larger than t but t is not rightmost, iterate left
        
        }
    }
}

void BSTSet::add(int v)
{
    addRec(root, v);
}

void BSTSet::removeRec(TNode*& root, int v) {
    if (root == NULL) 
        return;
    
    if (v < root->element)   // if v is to the left
        removeRec(root->left, v);
    
    else if (v > root->element)  // if v is to the right
        removeRec(root->right, v);
    
    else {
        
        if (root->left == NULL && root->right == NULL) { //if there are no children
            delete(root); // delete
            root = NULL;
        }
        
        else if (root->left == NULL) { //if child on right
            struct TNode* temp = root; // save currnt node
            root = root->right;
            delete temp; //delete temp
        }
      
        else if (root->right == NULL) { //if child on the left
            struct TNode* temp = root; // save current node
            root = root->left;
            delete temp;
        }
       
        else { //children on both sides
            struct TNode* temp = findTreeMin(root->right); // find min value of subtree
            root->element = temp->element; // duplicate node
            removeRec(root->right, temp->element); // delete duplicated node
        }
    }

}


bool BSTSet::remove(int v)
{
    
    bool node = isIn(v); //check if node in tree

    if (node) {
        removeRec(root, v); //if so remove
    }

    return node; //returns true if deleted, false if not 

}


TNode* BSTSet::findTreeMin(TNode* t) { 

    if (t == NULL) //return null for null lement
        return NULL;

    while (t->left != NULL) { //find leftmost element to return
        t = t->left;
    }
    
    return t; 
}

void BSTSet::UnionRec(TNode* s) {
    if (s != NULL) { 
        add(s->element); //add each non-repeating element to this BTSet
        UnionRec(s->left); //call function again for left elements
        UnionRec(s->right); //call again for right elements
    }
}

void BSTSet::Union(const BSTSet& s)
{
    UnionRec(s.root);
}

void BSTSet::intersecionRec(TNode*& t, TNode*& s) {

    if (t != NULL) {

        if (isInRec(s, t->element) == false) { //if t element not in s

            removeRec(t, t->element); //remove element t from t
            intersecionRec(t, s);  //call again
        }

        else {
            intersecionRec(t->left, s);
            intersecionRec(t->right, s);
        }
    }
}

void BSTSet::intersection(const BSTSet& s)
{
    TNode* input = s.root;
    intersecionRec(root, input);
}

void BSTSet::diffRec(TNode* s) {
    if (s != NULL) { //if s is not empty
        diffRec(s->left);
        diffRec(s->right); 
       if (isIn(s->element)) //remove element s from set
            remove(s->element); 
    }
}

void BSTSet::difference(const BSTSet& s)
{
    diffRec(s.root);
}

int BSTSet::sizeRec(TNode* t) {
    if (t == NULL) 
        return 0;
    
    else 
        return(sizeRec(t->left) + sizeRec(t->right) + 1);//every node traversed adds one
    
}


int BSTSet::size(){
    return sizeRec(root); //change this after completing this function
}

int BSTSet::heightRec(TNode* t) {
    if (t == NULL) 
        return -1; //-1 for empty set
    
    else {
        int rHeight = heightRec(t->right); //find depth of each subtree
        int lHeight = heightRec(t->left);
        if (rHeight > lHeight) {
            return rHeight + 1; //use larger one
        }
        else {
            return lHeight + 1;
        }
    }
}

int BSTSet::height()
{
	return heightRec(root); 
}

// create and use class MyStack
void BSTSet::printNonRec()
{
	// TODO
	cout << "-2"; //change this after completing this function
}


// Do not modify following provided methods

void BSTSet::printBSTSet()
{
    if (root == NULL)
        std::cout << "";
    else {
        printBSTSet(root);
    }
}

void BSTSet::printBSTSet(TNode* t)
{
    if (t != NULL) {
        printBSTSet(t->left);
        std::cout << t->element << ",";
        printBSTSet(t->right);
    }
}
