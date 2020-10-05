#pragma once

class Color
{

#define DEFCOLOR_SRC(name, r, g, b) static Color name##(){ return Color(r, g, b); }
public:
	int a, r, g, b;

	Color() 
	{ 
		Color(0, 0, 0, 0);
	}
	Color(int a, int r, int g, int b)
	{
		this->a = a;
		this->r = r;
		this->g = g;
		this->b = b;
	}
	Color(int r, int g, int b)
	{
		this->a = 255;
		this->r = r;
		this->g = g;
		this->b = b;
	}
	Color(unsigned long color)
	{
		this->b = (color & 0xff);
		this->g = ((color >> 8) & 0xff);
		this->r = ((color >> 16) & 0xff);
		this->a = ((color >> 24) & 0xff);
	}
	

	inline float* Base()
	{
		float fColor[3];
		fColor[0] = this->r / 255.0f;
		fColor[1] = this->g / 255.0f;
		fColor[2] = this->b / 255.0f;
		return &fColor[0];
	}
	inline float rBase() const { return this->r / 255.0f; }
	inline float gBase() const { return this->g / 255.0f; }
	inline float bBase() const { return this->b / 255.0f; }
	inline float aBase() const { return this->a / 255.0f; }


	inline operator unsigned long() const
	{ 	
		return (a << 24) | (r << 16) | (g << 8) | b;	
	}


	DEFCOLOR_SRC(Black, 0, 0, 0);
	DEFCOLOR_SRC(White, 255, 255, 255);
	DEFCOLOR_SRC(Red, 255, 0, 0);
	DEFCOLOR_SRC(Green, 0, 128, 0);
	DEFCOLOR_SRC(Blue, 0, 0, 255);
	 
};