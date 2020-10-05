#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Color.h"
#include <stdio.h>
#include <math.h>

#define DT_SHADOW  0x0040

struct DX_VERTEX
{
	DX_VERTEX(float X, float Y, float Z, DWORD Color) :
		x(X), y(Y), z(Z), color(Color) {};
	DX_VERTEX(){}


	float x;
	float y;
	float z;
	float rhw = 1.0f;
	DWORD color;
	static const DWORD FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;
};

class cRender
{
public:
	cRender(IDirect3DDevice9 *m_pDevice);
	~cRender();

	void LostDevice();
	void ResetDevice();

	void   render_Line(float x, float y, float x2, float y2, Color color);
	void   render_Border(float x, float y, float w, float h, Color color);
	void   render_Box(float x, float y, float w, float h, Color color);
	void   render_Circle(float x, float y, float radius, Color color);
	void   render_String(float x, float y, Color color, DWORD dwFlag, const TCHAR* fmt, ...);



	HRESULT  GetTextExtent(const char* text, SIZE* pSize);
private:
	IDirect3DDevice9 *m_pDevice;
	ID3DXFont        *m_pFont;
	TCHAR            *szFomtName;
};

extern cRender *pRender;