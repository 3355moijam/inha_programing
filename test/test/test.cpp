// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <locale.h>
#include <iostream>
#include <string>
#include <algorithm>
#include "rapidjson\document.h"
#include "rapidjson\filereadstream.h"
using namespace rapidjson;

using namespace std;

#include <typeinfo>
#include <map>




int main()
{

	ColliderBox.x += 5;
	if (DigimonCollision())
		ColliderBox.x -= 5; // >> 현재 상태는 항상 부딛치지 않은 상태

	if (!DigimonCollision())
		ColliderBox.y += 5;

	void setCollerBox()
	{
		
	}
	
	return 0;
}

class Ground
{
	HBITMAP grass;
	HBITMAP dirt;
	BITMAP grassData;
	BITMAP dirtData;

	Ground();
};
drawd
Ground()
{
	grass = (HBITMAP)LoadImage(____);
	dirt = (HBITMAP)LoadImage(____);
	
	dirt ->>
}


//
//int str_len2(char src[], char tar[])
//{
//	int k = str_len1(src, tar);
//	if (k == -1)
//		return -1;
//
//	for (int i = 0; i < strlen(tar); i++)
//	{
//		src[k + i] = '*';
//	}
//	return 0;
//}

//bool isBetweenPt(POINT target, POINT p1, POINT p2)
//{
//	int distance1 = PtDistance(target, p1);
//	int distance2 = PtDistance(target, p2);
//	int distance3 = PtDistance(p1, p2);
//
//	if (distance1 + distance2 == distance3)
//		return true;
//	else
//		return false;
//}
//
//int PtDistance(POINT p1, POINT p2)
//{
//	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
//}