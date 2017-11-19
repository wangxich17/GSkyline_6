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
	long long resultNum;
	UWiseP(int k, vector<GPoint*> allPoints, vector<vector<GPoint*>> layers);
	void UnitWisePlus(int k, vector<GPoint*> allPoints, vector<vector<GPoint*>> layers);
};
#endif