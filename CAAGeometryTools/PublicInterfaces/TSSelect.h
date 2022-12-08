#ifdef  _WINDOWS_SOURCE
#ifdef  __TSSelect
#define ExportedByTSSelect     __declspec(dllexport)
#else
#define ExportedByTSSelect     __declspec(dllimport)
#endif
#else
#define ExportedByTSSelect
#endif
