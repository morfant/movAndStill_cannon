#pragma once

#include "ofMain.h"
#include "ofxDeckLink.h"

#define IMAGE_NUM 5

class ofApp : public ofBaseApp{

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
    
    
        ofxDeckLinkAPI::Input input;
    
        ofVideoGrabber vidGrabber;
        int camWidth;
        int camHeight;
        int margin_left = 10;
        int margin_bottom = 30;
    
    
        const float INTERVAL_MAX = 10.0f;
        const float INTERVAL_MIN = 0.0f;
        const float INTERVAL_STEP = 0.1f;
    
        float stillCutInterval = 5.0f;
        bool stillCutMode = false;
        string stillCutMode_str = "";
        float curTimef = 0.0f;
        float prevTimef = 0.0f;
        float timeDiff = 0.0f;
    
    
        const int IMAGE_IDX_MAX = IMAGE_NUM - 1;
        ofImage infoDrawing[IMAGE_NUM];
        bool imageMode = false;
        string imageMode_str = "";
        int curImageIdx = -1;
    
		
};