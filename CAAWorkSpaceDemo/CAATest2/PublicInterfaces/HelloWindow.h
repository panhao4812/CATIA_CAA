#ifdef  _WINDOWS_SOURCE
#ifdef  __HelloWindow
#define ExportedByHelloWindow     __declspec(dllexport)
#else
#define ExportedByHelloWindow     __declspec(dllimport)
#endif
#else
#define ExportedByHelloWindow
#endif
