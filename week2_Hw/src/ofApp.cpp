#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
   
   
    
    ofBackground(0);
    ofSetBackgroundAuto(false);
 
    cat.loadImage("images/cat.png");
    cat2.loadImage("images/cat2.gif");
    song.loadSound("sounds/love.mp3");
    song.setVolume(0.75f);

   
    ofEnableAlphaBlending();
   
    
    
    
    soundStream.listDevices();
    
    //if you want to set a different device id
    //soundStream.setDeviceID(0); //bear in mind the device id corresponds to all audio devices, including  input-only and output-only devices.
    
    int bufferSize = 256;
    
    volHistory.assign(400, 0.0);
    
    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    volHistory.assign(400, 0.0);
    
    bufferCounter	= 0;
    smoothedVol     = 0.0;
    scaledVol		= 0.0;
    drawCounter		= 0;
    
    soundStream.setup(this, 0, 2, 44100, bufferSize, 2);
    //soundStream.setup(app, OutputChannels,InputChannels, sampleRate, bufferSize, nBuffers);
    
    // 0 output channels,
    // 2 input channels
    // 44100 samples per second
    // 256 samples per buffer
    // 2 num buffers (latency)


}

//--------------------------------------------------------------
void ofApp::update(){

    
    ofSoundUpdate();
    
    scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
    
    cout << "Vol is " << scaledVol << endl;
    
    
    
    //Record the volume into an array
    volHistory.push_back( scaledVol );
    
    if( volHistory.size() >= 400 ){
        volHistory.erase(volHistory.begin(), volHistory.begin()+1);
    }
    


}

//--------------------------------------------------------------
void ofApp::draw(){
  
   // cat.draw(250,150);
    
    
     cat.draw(450,300 , scaledVol * 2000.0f, scaledVol * 2000.0f);
    
    // If the left mouse button is pressed...
    if (ofGetMousePressed(OF_MOUSE_BUTTON_LEFT)) {
        
    
       
        cat2.draw(ofGetMouseX(), ofGetMouseY(), 50, 50);     }
    
    // If the right mouse button is pressed...
    if (ofGetMousePressed(OF_MOUSE_BUTTON_RIGHT)) {
        //ofBackground(0);  // Erase the screen with a black background
    
    }
     
     
    


}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    float curVol = 0.0;
    
    // samples are "interleaved"
    int numCounted = 0;
    
    //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
    for (int i = 0; i < bufferSize; i++){
        left[i]		= input[i*2]*0.5;
        right[i]	= input[i*2+1]*0.5;
        
        curVol += left[i] * left[i];
        curVol += right[i] * right[i];
        numCounted+=2;
    }
    
    curVol /= (float)numCounted;
    
    // this is how we get the root of rms
    curVol = sqrt( curVol );
    
    smoothedVol *= 0.93;
    smoothedVol += 0.07 * curVol;
    
    bufferCounter++;
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key == '1'){
        song.play();
    }
    
    if (key =='2'){
        ofBackground(0);
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
