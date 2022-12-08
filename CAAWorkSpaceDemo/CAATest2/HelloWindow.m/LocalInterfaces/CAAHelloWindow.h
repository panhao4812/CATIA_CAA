#ifndef CAAHelloWindow_H
#define CAAHelloWindow_H
// DialogEngine
#include "CATStateCommand.h"

//class CATPathElementAgent;

class CAAHelloWindow: public CATStateCommand
{
  //CATDeclareClass;
  public:
     CAAHelloWindow ();
     virtual ~CAAHelloWindow ();
     void BuildGraph();
};

//-----------------------------------------------------------------------

#endif
