#include "cInclude.h"
#include "cMenu.h"
#include "C:\Users\sqrtb\Desktop\Visual\u\GUI DX v.2017\cRender\cRender.h"



HRESULT APIENTRY myPresent(IDirect3DDevice9 * m_pDevice, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion)
{
	if (Create == false)
	{
		pRender = new cRender(m_pDevice);
		Create = true;
		
	}
	else
	{
		
		SIZE pSize;
		pRender->GetTextExtent("WARS", &pSize);
	
		cMenu *m = new cMenu(*pRender, 1, 2);
		m->Draw();
		
		
	}
	auto   result = oPresent->GetTrampoline()(m_pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
	return result;
}
HRESULT APIENTRY myReset(IDirect3DDevice9* m_pDevice, D3DPRESENT_PARAMETERS *pPresentationParameters)
{
	if (!Create)
		return m_pDevice->Reset(pPresentationParameters);

	pRender->LostDevice();
	auto   result = oReset->GetTrampoline()(m_pDevice, pPresentationParameters);

	if (SUCCEEDED(result))
	{
		pRender->ResetDevice();
	}
	return result;
}
bool Init()
{
	
	bool    bResult = false;
	HMODULE hD3d9 = NULL;
	if (hD3d9 = GetModuleHandleA("d3d9.dll"))
	{
		typedef HRESULT(APIENTRY* Direct3DCreate9ExFn)(UINT, IDirect3D9Ex**);
		Direct3DCreate9ExFn oDirect3DCreate9Ex = (Direct3DCreate9ExFn)GetProcAddress(hD3d9, "Direct3DCreate9Ex");
		if (oDirect3DCreate9Ex)
		{
			HRESULT hr = D3D_OK;
			LPDIRECT3D9EX m_pCreate9Ex = nullptr;
			if (SUCCEEDED(hr = oDirect3DCreate9Ex(D3D_SDK_VERSION, &m_pCreate9Ex)))
			{
				D3DPRESENT_PARAMETERS dp;
				ZeroMemory(&dp, sizeof(dp));
				dp.Windowed = 1;
				dp.SwapEffect = D3DSWAPEFFECT_FLIP;
				dp.BackBufferFormat = D3DFMT_A8R8G8B8;
				dp.BackBufferCount = 1;
				dp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

				IDirect3DDevice9Ex *mDevice = nullptr;
				if (SUCCEEDED(hr = m_pCreate9Ex->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_NULLREF, NULL, D3DCREATE_HARDWARE_VERTEXPROCESSING, &dp, NULL, &mDevice)))
				{
					bResult = true;
					PVOID* vtbl = *reinterpret_cast<PVOID**>(mDevice);
					auto& pContext = cContext::GetInstance();
					pContext.ApplyDetour<PresentFn>(static_cast<PresentFn>(vtbl[17]), reinterpret_cast<PresentFn>(myPresent), &oPresent);
					pContext.ApplyDetour<ResetFn>(static_cast<ResetFn>(vtbl[16]), reinterpret_cast<ResetFn>(myReset), &oReset);				
					mDevice->Release();

				}
				m_pCreate9Ex->Release();
			}
		}
	}
	return bResult;
}
unsigned APIENTRY GUIDX(LPVOID  lpParam)
{
	while (!Init())
		Sleep(200);
	return 0L;
}


BOOL APIENTRY DllMain(_In_ HINSTANCE hinstDLL,_In_ DWORD dwReason,_In_ LPVOID  lpvReserved)
{
	DisableThreadLibraryCalls(hinstDLL);
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
	{
		_beginthreadex(NULL, NULL, GUIDX, NULL, NULL, NULL);
	}
	break;
	case DLL_THREAD_ATTACH:

		break;
	case DLL_THREAD_DETACH:

		break;
	case DLL_PROCESS_DETACH:

		break;

	default:

		break;
	}
	return TRUE;
}









