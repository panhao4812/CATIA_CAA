#ifndef CAADlgHelloApplication_H
#define CAADlgHelloApplication_H
#include "CATInteractiveApplication.h"

class CAADlgHelloApplication: public CATInteractiveApplication
{
	
public:
CAADlgHelloApplication (const CATString &iIdentifier); 
virtual ~CAADlgHelloApplication ();
  
void BeginApplication();
int EndApplication();
/*
private:
CAADlgHelloApplication (); 
CAADlgHelloApplication(const CAADlgHelloApplication &iObjectToCopy); 
CAADlgHelloApplication & operator = (const CAADlgHelloApplication &iObjectToCopy); 
*/
};

#endif