#include "GSkyline.h"
#include <fstream>
#include <algorithm>
#include <assert.h>
#include <iostream>
void GGroup::CalculateCS()
{
	ChildSet.clear();
	set<GPoint*>::iterator it;
	for (it = pointSet.begin(); it != pointSet.end(); it++)
	{
		vector<GPoint*>::iterator cSetIt;
		for (cSetIt = (*it)->ChildrenSet.begin(); cSetIt != (*it)->ChildrenSet.end(); cSetIt++)
		{
			ChildSet.insert(*cSetIt);
		}
	}
}

bool GGroup::VerifyPoint(GPoint* p)
{
	if (p->isSkylinePoint)
		return true;
	for (vector<GPoint*>::iterator it = p->ParentSet.begin(); it != p->ParentSet.end(); it++)
	{
		GPoint* q = *it;
		if (pointSet.find(q) == pointSet.end())
		{
			return false;
		}
	}
	return true;
}
