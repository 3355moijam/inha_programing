﻿#pragma once
#include "cFrameCounter.h"
#include "cGuideline.h"
//#include "cCamera.h"
//#include "cCharacter.h"
//#include "cCube.h"
//#include "cGrid.h"

class CMainUI;
class CZealot;
class CFrustum;
class CFrustumCube;
class CSkinnedMesh;
class CObj_X;
class cFieldMap;
class CRay;
class cSphere;
class cMtlTex;
class cFrame;
class cGroupNode;
class cGroup;
class cCubeObj;
class cCubeMan2;
class cCubeMan;
class cCubePC;
class cCamera2;
class cGrid2;
class cPointLight;
class cDirectionalLight;
class cSpotLight;


class cMainGame
{
private:
	//vector<ST_PC_VERTEX> m_vecLineVertex;
	//vector<ST_PC_VERTEX> m_vecTriangleVertex;
	//cCube cube;
	//cGrid grid;
	//cCamera camera;
	//cCharacter player;

	cCubePC*	m_pCubePC;
	cCamera2*	m_pCamera;
	cGrid2*		m_pGrid;

	cCubeMan*	m_pCubeMan;

	// >> for texture
	LPDIRECT3DTEXTURE9	m_pTexture;
	vector<ST_PT_VERTEX> m_vecVertex;
	// <<

	// >> lighting
	cPointLight*		m_PointLight;
	cDirectionalLight*	m_DirectionalLight;
	cSpotLight*			m_SpotLight;
	// <<

	cGuideline*			m_pRoute;
	cGuideline*			m_pShort;

	cCubeMan2*			m_pRouteMan;
	cCubeMan2*			m_pShortCutMan;

	cCubeObj*			m_pCubeObj;

	vector<cGroup*>		m_vecGroup;
	vector<cGroup*>		m_vecGroupSurf;

	iMap*				m_pMap;
	vector<cGroupNode*> m_vecGroupNode;

	cFrame*				m_pRootFrame;
	vector<cFrame*>		m_vecRootFrame;

	LPD3DXFONT			m_pFont;
	cFrameCounter		m_FrameCounter;

	
public:
	cMainGame();
	~cMainGame();

	void setup();
	void update();
	void Draw_Texture();
	void render();
	
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Set_Light();

	void Setup_Obj();
	void Obj_Render();

	void Load_Surface();


private:
	LPD3DXMESH			m_pMeshTeapot;
	LPD3DXMESH			m_pMeshSphere;
	D3DMATERIAL9		m_stMtlTeapot;
	D3DMATERIAL9		m_stMtlSphere;

	LPD3DXMESH			m_pObjMesh;
	vector<cMtlTex*>	m_vecObjMtltex;
public:
	void Setup_MeshObject();
	void Mesh_Render();

	// >> peaking
private:
	vector<cSphere*>	m_vecSphere;
	CRay*				m_pcRay;
public:
	void				SetupPeakingObj();
	void				RenderPeakingObj();

//private:
//	vector<ST_SPHERE>	m_vecSphereT;
//	D3DMATERIAL9		m_stMtlNone;
//	D3DMATERIAL9		m_stMtlPicked;
//	D3DMATERIAL9		m_stMtlPlane;
//	vector<ST_PN_VERTEX> m_vecPlaneVertex;
//	D3DXVECTOR3			m_vPickedPosition;
//public:
//	void Setup_MeshObjectT();
//	void Mesh_RenderT();
//	void Setup_PickingObj();
//	void PickingObj_Render();
	// <<

	// >> cFieldMap
private:
	cFieldMap*			m_pFieldMap;
	
	// <<
	// >> anim
private:
	CObj_X*				m_pObj_X;
	CSkinnedMesh*		m_pSkinnedMesh;
public:
	void SkinnedMesh_Render();
	// <<
	// >> frustum culling
private:
	CFrustumCube*		m_pFrustumCube;

	LPD3DXMESH			m_pSphere;
	D3DMATERIAL9		m_stCullingMtl;
	vector<cSphere*>	m_vecCullingSphere;
	CFrustum*			m_pFrustum;
public:
	void SetupFrustum();
	void FrustumRender();
	// <<

	// >> obb
private:
	CZealot*		m_pHoldZealot;
	CZealot*		m_pMoveZealot;
public:
	void SetupOBB();
	void OBBRender();
	// <<

	// >> font
private:
	LPD3DXFONT			m_pFont2;
	ID3DXMesh*			m_p3DText;
public:
	void CreateFontW();
	void TextRender();
	
	// <<

	// >> ui
private:
	LPD3DXSPRITE			m_pSprite;
	D3DXIMAGE_INFO			m_stImageInfo;
	LPDIRECT3DTEXTURE9		m_pTextureUI;
public:
	void SetupUI();
	void UIRender();
	// <<

	// >> mainUI
private:
	CMainUI*				m_pMainUI;
	// <<

	// >> particle
private:
	vector<ST_PC_VERTEX>	m_vecVertexParticle;
public:
	void SetupParticle();
	void UpdateParticle();
	void ParticleRender();
	
	// <<

private:
	LPDIRECT3DTEXTURE9		m_pTex0;
	LPDIRECT3DTEXTURE9		m_pTex1;
	LPDIRECT3DTEXTURE9		m_pTex2;
	LPDIRECT3DTEXTURE9		m_pTex3;
	vector<ST_PT_VERTEX>	m_vecVertex_Multi;

	int						m_nType;
public:
	void SetupMultiTexture();
	void UpdateMultiTexture();
	void MultiTextureRender();

	void MultiTextureRender1();
	void MultiTextureRender2();
	void MultiTextureRender3();
	void MultiTextureRender4();
	void MultiTextureRender5();
	void MultiTextureRender6();
	void MultiTextureRender7();
	void MultiTextureRender8();
	void MultiTextureRender9();
	void MultiTextureRender0();
	void MultiTextureRender_default();
	
};
