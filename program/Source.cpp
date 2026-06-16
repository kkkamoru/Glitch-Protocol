#include "Main.h"
#include "Scene.h"
#include "GameInit.h"

void Draw(BaseCharacter& basecharacter,float rot) {
	DrawRotaGraph(		// x‚Æy‚Í¶ã‚Å‰Šú‰»‚µ‚Ä—Ç‚¢B
		basecharacter.x + basecharacter.w / 2,
		basecharacter.y + basecharacter.h / 2,
		1.0, rot,
		basecharacter.image, TRUE);
}

// ‰æ–Ê“à‚É§Œä‚·‚é
void ClampPosition(BaseCharacter& basecharacter, int gameSizeW,int gameSizeH) {
	if (basecharacter.x < 0)	basecharacter.x = 0;
	if (basecharacter.y < 0)	basecharacter.y = 0;
	if (basecharacter.x + basecharacter.w > gameSizeW)	basecharacter.x = gameSizeW - basecharacter.w;
	if (basecharacter.y + basecharacter.h > gameSizeH)	basecharacter.y = gameSizeH - basecharacter.h;
}


void Star::DrawStar(Star& star) {
	DrawCircle(
		star.x, star.y,
		star.radius,
		GetColor(255, 255, 255),
		TRUE
	);
}