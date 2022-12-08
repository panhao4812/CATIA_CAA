#ifndef Function_H
#define Function_H
//catia
#include "CATSessionServices.h"
#include "CATDocument.h"
#include "CATIDrawing.h"
#include "CATIDftDrawing.h"
#include "CATSession.h"
#include "CATDocumentServices.h"
#include "CATListOfDouble.h"
#include "CATIDftDocumentServices.h"
#include "CATISpecObject.h"
//std
#include <iostream.h>
#include <ios>
#include <fstream> //ofstream p;p.open("D:\\catiav5_r22\\log.txt");p.close();
#include <deque>  
#include <algorithm>  
#include <string>
#include <stdlib.h>
#include <io.h>
#include <string.h>


using namespace std;

class Function{
	Function();
	~Function();
public:

	static HRESULT OpenSession( char * SessionName);
	static HRESULT CloseSession( char * SessionName);

	static HRESULT CreateDoc(CATDocument*& pDoc);
	static HRESULT SelectDoc(const char *fileName,CATDocument*& pDoc );
	static HRESULT SaveDoc(const char * fileNameOut,CATDocument*& pDoc);
	static HRESULT CloseDoc(CATDocument*& pDoc);	

	static HRESULT  SelectDftDrawing(CATDocument*& pDoc,CATIDftDrawing*& piDftDrawing );
	static HRESULT  SelectDrawing(CATDocument*& pDoc,CATIDrawing*& piDrawing );


	static void PrintCATListOfDouble(CATListOfDouble& iCoordList);
	static void PrintType(CATBaseUnknown *pBase);
	
};
#endif