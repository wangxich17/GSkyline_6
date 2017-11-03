#include "GPoint.h"

bool GPoint::isDomain(const GPoint &p)
{
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i] > p.v[i])
		{
			return false;
		}
	}
	return true;
}

bool GPoint::operator < (const GPoint &m)const
{

	for (int i = 0; i < v.size(); i++)
	{
		if (v[i] < m.v[i])
		{
			return true;
		}
		else if (v[i] > m.v[i])
		{
			return false;
		}
	}
	return false;
}
