#include "CAAAddin.h"
#include "CATCommandHeader.h"
#include "CATCreateWorkshop.h"
#include "CATCmdContainer.h"
#include "CATCmdStarter.h"
////////////////////////////////////
MacDeclareHeader(CAAAddinHeader);
CATImplementClass( CAAAddin,DataExtension,CATBaseUnknown,CAAAddn);

#include "TIE_CATIDRWFRAMEAddin.h"
TIE_CATIDRWFRAMEAddin(CAAAddin);
////////////////////////////////////
CAAAddin::CAAAddin():CATBaseUnknown()
{
	cout<<"00000001"<<endl;
}
CAAAddin::~CAAAddin()
{
}
void CAAAddin::CreateCommands()
{
	///////////////////////////////////////////////////
	new CAAAddinHeader("Sel","TSSelect","CAASel",(void *)NULL);
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
