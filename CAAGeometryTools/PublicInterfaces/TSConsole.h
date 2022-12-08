#ifdef  _WINDOWS_SOURCE
#ifdef  __TSConsole
#define ExportedByTSConsole     __declspec(dllexport)
#else
#define ExportedByTSConsole     __declspec(dllimport)
#endif
#else
#define ExportedByTSConsole
#endif
