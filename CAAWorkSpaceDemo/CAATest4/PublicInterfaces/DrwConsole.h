#ifdef  _WINDOWS_SOURCE
#ifdef  __DrwConsole
#define ExportedByDrwConsole     __declspec(dllexport)
#else
#define ExportedByDrwConsole     __declspec(dllimport)
#endif
#else
#define ExportedByDrwConsole
#endif
