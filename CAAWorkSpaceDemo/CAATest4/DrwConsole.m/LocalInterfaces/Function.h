#ifndef Function_H
#define Function_H

#include "CATIDftDocumentServices.h"
#include "CATIDftDrawing.h"
#include "CATIDftSheet.h"
#include "CATIDftViewMakeUp.h"
#include "CATIDftView.h"
#include "CATIDftStandardManager.h"
#include "CATIDftFormat.h"
#include "CATIDftSheetFormat.h"
#include "CATIDftDrawingFormats.h"
#include "CATI2DWFFactory.h"
#include "CATIUnknownList.h"
#include "CATISketch.h"
#include "CATIView.h"
#include "CATIDrwFactory.h"
#include "CATISpecObject.h"

#include "CATDrwViewType.h"
#include "CATDocument.h"
#include "CATSession.h"
#include "CATDocumentServices.h"
#include "CATSessionServices.h"
#include <iostream.h>
class Function{
	Function();
	~Function();
public:
	static int CreateDoc(CATDocument*& pDoc);
	static int SelectDoc(const char *fileName,CATDocument*& pDoc );
	static int SaveAndClosedDoc(const char * fileNameOut,CATDocument*& pDoc);
	static void PrintType(CATBaseUnknown *pBase);
};
#endif