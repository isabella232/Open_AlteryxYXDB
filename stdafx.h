// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <SDKDDKVer.h>

#include <stdio.h>
#include <tchar.h>



#include <Windows.h>
#undef max
#undef min

#include <memory>
#include <string>
#include <algorithm>
#pragma warning( push )
#pragma warning( disable : 4100)
#include "SrcLib_Replacement.h"
#pragma warning( pop ) 
#define BOOST_PYTHON_STATIC_LIB
