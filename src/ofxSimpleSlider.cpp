/*
 *  ofxSimpleSlider.cpp
 *  Created by Golan Levin on 2/24/12.
 *  Updated by Dan Wilcox 2012.
 *  Updated by moebiusSurfing 2021.
 */

#include "ofxSimpleSlider.h"

 //----------------------------------------------------
ofxSimpleSlider::ofxSimpleSlider() {
	ofLogNotice(__FUNCTION__);

	bWasSetup = false;

	labelString = "";

	colorThumb.set(255, 255, 255);
	colorGlobal.set(200, 200, 200);
	colorSpine.set(255, 255, 255);
}

//----------------------------------------------------
ofxSimpleSlider::~ofxSimpleSlider() {
	ofLogNotice(__FUNCTION__);

	clear();
}

//-----------------------------------------------------------------------------------------------------------------------
void ofxSimpleSlider::setupParam(ofParameter<float>& parameter, float inx, float iny, float inw, float inh, bool bVert, bool bDrawNum, bool _bAutodraw) {
	ofLogNotice(__FUNCTION__);

	valueParam.makeReferenceTo(parameter);
	setup(inx, iny, inw, inh, parameter.getMin(), parameter.getMax(), parameter.get(), bVert, bDrawNum, _bAutodraw);

	// callback
	listener = valueParam.newListener([this](float &v) {
		ofLogNotice("ofxSimpleSlider::Changed") /*<< valueParam.getName() << ":"*/ << v;
		float _prc = ofMap(v, lowValue, highValue, 0, 1, true);
		setPercent(_prc);
	});
}

//-----------------------------------------------------------------------------------------------------------------------
void ofxSimpleSlider::setup(float inx, float iny, float inw, float inh, float loVal, float hiVal, float initialValue, bool bVert, bool bDrawNum, bool _bAutodraw) {
	ofLogNotice(__FUNCTION__);

	bWasSetup = false;
	bAutodraw = _bAutodraw;
	clear();

	x = inx;
	y = iny;
	width = inw;
	height = inh;
	box.set(x, y, width, height);
	numberDisplayPrecision = 2;

	bVertical = bVert;
	bDrawNumberLabel = bDrawNum;
	bHasFocus = false;

	lowValue = loVal;
	highValue = hiVal;
	percent = ofMap(initialValue, lowValue, highValue, 0, 1);
	percent = ofClamp(percent, 0, 1);

	if (!bWasSetup) {
		ofAddListener(ofEvents().draw, this, &ofxSimpleSlider::draw);
		ofAddListener(ofEvents().mouseMoved, this, &ofxSimpleSlider::mouseMoved);
		ofAddListener(ofEvents().mousePressed, this, &ofxSimpleSlider::mousePressed);
		ofAddListener(ofEvents().mouseReleased, this, &ofxSimpleSlider::mouseReleased);
		ofAddListener(ofEvents().mouseDragged, this, &ofxSimpleSlider::mouseDragged);
		bWasSetup = true;
	}

	//labelString = "";
}

//----------------------------------------------------
void ofxSimpleSlider::clear() {
	ofLogNotice(__FUNCTION__);

	if (bWasSetup) {
		ofRemoveListener(ofEvents().draw, this, &ofxSimpleSlider::draw);
		ofRemoveListener(ofEvents().mouseMoved, this, &ofxSimpleSlider::mouseMoved);
		ofRemoveListener(ofEvents().mousePressed, this, &ofxSimpleSlider::mousePressed);
		ofRemoveListener(ofEvents().mouseReleased, this, &ofxSimpleSlider::mouseReleased);
		ofRemoveListener(ofEvents().mouseDragged, this, &ofxSimpleSlider::mouseDragged);
	}
	bWasSetup = false;
}

//----------------------------------------------------
void ofxSimpleSlider::setLabelString(string str) {
	ofLogNotice(__FUNCTION__) << str;

	labelString = str;

	bLabel = true;
}

//----------------------------------------------------
void ofxSimpleSlider::draw(ofEventArgs& event) {
	if (!bAutodraw) return;

	drawSlider();
}

