/*Dummy file to satisfy source file dependencies on Windows platform*/
#ifndef strcasecmp
#define strcasecmp _stricmp
#endif

#ifndef strncasecmp
#define strncasecmp _strnicmp
#endif

#ifndef inline
#define inline __inline
#endif

//warning C4100
#pragma warning(disable:4100)
#pragma warning(disable:4189)
