#pragma once

namespace rt {
#ifndef _CRT_STRINGIZE
#define __CRT_STRINGIZE(_Value) #_Value
#define _CRT_STRINGIZE(_Value) __CRT_STRINGIZE(_Value)
#endif
#define __ATTRIBUTES__ " in \"" __FILE__ "\", line " _CRT_STRINGIZE(__LINE__) ""
#define RT_ASSERT(_condition_) \
	do { \
	    if (!(_condition_)) { \
	        printf("Assertion failed: %s", #_condition_ __ATTRIBUTES__); \
	        abort (); \
	    } \
	} while (0)

#define RT_ASSERT_MSG(_condition_, _format_, ...) \
	do { \
	    if (!(_condition_)) { \
			printf("Assertion failed: %s\n",  #_condition_ __ATTRIBUTES__); \
			printf(_format_"\n", ##__VA_ARGS__); \
	        abort (); \
	    } \
	} while (0)

#define RT_IF_WARNING(_condition_, _format_, ...) \
	do { \
	    if (_condition_) { \
			printf("WARNING: %s:\n",  #_condition_ __ATTRIBUTES__); \
			printf(_format_"\n", ##__VA_ARGS__); \
	    } \
	} while (0)

#define RT_WARNING(_format_, ...) \
	do { \
		printf("WARNING:%s:\n",  __ATTRIBUTES__); \
		printf(_format_"\n", ##__VA_ARGS__); \
	} while (0)

#define SIGN(a) (((a) >= 0) ? 1 : -1)
}
