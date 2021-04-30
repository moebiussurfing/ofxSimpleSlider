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
	params.add(bGui);

	ofAddListener(params.parameterChangedE(), this, &LayoutCanvas::Changed);

	xSlider.setupParam(xValue, false, false, false);//horizontal
	ySlider.setupParam(yValue, true, false, false);//vertical

	gui.setup(params);
	gui.setPosition(150, 150);

	if (bHandleSettings) {
		ofJson settings;
		settings = ofLoadJson(path_Settings);
		ofDeserialize(settings, params);
	}

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
	if (bVisible)
	{
		//border
		if (bDebug)
		{
			ofPushStyle();
			ofSetColor(0, 255);
			ofSetLineWidth(2);
			ofNoFill();
			ofDrawRectangle(r1);
			ofDrawRectangle(r2);
			ofDrawRectangle(r3);
			ofPopStyle();
		}

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

	if (bGui) gui.draw();
}

//--------------------------------------------------------------
void LayoutCanvas::refresh() {
	xSlider.setColorThumb(0);
	xSlider.setColorGlobal(0);
	xSlider.setColorSpine(0);

	ySlider.setColorThumb(0);
	ySlider.setColorGlobal(0);
	ySlider.setColorSpine(0);

	bool bSpline = false;

	//hide
	if (!bDebug) {
		xSlider.setAlphaPowerThumb(1);
		xSlider.setAlphaPowerGlobal(1);
		xSlider.setWidthThumbPick(2);
		xSlider.setDrawSpline(bSpline);
		xSlider.setDrawOutline(false);
	}
	//debug
	else {
		xSlider.setAlphaPowerThumb(1);
		xSlider.setAlphaPowerGlobal(1);
		xSlider.setWidthThumbPick(5);
		xSlider.setDrawSpline(bSpline);
		xSlider.setDrawOutline(true);
	}

	//hide
	if (!bDebug) {
		ySlider.setAlphaPowerThumb(1);
		ySlider.setAlphaPowerGlobal(1);
		ySlider.setWidthThumbPick(2);
		ySlider.setDrawSpline(bSpline);
		ySlider.setDrawOutline(false);
	}
	//debug
	else {
		ySlider.setAlphaPowerThumb(1);
		ySlider.setAlphaPowerGlobal(1);
		ySlider.setWidthThumbPick(5);
		ySlider.setDrawSpline(bSpline);
		ySlider.setDrawOutline(true);
	}
}

//--------------------------------------------------------------
void LayoutCanvas::exit() {
	if (bHandleSettings) {
		ofJson settings;
		ofSerialize(settings, params);
		bool b = ofSavePrettyJson(path_Settings, settings);
	}
}

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

		ofSetLogLevel("LayoutCanvas", bDebug ? OF_LOG_NOTICE : OF_LOG_SILENT);
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

////--------------------------------------------------------------
//void LayoutCanvas::setBool(bool b){
//		ofLogNotice(__FUNCTION__) << ofToString(b);
//}
//
////--------------------------------------------------------------
//bool LayoutCanvas::getBool(){
//	return true;
//}