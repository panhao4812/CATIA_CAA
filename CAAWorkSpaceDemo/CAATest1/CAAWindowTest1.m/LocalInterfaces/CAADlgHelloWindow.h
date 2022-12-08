#ifndef CAADlgHelloWindow_H
#define CAADlgHelloWindow_H
#include "CATDlgDocument.h"

class CAADlgHelloWindow : public CATDlgDocument {  
//CATDeclareClass;
//DeclareResource(CAADlgHelloWindow, CATDlgDocument)
public: 
CAADlgHelloWindow(CATInteractiveApplication * iParentCommand);     
virtual ~CAADlgHelloWindow();  
 void Build();  

 private:      
 void Exit (CATCommand  * iSendingCommand,
               CATNotification * iSentNotification,
               CATCommandClientData   iUsefulData);     
 /*
   CAADlgHelloWindow ();    
   CAADlgHelloWindow(const CAADlgHelloWindow &iObjectToCopy);    
   CAADlgHelloWindow & operator = (const CAADlgHelloWindow &iObjectToCopy);      
*/
   CATInteractiveApplication * _pHelloApplication; 
};

#endif
