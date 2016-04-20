//kenopsia @ Nithya Asokan
//Using example code from ofxOpenCV by


#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //openCV
    #ifdef _USE_LIVE_VIDEO
    vidGrabber.setVerbose(true);
    vidGrabber.setup(1024,768);
    #endif
    
    bLearnBakground = true;
    threshold = 80;
    
    //PHOTO LAYER
    target.load("img/bamiyan_state1_lowres.jpg");
    
    //setting window size to image size
    ofSetWindowShape(target.getWidth(), target.getHeight());
    
    int num = 30000;
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
    
    //openCV
    
    bool bNewFrame = false;
    
    #ifdef _USE_LIVE_VIDEO
       vidGrabber.update();
	   bNewFrame = vidGrabber.isFrameNew();
    #endif
    
    if (bNewFrame){
        
    #ifdef _USE_LIVE_VIDEO
        colorImg.setFromPixels(vidGrabber.getPixels());
        #else
        colorImg.setFromPixels(vidPlayer.getPixels());
        #endif
        
        grayImage = colorImg;
        if (bLearnBakground == true){
            grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
            bLearnBakground = false;
        }
        
        // take the abs value of the difference between background and incoming and then threshold:
        grayDiff.absDiff(grayBg, grayImage);
        grayDiff.threshold(threshold);
        
        //find contours between 20 pixels and 1/3rd of w*h
        contourFinder.findContours(grayDiff, 20, (1024*768)/3, 10, false);
        // if find holes is set to true so we will get interior contours as well....

    }
    
    
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
    ofSetWindowTitle("kenopsia");
    
    //drawing background visuals
    target.draw(0, 0);
    
    // we could draw the whole contour finder
    contourFinder.draw(0,0);
    
    // or, instead we can draw each blob individually from the blobs vector,
    // this is how to get access to them:
    for (int i = 0; i < contourFinder.nBlobs; i++){
        //contourFinder.blobs[i].draw(360,540);
        
    //drawing over the visuals if blob is detected
        if(contourFinder.blobs[i].hole){
                            target.load("img/bamiyan_state1_lowres.jpg");
        } else {
                target.load("img/bamiyan_state2_lowres.jpg");
        }
        
    }
    
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
    
//        if (mouseX >=0 && mouseX < 500){
//            //blendMode = ofRandom(0,24);
//            target.load("img/bamiyan_state1_lowres.jpg");
//        }
//    
//        if (mouseX >=500 && mouseX < 1000) {
//            //blendMode = ofRandom(0,24);
//            target.load("img/bamiyan_state2_lowres.jpg");
//        }
    
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
