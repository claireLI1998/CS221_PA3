

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
	stats data = stats(imIn);
	height = imIn.height();
	width = imIn.width();
	pair<int, int> ul, lr;
	ul = make_pair(0,0);
	lr = make_pair(width - 1, height - 1);
	root = buildTree(data, ul, lr);
}

KDTree::Node * KDTree::buildTree(stats & s, pair<int,int> ul, pair<int,int> lr) {

/* YOUR CODE HERE */

	Node *curr = new Node(ul, lr, s.getAvg(ul, lr));
	bool horizontal = true;
    int ulx = ul.first;
    int uly = ul.second;
    int lrx = lr.first;
    int lry = lr.second;
    double area = s.rectArea(ul,lr);
    double min = 100;

    for(int i = ulx; i < lrx; i ++){
    	pair<int, int> newlr = pair<int, int>(i, lry);
    	pair<int, int> newul = pair<int, int>(i + 1, uly);
    	pair<int, int> newLR, newUL;

    	double ulentro = s.entropy(ul, newlr);
    	double lrentro = s.entropy(newul, lr);
    	double ularea = s.rectArea(ul, newlr);
    	double lrarea = s.rectArea(newul, lr);
    	double entro = (ularea * ulentro)/area + (lrarea * lrentro)/area;
    	if(entro <= min){
    		min = entro;
    		newLR = make_pair(i, lry);
    		newUL = make_pair(i + 1, uly);
    	}
    }

    for(int j = uly; j < lry; j ++){
    	pair<int, int> newlr = pair<int, int>(lrx, j);
    	pair<int, int> newul = pair<int, int>(ulx, j + 1);
    	pair<int, int> newLR, newUL;

    	double ulentro = s.entropy(ul, newlr);
    	double lrentro = s.entropy(newul, lr);
    	double ularea = s.rectArea(ul, newlr);
    	double lrarea = s.rectArea(newul, lr);
    	double entro = (ularea * ulentro)/area + (lrarea * lrentro)/area;
    	if(entro <= min){
    		min = entro;
    		newLR = make_pair(lrx, j);
    		newUL = make_pair(ulx, j + 1);
    	}
    }
}

PNG KDTree::render(){

/* YOUR CODE HERE */
	PNG p = new PNG(width, height);
	renderHelper(p, root);
	return p;
}

void KDTree::renderHelper(PNG p, Node *curr){
	if(curr->left == NULL && curr->right == NULL){
		for(int i = curr->upLeft.first; i < curr->lowRight.first; i ++){
			for(int j = curr->upLeft.second; j < curr->lowRight.second; j ++){
				HSLAPixel *pixel = p.getPixel(i, j);
				*pixel = curr->avg;
			}
		}
		return;
	}
	else{
		renderHelper(p, curr->left);
		renderHelper(p, curr);
		renderHelper(p, curr->right);
	}
}

void KDTree::prune(double pct, double tol){

/* YOUR CODE HERE */

}

void KDTree::clear() {

/* YOUR CODE HERE */
	clearNode(root);
}

void KDTree::clearNode(Node *curr){
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

}

