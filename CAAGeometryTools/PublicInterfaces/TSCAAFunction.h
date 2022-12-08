#ifdef  _WINDOWS_SOURCE
#ifdef  __TSCAAFunction
#define ExportedByTSCAAFunction     __declspec(dllexport)
#else
#define ExportedByTSCAAFunction     __declspec(dllimport)
#endif
#else
#define ExportedByTSCAAFunction
#endif
