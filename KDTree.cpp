

/**
 *
 * KDTree (pa3)
 * slight modification of a Kd tree of dimension 2.
 * KDTree.cpp
 * This file will be used for grading.
 *
 */

#include "KDTree.h"

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
stats data = stats(inIn);
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
	
double temp = 0;
pair<int, int> min;


for(int i = ul.first; i < lr.first; i++) {
	long area1 = s.rectArea(ul, pair<int,int>(i,lr.second));
	long area2 = s.rectArea(pair<int,int>(i + 1,ul.second), lr);
//	s.buildHist(ul, pair<int,int>(i,lr.second));
	double temp1 = s.entropy(s.buildHist(ul, pair<int,int>(i,lr.second)), aera1);
	double temp2 = s.entropy(s.buildHist(pair<int,int>(i + 1,ul.second), lr), aera2);
//	s.buildHist(pair<int,int>(i,0), lr);
    double tempfinal = (double) (temp1 * aera1 + temp2 * aera2) / (aera1 + aera2);
	if(tempfinal > temp) {
		temp = tempfinal;
		min = make_pair(i,lr.second);
	}	
}

for(int j = ul.second; j < lr.second; j++) {
	long area1 = s.rectArea(ul, pair<int,int>(lr.first,j));
	long area2 = s.rectArea(pair<int,int>(ul.first,j+1), lr);
//	s.buildHist(ul, pair<int,int>(i,lr.second));
	double temp1 = s.entropy(s.buildHist(ul, pair<int,int>(lr.first,j)), aera1);
	double temp2 = s.entropy(s.buildHist(pair<int,int>(ul.first,j+1), lr), aera2);
//	s.buildHist(pair<int,int>(i,0), lr);
    double tempfinal = (double) (temp1 * aera1 + temp2 * aera2) / (aera1 + aera2);
	if(tempfinal > temp) {
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

}

void KDTree::prune(double pct, double tol){

/* YOUR CODE HERE */

}

void KDTree::clear() {

/* YOUR CODE HERE */

}

void KDTree::copy(const KDTree & orig){

/* YOUR CODE HERE */

}

