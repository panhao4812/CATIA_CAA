#include "CAAAddin.h"

////////////////////////////////////
MacDeclareHeader(CAAAddinHeader);
CATImplementClass( CAAAddin,DataExtension,CATBaseUnknown,CAAAddn);
//��disco�ļ������й�

#include "TIE_CATIDRWFRAMEAddin.h"
TIE_CATIDRWFRAMEAddin(CAAAddin);
//#include "TIE_CATICS0WKSAddin.h"
//TIE_CATICS0WKSAddin(CAAAddin);
//������λ��CATICS0WKSAddin���ڲ�ͼ������棬CATIDRWFRAMEAddin���ڹ�����ͼ����
////////////////////////////////////
CAAAddin::CAAAddin():CATBaseUnknown()
{}
CAAAddin::~CAAAddin(){}
void CAAAddin::CreateCommands()
{
	///////////////////////////////////////////////////
	//new CAAAddinHeader("Sel","SketchT3", "CAASketch",(void *)NULL);
	new CAAAddinHeader("Sel","SelT3", "CAASel",(void *)NULL);
	//��������model selT3��model�� CAASel������
	////////////////////////////////////////////////////
}
CATCmdContainer *CAAAddin::CreateToolbars()
{
    NewAccess        (CATCmdContainer, pCAADrwTlb,      CAAUseCaseCommands );
/////////////////////////////////////////////////////////////////////////////
    NewAccess        (CATCmdStarter,   pDimDressupStr , DimDressupStr );
    SetAccessCommand (pDimDressupStr,  "Sel" );
    SetAccessChild   (pCAADrwTlb,      pDimDressupStr  );
/////////////////////////////////////////////////////////////////////////////
	AddToolbarView   (pCAADrwTlb , -1 , UnDock); 
    return pCAADrwTlb;
}
