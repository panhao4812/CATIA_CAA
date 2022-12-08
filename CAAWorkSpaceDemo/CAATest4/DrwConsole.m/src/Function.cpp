#include "Function.h"
int Function :: CreateDoc(CATDocument*& pDoc){
	CATSession *pSampleSession = NULL;
	HRESULT hr=::Create_Session("SampleSession",pSampleSession);
	if (FAILED(hr)){
		cout << "Create_Session failed" <<endl;
		return 1001;}
	hr = CATDocumentServices::New("CATDrawing", pDoc);
	if (FAILED(hr) || !pDoc){
		::Delete_Session("SampleSession");
		cout << "Create failed" <<endl;
		return 1002;}
	cout << "Create Successfully" <<endl;
	return 0;
}

int Function ::SelectDoc(const char *fileName,CATDocument*& pDoc ){
	CATSession *pSampleSession = NULL;
	HRESULT hr = ::Create_Session("SampleSession",pSampleSession);
	if (FAILED(hr)){
		cout << "Create_Session failed" <<endl;
		return 1021;}
	if (!SUCCEEDED(CATDocumentServices::OpenDocument(fileName, pDoc)))
	{::Delete_Session("SampleSession");
	cout << "Open_file failed" <<endl;
	return 1022;}
	cout << "Select Successfully" <<endl;
	return 0;

}
int Function ::SaveAndClosedDoc(const char * fileNameOut,CATDocument*& pDoc){
	HRESULT hr = CATDocumentServices::SaveAs(*pDoc,fileNameOut);
	if (FAILED(hr)){
		cout << "Create_Session failed" <<endl;
		return 1031;}
	CATDocumentServices::Remove (*pDoc);	
	if(FAILED(::Delete_Session("SampleSession"))){	
		cout << "Delete_Session failed" <<endl;
		return 1032;}
	cout << "Save Successfully" <<endl;
	return 0;
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