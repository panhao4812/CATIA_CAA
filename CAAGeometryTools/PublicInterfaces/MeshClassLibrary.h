#ifndef MeshClassLibrary_H
#define MeshClassLibrary_H

#include <iostream.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <deque>  
#include <vector>  
#include <sstream>
#include "CPPOpenNurbs.h"
using namespace std;
#include "opennurbs.h"


class IndexPair;
class BasicVertice;

class ExportedByCPPOpenNurbs BasicVertice{
public:
	ON_3dPoint pos;
	bool dead;
	deque<int> refer;
	double energy;
public:
	BasicVertice(const ON_3dPoint& p);
	BasicVertice(const ON_3dPoint& p,int index);
	void Add(int i);
	bool equalTo(const ON_3dPoint& p);
	void CreateCollection(vector<ON_Line> x, vector<IndexPair>& id, vector<BasicVertice>& vs);
};

class ExportedByCPPOpenNurbs IndexPair{
public :
	int I;int J;
public :
	IndexPair( int a=0, int b=0){I=a;J=b;}
};
#endif