#ifndef _UNITGROUP_H_
#define _UNITGROUP_H_
#include<set>
#include"GPoint.h"

class Unit
{
public:
	int index;
	set<GPoint*> pSet;
	set<GPoint*> pointSet;
	GPoint* point;
public:
	Unit(GPoint* p);
};

struct classcomp
{
	bool operator()(GPoint* a, GPoint* b) {
		return a->id < b->id;
	}
};

class UnitGroup {
public:
	set<GPoint*> unitSet;
	set<GPoint*> allParentSet;
	set<GPoint*, classcomp> merge;
	int tail;
	int size;
public:
	UnitGroup();
	UnitGroup(const UnitGroup& u);
	UnitGroup(vector<GPoint*>);
	~UnitGroup();
	void clearUnitGroup();
	void insert(GPoint* p);
	void Print();
	void PrintAsc();
	void UnitGroup::PrintDetail();
	int allPointSize();
};
#endif