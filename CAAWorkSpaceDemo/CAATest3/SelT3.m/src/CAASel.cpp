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
	// _pObjectAgent ->AddElementType("IDMCircle2D");
	AddCSOClient(_pObjectAgent);  
	//  States definition
	CATDialogState* pState1 = GetInitialState("Sel Line");
	pState1->AddDialogAgent(_pObjectAgent);
	// Transition definition
	AddTransition(pState1, NULL, IsOutputSetCondition(_pObjectAgent),
		Action((ActionMethod)&CAASel::func1, NULL, NULL));
	//CATDlgEngMultiAcquisition--���Կ�ѡ���
	//CATDlgEngWithPrevaluation--ʰȡ����������
	//CATDlgEngWithCSO--������ʾѡ�е����� 
}
boolean CAASel::func1(void *iData)
{
	CATSO* pObjSO = _pObjectAgent->GetListOfValues(); 
	CATPathElement *pElemPath = NULL;
	//��2��ָ��release֮������
	if (NULL != pObjSO)  
	{
		pObjSO->InitElementList();
		while (NULL != (pElemPath = (CATPathElement*)pObjSO->NextElement())  )
		{         
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
/* 
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
		_pObjectAgent -> InitializeAcquisition();
		return TRUE;
	}
	return FALSE;
}