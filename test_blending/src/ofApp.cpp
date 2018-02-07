#include "ofApp.h"



//--------------------- private member method area --------------

void ofApp::runBlending()
{
    int count;
    int alpha;
    unsigned char r,g,b;
    ofColor colorOrgImage;
    ofColor colorAlphaImage;
    ofColor colorNewImage;
    ofPixels pixelOrgImage;
    ofPixels pixelAlphaImage;
    
    alpha = 255;
    
    count = 0;
    
    pixelOrgImage   = orgImage->getPixels();
    pixelAlphaImage = alphaImage->getPixels();
    
    for (int y=0;y<orgImage->getHeight();y++)
    {
        for (int x=0;x<orgImage->getWidth();x++)
        {
            colorOrgImage   = orgImage->getColor(x,y);
            colorAlphaImage = alphaImage->getColor(x,y);
            
            alpha = ofMap(colorAlphaImage.r, 0, 255, 0, 1);
            
            colorNewImage.r = (alpha * colorOrgImage.r);
            colorNewImage.g = (alpha * colorOrgImage.g);
            colorNewImage.b = (alpha * colorOrgImage.b);
            colorNewImage.a = colorAlphaImage.r;
            
            newImage->setColor(x, y, colorNewImage);
            
            newRGBImage->setColor(x,y,colorNewImage);
        }
    }
    
    newImage->update();
    newRGBImage->update();
}

void ofApp::testCanny()
{
    image->setFromPixels(newRGBImage->getPixels());
    
    grayImage->allocate(image->width, image->height);
    cannyImage->allocate(image->width, image->height);
    
    *grayImage = *image;
    
    grayImage->blurGaussian();
    
    cvCanny(grayImage->getCvImage() , cannyImage->getCvImage(), 75, 0);
    
    cannyImage->blurGaussian();
}

void ofApp::findContour()
{
    int count;
    
    count = contourFinder->findContours(*cannyImage, 0, (image->width*image->height) , 4, false,true);
    
    ofLog() << "Found contours = " << count;
    ofLog() << "Blos = " << contourFinder->nBlobs;
    
    for (int i=0;i<contourFinder->blobs.size();i++)
    {
        ofLog() << i << " , " << contourFinder->blobs[i].boundingRect.x  << " , " << contourFinder->blobs[i].boundingRect.y  << " , " << contourFinder->blobs[i].boundingRect.width  << " , " << contourFinder->blobs[i].boundingRect.height  << " , " << contourFinder->blobs[i].boundingRect.getArea();
    }
}


void ofApp::createFinalImage()
{
    ofRectangle tempRect;
    
    tempRect = contourFinder->blobs[0].boundingRect;
    
    newImage->crop(tempRect.x,tempRect.y,tempRect.width,tempRect.height);
}

//---------------------- public member method area --------------

void ofApp::setup()
{
    newImage    = new ofImage();
    newRGBImage = new ofImage();
    orgImage    = new ofImage("fish07.jpeg");
    alphaImage  = new ofImage("fish_alpha.png");
    
    image       = new ofxCvColorImage();
    grayImage   = new ofxCvGrayscaleImage();
    cannyImage  = new ofxCvGrayscaleImage();
    
    contourFinder = new ofxCvContourFinder();
    
    ofLog() << orgImage->getWidth() << "," << orgImage->getHeight();
    
    newImage->allocate(orgImage->getWidth(),orgImage->getHeight(), OF_IMAGE_COLOR_ALPHA);
    newImage->setColor(0);
    
    newRGBImage->allocate(orgImage->getWidth(),orgImage->getHeight(), OF_IMAGE_COLOR);
    newRGBImage->setColor(255);
    
    newRGBImage->update();
    
    newImage->update();
    
    runBlending();
    
    testCanny();
    
    findContour();
    
    createFinalImage();
}

//--------------------------------------------------------------
void ofApp::update()
{
    
}

//--------------------------------------------------------------
void ofApp::draw()
{
    cannyImage->draw(0,0);
    
    newImage->draw(0,0);
    
    contourFinder->draw(0,0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if (key == 's')
    {
        newImage->save("final.png");
        
        ofLog() << "Image saved.";
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
    
}
