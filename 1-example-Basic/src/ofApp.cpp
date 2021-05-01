#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	float w = 200;
	float h = 400;

	// float type
	slider1.setup(10, 10, w, h, 0, 1, 0.5, true, true, true);//vertical, drawNum, autodraw
	// options
	slider1.setVisibleOnlyIfHover(true);
	//slider1.setLabelString("myFloat1");
	//slider1.setLabeAlignBottom(true);

	// parameter float type
	slider2.setupParam(value2, 20 + w, 10, w, h, true, true, true);//vertical, drawNum, autodraw
	// options
	slider2.setLabelString(value2.getName());
	slider2.setLabeAlignBottom(true);
	slider2.setBlinkThumb(true);
	slider2.setDrawOutline(false);
	slider2.setWidthThumbPick(10);
	slider2.setColorSpine(0);
	slider2.setColorThumb(ofColor::yellow);

	// debug callback 
	listener = value2.newListener([this](float &v) {
		ofLogNotice("ofApp") << value2.getName() << " :" << v;
	});
}

//--------------------------------------------------------------
void ofApp::update() {

	// optional
	// float type
	// a simple callback to know when the float var changed
	if (slider1.isChanged())
	{
		value1 = slider1.getValue();
		ofLogNotice(__FUNCTION__) << value1;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	slider2.drawSlider();// must draw manually bc is initiated with last bool disabled
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	ofLogNotice(__FUNCTION__) << key;

	// parameter float type

	if (key == '-') {
		value2 -= 0.5;
		value2 = ofClamp(value2, value2.getMin(), value2.getMax());
	}
	else if (key == '+') {
		value2 += 0.5;
		value2 = ofClamp(value2, value2.getMin(), value2.getMax());
	}
}