#include "cMenu.h"
#include <vector>
#include "C:\Users\sqrtb\Desktop\Visual\u\GUI DX v.2017\cRender\cRender.h"


std::vector<int> vTab(COUNT_TAB);
int  Tab_Number = 0;
int  Tab_Max = 0;
cMenu *Menu = nullptr;

cMenu::cMenu(cRender &Render, float xPos, float yPos)
{
	m_pRender = &Render;
	ShowGUI = true;
	this->xPos = xPos;
	this->yPos = yPos;
	SetColor();
	pRender->GetTextExtent("<<", &pSize);

}

void cMenu::SetColor(int iAlfa/* = 255*/)
{
	GUIColor[color_Background] = Color(iAlfa, 26, 26, 26);
	GUIColor[color_Border] = Color(iAlfa, 73, 73, 73);
	GUIColor[color_Title] = Color(iAlfa, 245, 239, 3);
	GUIColor[color_Text] = Color(iAlfa, 0, 204, 0);
	GUIColor[color_Active] = Color(iAlfa, 0, 255, 0);
	GUIColor[color_Hover] = Color(iAlfa, 0, 191, 255);
}

bool cMenu::IsInControl(float x, float y, float w, float h)
{
	POINT MousePosition;
	GetCursorPos(&MousePosition);
	ScreenToClient(GetForegroundWindow(), &MousePosition);
	return(MousePosition.x >= x && MousePosition.x <= x + w && MousePosition.y >= y && MousePosition.y <= y + h);
}


void cMenu::Draw()
{
	if (GetAsyncKeyState(VK_END) & 1)ShowGUI ^= 1;
	if (!ShowGUI)
		return;

	(ItemMenu).x = this->xPos;
	(ItemMenu).y = this->yPos + m_pCtx.HeightTitle + 4;

	m_pRender->render_Box(this->xPos, this->yPos, m_pCtx.WidthMain, m_pCtx.HeightTitle, GUIColor[color_Background]);
	m_pRender->render_Border(this->xPos, this->yPos, m_pCtx.WidthMain, m_pCtx.HeightTitle, GUIColor[color_Border]);
	m_pRender->render_String(this->xPos + m_pCtx.WidthMain / 2, this->yPos + m_pCtx.HeightTitle / 2 - pSize.cy / 2, GUIColor[color_Title], DT_CENTER | DT_SHADOW, L"Oblivion hack WARS");


	RenderMenu();
	Tab_Number = 0;
}


void cMenu::RenderMenu()
{
	GuiTab(L"Armor");
	GuiTab(L"Weapon");
	GuiTab(L"Dress");
	

}

void cMenu::GuiTab(TCHAR* Text)
{
	Color isHover = GUIColor[color_Border];
	if (IsInControl((ItemMenu).x, (ItemMenu).y, m_pCtx.WidthMain, m_pCtx.HeightMain))
	{
		isHover = GUIColor[color_Hover];
		if (GetAsyncKeyState(VK_LBUTTON) & 1)
		{
			if (vTab[Tab_Number] != 1)
				vTab[Tab_Number] = 1;
		}
	}
	if (vTab[Tab_Number])
	{
		isHover = GUIColor[color_Active];
		for (int i = 0; i < COUNT_TAB; i++)
			if (i != Tab_Number) vTab[i] = 0;
	}

	m_pRender->render_Box((ItemMenu).x, (ItemMenu).y, m_pCtx.WidthMain, m_pCtx.HeightMain, GUIColor[color_Background]);
	m_pRender->render_Border((ItemMenu).x, (ItemMenu).y, m_pCtx.WidthMain, m_pCtx.HeightMain, isHover);
	m_pRender->render_String((ItemMenu).x + m_pCtx.WidthMain / 2, (ItemMenu).y + m_pCtx.HeightMain / 2 - pSize.cy / 2, GUIColor[color_Text], DT_CENTER | DT_SHADOW, Text);


	Tab_Number = Tab_Number + 1;
	if (Tab_Max < Tab_Number)
		Tab_Max = Tab_Number;
	(ItemMenu).y = (ItemMenu).y + m_pCtx.HeightMain + 2;
}




cMenu::~cMenu()
{
}
