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

	//-

	//slider1
	slider1.setup(50, 50, h, w, 0, 1, 0.5, true, true, true);//vertical

	//-

	//slider2
	slider2.setup(50 + h + 10, 50, w, h, 0, 1, 0.5, false, true, true);//horizontal
	slider2.setLabelString("myFloat2");

	//-

	//slider3
	slider3.setupParam(value3, true, true, true);//vertical
	slider3.setLabeAlignBottom(true);
	slider3.setLabelString(value3.getName());

	//-

	//slider4
	slider4.setupParam(value4, false, false, false);
	slider4.setNumberDisplay(true);
	slider4.setLabelString(value4.getName());
	slider4.setLabeAlignBottom(true);

	//decoration
	slider4.setWidthThumbPick(5);
	slider4.setColorThumb(ofColor::blue);
	slider4.setColorSpine(ofColor::black);
	slider4.setColorGlobal(ofColor::yellow);
	slider4.setAlphaPowerThumb(1);
	slider4.setAlphaPowerGlobal(1);//zero to hide
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
	ss += "a         : Animator " + ofToString(bAnim ? "[x]" : "[ ]") + "\n";
	ss += "1         : Slider1 | Set visible " + ofToString(b1visible ? "[x]" : "[ ]") + "\n";
	ss += "BACKSPACE : Slider1 | Randomize layout. \n";
	ss += "4         : Slider4 | AutoDraw disabled. Manual draw " + ofToString(bDrawManually ? "[x]" : "[ ]") + "\n";
	ss += "RETURN    : Slider4 | Randomize layout. \n";
	int yHelp = ofGetHeight() - 15 * 6;
	ofDrawBitmapStringHighlight(ss, 15, yHelp);

	// responsive layout
	int ww = ofGetWidth();
	int hh = ofGetHeight();
	int pad = 5;

	slider1.setPosition(pad, pad, hh - (hh - yHelp) - pad, w);
	slider2.setPosition(50 + 50, 50, ww - 50 + h + 10 - 5, h);
	slider3.setPosition(ww - 200 - pad, pad, 200, hh - 2 * pad);
	slider4.setPosition(pad + 100, 100, ww - pad + 100 - pad, hh - 100 - pad);

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

	if (key == OF_KEY_BACKSPACE) {//random position slider1
		float x, y, w, h;
		x = ofRandom(10, ofGetWidth() / 4);
		y = ofRandom(200, ofGetHeight() - 500);
		bool b = slider1.getIsVertical();
		slider1.setVertical(!b);
		w = (b ? 500 : 100);
		h = (!b ? 500 : 100);
		slider1.setPosition(x, y, w, h);
	}

	if (key == OF_KEY_RETURN) {//random position slider4
		float x, y, w, h;
		x = ofRandom(ofGetWidth() / 2, ofGetWidth() - 500);
		y = ofRandom(ofGetHeight() / 2, ofGetHeight() - 600);
		bool b = slider4.getIsVertical();
		slider4.setVertical(!b);
		w = (b ? 300 : 50);
		h = (!b ? 300 : 50);
		slider4.setPosition(x, y, w, h);
		slider4.setVertical(h > w);
		slider4.setDrawSpline(ofRandom(1) > 0.5);
	}
}

