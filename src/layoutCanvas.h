#pragma once

#include "ofMain.h"

#include "ofxSimpleSlider.h"
#include "ofxGui.h"

class LayoutCanvas
{

protected:

	ofParameterGroup params{ "layoutCanvas" };
	void Changed(ofAbstractParameter &e);

	ofxSimpleSlider xSlider;
	ofParameter<float> xValue{ "x", 0.5, 0, 1 };

	ofxSimpleSlider ySlider;
	ofParameter<float> yValue{ "y", 0.5, 0, 1 };

	ofRectangle r1, r2, r3;

public:

	LayoutCanvas();
	~LayoutCanvas();

	void setup();
	void exit();

	void refresh();

	void update(ofEventArgs & args);
	void draw(ofEventArgs & args);
	void keyPressed(ofKeyEventArgs &eventArgs);

protected:

	ofParameter<bool> bReset{ "Reset", false };
	ofParameter<bool> bDebug{ "Debug", true };
	ofParameter<bool> bVisible{ "Visible", true};
	ofParameter<bool> bEdit{ "Edit", true };

private:
	ofxPanel gui;

};

