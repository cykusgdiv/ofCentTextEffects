#pragma once

#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"
#include "ofxGui.h"

#include "whip.h"

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
		ofRectangle rect;
		int u, iterxy;

		std::string msg;
		std::vector<ofMesh> meshes;
		std::vector<ofPolyline> polys;
		std::vector<whip> whips;

		ofEasyCam cam;
		ofLight lights;

		int cx, cy;

};
