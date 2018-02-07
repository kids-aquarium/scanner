//
//  JLFish.cpp
//  test_flocking
//
//  Created by jlsy012 on 2018. 1. 29..
//

#include "JLFish.h"
#include <string.h>




//----------- publilc member method area -----------------

JLFish::JLFish(float x , float y , int width , int height)
{
    int fishNo;
    string fishName;
    
    fishNo = ofRandom(2,8);
    
    fishName = "fish0"+std::to_string(fishNo)+".png";
    
    imageFish.load(fishName);
    
    imageFish.resize(ofRandom(80,200), ofRandom(30,120));
    
    myWidth = width;
    myHeight = height;
    
    center.set(imageFish.getWidth()/2 , imageFish.getHeight()/2);
    
    radious = center.x/2;
    maxSpeed = 10;
    maxForce = 0.1;
    
    distNeighbor = 30;
    
    loc.set(x, y);
    acc.set(0,0);
    velocity.set(ofRandom(-1,1), ofRandom(-1,1));
    velocity *= ofRandom(0.1,3);
}

JLFish::~JLFish()
{
    
    
    ;
    
    
}

void JLFish::applyForce(int recvCount)
{
    distSum /= (float)recvCount;
    distSum = distSum.normalize();
    distSum *= maxSpeed;
    
    steer = (distSum - velocity);
    steer.limit(maxForce);
    
    acc += steer/4;
}

void JLFish::align(vector<JLFish *> *listFish)
{
    int count;
    float tempDist;
    
    count = 0;
    
    distSum.set(0);
    
    for (JLFish *fishFriend : *listFish)
    {
        tempDist = loc.distance(fishFriend->loc);
        
        if (tempDist > 0 && (tempDist < distNeighbor))
        {
            distSum += fishFriend->velocity;
            
            count++;
        }
    }
    
    if (count > 0)
    {
        applyForce(count);
    }
}

void JLFish::cohesion(vector<JLFish *> *listFish)
{
    float tempDist;
    float targetSeparation;
    int count;
    ofVec2f tempDiff;
    
    count = 0;
    
    distSum.set(0);
    
    targetSeparation = (radious * 40);
    
    for (JLFish *fishFriend : *listFish)
    {
        tempDist = loc.distance(fishFriend->loc);
        
        if (tempDist > targetSeparation)
        {
            tempDiff = (loc - fishFriend->loc);
            tempDiff.normalize();
            tempDiff *= -tempDist;
            distSum += tempDiff;
            count++;
        }
    }
    
    if (count > 0)
    {
        applyForce(count);
    }
}

void JLFish::separation(vector<JLFish *> *listFish)
{
    float tempDist;
    float targetSeparation;
    int count;
    ofVec2f tempDiff;
    
    count = 0;
    
    distSum.set(0);
    
    targetSeparation = (radious * 5);
    
    for (JLFish *fishFriend : *listFish)
    {
        tempDist = loc.distance(fishFriend->loc);
        
        if ( tempDist > 0 && tempDist < targetSeparation)
        {
            tempDiff = (loc - fishFriend->loc);
            tempDiff.normalize();
            tempDiff /= tempDist;
            distSum += tempDiff;
            count++;
        }
    }
    
    if (count > 0)
    {
        applyForce(count);
    }

}
void JLFish::update()
{
    velocity += acc;

    velocity.limit(maxSpeed);
    
    loc += velocity;
    
    acc *= 0;
}

void JLFish::checkBorders()
{
    if (loc.x < -radious)
    {
        loc.x = (myWidth+radious);
    }
    
    if (loc.y < -radious)
    {
        loc.y = (myHeight+radious);
    }
    
    if (loc.x > myWidth+radious)
    {
        loc.x = -radious;
    }
    
    if (loc.y > myHeight+radious)
    {
        loc.y = -radious;
    }
}

void JLFish::refresh()
{
    float angle;
    
    //ofEnableAlphaBlending();
    
    //ofSetColor(255, 255, 255,245);
    
    angle = ofRadToDeg(atan2(velocity.y, velocity.x)) + 180;
    
    ofPushMatrix();
    
    ofTranslate(loc);
    
    ofRotateZ(angle);

    imageFish.draw(-center.x,-center.y);
    
    //ofDrawCircle(0,0, radious);
    
    ofPopMatrix();
    
    //ofDisableAlphaBlending();
}
