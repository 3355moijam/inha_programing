﻿#pragma once
#include "stdafx.h"


class cCube
{
private:
	vector<ST_PC_VERTEX> vertex;
	//vector<DWORD> verIndex;
	vector<ST_PC_VERTEX> verIndex;

	D3DXVECTOR3 pos_;
	D3DXVECTOR3 rotate_;
	D3DXVECTOR3 direct_;
	D3DXVECTOR3 scale_;
	float speed;

public:
	cCube();

	D3DXVECTOR3& get_pos(){	return pos_; }
	__declspec(property(get = get_pos)) D3DXVECTOR3& pos;

	D3DXVECTOR3& get_rotate(){	return rotate_; }
	__declspec(property(get = get_rotate)) D3DXVECTOR3& rotate;

	D3DXVECTOR3& get_scale() { return scale_; }
	__declspec(property(get = get_scale)) D3DXVECTOR3& scale;

	void render();
	void render(D3DXMATRIXA16& matUpperWorld);
	void render(D3DXMATRIXA16& matS, D3DXMATRIXA16& matX, D3DXMATRIXA16& matY, D3DXMATRIXA16& matZ, D3DXMATRIXA16& matT);

	void update();
	//void getInput();
	//void render(HDC hdc, cMatrix& matWVP, cMatrix& matViewport, D3DXVECTOR3& cameraDirect);
	D3DXVECTOR3 move(float dir);
};
