#include "GSkyline.h"
#include <fstream>
#include <algorithm>
#include <assert.h>
#include <iostream>
using namespace std;

bool ComparePoints(GPoint* a, GPoint* b)
{
	return (*a < *b);
}
bool ComparePointByLayer(GPoint* a, GPoint* b) {
	return a->layer < b->layer;
}
void GSkyline::SortPoints()
{
	//将点集排序
	sort(this->allPoints.begin(), this->allPoints.end(), ComparePoints);
}
void GSkyline::SortPointsByLayer() {
	sort(this->allPoints.begin(), this->allPoints.end(), ComparePointByLayer);
	for (int i = 0; i < allPoints.size(); i++)
		allPoints[i]->index = i;
}
GSkyline::GSkyline(string filename)
{
	this->ReadFile(filename);
	this->SortPoints();
	this->ConstructingDSG();
	this->SortPointsByLayer();
	//this->Print_layers();
}

void GSkyline::ReadFile(string filename)
{
	this->allPoints.clear();
	ifstream ifile(filename);
	char buf[100];
	int id = 1;
	while (!ifile.eof())
	{
		ifile.getline(buf, 100);
		string str(buf);
		int index;
		GPoint* p = new GPoint();

		while ((index = str.find_first_of(' ')) >= 0)
		{
			string str1 = str.substr(0, index);
			p->v.push_back(atof(str1.c_str()));
			str = str.substr(index + 1);
		}
		p->v.push_back(atof(str.c_str()));
		p->id = id++;
		if (p->v.size() >= 2) {
			this->allPoints.push_back(p);
		}

	}
}


void GSkyline::ConstructingDSG()
{
	if (allPoints.size()) {
		allPoints[0]->layer = 0;
		allPoints[0]->isSkylinePoint = true;
		vector<GPoint*> layer;
		layer.push_back(allPoints[0]);
		layers.push_back(layer);
		int maxlayer = 0;
		for (int i = 1; i < allPoints.size(); i++)
		{
			GPoint* p = allPoints[i];
			if (!(*(layers[0][layers[0].size() - 1])).isDomain(*p))
			{
				p->layer = 0;
				p->isSkylinePoint = true;
				layers[0].push_back(p);
			}
			else if ((*(layers[layers.size() - 1][layers[layers.size() - 1].size() - 1])).isDomain(*p))
			{
				p->layer = ++maxlayer;
				p->isSkylinePoint = false;
				vector<GPoint*>layer;
				layer.push_back(p);
				layers.push_back(layer);
			}
			else
			{
				//使用二分查找法
				int l = 0, r = maxlayer, m;
				while (l < r)
				{
					m = (l + r) >> 1;
					if ((*(layers[m][layers[m].size() - 1])).isDomain(*p))
					{
						l = m + 1;
					}
					else
					{
						r = m;
					}
				}
				p->layer = r;
				p->isSkylinePoint = false;
				layers[l].push_back(p);

			}



		}
		for (int i = 0; i < layers.size(); i++)
		{
			for (int j = 0; j < layers[i].size(); j++)
			{
				GPoint * p = layers[i][j];
				for (int k = 0; k < i; k++)
				{
					for (int s = 0; s < layers[k].size(); s++)
					{
						if (layers[k][s]->isDomain(*p))
						{
							layers[k][s]->ChildrenSet.push_back(p);
							p->ParentSet.push_back(layers[k][s]);
						}
					}
				}
			}
		}
	}
}

vector<GGroup> GSkyline::Preprocessing(int k) {
	vector<GPoint*> temp;
	vector<GGroup> ret;
	int index = 0;
	for (vector<GPoint*>::iterator it = allPoints.begin(); it != allPoints.end(); it++) {
		GPoint* p = *it;
		if (p->layer > k) {
			//break;
			//remove p from its parent

			continue;
		}
		if (p->ParentSet.size() + 1 == k) {
			GGroup ng;
			ng.pointSet.insert(p->ParentSet.begin(), p->ParentSet.end());
			ng.pointSet.insert(p);
			ret.push_back(ng);
		}
		else if (p->ParentSet.size() + 1 < k) {
			p->index = index++;
			temp.push_back(p);
		}
		//if the size of unit (include point and its parent) is greater than k,delete
	}
	this->allPoints = temp;
	return ret;
}
void GSkyline::Print_layers()
{
	for (int i = 0; i < layers.size(); i++)
	{
		cout << i << " layer:" << endl;
		for (int j = 0; j < layers[i].size(); j++)
		{
			cout << "p" << layers[i][j]->id << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < allPoints.size(); i++)
	{
		//
		cout << "p" << allPoints[i]->id << "'s children: ";
		for (int j = 0; j < allPoints[i]->ChildrenSet.size(); j++)
		{
			cout << "p" << allPoints[i]->ChildrenSet[j]->id << " ";
		}
		cout << endl;
	}
}

int  GSkyline::PWP(int k)
{
	PWiseP PW(k, allPoints);
	return PW.PointWiseCount;
}
int  GSkyline::UWP(int k)
{
	UWiseP UP(k, false, allPoints, layers);
	return UP.resultNum;
}