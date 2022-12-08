#ifndef CAAAddin_H
#define CAAAddin_H
#include "CATBaseUnknown.h" 

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
