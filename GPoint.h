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
<<<<<<< HEAD:GPoint.h
	int index;
	vector<GPoint *> ParentSet;             //鐖朵翰闆嗗悎
	vector<GPoint *> ChildrenSet;             //瀛╁瓙闆嗗悎
	list<GPoint*> SimpleCSet;         //children whose parent is its first parent
=======
	int index;			             
	vector<GPoint*> ParentSet;             //父亲集合
	vector<GPoint*> ChildrenSet;             //孩子集合
	list<GPoint*> SimpleCSet;         //children whose parent is its first parent 
>>>>>>> a6253a618074fe52b3502e122624ecaf6299d07e:GSkyline_5/GPoint.h
	GPoint* firstParent;              //the first parent of all Parent
	bool isSkylinePoint;
	bool isVisited;
public:
	bool isDomain(const GPoint &p);
	bool operator < (const GPoint &m)const;
};

#endif