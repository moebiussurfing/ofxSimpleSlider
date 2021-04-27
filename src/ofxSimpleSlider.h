/*
 *  ofxSimpleSlider.h
 *  Created by Golan Levin on 2/24/12.
 *  Updated by Dan Wilcox 2012.
 *  Updated by moebiusSurfing 2021.
 */

#pragma once

#include "ofMain.h"

class ofxSimpleSlider {

public:
	ofxSimpleSlider();
	~ofxSimpleSlider();

	//NOTE: call setPosition(..) before setup(..)
	//NOTE: if not you must call setup(..) again after setPosition(..)!
	//--------------------------------------------------------------
	void setPosition(float inx, float iny, float inw, float inh) {
		x = inx;
		y = iny;
		width = inw;
		height = inh;
		box.set(x, y, width, height);
	}

	//float ofParameter
	void setupParam(ofParameter<float>& parameter, float inx, float iny, float inw, float inh, bool bVert, bool bDrawNum, bool _bAutodraw);

	void setup(float inx, float iny, float inw, float inh, float loVal, float hiVal, float initialPercent, bool bVert, bool bDrawNum, bool _bAutodraw);
	void clear();

	void drawSlider();
	void draw(ofEventArgs& event);
	void mouseMoved(ofMouseEventArgs& event);
	void mouseDragged(ofMouseEventArgs& event);
	void mousePressed(ofMouseEventArgs& event);
	void mouseReleased(ofMouseEventArgs& event);

	float getValue();
	float getLowValue();
	float getHighValue();
	float getPercent();

	void setLowValue(float lv);
	void setHighValue(float hv);
	void setPercent(float p);
	void setNumberDisplayPrecision(int prec);
	void setLabelString(std::string str);
	void updatePercentFromMouse(int mx, int my);

	void setVisible(bool b);

	ofParameter<float> valueParam = NULL;
protected:
	//ofEventListener listener;
	void Changed(float &v);

protected:
	bool isEnabled = true;
	bool bAutodraw = true;
	bool bLabelsAlignBottom = false;

public:
	//----------------------------------------------------
	void setLabeAlignBottom(bool b) {
		bLabelsAlignBottom = b;
	}

	//a simple callback
public:
	//----------------------------------------------------
	bool isChanged() {//to be called on every frame
		bool b;
		if (bChanged) {
			bChanged = false;
			b = true;
		}
		else
		{
			b = false;
		}
		return b;
	}
protected:
	bool bChanged = false;

	float x;
	float y;
	float width;
	float height;
	ofRectangle box;
	int numberDisplayPrecision;

	bool bVertical;
	bool bDrawNumber;
	bool bHasFocus;

	float lowValue;
	float highValue;
	float percent;

	std::string labelString;
	bool bLabel = false;

protected:
	bool bWasSetup;
};
