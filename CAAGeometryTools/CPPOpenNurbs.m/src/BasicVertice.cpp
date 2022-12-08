
#include <MeshClassLibrary.h>


BasicVertice:: BasicVertice(const ON_3dPoint& p)
{
	pos = p;
	dead=false;
	energy=0;
}
BasicVertice:: BasicVertice(const ON_3dPoint& p, int index)
{
	pos = p;
	dead=false;
	energy=0;
	refer.push_back(index);
}
void BasicVertice::Add(int i)
{
	refer.push_back(i);
}
bool BasicVertice::equalTo(const ON_3dPoint& p)
{
	if (pos.DistanceTo(p) < 0.001) { return true; }
	return false;
}
/// //////////////////static
void BasicVertice::CreateCollection(vector<ON_Line> x, vector<IndexPair>& id, vector<BasicVertice>& vs)
{
	id.push_back( IndexPair(0, 1));
	vs.push_back( BasicVertice(x[0].from, 1));
	vs.push_back( BasicVertice(x[0].to, 0));
	for (int i = 1; i < x.size(); i++)
	{
		bool sign1 = true;
		bool sign2 = true;
		int a = 0, b = 0;
		for (int j = 0; j < vs.size(); j++)
		{
			if (vs[j].equalTo(x[i].from)) { sign1 = false; a = j; }
			if (vs[j].equalTo(x[i].to)) { sign2 = false; b = j; }
			if (!sign1 && !sign2) { break; }
		}
		if (sign1) { vs.push_back( BasicVertice(x[i].from)); a = vs.size() - 1; }
		if (sign2) { vs.push_back( BasicVertice(x[i].to)); b = vs.size() - 1; }
		vs[a].Add(b); vs[b].Add(a);
		id.push_back(IndexPair(a, b));
	}
}