#pragma once

#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"
#include "ofxGui.h"

#define SEGSPAN 20
#define WAVSPAN 100

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofTrueTypeFont font;
		ofxTrueTypeFontUC fontuc;

		std::string msg;
		std::vector<ofMesh> meshes;
		std::vector<ofPolyline> polys;

		std::vector<ofMesh> segs;
		std::vector<float> segrds;
		std::vector<float> roffs;
		int mi, mii, itermi, itermii;

		ofEasyCam cam;
		ofLight lights;

};
