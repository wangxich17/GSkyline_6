//
// Created by niehao on 17-11-16.
//

#ifndef GSKYLINE_6_POINTWISE_H
#define GSKYLINE_6_POINTWISE_H
#include <vector>
#include <set>
#include <stack>
#include"GPoint.h"
#include"GGroup.h"
#include <fstream>
#include <algorithm>
#include <assert.h>
#include <iostream>

using namespace std;


class PWise {
public:
    int PwCount;

    PWise(int k, vector<GPoint *> PointCell);

    vector<vector<GGroup>> ggroups;

    void Solve(int k, GGroup &g);

    bool Vertify(GPoint* p,set<GPoint*> g);

    void PointWiseInit(int k, vector<GPoint *> allPoints);

    vector<GGroup> PointWise(int k, vector<GPoint *> allPoints);
};
#endif //GSKYLINE_6_POINTWISE_H
