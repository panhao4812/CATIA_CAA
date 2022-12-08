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
#include "IDMCurve2D.h"

#include "opennurbs.h"

#include <iostream.h>
#include "CATI2DWFFactory.h"
#include "CATI2DConstraintFactory.h"
#include "CATI2DLine.h"
#include "CATI2DWFGeometry.h"
#include "CATI2DFixTogether.h"

#include "CATIVisProperties.h"
#include "CATIVisPropertiesAbstract.h"
#include "CATVisPropertiesValues.h" 
#include "CATVisPropertyType.h"

#include "CATIDomain.h"
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
