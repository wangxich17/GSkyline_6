#include "PointWisePlus.h"
#include <fstream>
#include <algorithm>
#include <assert.h>
#include <iostream>
using namespace std;
PWiseP::PWiseP(int k, vector<GPoint*> allPoints)
{
	this->PointWisePlus(k, allPoints);
}
void PWiseP::PointWisePlus(int k, vector<GPoint*> allPoints)
{
	this->PointWiseCount = 0;
	int len = allPoints.size();
	GPoint* root = new GPoint();
	for (int i = len - 1; i >= 0; i--) {
		GPoint *p = allPoints[i];
		int player = p->layer - 1;
		if (player == -1) {
			p->firstParent = root;
			root->SimpleCSet.push_front(p);
		}
		else {
			GPoint *parent = NULL;
			for (vector<GPoint*>::iterator it = p->ParentSet.begin(); it != p->ParentSet.end(); it++) {
				if ((*it)->layer == player) {
					if (parent == NULL) {
						parent = *it;
					}
					else if ((*it)->index < parent->index) {
						parent = *it;
					}
				}
			}
			p->firstParent = parent;
			if (parent) {
				parent->SimpleCSet.push_front(p);
			}
		}
	}

	//breadth first

	GGroup g;
	g.pointSet.insert(root);
	g.pointStack.push_back(root);
	Solve(g, k);
}

void  PWiseP::Solve(GGroup &g, int k) {
	set<GPoint*> parentPoints;
	for (vector<GPoint*>::iterator it = g.pointStack.begin() + 1; it != g.pointStack.end(); it++) {
		parentPoints.insert(*it);
		for (vector<GPoint*>::iterator ij = (*it)->ParentSet.begin(); ij != (*it)->ParentSet.end(); ij++) {
			parentPoints.insert(*ij);
		}

	}

	int psize = parentPoints.size();
	GPoint* lastPoint = g.pointStack[g.pointStack.size() - 1];
	for (list<GPoint*>::iterator it = (lastPoint->SimpleCSet).begin(); it != lastPoint->SimpleCSet.end(); it++) {
		int cpsize = psize;
		if (parentPoints.find(*it) == parentPoints.end()) {
			cpsize++;
		}
		for (vector<GPoint*>::iterator ik = (*it)->ParentSet.begin(); ik != (*it)->ParentSet.end(); ik++) {
			if (parentPoints.find(*ik) == parentPoints.end()) {
				cpsize++;

			}
		}
		if (cpsize > k) {
			continue;
		}
		else if (cpsize == k && g.pointStack.size() == k) {

			GGroup ng;
			ng.pointSet.insert(parentPoints.begin(), parentPoints.end());
			ng.pointSet.insert(*it);
			for (vector<GPoint*>::iterator ik = (*it)->ParentSet.begin(); ik != (*it)->ParentSet.end(); ik++) {
				ng.pointSet.insert(*ik);
			}
			PointWiseCount++;
			continue;

		}

		else {
			g.pointStack.push_back(*it);
			Solve(g, k);
			g.pointStack.pop_back();
		}
	}
	// iterator all siblings.
	GPoint * parent = lastPoint->firstParent;
	while (parent) {
		if (parent->SimpleCSet.size() > 0) {
			list<GPoint*>::reverse_iterator it = parent->SimpleCSet.rbegin();

			while ((*it) != lastPoint) {
				//
				int cpsize = psize;
				if (parentPoints.find(*it) == parentPoints.end()) {
					cpsize++;
				}
				for (vector<GPoint*>::iterator ik = (*it)->ParentSet.begin(); ik != (*it)->ParentSet.end(); ik++) {
					if (parentPoints.find(*ik) == parentPoints.end()) {
						cpsize++;
					}
				}
				if (cpsize > k) {
					it++;
					continue;
				}
				else if (cpsize == k && g.pointStack.size() == k) {
					GGroup ng;
					ng.pointSet.insert(parentPoints.begin(), parentPoints.end());
					ng.pointSet.insert(*it);
					for (vector<GPoint*>::iterator ik = (*it)->ParentSet.begin(); ik != (*it)->ParentSet.end(); ik++) {
						ng.pointSet.insert(*ik);
					}
					PointWiseCount++;
					it++;
					continue;

				}

				else {
					g.pointStack.push_back(*it);
					Solve(g, k);
					g.pointStack.pop_back();
				}
				it++;
			}
		}
		lastPoint = parent;
		parent = parent->firstParent;
	}
}