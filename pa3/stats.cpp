
#include "stats.h"

stats::stats(PNG & im){

/* YOUR CODE HERE */

}

long stats::rectArea(pair<int,int> ul, pair<int,int> lr){

/* YOUR CODE HERE */

}

HSLAPixel stats::getAvg(pair<int,int> ul, pair<int,int> lr){

/* YOUR CODE HERE */

}

vector<int> stats::buildHist(pair<int,int> ul, pair<int,int> lr){

/* YOUR CODE HERE */

}

// takes a distribution and returns entropy
double stats::entropy(vector<int> & distn,int area){

    double entropy = 0;
    for (int i = 0; i < 36; i++) {
        if (distn[i] > 0 ) 
            entropy += ((double) distn[i]/(double) area) 
                                    * log2((double) distn[i]/(double) area);
    }
    return  -1 * entropy;

}

double stats::entropy(pair<int,int> ul, pair<int,int> lr){

    vector<int> distn =  buildHist(ul,lr);
    int area = rectArea(ul,lr);
    return  entropy(distn,area);

}
