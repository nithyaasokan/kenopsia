#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //ofSetBackgroundColor(255,0,0);
    
    //PHOTO LAYER
    target.load("img/bamiyan_state1_lowres.jpg");
    
    //setting window size to image size
    ofSetWindowShape(target.getWidth(), target.getHeight());
    
    int num = 20000;
    p.assign(num, floatParticle());
    resetParticles();
}

//--------------------------------------------------------------

//MOVING BOKEH LAYER

//setting bokeh particles
void ofApp::resetParticles(){
    
    MovePoints.clear();
    for(int i = 0; i < 4; i++){
        MovePoints.push_back( ofPoint( ofMap(i, 0, 4, 100, ofGetWidth()-100) , ofRandom(100, ofGetHeight()-100) ) );
    }
    
    MovePointsNoise = MovePoints;
    
    for(unsigned int i = 0; i < p.size(); i++){
        p[i].setMovePoints(&MovePointsNoise);;
        p[i].reset();
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
        
    //MOVING BOKEH LAYER
    
    //updating bokeh particles
    for(unsigned int i = 0; i < p.size(); i++){
        p[i].update();
    }
    
    for(unsigned int i = 0; i < MovePointsNoise.size(); i++){
        MovePointsNoise[i].x = MovePoints[i].x +
        ofSignedNoise(i * 10, ofGetElapsedTimef() * 0.7) * 12.0;
        
        MovePointsNoise[i].y = MovePoints[i].y +
        ofSignedNoise(i * -10, ofGetElapsedTimef() * 0.7) * 12.0;
    }


}

//--------------------------------------------------------------
void ofApp::draw(){
    
    target.draw(0, 0);
    
    ofSetWindowTitle("kenopsia");
    
    //MOVING BOKEH LAYER
    
    //drawing bokeh particles
    for(unsigned int i = 0; i < p.size(); i++){
        p[i].draw();
    }


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
    //PHOTO LAYER
    
        if (mouseX >=0 && mouseX < 500){
            //blendMode = ofRandom(0,24);
            target.load("img/bamiyan_state1_lowres.jpg");
        }
    
        if (mouseX >=500 && mouseX < 1000) {
            //blendMode = ofRandom(0,24);
            target.load("img/bamiyan_state2_lowres.jpg");
        }
    
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
