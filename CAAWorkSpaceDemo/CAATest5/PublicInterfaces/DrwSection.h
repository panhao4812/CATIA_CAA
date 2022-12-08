#ifdef  _WINDOWS_SOURCE
#ifdef  __DrwSection
#define ExportedByDrwSection     __declspec(dllexport)
#else
#define ExportedByDrwSection     __declspec(dllimport)
#endif
#else
#define ExportedByDrwSection
#endif
