#ifdef  _WINDOWS_SOURCE
#ifdef  __SelT3
#define ExportedBySelT3     __declspec(dllexport)
#else
#define ExportedBySelT3     __declspec(dllimport)
#endif
#else
#define ExportedBySelT3
#endif
