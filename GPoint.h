#ifndef _GPOINT_H_
#define _GPOINT_H_
#include <vector>
#include <set>
#include <list>
#include"GPoint.h"

using namespace std;

class GPoint
{
public:
	vector<double> v;
	int layer;
	int id;
	int index;
	vector<GPoint *> ParentSet;             //父亲集合
	vector<GPoint *> ChildrenSet;             //孩子集合
	list<GPoint*> SimpleCSet;         //children whose parent is its first parent
	GPoint* firstParent;              //the first parent of all Parent
	bool isSkylinePoint;
	bool isVisited;
public:
	bool isDomain(const GPoint &p);
	bool operator < (const GPoint &m)const;
};

#endif