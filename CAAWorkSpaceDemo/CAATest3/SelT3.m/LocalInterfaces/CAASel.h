#ifndef CAASel_H
#define CAASel_H

#include "CATStateCommand.h"//DialogEngine.CATStateCommand
#include "CATCreateExternalObject.h"   // Define the CATDeclareClass macro
#include "CATBaseUnknown.h"

#include "CATPathElementAgent.h"
#include "CATPathElement.h"
#include "CATSO.h"
#include "CATIDrwAnnotationFactory.h"
#include "IDMLine2D.h"
#include "IDMCircle2D.h"
#include <iostream.h>
#include "CATIDrwFactory.h"
#include "CATIDftViewMakeUp.h"
#include "CATIView.h"
#include "CATUnicodeString.h"
#include "CATISpecObject.h"
#include "CATISheet.h"

class CATPathElementAgent;
class CAASel: public CATStateCommand
{
  //CATDeclareClass;
  public:
     CAASel ();
     virtual ~CAASel ();
     void BuildGraph();//ѡ��������
     boolean func1(void* iData=NULL);//ѡ�����崦����
  private:
	  CATPathElementAgent *_pObjectAgent;//ѡ������������  
};

#endif
