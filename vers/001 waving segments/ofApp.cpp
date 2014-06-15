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
    ofRectangle r = font.getStringBoundingBox(msg, 0, 0);
    for (int i = 0; i < msg.size(); i++) {
        ttfcs[i].simplify(0.1f);

        ofMesh m = ttfcs[i].getTessellation();
        std::vector<ofPolyline> p = ttfcs[i].getOutline();

        ofPolyline pl;

        for (int pli = 0; pli < p.size(); pli++) {
            std::vector<ofPoint> vs = p[pli].getVertices();
            for (int plvi = 0; plvi < vs.size() - 1; plvi++) {
                pl.addVertex(vs[plvi]);
            }
            pl.addVertex(vs[0]);
        }
        pl.addVertex(p[0].getVertices()[0]);

        for (int vi = 0; vi < m.getNumVertices(); vi++) {
            float x = m.getVertex(vi).x;
            float y = m.getVertex(vi).y;
            float z = m.getVertex(vi).z;

            m.setVertex(vi, ofVec3f(x - r.getWidth() / 2, -(y + r.getHeight() / 2), z));
            m.addColor(ofFloatColor::black);
        }

        meshes.push_back(m);
        polys.push_back(pl);
    }

    mi = 0;
    mii = 0;
    itermi = 1;
    itermii = 1;
}

//--------------------------------------------------------------
void ofApp::update(){
    lights.setPosition(cos(ofGetElapsedTimef() * 10.0f) * 150.0f, 0, sin(ofGetElapsedTimef() * 10.0f) * 150.0f);

    for (int itmi = 0; itmi < itermi; itmi++) {
        if (mi < meshes.size()) {
            ofMesh m = meshes[mi];
            for (int itmii = 0; itmii < itermii; itmii++) {
                if (mii < m.getNumIndices()) {
                    ofVec3f v0 = m.getVertex(m.getIndex(mii));
                    ofVec3f v1 = m.getVertex(m.getIndex(mii + 1));
                    ofVec3f v2 = m.getVertex(m.getIndex(mii + 2));

                    float r = ofRandom(-SEGSPAN / 2, SEGSPAN / 2);
                    float d = r > 0 ? r - SEGSPAN : SEGSPAN + r;
                    // float r = -SEGSPAN / 2;
                    // float d = SEGSPAN / 2;

                    ofMesh seg;
                    seg.addVertex(ofVec3f(v0.x, v0.y, v0.z + r));
                    seg.addVertex(ofVec3f(v1.x, v1.y, v1.z + r));
                    seg.addVertex(ofVec3f(v2.x, v2.y, v2.z + r));
                    seg.addVertex(ofVec3f(v0.x, v0.y, v0.z + d));
                    seg.addVertex(ofVec3f(v1.x, v1.y, v1.z + d));
                    seg.addVertex(ofVec3f(v2.x, v2.y, v2.z + d));

                    ofFloatColor fc = ofColor(ofRandom(255));
                    for (int i = 0; i < seg.getNumVertices(); i++) seg.addColor(fc);

                    seg.addTriangle(0, 1, 2);
                    seg.addTriangle(3, 4, 5);
                    seg.addTriangle(0, 1, 3);
                    seg.addTriangle(1, 3, 4);
                    seg.addTriangle(1, 2, 4);
                    seg.addTriangle(2, 4, 5);
                    seg.addTriangle(2, 0, 5);
                    seg.addTriangle(0, 5, 3);

                    segs.push_back(seg);
                    segrds.push_back(r);
                    segrds.push_back(d);
                    roffs.push_back(ofRandom(0, TWO_PI));

                    mii += 3;
                } else {
                    mi++;
                    mii = 0;
                    break;
                }
            }
        } else break;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    lights.enable();
    glEnable(GL_DEPTH_TEST);/*
    for (int i = 0; i < meshes.size(); i++) {
        meshes[i].drawWireframe();
    }*/
    for (int i = 0; i < segs.size(); i++) {
        ofPushMatrix();
        ofTranslate(0, 0, sin(roffs[i] + ofGetElapsedTimef()) * WAVSPAN);
        segs[i].draw();
        ofPopMatrix();
    }/*
    for (int i = 0; i < polys.size(); i++) {
        polys[i].draw();
    }*/
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
