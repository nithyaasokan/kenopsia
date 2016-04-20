//
//  particles.cpp
//  mySketch
//
//  Created by Nithya Asokan on 4/7/16.
//
//

#include <stdio.h>
#include "particles.h"

//------------------------------------------------------------------
floatParticle::floatParticle(){
    
    MovePoints = NULL;
    
}

//------------------------------------------------------------------
void floatParticle::setMovePoints( vector <ofPoint> * move ){
    
    MovePoints = move;
    
}

//------------------------------------------------------------------
void floatParticle::reset(){
    
    //calling particles randomly
    eachParticle = ofRandom(-10000, 10000);
    
    pos.x = ofRandomWidth();
    pos.y = ofRandomHeight();
    
    vel.x = ofRandom(-10, 10);
    vel.y = ofRandom(-10, 10);
    
    force = ofPoint(0,0,0);
    
    scale = ofRandom(0.5, 1.0);
    drag  = ofRandom(0.95, 1.0);
    
}

//------------------------------------------------------------------
void floatParticle::update(){
    
    //circles repelling the mouse
    ofPoint movePt(ofGetMouseX(), ofGetMouseY());
    force = movePt-pos;
    
    float dist = force.length();
    force.normalize();
    
    vel *= drag;
    
    if ( dist < 100 ){
        
        vel += -force * 2;
        
        //noise when the mouse is not near the circles
    } else {
        
        force.x = ofSignedNoise(eachParticle, pos.y * 0.5, ofGetElapsedTimef()*0.5);
        force.y = ofSignedNoise(eachParticle, pos.x * 0.5, ofGetElapsedTimef()*0.5);
        vel += force * 0.5;
    }
    
    //update position
    pos.x += vel.x;
    pos.y += vel.y;
    
    //setting width and height of window as boundary for circles
    if( pos.x > ofGetWidth() ){
        pos.x = ofGetWidth();
        vel.x *= -1.5;
    }else if( pos.x < 0 ){
        pos.x = 0;
        vel.x *= -1.5;
    }
    if( pos.y > ofGetHeight() ){
        pos.y = ofGetHeight();
        vel.y *= -1.5;
    }
    else if( pos.y < 0 ){
        pos.y = 0;
        vel.y *= -1.5;
    }
    
}

//------------------------------------------------------------------
void floatParticle::draw(){
    
    ofEnableAlphaBlending();
    ofSetColor(100, 60, 40, 127);
    ofDrawEllipse(pos.x, pos.y,scale * 2.0 ,scale * 4.0);
    ofDrawCircle(pos.x, pos.y, scale * 1.5);
    ofDisableAlphaBlending();
}

