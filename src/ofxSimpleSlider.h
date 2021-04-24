/*
 *  ofxSimpleSlider.h
 *  Created by Golan Levin on 2/24/12.
 *  Updated by Dan Wilcox 2012.
 *  Updated by moebiusSurfing 2021.
 */

//TODO:
// + params
// + add setter, not setup

#pragma once

#include "ofMain.h"

class ofxSimpleSlider {

public:

    ofxSimpleSlider();
    ~ofxSimpleSlider();

	void setPosition(float inx, float iny, float inw, float inh) {
		x = inx;
		y = iny;
		width = inw;
		height = inh;
		box.set(x, y, width, height);
	}

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
    void setLabelString (string str);
    void updatePercentFromMouse(int mx, int my);

    bool isEnabled = true;
    void setVisible(bool b);

	//float ofParameter
	ofParameter<float> valueParam = NULL;
    void setupParam(ofParameter<float>& parameter, float inx, float iny, float inw, float inh, bool bVert, bool bDrawNum, bool _bAutodraw);
	ofEventListener listener;

protected:
	bool bAutodraw = true;
	bool bLabelsAlign = false;

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

    string labelString;
	bool bLabel = false;

private:

    bool bWasSetup;
};
