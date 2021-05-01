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

	// NOTE: call setPosition(..) before setup(..) ??
	// NOTE: if not you must call setup(..) again after setPosition(..) ??
	//--------------------------------------------------------------
	void setPosition(float inx, float iny, float inw, float inh) {
		x = inx;
		y = iny;
		width = inw;
		height = inh;
		box.set(x, y, width, height);
	}

	// ofParameter<float> type
	void setupParam(ofParameter<float>& parameter, float inx, float iny, float inw, float inh, bool bVert, bool bDrawNum, bool _bAutodraw);
	void setupParam(ofParameter<float>& parameter, bool bVert, bool bDrawNum, bool _bAutodraw);

	// float type
	void setup(float inx, float iny, float inw, float inh, float loVal, float hiVal, float initialPercent, bool bVert, bool bDrawNum, bool _bAutodraw);

	void setVertical(bool b) {
		bVertical = b;

		clear();

		box.set(x, y, width, height);

		bHasFocus = false;

		if (!bWasSetup) {
			ofAddListener(ofEvents().draw, this, &ofxSimpleSlider::draw);
			ofAddListener(ofEvents().mouseMoved, this, &ofxSimpleSlider::mouseMoved);
			ofAddListener(ofEvents().mousePressed, this, &ofxSimpleSlider::mousePressed);
			ofAddListener(ofEvents().mouseReleased, this, &ofxSimpleSlider::mouseReleased);
			ofAddListener(ofEvents().mouseDragged, this, &ofxSimpleSlider::mouseDragged);
			bWasSetup = true;
		}
	}

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

	bool getIsVertical() {
		return bVertical;
	}

	void setLowValue(float lv);
	void setHighValue(float hv);
	void setPercent(float p);
	void setNumberDisplayPrecision(int prec);
	void setLabelString(std::string str);
	void updatePercentFromMouse(int mx, int my);

	void setVisible(bool b);
	void setVisibleOnlyIfHover(bool b);
	void setEnabled(bool b);

protected:
	//ofParameter<float> valueParam = NULL;
	ofParameter<float> valueParam{ "-1", -1 , -1, -1 };
	ofEventListener listener;

protected:
	bool isEnabled = true;
	bool bAutodraw = true;
	bool bLabelsAlignBottom = false;
	bool bDrawSpline = true;
	bool bDrawOutline = true;

public:
	//----------------------------------------------------
	void setDrawSpline(bool b) {
		bDrawSpline = b;
	}
	//----------------------------------------------------
	void setDrawOutline(bool b) {
		bDrawOutline = b;
	}

	//----------------------------------------------------
	void setLabeAlignBottom(bool b) {
		bLabelsAlignBottom = b;
	}

public:
	// a simple callback
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

	//----------------------------------------------------
	void setNumberDisplay(bool b) {
		bDrawNumberLabel = b;
	}

	//----------------------------------------------------
	void setBlinkThumb(bool b) {
		bBlinkThumb = b;
	}

protected:
	/* Return a linear value in range [0,1] every delay (in seconds). */
	float Tick(float delay) {
		return fmodf(ofGetElapsedTimeMillis() / 1000.0f, delay) / delay;
	}
	/* Return a linear value in range [0,1] every delay (in seconds),
	 with value equal 0 at boundaries, and 1 at delay / 2. */
	float Bounce(float delay) {
		return 0.5f*(1.0 + glm::sin(Tick(delay) * glm::two_pi<float>()));
	}

	//--

	// decoration

public:
	//----------------------------------------------------
	void setWidthThumbPick(float v) {
		widthThumbPick = v;
	}

	//----------------------------------------------------
	void setColorThumb(ofColor c) {
		colorThumb = c;
	}
	//----------------------------------------------------
	void setColorGlobal(ofColor c) {
		colorGlobal = c;
	}
	//----------------------------------------------------
	void setColorSpine(ofColor c) {
		colorSpine = c;
	}

	//----------------------------------------------------
	void setAlphaPowerThumb(float v) {
		alphaPowerThumb = v;
	}
	//----------------------------------------------------
	void setAlphaPowerGlobal(float v) {
		alphaPowerGlobal = v;
	}


protected:
	float widthThumbPick = 5.0;
	bool bChanged = false;

	float x;
	float y;
	float width;
	float height;
	ofRectangle box;
	int numberDisplayPrecision;

	bool bVertical;
	bool bDrawNumberLabel;
	bool bHasFocus;
	bool bVisible;
	bool bVisibleOnlyIfHover;
	bool bBlinkThumb;

	float lowValue;
	float highValue;
	float percent;

	std::string labelString;
	bool bLabel = false;

	ofColor colorThumb;
	ofColor colorGlobal;
	ofColor colorSpine;

	float alphaPowerThumb = 1.0;
	float alphaPowerGlobal = 1.0;

//public:
//	float sizeThumb = 1.0;

protected:
	bool bWasSetup;
};
