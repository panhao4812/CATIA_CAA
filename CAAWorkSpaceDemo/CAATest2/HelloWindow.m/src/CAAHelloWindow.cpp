#include "CAAHelloWindow.h"
// System
#include "CATCreateExternalObject.h"   // Define the CATDeclareClass macro
#include "CATBaseUnknown.h"

CATCreateClass (CAAHelloWindow);

CAAHelloWindow::CAAHelloWindow():CATStateCommand(CATString("helloworld"))
{
}
CAAHelloWindow::~CAAHelloWindow()
{
	//if (NULL != _pObjectAgent) {_pObjectAgent->RequestDelayedDestruction(); _pObjectAgent = NULL;}
}

 void CAAHelloWindow::BuildGraph()
{ 
	RequestDelayedDestruction( ) ;
}