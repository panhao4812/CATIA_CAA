///*
#include "Function.h"

// ----------------------------------------------------------------------------
int Function::main1(){
#pragma region //定义变量
	///////////////////////////
	CATUnicodeString fileName="C:\\Users\\Administrator\\Desktop\\catia\\CAATest.CATDrawing";	
	int rs=0;
	CATIDrawing* piDrawing=NULL;
	CATDocument* pDoc=NULL;
	CATIDftView*  ipiMotherView=NULL;
	CATIDftView*  opiSectionView=NULL;
	CATIDftGenViewFactory *piDftGenViewFact = NULL;

	CATLISTP(CATMathPoint2D)  iListOfPoints;	
	CATMathPoint2D *pP1=new CATMathPoint2D(10,90);
	CATMathPoint2D *pP2=new CATMathPoint2D(10,20);
	CATMathPoint2D *pP3=new CATMathPoint2D(40,-30);
	CATMathPoint2D *pP4=new CATMathPoint2D(40,-110);
	CATISheet_var spSheet ;
	CATIView_var spCurrentView;
	/////////////////////////////////////////////
#pragma endregion 
#pragma region //主程序
	rs=Function :: SelectDoc(fileName,pDoc );if(rs!=0) goto release;
	rs=Function :: SelectDrawing(pDoc,piDrawing );if(rs!=0) goto release;
	spSheet = piDrawing->GetCurrentSheet();if (NULL_var==spSheet) goto release;
	spCurrentView = spSheet->GetCurrentView();if (NULL_var==spCurrentView)goto release;
	if FAILED(spSheet->QueryInterface(IID_CATIDftGenViewFactory,(void **)&piDftGenViewFact))goto release;
	if FAILED(spCurrentView->QueryInterface(IID_CATIDftView,(void **)&ipiMotherView))goto release	;
	iListOfPoints.Append(pP1);iListOfPoints.Append(pP2);
	iListOfPoints.Append(pP3);iListOfPoints.Append(pP4);
	double  iptOrigin[2]={0,0};
	CATDftViewType  iViewType=DftSectionView;	
	int  iViewProfile=0;
	int  iSideToDraw=0;	
	piDftGenViewFact->CreateSectionView(iptOrigin,iViewType,iViewProfile,iSideToDraw,iListOfPoints,ipiMotherView,&opiSectionView);
#pragma endregion 
release:
#pragma region //释放指针
	/////////////////////////////////
	if(piDrawing)piDrawing->Release();piDrawing=NULL;	
	if(piDftGenViewFact)piDftGenViewFact->Release();piDftGenViewFact=NULL;
	if(ipiMotherView)ipiMotherView->Release();ipiMotherView=NULL;
	if(opiSectionView)opiSectionView->Release();opiSectionView=NULL;
	//delete pP1,pP2,pP3,pP4;	
	/////////////////////////////////
#pragma endregion 
	rs=Function ::SaveAndClosedDoc(fileName,pDoc );if(rs!=0)return rs;
	cout<<"Press Any Key to Countinue..."<<endl;
	cin.get();
	return rs;
}
