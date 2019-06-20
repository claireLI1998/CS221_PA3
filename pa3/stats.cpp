
#include "stats.h"

stats::stats(PNG & im){

/* YOUR CODE HERE */
    for(int i = 0; i < im.width(); i++){
    for(int j =0; j < im.height(); j++) {
        if(i > 0 && j > 0) {
            sumSat[i][j] = im.getPixel(i,j) -> s + sumSat[i-1][j] + sumSat[i][j-1] - sumSat[i-1][j-1];
        } else if (i > 0) {
            sumSat[i][j] = im.getPixel(i,j) -> s + sumSat[i-1][j];
        } else if (j > 0) {
            sumSat[i][j] = im.getPixel(i,j) -> s + sumSat[i][j-1];
        } else {
            sumSat[i][j] = im.getPixel(i,j) -> s;
        }
//      sumSat[i][j] = im.getPixel(i,j) -> s;
    }
}

for(int i = 0; i < im.width(); i++){
    for(int j =0; j < im.height(); j++) {
        if(i > 0 && j > 0) {
            sumLum[i][j] = im.getPixel(i,j) -> l + sumLum[i-1][j] + sumLum[i][j-1] - sumLum[i-1][j-1];
        } else if (i > 0) {
            sumLum[i][j] = im.getPixel(i,j) -> l + sumLum[i-1][j];
        } else if (j > 0) {
            sumLum[i][j] = im.getPixel(i,j) -> l + sumLum[i][j-1];
        } else {
            sumLum[i][j] = im.getPixel(i,j) -> l;
        }
    }
}

for(int i = 0; i < im.width(); i++){
    for(int j =0; j < im.height(); j++) {
        if(i > 0 && j > 0) {
            sumHueX[i][j] = cos(im.getPixel(i,j) -> h) 
             + sumHueX[i-1][j] + sumHueX[i][j-1] - sumHueX[i-1][j-1];
        } else if (i > 0) {
            sumHueX[i][j] = cos(im.getPixel(i,j) -> h)
             + sumHueX[i-1][j];
        } else if (j > 0) {
            sumHueX[i][j] = cos(im.getPixel(i,j) -> h)
             + sumHueX[i][j-1];
        } else {
            sumHueX[i][j] = cos(im.getPixel(i,j) -> h);
        }
//      sumHueX[i][j] = cos(im.getPixel(i,j) -> h) * sumSat[i][j];
    }
}

for(int i = 0; i < im.width(); i++){
    for(int j =0; j < im.height(); j++) {
        if(i > 0 && j > 0) {
            sumHueY[i][j] = sin(im.getPixel(i,j) -> h )
             + sumHueY[i-1][j] + sumHueY[i][j-1] - sumHueY[i-1][j-1];
        } else if (i > 0) {
            sumHueY[i][j] = sin(im.getPixel(i,j) -> h)
             + sumHueY[i-1][j];
        } else if (j > 0) {
            sumHueY[i][j] = sin(im.getPixel(i,j) -> h)
             + sumHueY[i][j-1];
        } else {
            sumHueY[i][j] = sin(im.getPixel(i,j) -> h);
        }
    }
}


for(int i = 0; i < im.width(); i++){
    for(int j =0; j < im.height(); j++) {
        int temp = helper1(im.getPixel(i,j) -> h);
        for(int k = 0; k < 36; k++) {
        
        if(i > 0 && j > 0) {
            if(temp == k) {
            
            hist[i][j][k] = hist[i-1][j][k] + hist[i][j-1][k] - hist[i-1][j-1][k] + 1;
            } else {
            hist[i][j][k] = hist[i-1][j][k] + hist[i][j-1][k] - hist[i-1][j-1][k];  
            }
        } else if (i > 0) {
            if(temp == k) {
            hist[i][j][k] = hist[i-1][j][k] + 1;
            } else {
            hist[i][j][k] = hist[i-1][j][k];    
            }
        } else if (j > 0) {
            if(temp == k) {
            hist[i][j][k] = hist[i][j-1][k] + 1;
            } else {
            hist[i][j][k] = hist[i][j-1][k];    
            }
        } else {
            if(temp == k) {
            hist[i][j][k] = 1;
            } else {
            hist[i][j][k] = 0;  
            }
        }
    }
    }
    }
}

