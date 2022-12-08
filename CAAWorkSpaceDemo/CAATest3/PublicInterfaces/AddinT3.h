#ifdef  _WINDOWS_SOURCE
#ifdef  __AddinT3
#define ExportedByAddinT3     __declspec(dllexport)
#else
#define ExportedByAddinT3     __declspec(dllimport)
#endif
#else
#define ExportedByAddinT3
#endif
