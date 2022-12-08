#ifdef  _WINDOWS_SOURCE
#ifdef  __CPPOpenNurbs
#define ExportedByCPPOpenNurbs     __declspec(dllexport)
#else
#define ExportedByCPPOpenNurbs     __declspec(dllimport)
#endif
#else
#define ExportedByCPPOpenNurbs
#endif
