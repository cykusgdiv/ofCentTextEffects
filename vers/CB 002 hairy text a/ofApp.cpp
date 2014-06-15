#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(800, 600);
    ofBackground(255);

    cam.setDistance(500);

    lights.setAmbientColor(ofFloatColor::black);
    lights.setDiffuseColor(ofFloatColor::white);
    lights.setSpecularColor(ofFloatColor::white);

    font.loadFont("segoeui.ttf", 256, true, true, true);

    msg = "grow";

    std::vector<ofTTFCharacter> ttfcs = font.getStringAsPoints(msg);
    rect = font.getStringBoundingBox(msg, 0, 0);
    for (int i = 0; i < msg.size(); i++) {
        ttfcs[i].simplify(0.1f);

        ofMesh m = ttfcs[i].getTessellation();
        std::vector<ofPolyline> p = ttfcs[i].getOutline();

        ofPolyline pl;

        for (int pli = 0; pli < p.size(); pli++) {
            std::vector<ofPoint> vs = p[pli].getVertices();
            for (int plvi = 0; plvi < vs.size(); plvi++) {
                pl.addVertex(vs[plvi].x - rect.getWidth() / 2, -(vs[plvi].y + rect.getHeight() / 2), vs[plvi].z);
            }
                pl.addVertex(vs[0].x - rect.getWidth() / 2, -(vs[0].y + rect.getHeight() / 2), vs[0].z);
        }
        ofVec3f v = p[0].getVertices()[0];
        pl.addVertex(v.x - rect.getWidth() / 2, -(v.y + rect.getHeight() / 2), v.z);

        for (int vi = 0; vi < m.getNumVertices(); vi++) {
            float x = m.getVertex(vi).x;
            float y = m.getVertex(vi).y;
            float z = m.getVertex(vi).z;

            m.setVertex(vi, ofVec3f(x - rect.getWidth() / 2, -(y + rect.getHeight() / 2), z));
            m.addColor(ofFloatColor::black);
        }

        meshes.push_back(m);
        polys.push_back(pl);
    }

    cx = 0;
    cy = 0;
    u = 10;
    iterxy = 50;
}

//--------------------------------------------------------------
void ofApp::update(){
    float mx = ofGetMouseX() - ofGetWindowWidth() / 2;
    float my = -(ofGetMouseY() - ofGetWindowHeight() / 2);

    lights.setPosition(cos(ofGetElapsedTimef() * 10.0f) * 150.0f, 0, sin(ofGetElapsedTimef() * 10.0f) * 150.0f);

    for (int it = 0; it < iterxy; it++) {
        if (cy < rect.getHeight() * 2) {
            if (cx < rect.getWidth()) {
                for (int i = 0; i < polys.size(); i++) {
                    float tx = cx - rect.getWidth() / 2;
                    float ty = cy - (rect.getHeight() * 2) / 2;

                    if (polys[i].inside(tx, ty)) {
                        whips.push_back(whip(tx, ty, 0, 10, 10));
                        break;
                    }
                }
                cx += u;
            } else {
                cy += u;
                cx = -u / 2 * ((cy / u) % 2);
            }
        } else break;
    }

    for (int i = 0; i < whips.size(); i++) {
        float wmd = ofDist(mx, my, whips[i].x, whips[i].y);
        if (wmd < 100.0f) {
            float ga = atan2(whips[i].y - my, whips[i].x - mx) * 180.0f / PI;
            ga += ga > whips[i].r.z ? 0 : 360.0f;
            whips[i].r.z += (ga - whips[i].r.z) / 10.0f;
            whips[i].r.z = fmodf(whips[i].r.z, 360.0f);
        } else {
            whips[i].r.z -= whips[i].r.z / 10.0f;
        }

        float gry = 10.0f * (wmd < 100.0f ? (100.0f - wmd) : 0) / 100.0f;
        whips[i].gr = ofVec3f(0, gry, 0);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    lights.enable();
    glEnable(GL_DEPTH_TEST);/*
    for (int i = 0; i < meshes.size(); i++) {
        meshes[i].drawWireframe();
    }
    for (int i = 0; i < polys.size(); i++) {
        polys[i].draw();
    }*/
    for (int i = 0; i < whips.size(); i++) {
        whips[i].update();
        whips[i].draw();
    }
    glDisable(GL_DEPTH_TEST);
    lights.disable();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
