#ifndef _GSKYLINE_H_
#define _GSKYLINE_H_
#include <vector>
#include <set>
#include <stack>
#include"GPoint.h"
#include"GGroup.h"
#include"PointWisePlus.h"
#include"UnitWisePlus.h"
using namespace std;


class GSkyline
{

public:
	vector<GPoint*> allPoints;
	vector<vector<GPoint*>> layers;
public:
	GSkyline(string filename);
	void ReadFile(string filename);
	void SortPointsByLayer();
	void SortPoints();
	void ConstructingDSG();
	void Print_layers();
	vector<GGroup> Preprocessing(int k);
	int PWP(int k);
	int UWP(int k);
};
#endif