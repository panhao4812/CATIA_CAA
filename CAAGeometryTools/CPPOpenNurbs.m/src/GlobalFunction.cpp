#include "opennurbs.h"


GlobalFunction::GlobalFunction(){}

 void GlobalFunction::Print(const ON_3dPoint& pt){
	cout<<pt.x<<"/"<<pt.y<<"/"<<pt.z<<endl;
}

 void GlobalFunction::Print(const ON_3dVector& v){
	cout<<v.x<<"/"<<v.y<<"/"<<v.z<<endl;
}
 void GlobalFunction::Print(const ON_Line& line){
	if(!line.IsValid()){cout<<"invalid line"<<endl;return;}
	cout<<line.Length()<<endl;
	cout<<line.from.x<<"/"<<line.from.y<<"/"<<line.from.z<<endl;
	cout<<line.to.x<<"/"<<line.to.y<<"/"<<line.to.z<<endl;
}
 void GlobalFunction::Print(const ON_Polyline& pl){
	if(pl.size()<2){cout<<"invalid polyline"<<endl;return;}
	cout<<pl.size()<<endl;
	for(int i=0;i<pl.size();i++){
		cout<<pl[i].x<<"/"<<pl[i].y<<"/"<<pl[i].z<<endl;
	}
}
 void GlobalFunction::Print(const ON_Plane& plane){
	cout<<plane.equation[0]<<"/"<<plane.equation[1]<<"/"<<plane.equation[2]<<"/"<<plane.equation[3]<<endl;
}