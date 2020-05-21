#include "PainterEngine/PainterEngineHelper.h"
#include <iostream>

using namespace std;

int main()
{
	PX_Initialize("test", 800, 600);

	while (PX_Loop());
}
