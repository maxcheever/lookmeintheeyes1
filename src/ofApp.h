#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup() override;
		void update() override;
		void draw() override;
		void exit() override;
    
    
        	void makeFaceArr();
        	void makeNewImage();

		void windowResized(int w, int h) override;
    
	        struct indexBrightness {
	            int i;
	            float brightness;
	        };
	    
	        ofImage Face;
	        ofImage SampleSrc;
	        ofImage SampleDest;
	        indexBrightness faceArr[786432];
		
};
