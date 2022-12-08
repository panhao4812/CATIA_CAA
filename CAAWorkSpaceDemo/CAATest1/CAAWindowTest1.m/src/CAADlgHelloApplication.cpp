#include "CAADlgHelloApplication.h"
#include "CAADlgHelloWindow.h"
#include <iostream.h>



CAADlgHelloApplication::CAADlgHelloApplication(const CATString& iIdentifier):CATInteractiveApplication(NULL, iIdentifier)
{
cout << "The CAADlgHelloApplication begins..... " <<endl;
}

CAADlgHelloApplication::~CAADlgHelloApplication()
{
cout << "The CAADlgHelloApplication is finished. " <<endl;
}

void CAADlgHelloApplication::BeginApplication()
{
cout <<"CAADlgHelloApplication::BeginApplication" << endl;
CAADlgHelloWindow  * pMainWindow = NULL;
pMainWindow = new CAADlgHelloWindow(this);
pMainWindow->Build();
pMainWindow->SetVisibility(CATDlgShow);
}

int CAADlgHelloApplication::EndApplication()
{
cout << "CAADlgHelloApplication::EndApplication" << endl;
return(0);
}

CAADlgHelloApplication ApplicationInstance("Hello");