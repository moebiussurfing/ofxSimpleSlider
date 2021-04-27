#include "ofApp.h"

//------------------------------------------------------------------------------
	//animator functions taken from 
	//https://github.com/tcoppex/ofxFontSampler/blob/main/example/src/ofApp.cpp
namespace {

	/* Return a linear value in range [0,1] every delay (in seconds). */
	float Tick(float delay) {
		return fmodf(ofGetElapsedTimeMillis() / 1000.0f, delay) / delay;
	}

	/* Return a linear value in range [0,1] every delay (in seconds),
	 with value equal 0 at boundaries, and 1 at delay / 2. */
	float Bounce(float delay) {
		return 0.5f*(1.0 + glm::sin(Tick(delay) * glm::two_pi<float>()));
	}

	/* Noise function used by the gradient scaling. */
	float Noise(const ofPoint &vertex) {
		return /*24.0f **/ ofNoise(0.005f*vertex + 0.5f*ofGetElapsedTimeMillis()*0.0002f);
	}

	static constexpr int32_t kCharsetSize = 26;

}  // namespace

//--------------------------------------------------------------
void ofApp::setup() {
	float big = 200;
	float small = 50;

	slider1.setup(100, 50, small, big, 0, 1, 0.5, true, true, true);//vertical
	slider2.setup(100 + small + 10, 50, big, small, 0, 1, 0.5, false, true, true);//horizontal
	slider3.setupParam(value3, 600, 50, small, big, true, true, true);//vertical
	slider4.setupParam(value4, 610 + small, 50, small, big, true, true, false);// 1: vertical. 2: draw number label. 3: manual draw. disabled autodraw
}

//--------------------------------------------------------------
void ofApp::update() {
	if (bAnim)
	{
		//anim parameters
		float v;

		v = Noise(ofPoint(20, 4));
		value3 = value3.getMax() * v;
		ofLogNotice(__FUNCTION__) << "value3: " << value3;

		v = Bounce(2);
		//v = Tick(2);
		value4 = value4.getMax() * v;
		ofLogNotice(__FUNCTION__) << "value4: " << value4;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	if (!bDrawManually) slider4.drawSlider();//must draw manually bc is initiated with last bool disabled

	string ss;
	ss += "a: animator " + ofToString(bAnim ? "[x]" : "[ ]") + "\n";
	ss += "d: autodraw slider4 " + ofToString(bDrawManually ? "[x]" : "[ ]");
	ofDrawBitmapStringHighlight(ss, 10, ofGetHeight() - 15 * 2);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'a') bAnim = !bAnim;
	if (key == 'd') bDrawManually = !bDrawManually;
}

