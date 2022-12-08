#ifdef  _WINDOWS_SOURCE
#ifdef  __TSCatiaEXE
#define ExportedByTSCatiaEXE     __declspec(dllexport)
#else
#define ExportedByTSCatiaEXE     __declspec(dllimport)
#endif
#else
#define ExportedByTSCatiaEXE
#endif
