#ifndef WHIP_H
#define WHIP_H

#include "ofMain.h"

class whip {
public:
    float x, y, z; // where the whip is rooted
    float l; // length of each segment
    int nseg; // total # of segments

    ofVec3f r; // the rotation values of the whip itself
    ofVec3f gr; // the ideal rotation values of all segments
    std::vector<ofVec3f> segs; // segments = ofVec3f(rx, ry, rz); 0 = root, nseg - 1 = tip

    whip(float cx, float cy, float cz, float cl, int cnseg) {
        x = cx;
        y = cy;
        z = cz;
        l = cl;
        nseg = cnseg;

        r = ofVec3f(0, 0, 0);
        gr = ofVec3f(0, 0, 0);

        init();
    }

    void init() {
        segs.clear();

        for (int i = 0; i < nseg; i++) {
            segs.push_back(ofVec3f(0, 0, 0));
        }
    }

    void update() {
        for (int i = 0; i < segs.size(); i++) {
            segs[i] += (gr - segs[i]) / 10.0f;
        }
    }

    void draw() {
        ofSetColor(0);
        ofNoFill();

        ofPushMatrix();

        ofTranslate(x, y, z);
        ofRotateX(r.x);
        ofRotateY(r.y);
        ofRotateZ(r.z);
        for (int i = 0; i < segs.size(); i++) {
            ofRotateX(segs[i].x);
            ofRotateY(segs[i].y);
            ofRotateZ(segs[i].z);
            ofLine(0, 0, 0, 0, 0, l);
            ofTranslate(0, 0, l);
        }

        ofPopMatrix();
    }
};

#endif // WHIP_H
