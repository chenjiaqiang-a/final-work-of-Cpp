#include "PainterEngine/PainterEngineHelper.h"
#include <iostream>

using namespace std;

int main()
{
	PX_Initialize("test", 800, 600);
	PX_GeoDrawBorder(PX_GetSurface(), 100, 100, 500, 500, 8, PX_COLOR(255, 255, 0, 0));
	PX_GeoDrawSolidRoundRect(PX_GetSurface(), 110, 110, 220, 220, 20,PX_COLOR(255, 0, 255, 0));
	while (PX_Loop());
	return 0;
}
