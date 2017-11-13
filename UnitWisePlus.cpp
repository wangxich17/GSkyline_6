#include <fstream>
#include <algorithm>
#include <assert.h>
#include <iostream>
#include"UnitWisePlus.h"
using namespace std;
UWiseP::UWiseP(int k, bool optimization, vector<GPoint*> allPoints, vector<vector<GPoint*>> layers)
{
	this->UnitWisePlus(k, optimization, allPoints, layers);
}


UnitGroup UWiseP::getGLast(UnitGroup ug, vector<GPoint*> allPoints) {
	set<GPoint*>::iterator it = ug.unitSet.begin();
	GPoint* lastUnit = *it;
	UnitGroup ret;
	for (; it != ug.unitSet.end(); it++) {
		ret.insert(*it);
		if ((*it)->index < lastUnit->index)
			lastUnit = *it;
	}
	for (int i = lastUnit->index - 1; i >= 0; i--)
		ret.insert(allPoints[i]);
	return ret;
}


void UWiseP::UnitWisePlus(int k, bool optimization, vector<GPoint*> allPoints, vector<vector<GPoint*>> layers)
{
	this->resultNum = 0;
	vector<UnitGroup> result;
	for (int u1 = allPoints.size() - 1; u1 >= 0; u1--) {
		vector<GPoint*> points;
		points.push_back(allPoints[u1]);
		UnitGroup ug1(points);
		if (u1 + 1 == k) {
			resultNum++;
			break;
		}
		vector<UnitGroup> now_layer_i_ugs;
		vector<UnitGroup> last_layer_i_ugs;
		now_layer_i_ugs.push_back(ug1);

		int i = 2;
		while (true) {
			vector<UnitGroup>().swap(last_layer_i_ugs);
			last_layer_i_ugs = now_layer_i_ugs;
			vector<UnitGroup>().swap(now_layer_i_ugs);
			now_layer_i_ugs.clear();
			for (vector<UnitGroup>::iterator it = last_layer_i_ugs.begin(); it != last_layer_i_ugs.end(); it++) {
				UnitGroup ug = *it;
				if (optimization) {
					UnitGroup last = getGLast(ug, allPoints);
					if (last.size == k) {
						resultNum++;
						return;
					}
					else if (last.size < k)
						return;
				}
				set<GPoint*> ps = it->allParentSet;
				for (int j = ug.tail; j >= 0; j--) {
					if (ps.find(allPoints[j]) == ps.end()) {
						UnitGroup new_ug(ug);
						new_ug.insert(allPoints[j]);
						new_ug.tail = j - 1;
						if (new_ug.size == k)
							resultNum++;
						else if (new_ug.allPointSize() < k)
							now_layer_i_ugs.push_back(new_ug);
					}
				}
			}
			if (now_layer_i_ugs.empty())
				break;
			i++;
		}
	}
	return;
}
