#pragma once

#pragma warning(disable: 6387)
#pragma warning(disable: 26449)
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "winmm.lib")


#include <iostream>
#include <fstream>
#include <memory>
#include <string_view>
#include <windows.h>
#include <TlHelp32.h>
#include <vector>
#include <map>
#include <concepts>
#include <utility>
#include <thread>
#include <functional>
#include <fcntl.h>
#include <io.h>
#include <stack>
#include <algorithm>
#define _USE_MATH_DEFINES
#include <math.h>

#define log(x)\
std::wcout << x << "\n"

#define input(key)\
GetAsyncKeyState(key) & 0x8000

#define error(msg,witness)\
MessageBoxA(NULL, msg, "ERROR", MB_ICONERROR);\
fnRestoreAll(witness);\
exit(-1)

#include "Trainer.h"
#include "Ini.h"
#define UNICODE
#include "Dialog.h"
#include "Animation.h"
#include "Functions.h"
#include "resource.h"
