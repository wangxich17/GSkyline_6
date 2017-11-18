//
// Created by niehao on 17-11-16.
//

#include "PointWise.h"

using namespace std;

PWise::PWise(int k, vector<GPoint *> PointCell) {
    this->PwCount = this->PointWise(k, PointCell).size();
}

vector<GGroup> PWise::PointWise(int k, vector<GPoint *> PointCell) {
    vector<GGroup> gs;
    if (k == 0) {
        GPoint root;
        GGroup gGroup_r;
        gGroup_r.tail = 0;
        gGroup_r.maxLayer = 0;
        gs.push_back(gGroup_r);
        return gs;
    }
    gs = this -> PointWise(k-1,PointCell);
    vector<GGroup> gk;
    for (vector<GGroup>::iterator it = gs.begin(); it < gs.end(); it++) {
        it->CalculateCS();
        for (int ig = it->tail; ig < PointCell.size(); ig++) {
            GPoint *p = PointCell[ig];
            if ((p->isSkylinePoint
                 || it->ChildSet.find(p) != it->ChildSet.end())
                && p->layer < (it->maxLayer + 2)) {
                if (this->Vertify(p, it->pointSet)) {
                    GGroup gt;
                    gt.pointSet.insert(it->pointSet.begin(), it->pointSet.end());
                    gt.pointSet.insert(p);
                    gt.tail = ig + 1;
                    gt.maxLayer = it->maxLayer > p->layer ? it->maxLayer : p->layer;
                    gk.push_back(gt);
                }
            }
        }
    }
    gs.clear();
    return gk;
}


bool PWise::Vertify(GPoint *p, set<GPoint *> g) {
    if (p->isSkylinePoint)
        return true;
    vector<GPoint *> parent = p->ParentSet;
    for (int i = 0; i < parent.size(); i++) {
        if (g.find(parent[i]) == g.end())
            return false;
    }
    return true;
}
