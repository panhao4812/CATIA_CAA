#ifdef  _WINDOWS_SOURCE
#ifdef  __Addin
#define ExportedByAddin     __declspec(dllexport)
#else
#define ExportedByAddin     __declspec(dllimport)
#endif
#else
#define ExportedByAddin
#endif
