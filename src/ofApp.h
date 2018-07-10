#pragma once

#include "ofMain.h"

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
		
    
    float     counter;
    bool    bSmooth;
    int mouseX;
    int mouseY;
    float mouseSize;
    float mouseSizeY;
    
    float radius; 
    float radius2;
    
    void audioIn(float * input, int bufferSize, int nChannels);
    
    ofSoundStream matchSound ;
    
    vector <float> left;
    vector <float> right;
    vector <float> volHistory;
    
    int     bufferCounter;
    int     drawCounter;
    
    float smoothedVol;
    float scaledVol;
    
    string msg;
    
    
    ofTrueTypeFont font;
    ofTrueTypeFont font2;
    
    ofSoundPlayer wow;
    
    void setupArduino(const int & _version);
    ofArduino arduino;
    bool arduinoIsSetup = false;
    
    float v;
    
    
};
