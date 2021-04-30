#pragma once

#include "ofMain.h"

#include "ofxSimpleSlider.h"
#include "ofxGui.h"

class LayoutCanvas
{

protected:
	ofParameterGroup params{ "LayoutCanvas" };
	void Changed(ofAbstractParameter &e);

	ofxSimpleSlider xSlider;
	ofxSimpleSlider ySlider;

public:
	ofParameterGroup getParameters() {
		return params;
	}

	void setSizeThumb(int _sizeThumb) {
		sizeThumb = _sizeThumb;
		//xSlider.sizeThumb = _sizeThumb;
		//ySlider.sizeThumb = _sizeThumb;
	}

protected:
	int sizeThumb = 100;//slider size

public:
	ofParameter<float> xValue{ "x", 0.5, 0, 1 };
	ofParameter<float> yValue{ "y", 0.5, 0, 1 };

public:
	ofRectangle r1, r2, r3;

public:

	LayoutCanvas();
	~LayoutCanvas();

	void setup();
	void exit();

protected:
	void refresh();
	void update(ofEventArgs & args);
	void draw(ofEventArgs & args);
	void keyPressed(ofKeyEventArgs &eventArgs);

	//protected:
public:
	ofParameter<bool> bReset{ "Reset", false };
	ofParameter<bool> bDebug{ "Debug", true };
	ofParameter<bool> bVisible{ "Visible", true };
	ofParameter<bool> bGui{ "Gui", true };
	ofParameter<bool> bEdit{ "Edit", true };
	//ofParameter<bool> bSpin{ "Spin", true };

public:
	void setHandleSettings(bool b) {
		bHandleSettings = b;
	}
	void setVisibleGui(bool b) {
		bGui = b;
	}

private:
	bool bHandleSettings = true;
	string path_Settings = "LayoutCanvas.json";
	ofxPanel gui;

};

