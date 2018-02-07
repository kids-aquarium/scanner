#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "imgproc_c.h"

class ofApp : public ofBaseApp
{
    private:
    
    ofxCvColorImage *image;
    ofxCvColorImage *warpImage;
    ofxCvGrayscaleImage *grayImage;
    ofxCvGrayscaleImage *cannyImage;
    ofImage *fileImage;
    ofImage *screenImage;
    ofxCvContourFinder *contourFinder;
    
    ofVec2f points[4];
    
    int posIndex;
    
    
    //------------- private member method area ----------------------
    
    void testCanny();
    void findContour();
    void doPerspectiveTransformation();


	public:
    
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
		
};
