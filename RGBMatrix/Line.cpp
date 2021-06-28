#include "Line.h"

Line::Line(Vector2i p1, Vector2i p2, RGB color): Drawable(p1, color), p2(p2) {}

void Line::draw(RGBMatrix &matrix) {
	bool yLonger=false;
	int incrementVal, endVal;
	int shortLen=p2.y-p1.y;
	int longLen=p2.x-p1.x;
	if (abs(shortLen)>abs(longLen)) {
		int swap=shortLen;
		shortLen=longLen;
		longLen=swap;
		yLonger=true;
	}
	endVal=longLen;
	if (longLen<0) {
		incrementVal=-1;
		longLen=-longLen;
	} else incrementVal=1;
	int decInc;
	if (longLen==0) decInc=0;
	else decInc=(shortLen << 16)/longLen;
	int j=0;
	if (yLonger) {	
		for (int i=0;i!=endVal+1;i+=incrementVal) {
			matrix.setPixel(Vector2i(p1.x+(j>>16), p1.y+i), color);
			j+=decInc;
		}
	} else {
		for (int i=0;i!=endVal+1;i+=incrementVal) {
			matrix.setPixel(Vector2i(p1.x+i, p1.y+(j>>16)), color);
			j+=decInc;
		}
	}
}
