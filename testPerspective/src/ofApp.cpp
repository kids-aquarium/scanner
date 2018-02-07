#include "ofApp.h"

//------------- private member method area ----------------------

void ofApp::testCanny()
{
    image->setFromPixels(fileImage->getPixels());
    
    warpImage->allocate(image->width, image->height);
    grayImage->allocate(image->width, image->height);
    cannyImage->allocate(image->width, image->height);
    
    *grayImage = *image;
    
    grayImage->blurGaussian();
    
    cvCanny(grayImage->getCvImage() , cannyImage->getCvImage(), 80, 0);
    
    cannyImage->blurGaussian();
}

void ofApp::findContour()
{
    int count;
    
    count = contourFinder->findContours(*cannyImage, 0, (1280*960) , 4, false,true);
}

void ofApp::doPerspectiveTransformation()
{
    image->warpPerspective(points[0], points[1], points[2], points[3]);
}


//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetWindowShape(1280, 960);
    
    image         = new ofxCvColorImage();
    warpImage     = new ofxCvColorImage();
    grayImage     = new ofxCvGrayscaleImage();
    cannyImage    = new ofxCvGrayscaleImage();
    contourFinder = new ofxCvContourFinder();
    fileImage     = new ofImage();
    screenImage   = new ofImage();
    
    fileImage->load("forDoc.JPG");
    
    testCanny();
    
    findContour();
    
    for (int i=0;i<4;i++)
    {
        points[i].set(-50,-50);
    }
}

//--------------------------------------------------------------
void ofApp::update()
{
    
}

//--------------------------------------------------------------
void ofApp::draw()
{
    image->draw(0,0);
    
    //cannyImage->draw(0,0);
    
    contourFinder->draw(0,0,1280,960);
    
    for (int i=0;i<4;i++)
    {
        ofDrawCircle(points[i].x, points[i].y, 5);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if (key == 's')
    {
        posIndex = 0;
        
        for (int i=0;i<4;i++)
        {
            points[i].set(-50,-50);
        }
        
        ofLogNotice() << "Select four points";
    }
    
    if (key == ' ')
    {
        doPerspectiveTransformation();
        
        ofSaveImage(image->getPixels() , "test_mask_warpped.jpg");
    }
    
    if (key == 13)
    {
        image->setFromPixels(fileImage->getPixels());
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    ;
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    points[posIndex++].set(x, y);
    
    if (posIndex >= 4)
    {
        posIndex = 3;
    }
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
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
