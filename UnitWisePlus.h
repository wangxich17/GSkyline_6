#ifndef _UnitWisePLUS_H_
#define _UnitWisePLUS_H_
#include <vector>
#include <set>
#include <stack>
#include"GPoint.h"
#include"UnitGroup.h"
#include"GGroup.h"
using namespace std;
class UWiseP
{
public:
	int resultNum;
	UWiseP(int k, bool optimization, vector<GPoint*> allPoints, vector<vector<GPoint*>> layers);
	void UnitWisePlus(int k, bool optimization, vector<GPoint*> allPoints, vector<vector<GPoint*>> layers);
	UnitGroup getGLast(UnitGroup p, vector<GPoint*> allPoints);
};
#endif