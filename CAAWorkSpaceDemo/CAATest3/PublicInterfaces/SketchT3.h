#ifdef  _WINDOWS_SOURCE
#ifdef  __SketchT3
#define ExportedBySketchT3     __declspec(dllexport)
#else
#define ExportedBySketchT3     __declspec(dllimport)
#endif
#else
#define ExportedBySketchT3
#endif
