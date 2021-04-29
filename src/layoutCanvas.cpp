#include "LayoutCanvas.h"

//--------------------------------------------------------------
LayoutCanvas::LayoutCanvas() {
	ofAddListener(ofEvents().update, this, &LayoutCanvas::update);
	ofAddListener(ofEvents().draw, this, &LayoutCanvas::draw);
	ofAddListener(ofEvents().keyPressed, this, &LayoutCanvas::keyPressed);

	setup();
}

//--------------------------------------------------------------
LayoutCanvas::~LayoutCanvas() {
	ofRemoveListener(ofEvents().update, this, &LayoutCanvas::update);
	ofRemoveListener(ofEvents().draw, this, &LayoutCanvas::draw);
	ofRemoveListener(ofEvents().keyPressed, this, &LayoutCanvas::keyPressed);

	ofRemoveListener(params.parameterChangedE(), this, &LayoutCanvas::Changed);

	exit();
}

//--------------------------------------------------------------
void LayoutCanvas::setup() {
	params.add(xValue);
	params.add(yValue);

	params.add(bDebug);
	params.add(bVisible);
	params.add(bEdit);
	params.add(bReset);

	ofAddListener(params.parameterChangedE(), this, &LayoutCanvas::Changed);

	xSlider.setupParam(xValue, -1, -1, -1, -1, false, false, false);//horizontal
	ySlider.setupParam(yValue, -1, -1, -1, -1, true, false, false);//vertical

	gui.setup(params);
	gui.setPosition(100, 100);

	ofJson settings;
	settings = ofLoadJson("Settings.json");
	ofDeserialize(settings, params);

	refresh();
}

//--------------------------------------------------------------
void LayoutCanvas::update(ofEventArgs & args)
{
	int x, y, w, h;

	x = 0;
	y = 0;
	w = ofGetWidth() *  xValue;
	h = ofGetHeight() * (1 - yValue);
	r1 = ofRectangle(x, y, w, h);

	x = w;
	y = 0;
	w = ofGetWidth() - x;
	h = h;
	r2 = ofRectangle(x, y, w, h);

	x = 0;
	y = h;
	w = ofGetWidth();
	h = ofGetHeight() - y;
	r3 = ofRectangle(x, y, w, h);
}

//--------------------------------------------------------------
void LayoutCanvas::draw(ofEventArgs & args)
{
	ofPushStyle();
	{
		//filled
		ofFill();
		int alpha = 255;
		ofSetColor(ofColor::red, alpha);
		ofDrawRectangle(r1);
		ofSetColor(ofColor::green, alpha);
		ofDrawRectangle(r2);
		ofSetColor(ofColor::blue, alpha);
		ofDrawRectangle(r3);

		//border
		if (bDebug) {
			ofSetColor(0, 255);
			ofSetLineWidth(2);
			ofNoFill();
			ofDrawRectangle(r1);
			ofDrawRectangle(r2);
			ofDrawRectangle(r3);
		}
	}
	ofPopStyle();

	if (bVisible) {
		int sz;//slider size
		sz = 100;
		
		//sz = ofGetWidth();
		xSlider.setPosition(0, r1.getY() / 2, ofGetWidth(), sz);//top
		//xSlider.setPosition(0, r1.getHeight() / 2 - sz / 2, ofGetWidth(), sz);//centered
		xSlider.drawSlider();

		//sz = ofGetHeight();
		ySlider.setPosition(0, 0, sz, ofGetHeight());//left
		//ySlider.setPosition(r3.getWidth() / 2 - sz / 2, 0, sz, ofGetHeight());//centered
		ySlider.drawSlider();
	}
	gui.draw();
}

//--------------------------------------------------------------
void LayoutCanvas::refresh() {

	//hide
	if (!bDebug) {
		xSlider.setAlphaThumbPower(0);
		xSlider.setAlphaGlobalPower(0);
		xSlider.setWidthThumbPick(1);
	}
	//debug
	else {
		xSlider.setAlphaThumbPower(1);
		xSlider.setAlphaGlobalPower(1);
		xSlider.setWidthThumbPick(5);
		xSlider.setDrawSpline(true);
		xSlider.setColorThumb(0);
		xSlider.setColorGlobal(0);
		xSlider.setColorSpine(0);
	}

	//hide
	if (!bDebug) {
		ySlider.setAlphaThumbPower(0);
		ySlider.setAlphaGlobalPower(0);
		ySlider.setWidthThumbPick(1);
	}
	//debug
	else {
		ySlider.setAlphaThumbPower(1);
		ySlider.setAlphaGlobalPower(1);
		ySlider.setWidthThumbPick(5);
		ySlider.setDrawSpline(true);
		ySlider.setColorThumb(0);
		ySlider.setColorGlobal(0);
		ySlider.setColorSpine(0);
	}
}

//--------------------------------------------------------------
void LayoutCanvas::exit() {
	ofJson settings;
	ofSerialize(settings, params);
	bool b = ofSavePrettyJson("Settings.json", settings);
}

////--------------------------------------------------------------
//void LayoutCanvas::setBool(bool b){
//		ofLogNotice(__FUNCTION__) << ofToString(b);
//}
//
////--------------------------------------------------------------
//bool LayoutCanvas::getBool(){
//	return true;
//}

//--------------------------------------------------------------
void LayoutCanvas::Changed(ofAbstractParameter &e)
{
	std::string name = e.getName();

	ofLogNotice(__FUNCTION__) << name << " : " << e;

	//--

	if (false) {}

	else if (name == xValue.getName())
	{
		refresh();
	}
	else if (name == yValue.getName())
	{
		refresh();
	}

	else if (name == bEdit.getName())
	{
		xSlider.setEnabled(bEdit);
		ySlider.setEnabled(bEdit);
		
		//refresh();
	}

	else if (name == bVisible.getName())
	{
		refresh();
	}
	else if (name == bDebug.getName())
	{
		refresh();
	}
	else if (name == bReset.getName() && bReset)
	{
		bReset = false;

		xValue = 0.5;
		yValue = 0.5;
	}
}

//--------------------------------------------------------------
void LayoutCanvas::keyPressed(ofKeyEventArgs &eventArgs)
{
	const int key = eventArgs.key;

	// modifiers
	bool mod_COMMAND = eventArgs.hasModifier(OF_KEY_COMMAND);
	bool mod_CONTROL = eventArgs.hasModifier(OF_KEY_CONTROL);
	bool mod_ALT = eventArgs.hasModifier(OF_KEY_ALT);
	bool mod_SHIFT = eventArgs.hasModifier(OF_KEY_SHIFT);

	ofLogNotice(__FUNCTION__) << " : " << key;

	//--
}