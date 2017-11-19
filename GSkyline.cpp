#include<iostream>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<assert.h>
#include<cstring>
#include"GSkyline.h"
#include "PointWise.h"

using namespace std;


void GSkyline::ReadFile(string filename)
{
	this->allPoints.clear();
	ifstream input;
	input.open(filename);
	if (input.fail())
	{
		cout << "Unable to open file";
	}
	string line;
	int id = 1;
	while (getline(input, line))
	{
		istringstream iss(line);
		GPoint* p = new GPoint();
		double temp;
		while (iss)
		{
			iss >> temp;
			p->v.push_back(temp);
		}
		p->id = id++;
		this->allPoints.push_back(p);
	}
	input.close();
}

bool ComparePoints(GPoint* a, GPoint* b)
{
	return (*a < *b);
}
bool ComparePointByLayer(GPoint* a, GPoint* b) {
	return a->layer < b->layer;
}
void GSkyline::SortPoints()
{
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
}

void GSkyline::ConstructingDSG()
{
	allPoints[0]->layer = 0;
	int maxlayer = 0;
	vector<GPoint*> layer;
	layer.push_back(allPoints[0]);
	layers.push_back(layer);
	allPoints[0]->isSkylinePoint = true;

	int n = allPoints.size();
	for (int i = 1; i < n; i++)
	{
		GPoint* p = allPoints[i];
		if (!(*(layers[0][layers[0].size() - 1])).isDomain(*p))
		{
			p->layer = 0;
			p->isSkylinePoint = true;
			layers[0].push_back(p);
		}
		else if ((*(layers[maxlayer][layers[layers.size() - 1].size() - 1])).isDomain(*p))
		{
			p->layer = ++maxlayer;
			p->isSkylinePoint = false;
			vector<GPoint*>layer;
			layer.push_back(p);
			layers.push_back(layer);
		}
		else
		{
			int l = 0, r = maxlayer, mid;
			while (l < r)
			{
				mid = (l + r) >> 1;
				if ((*(layers[mid][layers[mid].size() - 1])).isDomain(*p))
				{
					l = mid + 1;
				}
				else
				{
					r = mid;
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

vector<GGroup> GSkyline::Preprocessing(int k) {
	vector<GPoint*> temp;
	vector<GGroup> ret;
	int index = 0;
	for (int i = 0; i < allPoints.size(); i++) {
		GPoint* p = allPoints[i];
		if (p->layer > k) {
			break;
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
	}
	this->allPoints = temp;
	return ret;
}

int  GSkyline::PWP(int k)
{
	PWiseP PW(k, allPoints);
	return PW.PwCount;
}
long long  GSkyline::UWP(int k)
{
	UWiseP UP(k, allPoints, layers);
	return UP.resultNum;
}