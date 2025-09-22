# if defined(SYSTEMCONFIG_LIB)
#  define SYSTEMCONFIG_EXPORT __declspec(dllexport)
# else
#  define SYSTEMCONFIG_EXPORT __declspec(dllimport)
# endif

