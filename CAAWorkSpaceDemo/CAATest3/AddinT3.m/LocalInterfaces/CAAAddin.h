#ifndef CAAAddin_H
#define CAAAddin_H
#include "CATBaseUnknown.h" 
#include "CATCommandHeader.h"//ApplicationFrame
#include "CATCreateWorkshop.h"//∫Í∂®“Â
#include "CATCmdContainer.h"//ApplicationFrame.CATCmdContainer
#include "CATCmdStarter.h"//ApplicationFrame.CATCmdStarter


class CATCmdContainer;      
class CAAAddin : public CATBaseUnknown
{
  CATDeclareClass;
     public:
     CAAAddin();
     virtual ~CAAAddin();
     void CreateCommands();
     CATCmdContainer *CreateToolbars();
};
#endif
