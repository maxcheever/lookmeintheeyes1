#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    Face.load("face.jpg");
    Face.setImageType(OF_IMAGE_GRAYSCALE);
    makeFaceArr();
    
    SampleSrc.load("sample.jpg");
    SampleSrc.setImageType(OF_IMAGE_GRAYSCALE);
    SampleSrc.setUseTexture(false);
    SampleDest.allocate(1024, 768, OF_IMAGE_GRAYSCALE);
    makeNewImage();
    SampleDest.update();
    
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
        faceBrightness[i].brightness = Face.getColor(i).getBrightness();
        
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

bool compare(ofApp::indexBrightness x, ofApp::indexBrightness y) { return x.brightness < y.brightness; };

//--------------------------------------------------------------
void ofApp::makeNewImage(){
    
    /*
     * i am not reusing the sorting from makeFaceArr() because
     * there is not an assumption that can be made about the data
     * (so counting sort is not the best algorithm to use)
     * therefore, i will just use std::sort which is O(nlogn)
     */
    
    int iWidth = SampleSrc.getWidth();
    int iHeight = SampleSrc.getHeight();
    int n = iWidth*iHeight;
    ofPixels src = SampleSrc.getPixels();
    
    
    vector<indexBrightness> sampleBrightness(n);
    
    // populate temp brightness array
    for (int i = 0; i < n; i++) {
        sampleBrightness[i].i = i;
        sampleBrightness[i].brightness = src.getColor(i).getBrightness();
    }
    
    sort(sampleBrightness.begin(), sampleBrightness.end(), compare);
    
    // map pixels to the correct position
    for (int i = 0; i < n; i++) {
        SampleDest.setColor(faceArr[i].i, SampleSrc.getColor(sampleBrightness[i].i));
    }
    
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
