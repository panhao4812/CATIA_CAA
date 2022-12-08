#include "CAAAddin.h"

////////////////////////////////////
MacDeclareHeader(CAAAddinHeader);
CATImplementClass( CAAAddin,DataExtension,CATBaseUnknown,CAAAddn);
//和disco文件里面有关

#include "TIE_CATIDRWFRAMEAddin.h"
TIE_CATIDRWFRAMEAddin(CAAAddin);
//#include "TIE_CATICS0WKSAddin.h"
//TIE_CATICS0WKSAddin(CAAAddin);
//工具栏位置CATICS0WKSAddin是在草图设计里面，CATIDRWFRAMEAddin是在工程制图界面
////////////////////////////////////
CAAAddin::CAAAddin():CATBaseUnknown()
{}
CAAAddin::~CAAAddin(){}
void CAAAddin::CreateCommands()
{
	///////////////////////////////////////////////////
	//new CAAAddinHeader("Sel","SketchT3", "CAASketch",(void *)NULL);
	new CAAAddinHeader("Sel","SelT3", "CAASel",(void *)NULL);
	//关联下面model selT3是model名 CAASel是类名
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
