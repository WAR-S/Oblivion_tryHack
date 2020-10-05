#include "cRender.h"


#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

cRender *pRender = nullptr;
cRender::cRender(IDirect3DDevice9 *m_pDevice)
{
	this->m_pDevice = m_pDevice;
	szFomtName = __TEXT("Tahoma");
	
	D3DXCreateFont(m_pDevice, 13, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, szFomtName , &m_pFont);

}

void cRender::LostDevice()
{
	if (m_pFont)
		m_pFont->OnLostDevice();
}
void cRender::ResetDevice()
{
	if (m_pFont)
		m_pFont->OnResetDevice();
}

void cRender::render_Line(float x, float y,float x2, float y2, Color color)
{
	DX_VERTEX Vertices[2] =
	{
		DX_VERTEX(x, y, 0.f, color),
		DX_VERTEX(x2, y2, 0.f, color)
	};

	this->m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	this->m_pDevice->SetFVF(DX_VERTEX::FVF);
	this->m_pDevice->SetTexture(0, NULL);
	this->m_pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, Vertices, sizeof(DX_VERTEX));
}
void cRender::render_Border(float x, float y, float w, float h, Color color)
{
	 
	DX_VERTEX Vertex[5] =
	{
		DX_VERTEX(x, y, 0.0f, color),
		DX_VERTEX(x + w, y, 0.0f, color),
		DX_VERTEX(x + w, y + h, 0.0f, color),
		DX_VERTEX(x, y + h, 0.0f, color),
		DX_VERTEX(x, y, 0.0f, color)
	};
	this->m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	this->m_pDevice->SetFVF(DX_VERTEX::FVF);
	this->m_pDevice->SetTexture(0, NULL);
	this->m_pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, Vertex, sizeof(DX_VERTEX));
}
void cRender::render_Box(float x, float y, float w, float h, Color color)
{
	DX_VERTEX Vertex[4] =
	{
		DX_VERTEX(x, y, 0.0f,        color),
		DX_VERTEX(x + w, y, 0.0f,     color),
		DX_VERTEX(x, y + h, 0.0f,     color),
		DX_VERTEX(x + w, y + h, 0.0f,  color)
	};
	this->m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	this->m_pDevice->SetFVF(DX_VERTEX::FVF);
	this->m_pDevice->SetTexture(0, NULL);
	m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &Vertex[0], sizeof(DX_VERTEX));
}
void cRender::render_Circle(float x, float y, float radius, Color color)
{
	const int NUMPOINTS = 360/*24*/;
	DX_VERTEX circle[NUMPOINTS + 1];
	float theta;
	float  wedgeAngle = (float)((2 * D3DX_PI) / NUMPOINTS);
	for (int i = 0; i <= NUMPOINTS; i++) 
	{
		theta = i * wedgeAngle;
		circle[i].x = (float)(x + radius * cos(theta));
		circle[i].y = (float)(y - radius * sin(theta));
		circle[i].z = 0;
		circle[i].rhw = 1.0f;
		circle[i].color = color;
	}

	this->m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	this->m_pDevice->SetFVF(DX_VERTEX::FVF);
	this->m_pDevice->SetTexture(0, NULL);
	this->m_pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, NUMPOINTS, &circle[0], sizeof(DX_VERTEX/*circle[0]*/));

}
void cRender::render_String(float x, float y, Color color, DWORD dwFlag, const TCHAR* fmt, ...)
{
	TCHAR buffer[512];
	va_list args;
	va_start(args, fmt);

#ifdef _UNICODE
	vswprintf_s(buffer, fmt, args);
#else
	vsprintf_s(buffer, fmt, args);
#endif
	
	va_end(args);

	DWORD dwMainFlags = NULL;
	RECT r,
		rs[4];

	dwMainFlags = dwFlag | DT_CALCRECT | DT_NOCLIP;

	if (dwFlag & DT_SHADOW)
	{
		SetRect(&rs[0], (int)x - 1, (int)y, (int)x, 0);
		SetRect(&rs[1], (int)x + 1, (int)y, (int)x, 0);
		SetRect(&rs[2], (int)x, (int)y - 1, (int)x, 0);
		SetRect(&rs[3], (int)x, (int)y + 1, (int)x, 0);
		for (INT i = NULL; i < 4; i++)
		{
			this->m_pFont->DrawText(nullptr, buffer, -1, &rs[i], dwMainFlags, 0xFF000000);
			if (dwMainFlags & DT_CALCRECT)
				this->m_pFont->DrawText(nullptr, buffer, -1, &rs[i], NULL, 0xFF000000);
		}
	}
	SetRect(&r, (int)x, (int)y, (int)x, 0);
	this->m_pFont->DrawText(nullptr, buffer, -1, &r, dwMainFlags, color);
	if (dwMainFlags & DT_CALCRECT)
		this->m_pFont->DrawText(nullptr, buffer, -1, &r, NULL, color);
}


HRESULT cRender::GetTextExtent(const char* text, SIZE* pSize)
{
	if (NULL == text || NULL == pSize)
		return E_FAIL;

	RECT Rect = { 0, 0, 0, 0 };
	this->m_pFont->DrawTextA(NULL, text, -1, &Rect, DT_CALCRECT, 0xff000000);
	pSize->cx = Rect.right - Rect.left;
	pSize->cy = Rect.bottom - Rect.top;
	return S_OK;
}
cRender::~cRender()
{
}
