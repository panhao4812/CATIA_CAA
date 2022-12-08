#ifdef  _WINDOWS_SOURCE
#ifdef  __CAAWindowTest1
#define ExportedByCAAWindowTest1     __declspec(dllexport)
#else
#define ExportedByCAAWindowTest1     __declspec(dllimport)
#endif
#else
#define ExportedByCAAWindowTest1
#endif
