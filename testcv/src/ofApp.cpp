#include "ofApp.h"



//--------------- private member method area ---------------------------------------


void ofApp::checkCamera()
{
    vector<ofVideoDevice> devices = camera->listDevices();
    
    for(size_t i = 0; i < devices.size(); i++)
    {
        if(devices[i].bAvailable)
        {
            //log the device
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
        }
        else
        {
            //log the device and note it as unavailable
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
        }
    }
    
    camera->setDeviceID(1);
    camera->setDesiredFrameRate(30);
    camera->initGrabber(1280,960);
}

void ofApp::testCanny()
{
    fileImage->load("1.jpeg");
    
    image->setFromPixels(fileImage->getPixels());
    
    grayImage->allocate(image->width, image->height);
    cannyImage->allocate(image->width, image->height);
    
    *grayImage = *image;
    
    grayImage->blurGaussian();
    
    cvCanny(grayImage->getCvImage() , cannyImage->getCvImage(), 75, 200);
}

//--------------------------------------------------------------
void ofApp::setup()
{
    
    ofSetWindowShape(1280, 960);
    
    image       = new ofxCvColorImage();
    grayImage   = new ofxCvGrayscaleImage();
    cannyImage  = new ofxCvGrayscaleImage();
    fileImage   = new ofImage();
    screenImage = new ofImage();
    camera      = new ofVideoGrabber();
    
    checkCamera();
    
    //testCanny();
}

//--------------------------------------------------------------
void ofApp::update()
{
    camera->update();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    //image->draw(0,0);
    
    //cannyImage->draw(0,0);
    
    camera->draw(0, 0);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{

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
void ofApp::mousePressed(int x, int y, int button)
{
    ofSaveImage(camera->getPixels() , "test.jpg");
    
    ofLogNotice() << "screen saved";
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
