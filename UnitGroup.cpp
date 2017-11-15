#include"UnitGroup.h"
#include<iostream>
#include<algorithm>
#include <assert.h>
#include <climits>




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
UnitGroup::UnitGroup(vector<GPoint*> vp) {
	tail = INT_MAX;
	size = 0;
	for (vector<GPoint*>::iterator it = vp.begin(); it != vp.end(); it++) {
		insert(*it);
	}
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