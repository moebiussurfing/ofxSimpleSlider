#pragma once

#include "ofMain.h"

#include "ofxSimpleSlider.h"
#include "LayoutCanvas.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
		
		LayoutCanvas canvas;

		bool bGui = false;
};
