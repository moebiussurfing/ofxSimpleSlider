#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	float w = 50;
	float h = 200;

	// float type
	slider1.setup(100, 50, w, h, 0, 1, 0.5, true, true, true);//vertical, drawNum, autodraw
	//slider1.setLabelString("myFloat1");
	//slider1.setLabeAlignBottom(true);

	// parameter float type
	slider2.setupParam(value2, 110 + 2 * w, 50, w, h, true, true, true);//vertical, drawNum, autodraw
	slider2.setLabelString(value2.getName());
	slider2.setLabeAlignBottom(true);

	// debug callback 
	listener = value2.newListener([this](float &v) {
		ofLogNotice("ofApp") << value2.getName() << " :" << v;
	});
}

//--------------------------------------------------------------
void ofApp::update() {

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