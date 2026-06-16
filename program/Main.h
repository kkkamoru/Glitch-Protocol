#pragma once
#ifndef __MAIN_H__
#define __MAIN_H__
#include "Source.h"

#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <time.h>
#include <math.h>

#pragma warning (disable : 4819)

#include <d3d9.h>
//#include <d3dx9.h>

#include <DxLib.h>

bool PushHitKey( int key );
bool CheckMouseInput( int button = MOUSE_INPUT_LEFT|MOUSE_INPUT_RIGHT );
bool PushMouseInput( int button = MOUSE_INPUT_LEFT|MOUSE_INPUT_RIGHT );
int GetMouseX();
int GetMouseY();

float GetDistance(float x1, float y1, float x2, float y2);
bool CheckPointCircleHit(float point_x, float point_y, float circle_x, float circle_y, float circle_r);
bool CheckCircleBoxHit(float circle_x, float circle_y, float circle_r, float box_x, float box_y, float box_w, float box_h);

bool CheckBoxHit(const BaseCharacter& c1,const BaseCharacter& c2);
float TO_RADIAN(float degree);
float TO_DEGREE(float radian);

float GetRandomF(float f_from, float f_to);

#endif