#include "opennurbs.h"
ON_Polyline::ON_Polyline(): deque<ON_3dPoint>()
{}
ON_Polyline::ON_Polyline(const deque<ON_3dPoint>& src) : deque<ON_3dPoint>(src)
{}
ON_Polyline& ON_Polyline::operator=(const deque<ON_3dPoint>& src)
{
	if ( this != &src ) {
		deque<ON_3dPoint>::operator=(src);
	}
	return *this;
}
void ON_Polyline::Add(const ON_3dPoint& p)
{
	push_back(p);
}
//////////////////////////////////
ON_Polyline ON_Polyline::ComputeHull2d(vector<ON_3dPoint> nodes)
{
	ON_Polyline pl ;
	vector<int> hull;
	if (ON_Polyline::ComputeHull2d(nodes, hull)) {
		for (int i = 0; i < hull.size(); i++) {
			pl.Add(nodes[hull[i]]);
		}
	}
	return pl;
}
bool ON_Polyline::ComputeHull2d(vector<ON_3dPoint>& nodes,  vector<int>& hull) 
{
	if (nodes.empty())
	{
		cout<<"QHull points error"<<endl;
	}

	vector<bool> list;
	hull.clear();
	list.clear();

	if (nodes.size() == 0)
	{
		return false;
	}
	if (nodes.size() == 1)
	{
		return false;
	}
	if (nodes.size() == 2)
	{
		hull.push_back (0);
		hull.push_back (1);
		return true;
	}
	int num9 = nodes.size() - 1;
	for (int i = 0; i <= num9; i++)
	{
		list.push_back (false);
	}
	int num = -1;
	int item = -1;
	int num10 = nodes.size() - 1;
	for (int j = 0; j <= num10; j++)
	{
		if (nodes[j].IsValid())
		{
			num = j;
			item = j;
			break;
		}
	}
	if (num < 0)
	{
		return false;
	}
	int num11 = nodes.size() - 1;
	for (int k = 1; k <= num11; k++)
	{
		if (nodes[k].IsValid())
		{
			if (nodes[k].x < nodes[num].x)
			{
				num = k;
			}
			else if ((nodes[k].x == nodes[num].x) && (nodes[k].y < nodes[num].y))
			{
				num = k;
			}
		}
	}
	item = num;
	do
	{
		int num6 = -1;
		int num12 = nodes.size() - 1;
		for (int m = 0; m <= num12; m++)
		{
			if ((nodes[m].IsValid()) && (!list[m] && (m != item)))
			{
				if (num6 == -1)
				{
					num6 = m;
				}
				else
				{
					double num8 = ON_3dPoint::CrossProduct(nodes[m], nodes[item], nodes[num6]);
					if (num8 == 0.0)
					{
						if (ON_3dPoint::DotProduct(nodes[item], nodes[m], nodes[m]) > ON_3dPoint::DotProduct(nodes[item], nodes[num6], nodes[num6]))
						{
							num6 = m;
						}
					}
					else if (num8 < 0.0)
					{
						num6 = m;
					}
				}
			}
		}
		item = num6;
		list[item] = true;
		hull.push_back (item);
	} while (item != num);
	return true;
}


vector<ON_3dPoint>  ON_Polyline::RemoveDupPts(vector<ON_3dPoint> mypoints, double tolerance)
{
	vector<ON_3dPoint> list ;
	if (mypoints.size() > 0)
	{
		list.push_back(mypoints[0]);
		for (int i = 1; i < mypoints.size(); i++)
		{
			bool flag = true;
			ON_3dPoint pointd = mypoints[i];
			for (int j = 0; j < list.size(); j++)
			{
				if (ON_3dPoint::OrthoClose(pointd, list[j], tolerance))
				{
					flag = false;
					break;
				}
			}
			if (flag)
			{
				list.push_back(pointd);
			}
		}
	}
	return list;
}