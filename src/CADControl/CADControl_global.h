#pragma once


#ifndef BUILD_STATIC
# if defined(CADCONTROL_LIB)
#  define CADCONTROL_EXPORT __declspec(dllexport)
# else
#  define CADCONTROL_EXPORT __declspec(dllimport)
# endif
#else
# define MOTIONACTOR_EXPORT
#endif

