#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    arduinoIsSetup = false;
    ofAddListener(arduino.EInitialized, this, &ofApp::setupArduino);
    arduino.connect("/dev/tty.usbmodem1411", 57600);
    
    
    font.drawString(msg, 50, 200);
    font.loadFont("CODE Bold.otf", 100);
    
    font2.drawString(msg, 50, 200);
    font2.loadFont("CODE Bold.otf", 25);
    
    counter = 0;
    ofSetCircleResolution(50);
    ofBackground(255,255,255);
    bSmooth = false;
    
    int bufferSize = 256;
    
    matchSound.printDeviceList();
    matchSound.setup(this,0,2,44100,bufferSize,4);
    
    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    volHistory.assign(400, 0.0);
    
    smoothedVol     = 0.0;
    scaledVol        = 0.0;
    
    wow.load("synth.wav");
    wow.setVolume(5.0f);
    
    
}

void ofApp::setupArduino(const int & _version) {
    ofLog() << "setupArduino" << endl;
    
    arduinoIsSetup = true;
    ofRemoveListener(arduino.EInitialized, this, &ofApp::setupArduino);
    
    //arduino.sendDigitalPinMode(13, ARD_OUTPUT);
    arduino.sendAnalogPinReporting(0, ARD_ANALOG);
    
    
}


//--------------------------------------------------------------
void ofApp::update(){
   
    arduino.update();
    
    ofSoundUpdate();

   scaledVol = ofMap(smoothedVol, 0.0, 0.17, 5, 200, true);
    
    //lets record the volume into an array
    volHistory.push_back( scaledVol );
    
    //if we are bigger the the size we want to record - lets drop the oldest value
    if( volHistory.size() >= 400 ){
        volHistory.erase(volHistory.begin(), volHistory.begin()+1);
    }
    
    
    if ( radius == radius2
        || -radius == radius2
        || radius == -radius2
        || -radius == -radius2) {
        
        
        ofSetColor(255);
        font.drawString(msg, 50, 100);
        //ofSetColor(255);
        msg = "M A T C H ! ! !";
        ofSleepMillis(2000);
        //ofTimer(2000);
        wow.play();
        
            }else{
              ofBackground(255);
                
    }
    
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if(arduinoIsSetup){
        v = arduino.getAnalog(0);
        ofLog() << v << endl;
        //arduino.sendDigital(13, false);
        
    }
    
    //font2.drawString(msg, 30, 50);
    //msg = " match the circle ";
    
    
    //ofMap(mouseX, 0, ofGetWidth(), 0, 255);
    //ofMap(mouseY,0,ofGetHeight(),0,255);
    ofSetColor(mouseX,mouseY,0);
    
    //for(int i = 1; i <100; i++){
    //float radius = 50 + 10 * mouseSize;
    
    ofMap(mouseSize,0,ofGetWidth(),10,30);
    radius = 130 + mouseSize;
    //radius =mouseSize * 0.2;
    ofNoFill();        // draw "unfilled shapes"   //ofSetColor(255, 0, 0)
    ofSetLineWidth(3.0f);
    ofDrawCircle(ofGetWidth()/2,ofGetHeight()/2,radius);
    
    
    ofLog() << radius << endl;
    ofSetColor(mouseX,mouseY,0);
    
    
    ofMap(mouseSizeY,0,ofGetHeight(),10,30);
    radius2  = 100 + mouseSizeY;
    
    //float radius = 50 + 10 * mouseSize;
    // draw "unfilled shapes"   //ofSetColor(255, 0, 0)
    
    radius2 = int(scaledVol * 10);
    ofNoFill();
    ofDrawCircle(ofGetWidth()/2,ofGetHeight()/2, radius2);
    
    ofLog() << radius << " radius:  " << endl;
    ofLog() << radius2 << "radius2:  " << endl;
    

    if ( radius == radius2
        || -radius == radius2
        || radius == -radius2
        || -radius == -radius2) {
        ofBackground(255, 0, 0);
        ofSetColor(255);
        font.drawString(msg, 50 ,ofGetHeight()/2+50);
        //ofSetColor(255);
        msg = " M A T C H ! ! !";
        //ofTimer(2000);
        wow.play();

        
    }

        
    
    
    
//    if ( radius == radius2) && ( radius2 == radius){
        
//        ofDrawBitmapString("Yahoo", ofGetWidth()/2,ofGetHeight()/2);
//        ofBackground(255, 0, 0);
    
//    }else{
 //      ofBackground(255);
    
        
        
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    float curVol = 0.0;
    
    // samples are "interleaved"
    int numCounted = 0;
    
    //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
    for (int i = 0; i < bufferSize; i++){
        left[i]        = input[i*2]*0.5;
        right[i]    = input[i*2+1]*0.5;
        
        curVol += left[i] * left[i];
        curVol += right[i] * right[i];
        numCounted+=2;
    }
    
    //this is how we get the mean of rms :)
    curVol /= (float)numCounted;
    
    // this is how we get the root of rms :)
    curVol = sqrt( curVol );
    
    smoothedVol *= 0.93;
    smoothedVol += 0.07 * curVol;
    
    bufferCounter++;
    
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    ofLog() << x << " " << y << endl;
    mouseX = x;
    mouseY = y;
    mouseSize = x;
    mouseSizeY = y;
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
