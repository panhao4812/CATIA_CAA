#ifdef  _WINDOWS_SOURCE
#ifdef  __TSAddin
#define ExportedByTSAddin     __declspec(dllexport)
#else
#define ExportedByTSAddin     __declspec(dllimport)
#endif
#else
#define ExportedByTSAddin
#endif
