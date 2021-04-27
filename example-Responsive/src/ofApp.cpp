#include "ofApp.h"

//------------------------------------------------------------------------------
// animator functions taken from 
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

	float w = 200;
	float h = 50;

	slider1.setup(50, 50, h, w, 0, 1, 0.5, true, true, true);//vertical

	slider2.setup(50 + h + 10, 50, w, h, 0, 1, 0.5, false, true, true);//horizontal
	slider2.setLabelString("myFloat2");

	slider3.setupParam(value3, 0, 0, 0, 0, true, true, true);//vertical
	slider3.setLabeAlignBottom(true);
	slider3.setLabelString(value3.getName());

	slider4.setupParam(value4, 0, 0, 0, 0, true, true, false);// 1: vertical. 2: draw number label. 3: manual draw. disabled autodraw
	slider4.setLabelString(value4.getName());
	//slider4.setLabeAlignBottom(true);
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

	// help info
	string ss;
	ss += "a : Animator " + ofToString(bAnim ? "[x]" : "[ ]") + "\n";
	ss += "1 : Slider1 > Set visible " + ofToString(b1visible ? "[x]" : "[ ]") + "\n";
	ss += "4 : Slider4 > AutoDraw disabled. Manual draw " + ofToString(bDrawManually ? "[x]" : "[ ]");
	ofDrawBitmapStringHighlight(ss, 15, ofGetHeight() - 15 * 4);

	// responsive layout
	float pad = 20;
	float ww = ofGetWidth() / 2;
	float hh = ofGetHeight() - 20;
	slider3.setPosition(ww + pad - 70, pad, (ww / 2) - 2 * pad, hh - 2 * pad);
	slider4.setPosition(ww + pad - 70 + (ww / 2), pad, (ww / 2) - 2 * pad, hh - 2 * pad);

	if (bDrawManually) slider4.drawSlider();// must draw this slider manually bc is initiated with last bool autoDraw disabled
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	if (key == 'a') bAnim = !bAnim;
	if (key == '1') {
		b1visible = !b1visible;
		slider1.setVisible(b1visible);
	}
	if (key == '4') bDrawManually = !bDrawManually;
}

