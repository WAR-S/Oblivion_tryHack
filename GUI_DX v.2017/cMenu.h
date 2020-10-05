#pragma once
#include "C:\Users\sqrtb\Desktop\Visual\u\GUI DX v.2017\cRender/cRender.h"
/*перечисления для цветов интерфейса*/
#include <vector>
/*перечисления для цветов интерфейса*/
enum GUIColorScheme
{
	color_Background,
	color_Border,
	color_Title,
	color_Text,
	color_Active,
	color_Hover,
	COUNT_COLOR
};
/*перечисления основных кнопок*/
enum Button
{
	TAB_VISUAL, // 
	TAB_ARMOR,
	TAB_WEAPON,
	TAB_DRESS,
	COUNT_TAB
};

class cMenu
{
public:
	cMenu(cRender &Render, float xPos, float yPos);
	virtual ~cMenu();
protected:
	struct MenuItem
	{
		float x;
		float y;
	};
	struct Context
	{
		float WidthMain;
		float HeightMain;
		float WidthControl;
		float HeightControl;
		float HeightTitle;
		Context()
		{
			WidthMain = 160.f;
			HeightMain = 22.f;

			WidthControl = 350.f;
			HeightControl = 22.f;

			HeightTitle = 26.f;
		}
	};
private:
	Context  m_pCtx;
	MenuItem ItemMenu;
	Color  GUIColor[COUNT_COLOR];
public:
	void Draw();
private:
	void  RenderMenu();
	bool  IsInControl(float x, float y, float w, float h);
	void  SetColor(int iAlfa = 255);

	void  GuiTab(TCHAR *Text);
private:
	cRender *m_pRender;
	float xPos;
	float yPos;
	bool  ShowGUI;
	SIZE pSize;
};
extern cMenu *Menu;