

/**
 *
 * KDTree (pa3)
 * slight modification of a Kd tree of dimension 2.
 * KDTree.cpp
 * This file will be used for grading.
 *
 */

#include "KDTree.h"
using std::pair;
KDTree::Node::Node(pair<int,int> ul, pair<int,int> lr, HSLAPixel a)
	:upLeft(ul),lowRight(lr),avg(a),left(NULL),right(NULL)
	{}

KDTree::~KDTree(){
	clear();
}

KDTree::KDTree(const KDTree & other) {
	copy(other);
}


KDTree & KDTree::operator=(const KDTree & rhs){
	if (this != &rhs) {
		clear();
		copy(rhs);
	}
	return *this;
}

KDTree::KDTree(PNG & imIn){ 

/* YOUR CODE HERE */
stats data = stats(imIn);
height = imIn.height();
width = imIn.width();
pair<int,int> ul, lr;
ul = make_pair(0,0);
lr = make_pair(width - 1, height -1);
root = buildTree(data,ul,lr);

}

KDTree::Node * KDTree::buildTree(stats & s, pair<int,int> ul, pair<int,int> lr) {

/* YOUR CODE HERE */
Node *root = new Node(ul, lr, s.getAvg(ul,lr));
if(ul.first != lr.first || ul.second != lr.second){
	
double temp = 9999999;
pair<int, int> min;


for(int i = ul.first; i < lr.first; i++) {
	long area1 = s.rectArea(ul, pair<int,int>(i,lr.second));
	long area2 = s.rectArea(pair<int,int>(i + 1,ul.second), lr);
//	s.buildHist(ul, pair<int,int>(i,lr.second));
	double temp1 = s.entropy(ul, pair<int,int>(i,lr.second));
	double temp2 = s.entropy(pair<int,int>(i + 1,ul.second), lr);
//	s.buildHist(pair<int,int>(i,0), lr);
    double tempfinal = (double) (temp1 * area1 + temp2 * area2) / (area1 + area2);
	if(tempfinal < temp) {
		temp = tempfinal;
		min = make_pair(i,lr.second);
	}	
}

for(int j = ul.second; j < lr.second; j++) {
	long area1 = s.rectArea(ul, pair<int,int>(lr.first,j));
	long area2 = s.rectArea(pair<int,int>(ul.first,j+1), lr);
//	s.buildHist(ul, pair<int,int>(i,lr.second));
	double temp1 = s.entropy(ul, pair<int,int>(lr.first,j));
	double temp2 = s.entropy(pair<int,int>(ul.first,j+1), lr);
//	s.buildHist(pair<int,int>(i,0), lr);
    double tempfinal = (double) (temp1 * area1 + temp2 * area2) / (area1 + area2);
	if(tempfinal < temp) {
		temp = tempfinal;
		min = make_pair(lr.first,j);
	}		
}

//root = new Node(ul, lr, )
if(min.second == lr.second) {
	root -> left  = buildTree(s, ul, min);
	root -> right = buildTree(s, pair<int,int>(min.first + 1,ul.second) , lr);
} else {
	root -> left  =  buildTree(s, ul, min);
	root -> right = buildTree(s, pair<int,int>(ul.first,min.second + 1), lr);
}

return root;
} else {
	root -> left = NULL;
	root -> right = NULL;
	return root;
}

}

PNG KDTree::render(){

/* YOUR CODE HERE */
	PNG *p = new PNG(width, height);
	renderHelper(*p, root);
	return *p;

}

void KDTree::renderHelper(PNG & p, Node * & curr){
	if(curr->left == NULL && curr->right == NULL){
		int i = curr->upLeft.first;
		int j = curr->upLeft.second;
		*p.getPixel(i, j) = curr->avg;
		return;
	}
	renderHelper(p, curr->left);
	renderHelper(p, curr->right);
}


void KDTree::prune(double pct, double tol){

/* YOUR CODE HERE */
pair<int,int> p = prunehelper(tol, root, root -> avg);
if(p.second == 0) return;
double per = (double) (p.first / p.second);

if(per > pct) {
//	root -> left = NULL;
//	root -> right = NULL;
    clearNode(root -> left);
    clearNode(root -> right);
    	root -> left = NULL;
    	root -> right = NULL;
}
}

pair<int,int> KDTree::prunehelper(double tol, Node* & root, HSLAPixel avg) {
	if(root != NULL) {
		
	pair<int,int> ul = make_pair(0,0);
	if(root -> left == NULL && root -> right == NULL) {
		ul.second++;
		if(avg.dist(root -> avg) < tol) {
			ul.first++;
		}
	}
	int first = prunehelper(tol, root -> left, avg).first 
	            + prunehelper(tol, root -> right, avg).first
	            + ul.first;
	            
    int second = prunehelper(tol, root -> left, avg).second 
	            + prunehelper(tol, root -> right, avg).second
	            + ul.second;
    return pair<int,int> (first,second);
    } else {
    	return pair<int,int> (0,0);
	}
}

void KDTree::clear() {

/* YOUR CODE HERE */
clearNode(root);

}

void KDTree::clearNode(Node* & curr){
	if(curr == NULL){
		return;
	}else{
		clearNode(curr->left);
		clearNode(curr->right);
		delete curr;
	}
}

void KDTree::copy(const KDTree & orig){

/* YOUR CODE HERE */
//    Node *copyTree = orig.root;
    height = orig.height;
    width = orig.width;
    Node* root1 = orig.root;
    root = copyHelper(root1);

}

KDTree::Node* KDTree::copyHelper(const Node* rt){

/* YOUR CODE HERE */
    if(rt != NULL) {
    Node* temp = new Node(rt -> upLeft, rt -> lowRight, rt -> avg);

    temp->left = copyHelper(rt -> left);
    temp->right = copyHelper(rt -> right);
    return temp;
    } else {
    	return NULL;
	}

}



