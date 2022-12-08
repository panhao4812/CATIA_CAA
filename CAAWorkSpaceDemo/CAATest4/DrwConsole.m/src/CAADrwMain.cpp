#include "Function.h"

// ----------------------------------------------------------------------------

int main()
{
	// Checks arguments
	char fileName[] = "C:\\Users\\Administrator\\Desktop\\catia\\Drawing1.CATDrawing";
#pragma region //定义变量
	CATDocument* pDoc=NULL;	//不要自行释放
	CATIDftDrawing *piDftDrawing = NULL;
	CATIDftDocumentServices *piDftDocServices = NULL;
	CATIDftSheet *piDftSheet=NULL;
	CATISpecObject *piSpecObj=NULL;
	CATIDftViewMakeUp *piViewMU;
	CATIUnknownList *piUnknownList=NULL;
	IUnknown* piUnKnow=NULL;
	int	rs=0;
#pragma endregion 
#pragma region //主程序
	rs=Function :: SelectDoc(fileName,pDoc );if(rs!=0)goto release;
	if (FAILED(pDoc->QueryInterface(IID_CATIDftDocumentServices, (void **)&piDftDocServices)))goto release;
	if (FAILED(piDftDocServices->GetDrawing(IID_CATIDftDrawing, (void **)&piDftDrawing)))goto release;
	if(FAILED(piDftDrawing->GetActiveSheet(&piDftSheet)))goto release;

	piDftSheet->GetViewMakeUps(&piUnknownList);
	piUnknownList->Item(0,&piUnKnow);

	if (FAILED(piUnKnow->QueryInterface(IID_CATIDftViewMakeUp,(void **)&piViewMU)))goto release;
	piViewMU->SetScale(0.5);
#pragma endregion 
release:
#pragma region //释放变量
	/////////////////////////////////
	if (piUnKnow){piUnKnow->Release();piUnKnow=NULL;}
	if (piUnknownList){piUnknownList->Release();piUnknownList=NULL;}
	if (piViewMU){piViewMU->Release();piViewMU=NULL;}
	if (piSpecObj){piSpecObj->Release();piSpecObj=NULL;}
	if (piDftSheet){piDftSheet->Release();piDftSheet=NULL;}
	if (piDftDocServices){piDftDocServices->Release();piDftDocServices=NULL;}
	if (piDftDrawing){piDftDrawing->Release();piDftDrawing=NULL;}
	
	///////////////////////////////////////////
#pragma endregion 
	rs=Function ::SaveAndClosedDoc(fileName,pDoc );if(rs!=0)return rs;

	cout<<"Press Any Key to Countinue..."<<endl;
	cin.get();
	return 0;
}
