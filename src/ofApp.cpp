#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    /*
     * for grayscale mapping, you must remove the multiplication on index "i" on
     * lines 60, 107, and 114. this is due to the fact that pixels are stored
     * differently for grayscale and color images. for grayscale, they are stored like so:
     * [0-255, 0-255, 0-255]
     *  |____| |____| |____|
     *  pixel1 pixel2 pixel3
     * for color, the red, green and blue values all need to be stored for each pixel like so:
     * [0-255, 0-255, 0-255, 0-255, 0-255, 0-255]
     *  |__________________| |__________________|
     *        pixel1                pixel2
     * thus we must use the multiplication to get to the starting index of each color
     */
    
    // loaded jpg are OF_IMAGE_COLOR by default
    Face.load("face4.jpg");
    // Face.setImageType(OF_IMAGE_GRAYSCALE);
    makeFaceArr();
    
    SampleSrc.load("sample3.jpg");
    // Face.setImageType(OF_IMAGE_GRAYSCALE);
    SampleSrc.setUseTexture(false);
    makeNewImage();
    
//    SampleDest.save("face5.jpg");
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);
    ofSetColor(255);
    
    int iWidth = SampleDest.getWidth();
    int iHeight = SampleDest.getHeight();
    SampleDest.draw(0,0, iWidth, iHeight);
    
    
}

bool compare(ofApp::indexBrightness x, ofApp::indexBrightness y) { return x.brightness < y.brightness; };

// creates array of pixels in face sorted by brightness (ascending) while keeping track of original index
void ofApp::makeFaceArr(){
    
    /*
     * this function uses counting sort (https://www.geeksforgeeks.org/counting-sort/)
     * due to the fact that the difference between the number of values being sorted (786432)
     * is much larger than the range of values represented (0-255)
     * essentially, this is nearly O(n) on the array size due to the number of repeated values
     */
    
    int n = Face.getWidth()*Face.getHeight();
    int m = 0;
    
    vector<indexBrightness> faceBrightness(n);
    
    // populate temp brightness array
    for (int i = 0; i < n; i++) {
        faceBrightness[i].i = i;
        faceBrightness[i].brightness = Face.getColor(i*3).getBrightness();
        
        if (faceBrightness[i].brightness > m)
            m = faceBrightness[i].brightness;
    }
    
    vector<int> count(m+1, 0);
    
    // count the occurences of each brightness value
    for (int i = 0; i < n; i++)
        count[faceBrightness[i].brightness]++;
    
    // prefix sum at each index
    for (int i = 1; i <= m; i++)
        count[i] += count[i-1];
    
    // populate final array
    for (int i = n-1; i >= 0; i--) {
        faceArr[count[faceBrightness[i].brightness]-1] = faceBrightness[i];
        count[faceBrightness[i].brightness]--;
    }
    
}

// makes the output image
void ofApp::makeNewImage(){
    
    /*
     * it would make sense to use counting sort again here due to the fact
     * since the range of values is still much smaller than the number of values,
     * but i noticed that using std::sort here creates a distribution of color
     * that is much smoother in the output (std::sort is still efficient at O(nlogn))
     */
    
    int iWidth = SampleSrc.getWidth();
    int iHeight = SampleSrc.getHeight();
    int n = iWidth*iHeight;
    ofPixels src = SampleSrc.getPixels();
    
    
    vector<indexBrightness> sampleBrightness(n);
    
    // populate temp brightness array
    for (int i = 0; i < n; i++) {
        sampleBrightness[i].i = i;
        sampleBrightness[i].brightness = src.getColor(i*3).getBrightness();
    }
    
    sort(sampleBrightness.begin(), sampleBrightness.end(), compare);
    
    SampleDest.allocate(iWidth, iHeight, OF_IMAGE_COLOR);
    
    // map pixels to the correct position
    for (int i = 0; i < n; i++) {
        SampleDest.setColor(faceArr[i].i*3, SampleSrc.getColor(sampleBrightness[i].i*3));
    }
    
    SampleDest.update();
    
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}
