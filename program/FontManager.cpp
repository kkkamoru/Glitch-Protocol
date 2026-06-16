#include "FontManager.h"

GameFonts gameFonts;
void LoadFonts() {
	AddFontResourceExA("data/DotGothic16-Regular.ttf", FR_PRIVATE, NULL);

	gameFonts.mainFont = CreateFontToHandle("DotGothic16", 22, 10, DX_FONTTYPE_NORMAL);
}

void DeleteFonts() {
	DeleteFontToHandle(gameFonts.mainFont);
}