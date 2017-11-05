#include <vector>
#include <set>
#include <stack>
#include"GPoint.h"
#include"GGroup.h"
#include <fstream>
#include <algorithm>
#include <assert.h>
#include <iostream>

using namespace std;


class PWiseP
{
public:
	int PwCount;
	PWiseP(int k, vector<GPoint*> allPoints);
	GGroup PointWiseInit(int k, vector<GPoint*> allPoints);
	void Solve( int k,GGroup & g);
};