#pragma once
#ifndef _POINTWISEPLUS_H_
#define _POINTWISEPLUS_H_
#include <vector>
#include <set>
#include <stack>
#include"GPoint.h"
#include"GGroup.h"
using namespace std;


class PWiseP
{
public:
	int PointWiseCount;
	PWiseP(int k, vector<GPoint*> allPoints);
	void PointWisePlus(int k, vector<GPoint*> allPoints);
	void Solve(GGroup & g, int k);
};
#endif