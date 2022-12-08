#include "Function.h"

HRESULT Function ::OpenSession( char * SessionName){
	HRESULT hr=NULL;
	CATSession *pSampleSession = NULL;
	hr = ::Create_Session(SessionName,pSampleSession);
	if (FAILED(hr)){
		cout << "Create "<<SessionName<< " Failed" <<endl;
		return hr;}
	cout << "Create "<<SessionName<< " Successfully" <<endl;
	return hr;	
}
HRESULT Function ::CloseSession( char * SessionName){
	HRESULT hr=::Delete_Session(SessionName);
	if(FAILED(hr)){	
		cout << "Delete "<< SessionName<< " Failed"<<endl;
		return hr;}
	cout << "Delete "<<SessionName<<" Successfully" <<endl;
	cout<<"Press Any Key to Countinue..."<<endl;cin.get();
	return hr;	
}
HRESULT Function :: CreateDoc(CATDocument*& pDoc){
	HRESULT hr = CATDocumentServices::New("CATDrawing", pDoc);
	if (FAILED(hr) || !pDoc){
		cout << "Create Doc failed" <<endl;
		return hr;}
	cout << "Create Doc Successfully" <<endl;
	return hr;
}
HRESULT Function ::SelectDoc(const char *fileName,CATDocument*& pDoc ){
	HRESULT hr=CATDocumentServices::OpenDocument(fileName, pDoc);
	if (FAILED(hr) || !pDoc){
		cout << "Open File failed" <<endl;
		return hr;}
	cout << "Open File Successfully" <<endl;
	return hr;
}
HRESULT Function ::SaveDoc(const char * fileNameOut,CATDocument*& pDoc){
	HRESULT hr = CATDocumentServices::SaveAs(*pDoc,fileNameOut);
	if (FAILED(hr)){
		cout << "Save Doc failed" <<endl;
		return hr;}
	cout << "Save Doc Successfully" <<endl;
	return hr;
}
HRESULT Function ::CloseDoc(CATDocument*& pDoc){
	HRESULT hr=CATDocumentServices::Remove (*pDoc);
	if (FAILED(hr)){
		cout << "Remove Doc failed" <<endl;
		return hr;}
	cout << "Remove Doc Successfully" <<endl;
	return hr;
}
void Function :: PrintType(CATBaseUnknown *pBase){
	CATISpecObject *piSpecObj=NULL;
	if (SUCCEEDED(pBase->QueryInterface(IID_CATISpecObject,(void **)&piSpecObj)))
	{
		cout<< piSpecObj->GetType() <<endl;
	}else{
		cout << "CATBaseUnknown_var"<<endl;
	}
	if(piSpecObj)piSpecObj->Release();piSpecObj=NULL;
}

void Function :: PrintCATListOfDouble(CATListOfDouble& iCoordList){
	cout<< "#PrintList"<<endl;
	for (int j=1;j<=iCoordList.Size();j++)
	{
		cout<<"["<<j<<"]"<<iCoordList[j]<<endl;
	}
	cout<< "#EndPrint"<<endl;
}
HRESULT Function::SelectDftDrawing(CATDocument*& pDoc,CATIDftDrawing*& piDftDrawing ){
	CATIDftDocumentServices *piDftDocServices = NULL;
	HRESULT hr =NULL;
	hr=pDoc->QueryInterface(IID_CATIDftDocumentServices, (void **)&piDftDocServices);
	if(FAILED(hr))return hr;
	hr=piDftDocServices->GetDrawing(IID_CATIDftDrawing, (void **)&piDftDrawing);
	if (FAILED(hr) || !piDftDrawing)
	{cout<<"SelectDftDrawing Failed"<<endl;}
	else{cout<<"SelectDftDrawing Successfully"<<endl;}
	if(piDftDocServices)piDftDocServices->Release();piDftDocServices=NULL;
	return hr;
}
HRESULT Function::SelectDrawing(CATDocument*& pDoc,CATIDrawing*& piDrawing){
	CATIDftDocumentServices *piDftDocServices = NULL;
	HRESULT hr =NULL;
	hr=pDoc->QueryInterface(IID_CATIDftDocumentServices, (void **)&piDftDocServices);
	if(FAILED(hr))return hr;
	hr=piDftDocServices->GetDrawing(IID_CATIDrawing, (void **)&piDrawing);
	if (FAILED(hr) || !piDrawing)
	{cout<<"SelectDrawing Failed"<<endl;}
	else{cout<<"SelectDrawing Successfully"<<endl;}
	if(piDftDocServices)piDftDocServices->Release();piDftDocServices=NULL;
	return hr;
}