#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(255,255,255);
    time = 0;
    ofSetFrameRate(30);

    //ofLog(OF_LOG_NOTICE,ofToString(z.zap));
    //csv.loadFile(ofToDataPath("Tarjetas.csv"));
}

//--------------------------------------------------------------
void testApp::update(){

    if(time >= 5){
        time = 0;
        arduinos.lee(&producto);
        //ofLog(OF_LOG_NOTICE, ofToString(producto.tarjeta[0].size()));
        //ofLog(OF_LOG_NOTICE, producto.tarjeta[0] + "bien");
    }

    time++;

    int frameRate = ofGetFrameRate();
    if(frameRate < 10){
        ofLog(OF_LOG_NOTICE,ofToString(frameRate));
    }

}


//--------------------------------------------------------------
void testApp::draw(){

   z.draw(producto);


}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

    //ofBackground(ofRandom(255),ofRandom(255),ofRandom(255));




}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
