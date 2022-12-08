#include "CAADlgHelloApplication.h"
#include "CAADlgHelloWindow.h"
#include "CATDlgInclude.h"
#include <iostream.h>


CAADlgHelloWindow::CAADlgHelloWindow(CATInteractiveApplication * iParentCommand) :CATDlgDocument(iParentCommand, "CAADlgHelloWindowId"),_pHelloApplication(iParentCommand)
{
cout << "CAADlgHelloWindow::CAADlgHelloWindow" << endl;
}

CAADlgHelloWindow::~CAADlgHelloWindow()
{
cout << "CAADlgHelloWindow::~CAADlgHelloWindow" << endl;
_pHelloApplication = NULL ;
}

void CAADlgHelloWindow::Build()
{
cout << "CAADlgHelloWindow::Build" << endl;
CATDlgLabel * pLabel = new CATDlgLabel(this,"MessageId");
AddAnalyseNotificationCB(this,GetWindCloseNotification(),(CATCommandMethod)&CAADlgHelloWindow::Exit, NULL);
}

void CAADlgHelloWindow::Exit(CATCommand * iSendingCommand,CATNotification * iSentNotification,CATCommandClientData iUsefulData)
{
_pHelloApplication->Destroy();
_pHelloApplication = NULL ;
}

 
