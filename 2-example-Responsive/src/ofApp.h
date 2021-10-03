#pragma once

#include "ofMain.h"

#include "ofxSimpleSlider.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	ofxSimpleSlider slider1;
	float value1;

	ofxSimpleSlider slider2;
	float value2;

	ofxSimpleSlider slider3;
	ofParameter<float> value3{ "myParam3", 2, 0, 7 };

	ofxSimpleSlider slider4;
	ofParameter<float> value4{ "myParam4", 0.5, 0, 2 };

	bool b1visible = true;
	bool bAnim = false;
	bool bDrawManually = true;

	float w = 200;
	float h = 50;
};
