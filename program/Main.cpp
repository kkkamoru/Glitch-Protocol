#include "Main.h"
#include "Stage1.h"
#include "Scene.h"

char KeyBuffer[256];
int KeyFrame[256];
int MouseLeftFrame;
int MouseRightFrame;

//---------------------------------------------------------------------------------
//	WinMain
//---------------------------------------------------------------------------------
int WINAPI WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow )
{
	int Time;


	SetOutApplicationLogValidFlag( FALSE );
	ChangeWindowMode(FALSE);	// フルスクリーンはFALSE
	SetMainWindowText( "サンプル" );
	SetBackgroundColor( 100, 100, 100 );

	SetDoubleStartValidFlag( TRUE );
	SetAlwaysRunFlag( TRUE );

	SetGraphMode( screenW, screenH, 32 );

	if( DxLib_Init() == -1 )	return -1;

	SetDrawScreen( DX_SCREEN_BACK );
	SetTransColor( 255, 0, 255 );
	srand( GetNowCount() % RAND_MAX );

	for( int i = 0; i < 256; i++ ){
		KeyFrame[i] = 0;
	}
	MouseLeftFrame = 0;
	MouseRightFrame = 0;

	SceneInit();

	while( TRUE )
	{
		Time = GetNowCount();
		ClearDrawScreen();

		GetHitKeyStateAll( KeyBuffer );

		for( int i = 0; i < 256; i++ ){
			if( KeyBuffer[i] )	KeyFrame[i]++;
			else				KeyFrame[i] = 0;
		}

		if( CheckMouseInput( MOUSE_INPUT_LEFT ) )	MouseLeftFrame++;
		else										MouseLeftFrame = 0;

		if( CheckMouseInput( MOUSE_INPUT_RIGHT ) )	MouseRightFrame++;
		else										MouseRightFrame = 0;

		SceneUpdate();
		SceneRender();

		ScreenFlip();
		while( GetNowCount() - Time < 17 ){}
		if( ProcessMessage() )	break;
		if( CheckHitKey( KEY_INPUT_ESCAPE ) )	break;
	}

	SceneExit();

	DxLib_End();
	return 0;
}

//---------------------------------------------------------------------------------
//	キーが押された瞬間を取得する
//---------------------------------------------------------------------------------
bool PushHitKey( int key )
{
	if( KeyFrame[key] == 1 ){
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------
//	マウスが押されているかを取得する
//---------------------------------------------------------------------------------
bool CheckMouseInput( int button )
{
	if( GetMouseInput() & button ){
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------
//	マウスが押された瞬間を取得する
//---------------------------------------------------------------------------------
bool PushMouseInput( int button )
{
	if( button & MOUSE_INPUT_LEFT ){
		if( MouseLeftFrame == 1 ){
			return true;
		}
	}
	if( button & MOUSE_INPUT_RIGHT ){
		if( MouseRightFrame == 1 ){
			return true;
		}
	}
	return false;
}
//---------------------------------------------------------------------------------
//	マウスの座標を取得する
//---------------------------------------------------------------------------------
int GetMouseX()
{
	int mouse_x;
	int mouse_y;
	GetMousePoint( &mouse_x, &mouse_y );
	return mouse_x;
}
int GetMouseY()
{
	int mouse_x;
	int mouse_y;
	GetMousePoint( &mouse_x, &mouse_y );
	return mouse_y;
}

//---------------------------------------------------------------------------------
//	２点の長さを取得する関数
//---------------------------------------------------------------------------------
float GetDistance(float x1, float y1, float x2, float y2)
{
	float x = x1 - x2;
	float y = y1 - y2;
	float distance = sqrtf(x * x + y * y);
	return distance;
}

//--------------------------------------------------------------------
// 四角同士の当たり判定
//--------------------------------------------------------------------
bool CheckBoxHit(const BaseCharacter& c1,const BaseCharacter& c2) {
	if (c1.x + c1.w >= c2.x && c1.x <= c2.x + c2.w) {
		if (c1.y + c1.h >= c2.y && c1.y <= c2.y + c2.h) {
			return true;
		}
	}
	return false;
}

//---------------------------------------------------------------------------------
//	点と円の当たり判定
//---------------------------------------------------------------------------------
bool CheckPointCircleHit(float point_x, float point_y, float circle_x, float circle_y, float circle_r)
{
	float distance = GetDistance(point_x, point_y, circle_x, circle_y);
	if (distance <= circle_r) {
		return true;
	}
	return false;
}

//---------------------------------------------------------------------------------
//	円と四角の当たり判定
//---------------------------------------------------------------------------------
bool CheckCircleBoxHit(float circle_x, float circle_y, float circle_r, float box_x, float box_y, float box_w, float box_h)
{
	float near_x = circle_x;
	if (near_x < box_x)			near_x = box_x;
	if (near_x > box_x + box_w)	near_x = box_x + box_w;

	float near_y = circle_y;
	if (near_y < box_y)			near_y = box_y;
	if (near_y > box_y + box_h)	near_y = box_y + box_h;

	if (CheckPointCircleHit(near_x, near_y, circle_x, circle_y, circle_r)) {
		return true;
	}

	return false;
}


//---------------------------------------------------------------------------------
//	度をラジアンに変換する関数
//---------------------------------------------------------------------------------
float TO_RADIAN(float degree)
{
	return degree * 3.14159265f / 180.0f;
}

//---------------------------------------------------------------------------------
//	ラジアンを度に変換する関数
//---------------------------------------------------------------------------------
float TO_DEGREE(float radian)
{
	return radian * 180.0f / 3.14159265f;
}

//---------------------------------------------------------------------------------
//	0.0 ～ 1.0 までのランダムな値を返す関数（ float 型）
//---------------------------------------------------------------------------------
float GetRandomF()
{
	//	０～ RAND_MAX（32767）までのランダムな値を取得
	float random = (float)rand();
	//	この値を RAND_MAX で割った値（ 0.0 ～ 1.0 ）を返す
	return random / RAND_MAX;
}

//---------------------------------------------------------------------------------
//	0.0 ～ f_max までのランダムな値を返す関数（ float 型）
//---------------------------------------------------------------------------------
float GetRandomF(float f_max)
{
	//	0.0 ～ 1.0 の値を取得
	float random = GetRandomF();
	//	この値を f_max 倍したものを返す
	return random * f_max;
}

//---------------------------------------------------------------------------------
//	f_from ～ f_to までのランダムな値を返す関数（ float 型）
//---------------------------------------------------------------------------------
float GetRandomF(float f_from, float f_to)
{
	//	２つの値の差（この幅のランダムが欲しい）
	float value = f_to - f_from;
	//	0.0 ～この値までのランダムな値
	float random = GetRandomF(value);
	//	そのランダムな値に from の値を足したものを返す
	return f_from + random;
}
