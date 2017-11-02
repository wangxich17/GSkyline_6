#include"Unitgroup.h"
#include<iostream>
#include<algorithm>
#include <assert.h>

Unit::Unit(GPoint* p) {
	index = p->index;
	vector<GPoint*>::iterator it;
	for (it = p->ParentSet.begin(); it != p->ParentSet.end(); it++)
	{
		pointSet.insert(*it);
	}
	pointSet.insert(p);
	point = p;
}

UnitGroup::UnitGroup(vector<GPoint*> vp) {
	tail = INT_MAX;
	size = 0;
	for (vector<GPoint*>::iterator it = vp.begin(); it != vp.end(); it++) {
		insert(*it);
	}
}

UnitGroup::UnitGroup() {
	tail = INT_MAX;
	size = 0;
}
UnitGroup::UnitGroup(const UnitGroup& u) {
	tail = u.tail;
	size = u.size;
	allParentSet = u.allParentSet;
	unitSet = u.unitSet;
	merge = u.merge;
}

void UnitGroup::insert(GPoint* p) {
	if (unitSet.find(p) == unitSet.end()) {
		unitSet.insert(p);
		allParentSet.insert(p->ParentSet.begin(), p->ParentSet.end());
		if (tail > p->index - 1)
			tail = p->index - 1;
		merge.insert(p);
		merge.insert(p->ParentSet.begin(), p->ParentSet.end());
		size = merge.size();
	}
}

int UnitGroup::allPointSize() {
	return size;
}



bool compareById(GPoint* a, GPoint*b) {
	return a->id < b->id;
}

void UnitGroup::PrintAsc() {
	std::cout << "{";
	set<GPoint*>::iterator it = merge.begin();
	while (true)
	{
		cout << "p" << (*it)->id;
		it++;
		if (it != merge.end())
		{
			std::cout << ",";
		}
		else
		{
			break;
		}
	}
	cout << "}" << endl;
}
void UnitGroup::PrintDetail() {
	cout << "unit:";
	for (set<GPoint*>::iterator it = unitSet.begin(); it != unitSet.end(); it++) {
		cout << 'p' << (*it)->id << ":" << (*it)->index << ',';
	}
	cout << "parent:";
	for (set<GPoint*>::iterator it = allParentSet.begin(); it != allParentSet.end(); it++) {
		cout << 'p' << (*it)->id << ":" << (*it)->index << ',';
	}
	cout << "size:" << size << endl;
}
UnitGroup::~UnitGroup() {
	set<GPoint*>().swap(allParentSet);
	set<GPoint*>().swap(unitSet);
	set<GPoint*, classcomp>().swap(merge);
}
void UnitGroup::clearUnitGroup() {
	allParentSet.clear();
	unitSet.clear();
	merge.clear();
}