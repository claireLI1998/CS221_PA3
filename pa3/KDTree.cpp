

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
pair<int,int> ul, lr;
ul = make_pair(0,0);
lr = make_pair(width - 1, height -1);
root = buildTree(data,ul,lr);



}

KDTree::Node * KDTree::buildTree(stats & s, pair<int,int> ul, pair<int,int> lr) {

/* YOUR CODE HERE */
	Node *root = new Node(ul, lr, s.getAvg(ul,lr));
	int ulx = ul.first;
    int uly = ul.second;
    int lrx = lr.first;
    int lry = lr.second;
    double area = s.rectArea(ul,lr);
    

if(ul.first != lr.first || ul.second != lr.second){
	
double temp = 0;
pair<int, int> min;


for(int i = ulx; i < lrx; i ++){
    	pair<int, int> newlr = pair<int, int>(i, lry);
    	pair<int, int> newul = pair<int, int>(i + 1, uly);
    	pair<int, int> newLR, newUL;

    	double ulentro = s.entropy(ul, newlr);
    	double lrentro = s.entropy(newul, lr);
    	double ularea = s.rectArea(ul, newlr);
    	double lrarea = s.rectArea(newul, lr);
    	double entro = (ularea * ulentro)/area + (lrarea * lrentro)/area;
    	if(entro <= temp){
    		temp = entro;
    		min = make_pair(i, lry);
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
    	if(entro <= temp){
    		temp = entro;
    		min = make_pair(lrx, j);
    		newUL = make_pair(ulx, j + 1);
    	}

// for(int i = ul.first; i < lr.first; i++) {
// 	long area1 = s.rectArea(ul, pair<int,int>(i,lr.second));
// 	long area2 = s.rectArea(pair<int,int>(i + 1,ul.second), lr);
// //	s.buildHist(ul, pair<int,int>(i,lr.second));
// 	double temp1 = s.entropy(s.buildHist(ul, pair<int,int>(i,lr.second)), area1);
// 	double temp2 = s.entropy(s.buildHist(pair<int,int>(i + 1,ul.second), lr), area2);
// //	s.buildHist(pair<int,int>(i,0), lr);
//     double tempfinal = (double) (temp1 * area1 + temp2 * area2) / (area1 + area2);
// 	if(tempfinal > temp) {
// 		temp = tempfinal;
// 		min = make_pair(i,lr.second);
// 	}	
// }

// for(int j = ul.second; j < lr.second; j++) {
// 	long area1 = s.rectArea(ul, pair<int,int>(lr.first,j));
// 	long area2 = s.rectArea(pair<int,int>(ul.first,j+1), lr);
// //	s.buildHist(ul, pair<int,int>(i,lr.second));
// 	double temp1 = s.entropy(s.buildHist(ul, pair<int,int>(lr.first,j)), area1);
// 	double temp2 = s.entropy(s.buildHist(pair<int,int>(ul.first,j+1), lr), area2);
// //	s.buildHist(pair<int,int>(i,0), lr);
//     double tempfinal = (double) (temp1 * area1 + temp2 * area2) / (area1 + area2);
// 	if(tempfinal > temp) {
// 		temp = tempfinal;
// 		min = make_pair(lr.first,j);
// 	}		
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
	renderHelper(root, p);
	return *p;

}

void KDTree::renderHelper(Node *curr, PNG *p){
	if(curr->left == NULL && curr->right == NULL){
		for(int i = curr->upLeft.first; i < curr->lowRight.first; i ++){
			for(int j = curr->upLeft.second; j < curr->lowRight.second; j ++){
				HSLAPixel *pixel = p->getPixel(i, j);
				*pixel = curr->avg;
			}
		}
		return;
	}
	else{
		renderHelper(curr->left, p);
		renderHelper(curr, p);
		renderHelper(curr->right, p);
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
	Node *copyTree = orig.root;
}



