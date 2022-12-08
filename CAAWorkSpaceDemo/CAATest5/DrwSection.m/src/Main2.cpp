
#include "Function.h"

int Function::main2()  
{  
	CATUnicodeString fileName="C:\\Users\\Administrator\\Desktop\\catia\\CAATest.CATDrawing";	
	CATSession *pSampleSession = NULL;
	HRESULT hr = ::Create_Session("SampleSession",pSampleSession);
	if (FAILED(hr)) return 1;

	// read the document
	CATDocument* pDoc = NULL;
	if (!SUCCEEDED(CATDocumentServices::OpenDocument(fileName, pDoc)))
	{
		// Ends session
		::Delete_Session("SampleSession");
		return 2;
	}
	CATIDrawing *piDrawing = NULL;
	CATIDftDocumentServices *piDftDocServices = NULL;
	if (SUCCEEDED(pDoc->QueryInterface(IID_CATIDftDocumentServices, (void **)&piDftDocServices)))
	{
		piDftDocServices->GetDrawing(IID_CATIDrawing, (void **)&piDrawing);
		piDftDocServices->Release();
	}
	if (NULL == piDrawing)return 3;
	CATISheet_var spSheet = piDrawing->GetCurrentSheet();
	CATIView_var spCurrentView = spSheet->GetCurrentView();
	 piDrawing->Release();

	 CATIDftGenViewFactory *piDftGenViewFact = NULL;
    if (NULL_var!=spSheet && SUCCEEDED(spSheet->QueryInterface(IID_CATIDftGenViewFactory,(void **)&piDftGenViewFact))) 
    {
		double  iptOrigin[2]={0,0};
		CATDftViewType  iViewType=DftSectionView;
		int  iViewProfile=0;
		int  iSideToDraw=0;

		CATLISTP(CATMathPoint2D)  iListOfPoints;
		CATMathPoint2D *pP1=new CATMathPoint2D(640,230);iListOfPoints.Append(pP1);
		CATMathPoint2D *pP2=new CATMathPoint2D(640,60);iListOfPoints.Append(pP2);	
		CATIDftView*  ipiMotherView=NULL;
		hr=spCurrentView->QueryInterface(IID_CATIDftView,(void **)&ipiMotherView);
		CATIDftView*  opiSectionView=NULL;
      hr=piDftGenViewFact->CreateSectionView(iptOrigin,
		  iViewType,
		  iViewProfile,
		  iSideToDraw,
		  iListOfPoints,
		  ipiMotherView,
		  &opiSectionView
		  );

	  cout<<hr<<endl;
	  piDftGenViewFact->Release();piDftGenViewFact=NULL;
	  ipiMotherView->Release();ipiMotherView=NULL;
	  opiSectionView->Release();opiSectionView=NULL;
	  //delete pP1,pP2;
     }
	// Save the result
   hr = CATDocumentServices::SaveAs(*pDoc, fileName);
   if (FAILED(hr)) return 4;
   // Ends session and drops document	
   CATDocumentServices::Remove (*pDoc);
   ::Delete_Session("SampleSession");
   cout<<"Press Any Key to Countinue..."<<endl;
	cin.get();
	return 1;
}  