#include <Wt/WCompositeWidget>
#include <Wt/WJavaScript>
#include <Wt/WSignal>
#include <Wt/WContainerWidget>
#include <Wt/WApplication>

//==============================================================================
// Compiler type macros.

#ifdef __clang__
#define YSE_CLANG 1
#define YSE_GCC 1
#elif defined (__GNUC__)
#define YSE_GCC 1
#elif defined (_MSC_VER)
#define MB_MSVC 1
#endif

//==============================================================================
// DLL building settings on Windows
#if MB_MSVC
#ifdef MB_DLL_BUILD
#define API __declspec (dllexport)
#define EXTERN
#pragma warning (disable: 4251)
#else
#define API __declspec (dllimport)
#define EXTERN extern
#pragma warning (disable: 4251)
#endif
#endif

//==============================================================================
// DLL building on mac
#if YSE_MAC
#ifdef YSE_DLL_BUILD
#define API __attribute__((visibility("default")))
#define EXTERN
#elif defined(YSE_DLL)
#define API
#define EXTERN extern
#endif
#endif

//==============================================================================
#ifndef API
#define API   /**< This macro is added to all public class declarations. */
#define EXTERN
#endif