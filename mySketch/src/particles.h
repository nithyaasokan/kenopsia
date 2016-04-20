//
//  particles.h
//  mySketch
//
//  Created by Nithya Asokan on 4/7/16.
//
//

#ifndef particles_h
#define particles_h


#endif /* particles_h */


#pragma once
#include "ofMain.h"

class floatParticle{
    
public:
    floatParticle();
    
    void setMovePoints( vector <ofPoint> * move );
    
    void reset();
    void update();
    void draw();
    
    ofPoint pos;
    ofPoint vel;
    ofPoint force;
    
    float drag;
    float eachParticle;
    float scale;
    
    vector <ofPoint> * MovePoints;
    
};