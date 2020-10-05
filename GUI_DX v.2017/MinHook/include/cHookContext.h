#pragma once
#include "MinHook.h"
#include "cDetour.h"
#include "cVmt.h"

class cContext
{
public:
	static cContext& GetInstance();
	 
	template<typename T> cDetour<T>* CreateDetour(T target, T detour)
	{
		auto pDetour = new cDetour<T>(target, detour);
		return pDetour;
	}
	template<typename T> bool        ApplyDetour(T target, T detour, cDetour<T>** ppDetour)
	{
		auto pDetour = CreateDetour(target, detour);
		if (pDetour)
		{
			*ppDetour = pDetour;
			pDetour->Apply();
			return true;
		}
		return false;
	}
	
	template<typename T> cVmt<T>* CreateVmt(void** ppVtable, size_t index, T detour)
	{
		auto pVmtHook = new cVmt<T>(ppVtable, index, detour);
		return pVmtHook;
	}
	template<typename T> bool     ApplyVmt(void** ppVtable, size_t index, T detour, cVmt<T>** ppVmtHook)
	{
		auto pVmtHook = CreateVmt(ppVtable, index, detour);
		if (pVmtHook)
		{
			*ppVmtHook = pVmtHook;
			pVmtHook->Apply();
			return true;
		}
		return false;
	}
	
	
	void CloseExit()
	{
		if (!(MH_Uninitialize() == MH_OK))
			TerminateProcess(GetCurrentProcess(), -1);
	}
	cContext() {}
	~cContext() {}
};

bool bInitialized = false;
cContext& cContext::GetInstance()
{
	if (!bInitialized)
		bInitialized = MH_Initialize() == MH_OK;
	static cContext pCtx;
	return pCtx;
}

