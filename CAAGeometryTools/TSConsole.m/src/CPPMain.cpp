#include "CPPMain.h"
//std
#include <iostream.h>
#include <ios>
#include <fstream> //ofstream p;p.open("D:\\catiav5_r22\\log.txt");p.close();
#include <deque>  
#include <algorithm>  
#include <string>
#include <stdlib.h>
#include <io.h>
#include <string.h>
using namespace std;

int main(){

	ofstream fs("C:\\Users\\Administrator\\Desktop\\catia\\log.txt",ios::out);
	streambuf* pOld = cout.rdbuf(fs.rdbuf());

	cout<<"Main!"<<endl;

	ON_3dPoint p1(46, 6, 324);
	ON_3dVector p2(4, 678, 2);
	ON_3dVector p3(5, 8, 2);
	ON_Plane p(p1,p2,p3);

	cout<<p.equation[0]<<","
		<<p.equation[1]<<","
		<<p.equation[2]<<","
		<<p.equation[3]<<endl;

	cout.rdbuf(pOld);



	cin.get();
	return 0;


}