//----------------------------------------------------
void ofxSimpleSlider::drawSlider() {

	if (isEnabled) {

		ofPushStyle();

		ofPushMatrix();
		ofTranslate(x, y, 0);

		// Use different alphas if we're actively maniupulating me.
		float sliderAlpha = alphaGlobalPower * ((bHasFocus) ? 128 : 64);
		float spineAlpha = alphaGlobalPower * ((bHasFocus) ? 192 : 128);
		float thumbAlpha = thumbAlphaPower * ((bHasFocus) ? 255 : 200);

		// draw box outline
		if (alphaGlobalPower != 0) {
			ofNoFill();
			ofSetLineWidth(1.0);
			ofSetColor(ofColor(colorGlobal, sliderAlpha));
			ofSetRectMode(OF_RECTMODE_CORNER);
			ofDrawRectangle(0, 0, width, height);
		}

		// draw spine
		if (bDrawCenterLine && spineAlpha!=0) {
			ofSetLineWidth(1.0);
			ofSetColor(ofColor(colorSpine, spineAlpha));
			if (bVertical) {
				ofDrawLine(width / 2, 0, width / 2, height);
			}
			else {
				ofDrawLine(0, height / 2, width, height / 2);
			}
		}

		// draw thumb pick
		if (thumbAlpha != 0) {
			ofSetLineWidth(widthThumbPick);
			ofSetColor(ofColor(colorThumb, thumbAlpha));
			if (bVertical) {
				float thumbY = ofMap(percent, 0, 1, height, 0, true);
				ofDrawLine(0, thumbY, width, thumbY);
			}
			else {
				float thumbX = ofMap(percent, 0, 1, 0, width, true);
				ofDrawLine(thumbX, 0, thumbX, height);
			}
		}

		//--

		// number and name labels
		
		//TODO:
		////move label up left
		//ofTranslate(-77, -7);
		////move label down left
		//ofTranslate(-32, 33);
		////move label down left
		//ofTranslate(-30, 20);
		ofTranslate(10, -7);

		for (int i = 0; i < 2; i++) {
			if (bHasFocus) {
				if (i == 0) ofSetColor(0, 255);
				else if (i == 1) {
					ofSetColor(255, 255);
					ofTranslate(-1, -1);
				}
			}
			else {
				if (i == 0) ofSetColor(0, 200);
				else if (i == 1) {
					ofSetColor(255, 200);
					ofTranslate(-1, -1);
				}
			}

			// draw numeric value
			if (bDrawNumberLabel)
			{
				int _pw = 4;//TODO: get text width
				int _ph = 15;//font height
				int _x, _y;

				if (bVertical)//vertical
				{
					if (!bLabelsAlignBottom) {//right
						_x = width + 2;
						_y = height;

						if (bLabel) _y -= 16;
					}
					else//bottom
					{
						_x = -5;
						_y = height + _ph + 10;
					}

					//label
					if (bLabel)
					{
						ofDrawBitmapString(labelString, _x, _y);
						_y += _ph;
					}
					//number
					ofDrawBitmapString(ofToString(getValue(), numberDisplayPrecision), _x, _y);
				}
				else//hoizontal
				{
					if (!bLabelsAlignBottom) {//right
						_x = width + 5;
						_y = height / 2 + 4;
					}
					else {//bottom
						_x = -5;
						_y = height + _ph + 10;
					}
					//label
					if (bLabel) {
						ofDrawBitmapString(labelString, _x, _y);
						_y += _ph;
					}
					//number
					ofDrawBitmapString(ofToString(getValue(), numberDisplayPrecision), _x, _y);
				}
			}

		}
		ofPopMatrix();

		ofPopStyle();
	}
}

//----------------------------------------------------
float ofxSimpleSlider::getValue() {
	// this is the main way you get the value from the slider
	float out = ofMap(percent, 0, 1, lowValue, highValue, true);
	return out;
}

//----------------------------------------------------
// Probably not used very much. 
float ofxSimpleSlider::getLowValue() {
	return lowValue;
}
float ofxSimpleSlider::getHighValue() {
	return highValue;
}
float ofxSimpleSlider::getPercent() {
	return percent;
}

//----------------------------------------------------
// Probably not used very much. 
void ofxSimpleSlider::setLowValue(float lv) {
	lowValue = lv;
}
void ofxSimpleSlider::setHighValue(float hv) {
	highValue = hv;
}
void ofxSimpleSlider::setPercent(float p) {
	// Set the slider's percentage from the outside. 
	p = ofClamp(p, 0, 1);
	percent = p;

	bChanged = true;
}
void ofxSimpleSlider::setNumberDisplayPrecision(int prec) {
	numberDisplayPrecision = prec;
}

//----------------------------------------------------
void ofxSimpleSlider::mouseMoved(ofMouseEventArgs& event) {

	if (isEnabled) {
		bHasFocus = false;
	}
}
void ofxSimpleSlider::mouseDragged(ofMouseEventArgs& event) {
	if (isEnabled) {
		if (bHasFocus) {
			updatePercentFromMouse(event.x, event.y);
		}
	}
}
void ofxSimpleSlider::mousePressed(ofMouseEventArgs& event) {
	if (isEnabled) {
		bHasFocus = false;
		if (box.inside(event.x, event.y)) {
			bHasFocus = true;
			updatePercentFromMouse(event.x, event.y);
		}
	}
}
void ofxSimpleSlider::mouseReleased(ofMouseEventArgs& event) {
	if (isEnabled) {
		if (bHasFocus) {
			if (box.inside(event.x, event.y)) {
				updatePercentFromMouse(event.x, event.y);
			}
		}
		bHasFocus = false;
	}
}

//----------------------------------------------------
void ofxSimpleSlider::updatePercentFromMouse(int mx, int my) {
	if (isEnabled) {
		// Given the mouse value, compute the percentage.
		if (bVertical) {
			percent = ofMap(my, y, y + height, 1, 0, true);

			if (valueParam.getName() != "-1")//ugly workaround
				valueParam = ofMap(percent, 0, 1, valueParam.getMin(), valueParam.getMax(), true);
		}
		else {
			percent = ofMap(mx, x, x + width, 0, 1, true);

			if (valueParam.getName() != "-1")//ugly workaround
				valueParam = ofMap(percent, 0, 1, valueParam.getMin(), valueParam.getMax(), true);
		}

		bChanged = true;
	}
}

//--------------------------------------------------------------
void ofxSimpleSlider::setVisible(bool b)
{
	isEnabled = b;
}

//--------------------------------------------------------------
void ofxSimpleSlider::setEnabled(bool b)
{
	isEnabled = b;
}

