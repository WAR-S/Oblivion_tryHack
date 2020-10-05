#pragma once
#include <Windows.h>
#include "MinHook\include\cHookContext.h"
#include <process.h>
#include "C:\Users\sqrtb\Desktop\Visual\u\GUI DX v.2017\cMenu.h"

#include "C:\Users\sqrtb\Desktop\Visual\u\GUI DX v.2017\cRender\cRender.h"


typedef HRESULT(APIENTRY* PresentFn)(IDirect3DDevice9 *, CONST RECT*, CONST RECT*, HWND, CONST RGNDATA*);
cDetour<PresentFn>* oPresent;
typedef HRESULT(APIENTRY *ResetFn)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
cDetour<ResetFn>* oReset;
bool     Create = false;
