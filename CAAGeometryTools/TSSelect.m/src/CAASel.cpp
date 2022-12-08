#include "CAASel.h"

CATCreateClass (CAASel);
CAASel::CAASel():CATStateCommand(CATString("helloworld")),_pObjectAgent(NULL)
{
}
CAASel::~CAASel()
{
	if (NULL != _pObjectAgent) {_pObjectAgent->RequestDelayedDestruction(); _pObjectAgent = NULL;}
}

void CAASel::BuildGraph()
{ 	
	// Creation of the acquisition agent
	_pObjectAgent = new CATPathElementAgent("_pObjectAgent A");
	_pObjectAgent ->SetBehavior( CATDlgEngWithPrevaluation | 
		CATDlgEngMultiAcquisition | 
		CATDlgEngWithCSO); 
	_pObjectAgent ->AddElementType("IDMCurve2D");//筛选器
	AddCSOClient(_pObjectAgent);  
	//  States definition
	CATDialogState* pState1 = GetInitialState("Sel Line");
	pState1->AddDialogAgent(_pObjectAgent);
	// Transition definition
	AddTransition(pState1, NULL, IsOutputSetCondition(_pObjectAgent),
		Action((ActionMethod)&CAASel::func1, NULL, NULL));
	//CATDlgEngMultiAcquisition--可以框选多个
	//CATDlgEngWithPrevaluation--拾取后再敲命令
	//CATDlgEngWithCSO--高亮显示选中的物体 
}
boolean CAASel::func1(void *iData)
{
	CATSO* pObjSO = _pObjectAgent->GetListOfValues(); 
	CATPathElement *pElemPath = NULL;
	std::vector<ON_3dPoint> nodes;

	//这2个指针release之后会出错
	if (NULL != pObjSO)  
	{
		pObjSO->InitElementList();

		CATI2DWFFactory_var spGeomFactory;//画线的接口 直接由view得到
		CATI2DConstraintFactory_var spConstraint2DFactory;//创建约束接口
		while (NULL != (pElemPath = (CATPathElement*)pObjSO->NextElement())  )
		{         	//
			/*//查询选择物体类型
			for(int i=0;i<pElemPath->GetSize();i++){		
			CATBaseUnknown_var spBase=(*pElemPath)[i];
			CATISpecObject *piSpecObj=NULL;
			if (SUCCEEDED(spBase->QueryInterface(IID_CATISpecObject,(void **)&piSpecObj)))
			{
			cout<< piSpecObj->GetType() <<endl;
			}else{
			cout << "CATBaseUnknown_var"<<endl;
			}
			}
			//*/
			if(spGeomFactory==NULL){
				CATIView_var spBgView;
				spBgView=(CATIView*)pElemPath->FindElement(IID_CATIView);
				spGeomFactory = spBgView;
				spConstraint2DFactory=spBgView;
			}
			IDMCurve2D *piElementRef = (IDMCurve2D *)pElemPath->FindElement(IID_IDMCurve2D);
			if (NULL != piElementRef)
			{
				double* StartPoint = new double[2];
				double* EndPoint = new double[2];
				piElementRef->GetEndPoints(StartPoint,EndPoint);
				cout<<StartPoint[0]<<"|"<<StartPoint[1]<<endl;
				cout<<EndPoint[0]<<"|"<<EndPoint[1]<<endl;
				ON_3dPoint pt(StartPoint[0],StartPoint[1],0.0);
				nodes. push_back(pt); 
				ON_3dPoint pt2(EndPoint[0],EndPoint[1],0.0);
				nodes. push_back(pt2); 
				delete StartPoint,EndPoint;
				piElementRef->Release();
			}

			/* //find ViewMakeUp
			CATIView *pView=NULL;
			CATIDftViewMakeUp *pViewMU = NULL; 
			pViewMU=(CATIDftViewMakeUp*)pElemPath->FindElement(IID_CATIDftViewMakeUp);
			pView=(CATIView*)pElemPath->FindElement(IID_CATIView);
			cout<< pViewMU <<endl;       
			pViewMU->SetScale(0.5);
			if(NULL!=pViewMU){pViewMU->Release();pViewMU=NULL;}
			if(NULL!=pView){pView->Release();pView=NULL;}
			//*/
			//******************************************************************
		} 	
		nodes =ON_Polyline::RemoveDupPts(nodes,0.001);
		if(nodes.size()>3){
			ON_Polyline pl1=ON_Polyline::ComputeHull2d(nodes);//
			if(pl1.size()>3){
				double startPoint[2], endPoint[2];
				CATListValCATI2DWFGeometry_var Lines_var;
				CATIVisProperties *piVisProp = NULL;
				CATVisPropertiesValues ioValues;	ioValues.SetLineType(2);	
				for(int i=1;i<pl1.size();i++){
					startPoint[0] = pl1[i-1].x;
					startPoint[1] = pl1[i-1].y;
					endPoint[0] = pl1[i].x;
					endPoint[1] = pl1[i].y;
					CATISpecObject_var line1=spGeomFactory->CreateLine(startPoint, endPoint);	
					piVisProp=NULL;line1->QueryInterface(IID_CATIVisProperties,(void**) & piVisProp);
					piVisProp->SetPropertiesAtt(ioValues,CATVPLineType,CATVPLine);
					//line1->Update(NULL_var);
					Lines_var.Append((CATI2DWFGeometry_var)line1);
				}
				startPoint[0] = pl1[pl1.size()-1].x;
				startPoint[1] = pl1[pl1.size()-1].y;
				endPoint[0] = pl1[0].x;
				endPoint[1] = pl1[0].y;
				CATISpecObject_var line1=spGeomFactory->CreateLine(startPoint, endPoint);	
				piVisProp=NULL;line1->QueryInterface(IID_CATIVisProperties,(void**) & piVisProp);
				piVisProp->SetPropertiesAtt(ioValues,CATVPLineType,CATVPLine);
				piVisProp->Release();
				//line1->Update();
				Lines_var.Append((CATI2DWFGeometry_var)line1);
				//	CATISpecObject_var constraint1=	spConstraint2DFactory->CreateConstraint( Lines_var[0], NULL, Lines_var[1], NULL, NULL, NULL, NULL, Cst2DType_Reference, 0, 0 );
				CATBaseUnknown* pFixTogether;
				HRESULT rs=spGeomFactory->FixTogether(Lines_var,IID_CATI2DFixTogether,&pFixTogether);
				pFixTogether->Release();
			}
		}
		_pObjectAgent -> InitializeAcquisition();
		return TRUE;
	}
	return FALSE;
}