int stats::helper1(double hue) {
    for(int i = 0; i < 36; i++) {
        if(i*10 <= hue && hue < (i+1)*10)
        return i;
    }
}


long stats::rectArea(pair<int,int> ul, pair<int,int> lr){

/* YOUR CODE HERE */
    cout<< (lr.first - ul.first + 1) * (lr.second - ul.second + 1)<< endl;
    return (lr.first - ul.first + 1) * (lr.second - ul.second + 1);
    
}


HSLAPixel stats::getAvg(pair<int,int> ul, pair<int,int> lr){
/* YOUR CODE HERE */
    
    HSLAPixel pixel;
    //total number of pixels
    long sum = rectArea(ul, lr);
    double avgHue, avgSat, avgLum;
    int ulx = ul.first;
    int uly = ul.second;
    int lrx = lr.first;
    int lry = lr.second;

    if(ulx == 0 && uly == 0){
        avgSat = sumSat[lrx][lry]/sum;
        avgLum = sumLum[lrx][lry]/sum;
        avgHue = atan2(sumHueY[lrx][lry], sumHueX[lrx][lry])*180/PI;
    }else if(ulx == 0){
        avgSat = (sumSat[lrx][lry] - sumSat[lrx][uly - 1])/sum;
        avgLum = (sumLum[lrx][lry] - sumLum[lrx][uly - 1])/sum;
        avgHue = atan2(sumHueY[lrx][lry] - sumHueY[lrx][uly - 1], sumHueX[lrx][lry] - sumHueX[lrx][uly - 1])*180/PI;

    }else if(uly == 0){
        avgSat = (sumSat[lrx][lry] - sumSat[ulx - 1][lry])/sum;
        avgLum = (sumLum[lrx][lry] - sumLum[ulx - 1][lry])/sum;
        avgHue = atan2(sumHueY[lrx][lry] - sumHueY[ulx - 1][lry], sumHueX[lrx][lry] - sumHueX[ulx - 1][lry])*180/PI;
    }else{
        avgSat = (sumSat[lrx][lry] - sumSat[lrx][uly - 1] - sumSat[ulx - 1][lry] + sumSat[ulx - 1][uly - 1])/sum;
        avgLum = (sumLum[lrx][lry] - sumLum[lrx][uly - 1] - sumLum[ulx - 1][lry] + sumLum[ulx - 1][uly - 1])/sum;
        avgHue = atan2(sumHueY[lrx][lry] - sumHueY[lrx][uly - 1] - sumHueY[ulx - 1][lry] + sumHueY[ulx - 1][uly - 1],
                       sumHueX[lrx][lry] - sumHueX[lrx][uly - 1] - sumHueX[ulx - 1][lry] + sumHueX[ulx - 1][uly - 1])*180/PI;

    }

    return pixel = HSLAPixel(avgHue, avgSat, avgLum);
}

vector<int> stats::buildHist(pair<int,int> ul, pair<int,int> lr){

/* YOUR CODE HERE */
    vector<int> arr;
for(int k=0; k < 36; k++) {
    if(ul.first > 0 && ul.second > 0) {
        int temp = hist[lr.first][lr.second][k] - hist[ul.first - 1][lr.second][k]
     - hist[ul.first][lr.second - 1][k] + hist[ul.first - 1][lr.second - 1][k];
        arr.push_back(temp);
    } else if (ul.first > 0) {
        int temp = hist[lr.first][lr.second][k] - hist[ul.first - 1][lr.second][k];
        arr.push_back(temp);
    } else if (ul.second > 0) {
        int temp = hist[lr.first][lr.second][k] - hist[ul.first][lr.second - 1][k];
        arr.push_back(temp);
    } else {
        int temp = hist[lr.first][lr.second][k];
        arr.push_back(temp);
    }
    
}
    
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
