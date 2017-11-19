#include <fstream>
#include <algorithm>
#include <assert.h>
#include <iostream>
#include"UnitWisePlus.h"
using namespace std;
UWiseP::UWiseP(int k, vector<GPoint*> allPoints, vector<vector<GPoint*>> layers)
{
	this->UnitWisePlus(k, allPoints, layers);
}



void UWiseP::UnitWisePlus(int k, vector<GPoint*> allPoints, vector<vector<GPoint*>> layers)
{
	this->resultNum = 0;
	vector<UnitGroup> result;
	for (int u1 = allPoints.size() - 1; u1 >= 0; u1--) {
		vector<GPoint*> points;
		points.push_back(allPoints[u1]);
		UnitGroup ug1(points);
		if ((allPoints[u1]->layer == 0) && (u1+1>=k))
		{
			long long num1 = 1;
			long long num2 = 1;
			for (int i = u1+2-k;i<=u1+1;i++)
				num1 = num1 * i;
			for (int i = 1;i<=k;i++)
				num2 = num2 * i;
			resultNum +=  num1/num2;
			break;
		}
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
			vector<UnitGroup>::iterator it;
			UnitGroup ug;
			while(true){
				it = last_layer_i_ugs.begin();
				ug = *it;
				set<GPoint*> ps = it->allParentSet;
				for (int j = ug.tail; j >= 0; j--) {
					if (ps.find(allPoints[j]) == ps.end()) {
						UnitGroup new_ug(ug);
						new_ug.insert(allPoints[j]);
						new_ug.tail = j - 1;
						if (new_ug.size == k)
							resultNum++;
						else if (new_ug.allPointSize() < k){
							if ((allPoints[j]->layer==0)&&(j>k)){
								int ii = 0;
								set<GPoint*> temp = new_ug.allParentSet;
								for (set<GPoint*>::iterator tt = temp.begin(); tt != temp.end(); tt++) {
									if ((*tt)->layer == 0)ii++;
								}
								int kk = k-1-ii;
								long long num1 = 1;
								long long num2 = 1;
								for (int ii = j+1-kk;ii<=j;ii++)
									num1 = num1 * ii;
								for (int i = 1;ii<=kk;ii++)
									num2 = num2 * ii;
								resultNum +=  num1/num2;
								break;
							}
							now_layer_i_ugs.push_back(new_ug);
						}
					}
				}
				last_layer_i_ugs.erase(it);
				if (last_layer_i_ugs.empty())
				break;
			}
			if (now_layer_i_ugs.empty())
				break;
			i++;
		}
	}
	return;
}
