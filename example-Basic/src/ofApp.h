#pragma once

#include "ofMain.h"

#include "ofxSimpleSlider.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);

		// float type
		ofxSimpleSlider slider1;
		float value1;
		
		// parameter float type
		ofxSimpleSlider slider2;
		ofParameter<float> value2{ "myParam", 2.0f, 0.0f, 7.0f };
		ofEventListener listener;
};
