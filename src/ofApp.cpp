#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // IMAGES
    infoDrawing[0].load("images/infoDrawing_0.jpeg");
    infoDrawing[1].load("images/infoDrawing_1.jpeg");
    infoDrawing[2].load("images/infoDrawing_2.jpeg");
    infoDrawing[3].load("images/infoDrawing_3.jpeg");
    infoDrawing[4].load("images/infoDrawing_4.jpeg");
    
    
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    // CAMERA - cannon
    if (input.setup(0)) {
        input.start(bmdModeHD1080i5994);
    }
    
    // prevent vertical line effect
    input.setDrawMode(ofxDeckLinkAPI::Input::DRAWMODE_UPPERFIELD);
    
//    camWidth = 320;  // try to grab at this size.
//    camHeight = 240;
    
    camWidth = ofGetWidth();  // try to grab at this size.
    camHeight = ofGetHeight();

    //we can now get back a list of devices.
    vector<ofVideoDevice> devices = vidGrabber.listDevices();

    for(int i = 0; i < devices.size(); i++){
        if(devices[i].bAvailable){
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
        }else{
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
        }
    }

    // CAMERA - usb web cam
//    vidGrabber.setDeviceID(0);
//    vidGrabber.setDeviceID(1);
//    vidGrabber.setDesiredFrameRate(30);
//    vidGrabber.initGrabber(camWidth, camHeight);

}

//--------------------------------------------------------------
void ofApp::update(){
    
//    ofBackground(0, 0, 0);
    
    if (!imageMode) {
        // first video update - NOT WORKING!!
        if (curTimef == 0.0f){
//            vidGrabber.update();
            input.update();
            ofLog(OF_LOG_NOTICE, "first video updated!");
        }
        
        if (stillCutMode) {
            // Insert interval between frames
            curTimef = ofGetElapsedTimef();
            timeDiff = curTimef - prevTimef;
            if (timeDiff >= stillCutInterval) {
//                vidGrabber.update();
                input.update();
                prevTimef = curTimef;
            }
        } else {
//            vidGrabber.update();
            input.update();
        }
    } else if (imageMode) {
        
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofClear(0);
    
    if (blackOut) {
        ofClear(0);
    } else if(whiteOut){
        ofClear(0xffffffff);
    }
    
    if (!blackOut && !whiteOut) {
        if (!imageMode) {
    //        vidGrabber.draw(20, 20);
            input.draw(0, 0, camWidth, camHeight);
        
        } else if (imageMode) {
            infoDrawing[curImageIdx].draw(0, 0, camWidth, camHeight);
    //        infoDrawing[curImageIdx].draw(0, 0);
        }
        
        
        ofSetHexColor(0xffffff);
        ofDrawBitmapStringHighlight(mode_str, margin_left, ofGetHeight() - margin_bottom);
        ofDrawBitmapStringHighlight(ofToString(roundf(timeDiff*100)/100) + " / " + ofToString(stillCutInterval), margin_left + 250, ofGetHeight() - margin_bottom);
    //    ofDrawBitmapString(ofToString(stillCutInterval), margin_left + 500, ofGetHeight() - margin_bottom);
        
        
        ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), margin_left + 550, ofGetHeight() - margin_bottom);
        ofDrawBitmapStringHighlight(ofToString(input.getDrawMode()), margin_left + 650, ofGetHeight() - margin_bottom);

    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == 'f') {
        ofToggleFullscreen();
        ofHideCursor();
    }
    if (key == '1') {
//        input.setDrawMode(ofxDeckLinkAPI::Input::DRAWMODE_PROGRESSIVE);
        blackOut = false;
        whiteOut = false;
        stillCutMode = false; imageMode = true; curImageIdx = 0;
        mode_str = "imageMode";
    }
    if (key == '2') {
//        input.setDrawMode(ofxDeckLinkAPI::Input::DRAWMODE_UPPERFIELD);
        blackOut = false;
        whiteOut = false;
        stillCutMode = false; imageMode = true; curImageIdx = 1;
        mode_str = "imageMode";
    }
    if (key == '3') {
//        input.setDrawMode(ofxDeckLinkAPI::Input::DRAWMODE_LOWERFIELD);
        blackOut = false;
        whiteOut = false;
        stillCutMode = false; imageMode = true; curImageIdx = 2;
        mode_str = "imageMode";
    }
    if (key == '4') {
//        input.setDrawMode(ofxDeckLinkAPI::Input::DRAWMODE_AUTOFIELD);
        blackOut = false;
        whiteOut = false;
        stillCutMode = false; imageMode = true; curImageIdx = 3;
        mode_str = "imageMode";
    }
    if (key == '5') {
//        input.setDrawMode(ofxDeckLinkAPI::Input::DRAWMODE_AUTOFIELD);
        blackOut = false;
        whiteOut = false;
        stillCutMode = false; imageMode = true; curImageIdx = 4;
        mode_str = "imageMode";
    }
    
    // STILL CUT MODE
    if(key == 's' || key == 'S'){
        blackOut = false;
        whiteOut = false;
        imageMode = false;
        stillCutMode = true;
//    if (stillCutMode) {
        mode_str = "stillCutMode";
//    } else {
//        mode_str = "stillCutMode : false";
//    }
        ofLog(OF_LOG_NOTICE, mode_str);
    }
    
    
    if (key == '+' || key == '=') {
        if (stillCutInterval <= (INTERVAL_MAX - INTERVAL_STEP)) stillCutInterval+=INTERVAL_STEP;
    }
    
    if (key == '_' || key == '-') {
        if (stillCutInterval >= (INTERVAL_MIN + INTERVAL_STEP)) stillCutInterval-=INTERVAL_STEP;
    }
    
    
    // IMAGE MODE
//    if (key == 'i' || key == 'I') {
//        if (!imageMode) {
//            stillCutMode = false;
//            imageMode = true;
//
//            if (curImageIdx < IMAGE_IDX_MAX){
//                curImageIdx++;
//            }
//            
//            if (imageMode) {
//                imageMode_str = "imageMode : true";
//            } else {
//                imageMode_str = "imageMode : false";
//            }
//            
//            ofLog(OF_LOG_NOTICE, imageMode_str);
//        }
//    }
//

    // VIDEO MODE
    if (key == 'v' || key == 'V'){
        blackOut = false;
        whiteOut = false;
        imageMode = false;
        stillCutMode = false;
        mode_str = "videoMode";
    }
    
    if (key == 'b') {
        blackOut = true;
        whiteOut = false;
    }
    
    if (key == 'w') {
        whiteOut = true;
        blackOut = false;
    }
 
 

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
