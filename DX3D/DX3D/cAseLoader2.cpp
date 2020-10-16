﻿#include "stdafx.h"
#include "cAseLoader2.h"
#include "Asciitok.h"
#include "cFrame.h"
#include "cMtlTex.h"

cAseLoader2::cAseLoader2(): m_fp(nullptr), m_szToken{}, m_dwTicksPerFrame(0), m_dwFirstFrame(0), m_dwLastFrame(0),
                            m_dwFrameSpeed(0)
{
}

cAseLoader2::~cAseLoader2()
{
}

cFrame* cAseLoader2::Load(char* szFullPath)
{
	cFrame* pRoot = nullptr;

	fopen_s(&m_fp, szFullPath, "r");

	while (char* szToken = GetToken())
	{
		if (IsEqual(szToken,ID_SCENE))
		{
			// : skip
			ProcessScene();
		}
		else if (IsEqual(szToken, ID_MATERIAL_LIST))
		{
			ProcessMATERIAL_LIST();
		}
		else if (IsEqual(szToken, ID_GEOMETRY))
		{
			cFrame* pFrame = ProcessGEOMOBJECT();
			if (pRoot == nullptr)
			{
				pRoot = pFrame;
				Set_SceneFrame(pRoot);
			}
		}
	}
	fclose(m_fp);

	for (auto * p : m_vecMtlTex)
	{
		SafeRelease(p);
	}
	m_vecMtlTex.clear();
	
	pRoot->CalcOriginLocalTM(NULL);
	
	return pRoot;
}

char* cAseLoader2::GetToken()
{
	int nReadCnt = 0;
	bool isQuote = false;
	while (true)
	{
		char c = fgetc(m_fp);
		if (feof(m_fp))
			break;

		if (c == '\"')
		{
			if (isQuote)
				break;
			isQuote = true;
			continue;
		}

		if(!isQuote && IsWhite(c))
		{
			if (nReadCnt == 0)
				continue;
			else
				break;
			
		}

		m_szToken[nReadCnt++] = c;
	}

	if (nReadCnt == 0)
		return nullptr;

	m_szToken[nReadCnt] = '\0';

	return m_szToken;
}

int cAseLoader2::GetInteger()
{
	return atoi(GetToken());
}

float cAseLoader2::GetFloat()
{
	return (float)atof(GetToken());
}

bool cAseLoader2::IsWhite(char c)
{
	return c < 33;
}

bool cAseLoader2::IsEqual(char* str1, char* str2)
{
	return strcmp(str1, str2) == 0;
}

void cAseLoader2::SkipBlock()
{
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if(IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
	}
	while (nLevel > 0);
}

void cAseLoader2::ProcessMATERIAL_LIST()
{
	int nLevel = 0;
	do
	{
		char *szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if(IsEqual(szToken, ID_MATERIAL_COUNT))
		{
			for (auto * p : m_vecMtlTex)
			{
				SafeRelease(p);
			}
			m_vecMtlTex.resize(GetInteger());
		}
		else if(IsEqual(szToken, ID_MATERIAL))
		{
			int nIndex = GetInteger();
			m_vecMtlTex[nIndex] = new cMtlTex;
			m_vecMtlTex[nIndex]->SetAttrID(nIndex);
			ProcessMATERIAL(m_vecMtlTex[nIndex]);
		}
	}
	while (nLevel > 0);
}

void cAseLoader2::ProcessMATERIAL(cMtlTex* pMtlTex)
{
	D3DMATERIAL9	stMtl{};
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_AMBIENT))
		{
			stMtl.Ambient.r = GetFloat();
			stMtl.Ambient.g = GetFloat();
			stMtl.Ambient.b = GetFloat();
			stMtl.Ambient.a = 1.0f;
		}
		else if (IsEqual(szToken, ID_DIFFUSE))
		{
			stMtl.Diffuse.r = GetFloat();
			stMtl.Diffuse.g = GetFloat();
			stMtl.Diffuse.b = GetFloat();
			stMtl.Diffuse.a = 1.0f;
		}
		else if (IsEqual(szToken, ID_SPECULAR))
		{
			stMtl.Specular.r = GetFloat();
			stMtl.Specular.g = GetFloat();
			stMtl.Specular.b = GetFloat();
			stMtl.Specular.a = 1.0f;
		}
		else if (IsEqual(szToken, ID_MAP_DIFFUSE))
		{
			ProcessMAP_DIFFUSE(pMtlTex);
		}
	} while (nLevel > 0);

	pMtlTex->SetMaterial(stMtl);
}

void cAseLoader2::ProcessMAP_DIFFUSE(cMtlTex* pMtlTex)
{
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_BITMAP))
		{
			szToken = GetToken();
			pMtlTex->SetTexture(g_pTextureManager.GetTexture(szToken));
		}
	} while (nLevel > 0);
}

cFrame* cAseLoader2::ProcessGEOMOBJECT()
{
	cFrame * pFrame = new cFrame;
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_NODE_NAME))
		{
			m_mapFrame[GetToken()] = pFrame;
		}
		else if (IsEqual(szToken, ID_NODE_PARENT))
		{
			m_mapFrame[GetToken()]->AddChild(pFrame);
		}
		else if (IsEqual(szToken, ID_NODE_TM))
		{
			ProcessNODE_TM(pFrame);
		}
		else if (IsEqual(szToken, ID_MESH))
		{
			ProcessMESH(pFrame);
		}
		else if (IsEqual(szToken, ID_TM_ANIMATION))
		{
			ProcessTM_ANIMATION(pFrame);
		}
		else if (IsEqual(szToken, ID_MATERIAL_REF))
		{
			int nMtlIndex = GetInteger();
			pFrame->SetMtlTex(m_vecMtlTex[nMtlIndex]);
		}
	} while (nLevel > 0);
	
	return pFrame;
}

void cAseLoader2::ProcessMESH(cFrame* pFrame)
{
	vector<D3DXVECTOR3> vecV;
	vector<D3DXVECTOR2> vecVT;
	vector<ST_PNT_VERTEX> vecVertex;
	
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MESH_NUMVERTEX))
		{
			vecV.resize(GetInteger());
		}
		else if (IsEqual(szToken, ID_MESH_NUMFACES))
		{
			vecVertex.resize(GetInteger() * 3);
		}
		else if (IsEqual(szToken, ID_MESH_VERTEX_LIST))
		{
			ProcessMESH_VERTEX_LIST(vecV);
		}
		else if (IsEqual(szToken, ID_MESH_FACE_LIST))
		{
			ProcessMESH_FACE_LIST(vecVertex, vecV);
		}
		else if (IsEqual(szToken, ID_MESH_NUMTVERTEX))
		{
			vecVT.resize(GetInteger());
		}
		else if (IsEqual(szToken, ID_MESH_TVERTLIST))
		{
			ProcessMESH_TVERTLIST(vecVT);
		}
		else if (IsEqual(szToken, ID_MESH_TFACELIST))
		{
			ProcessMESH_TFACELIST(vecVertex, vecVT);
		}
		else if (IsEqual(szToken, ID_MESH_NORMALS))
		{
			ProcessMESH_NORMALS(vecVertex);
		}
	} while (nLevel > 0);
	D3DXMATRIXA16 matInvWorld;
	D3DXMatrixInverse(&matInvWorld, 0, &pFrame->GetWorldTM());
	for (int i = 0; i < vecVertex.size(); ++i)
	{
		D3DXVec3TransformCoord(&vecVertex[i].p, &vecVertex[i].p, &matInvWorld);

		D3DXVec3TransformNormal(&vecVertex[i].n, &vecVertex[i].n, &matInvWorld);
		
	}
	pFrame->SetVertex(vecVertex);
	pFrame->BuildVB(vecVertex);
	pFrame->BuildIB(vecVertex);
}

void cAseLoader2::ProcessMESH_VERTEX_LIST(vector<D3DXVECTOR3>& vecV)
{
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MESH_VERTEX))
		{
			int nIndex = GetInteger();
			vecV[nIndex].x = GetFloat();
			vecV[nIndex].z = GetFloat();
			vecV[nIndex].y = GetFloat();
		}
	} while (nLevel > 0);
}

void cAseLoader2::ProcessMESH_FACE_LIST(vector<ST_PNT_VERTEX>& vecVertex, vector<D3DXVECTOR3>& vecV)
{
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MESH_FACE))
		{
			int nFaceIndex = GetInteger();
			// 문자 하나 버림
			GetToken(); vecVertex[nFaceIndex * 3 + 0].p = vecV[GetInteger()];
			GetToken(); vecVertex[nFaceIndex * 3 + 2].p = vecV[GetInteger()];
			GetToken(); vecVertex[nFaceIndex * 3 + 1].p = vecV[GetInteger()];
		}
	} while (nLevel > 0);
}

void cAseLoader2::ProcessMESH_TVERTLIST(vector<D3DXVECTOR2>& vecVT)
{
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MESH_TVERT))
		{
			int nIndex = GetInteger();
			vecVT[nIndex].x = GetFloat();
			vecVT[nIndex].y = 1.0f - GetFloat();
		}
	} while (nLevel > 0);
}

void cAseLoader2::ProcessMESH_TFACELIST(vector<ST_PNT_VERTEX>& vecVertex, vector<D3DXVECTOR2>& vecVT)
{
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MESH_TFACE))
		{
			int nFaceIndex = GetInteger();
			vecVertex[nFaceIndex * 3 + 0].t = vecVT[GetInteger()];
			vecVertex[nFaceIndex * 3 + 2].t = vecVT[GetInteger()];
			vecVertex[nFaceIndex * 3 + 1].t = vecVT[GetInteger()];
		}
	} while (nLevel > 0);
}

void cAseLoader2::ProcessMESH_NORMALS(vector<ST_PNT_VERTEX>& vecVertex)
{
	int nFaceIndex = 0;
	int aModIndex[3] = { 0,2,1 };
	int nModCount = 0;

	
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MESH_FACENORMAL))
		{
			nFaceIndex = GetInteger();
			nModCount = 0;
		}
		else if (IsEqual(szToken, ID_MESH_VERTEXNORMAL))
		{
			GetToken();
			D3DXVECTOR3 n;
			n.x = GetFloat();
			n.z = GetFloat();
			n.y = GetFloat();

			vecVertex[nFaceIndex * 3 + aModIndex[nModCount++]].n = n;
		}
	} while (nLevel > 0);
}

void cAseLoader2::ProcessNODE_TM(cFrame* pFrame)
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_TM_ROW0))
		{
			matWorld._11 = GetFloat();
			matWorld._13 = GetFloat();
			matWorld._12 = GetFloat();
		}
		else if (IsEqual(szToken, ID_TM_ROW1))
		{
			matWorld._31 = GetFloat();
			matWorld._33 = GetFloat();
			matWorld._32 = GetFloat();
		}
		else if (IsEqual(szToken, ID_TM_ROW2))
		{
			matWorld._21 = GetFloat();
			matWorld._23 = GetFloat();
			matWorld._22 = GetFloat();
		}
		else if (IsEqual(szToken, ID_TM_ROW3))
		{
			matWorld._41 = GetFloat();
			matWorld._43 = GetFloat();
			matWorld._42 = GetFloat();
		}
	} while (nLevel > 0);

	pFrame->SetWorldTM(matWorld);
}

void cAseLoader2::ProcessTM_ANIMATION(cFrame* pFrame)
{
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_POS_TRACK))
		{
			ProcessCONTROL_POS_TRACK(pFrame);
		}
		else if (IsEqual(szToken, ID_ROT_TRACK))
		{
			ProcessCONTROL_ROT_TRACK(pFrame);
		}
	} while (nLevel > 0);
}

void cAseLoader2::ProcessCONTROL_POS_TRACK(cFrame* pFrame)
{
	vector<ST_POS_SAMPLE> vecPosTrack;
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_POS_SAMPLE))
		{
			ST_POS_SAMPLE s;
			s.n = GetInteger();
			s.v.x = GetFloat();
			s.v.z = GetFloat();
			s.v.y = GetFloat();
			vecPosTrack.push_back(s);
		}
	} while (nLevel > 0);

	pFrame->SetPosTrack(vecPosTrack);
}

void cAseLoader2::ProcessCONTROL_ROT_TRACK(cFrame* pFrame)
{
	vector<ST_ROT_SAMPLE> vecRotTrack;
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_ROT_SAMPLE))
		{
			ST_ROT_SAMPLE s;
			s.n = GetInteger();
			s.q.x = GetFloat();
			s.q.z = GetFloat();
			s.q.y = GetFloat();
			s.q.w = GetFloat();

			s.q.x *= sinf(s.q.w / 2.0f);
			s.q.y *= sinf(s.q.w / 2.0f);
			s.q.z *= sinf(s.q.w / 2.0f);
			s.q.w = cosf(s.q.w / 2.0f);

			if(!vecRotTrack.empty())
			{
				s.q = vecRotTrack.back().q * s.q;
			}
			
			vecRotTrack.push_back(s);
		}
	} while (nLevel > 0);

	pFrame->SetRotTrack(vecRotTrack);
}

void cAseLoader2::ProcessScene()
{
	int nLevel = 0;
	do
	{
		char * szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_FIRSTFRAME))
		{
			m_dwFirstFrame = GetInteger();
		}
		else if (IsEqual(szToken, ID_LASTFRAME))
		{
			m_dwLastFrame = GetInteger();
		}
		else if (IsEqual(szToken, ID_FRAMESPEED))
		{
			m_dwFrameSpeed = GetInteger();
		}
		else if (IsEqual(szToken, ID_TICKSPERFRAME))
		{
			m_dwTicksPerFrame = GetInteger();
		}
	} while (nLevel > 0);

}

void cAseLoader2::Set_SceneFrame(cFrame* pRoot)
{
	pRoot->m_dwFirstFrame = m_dwFirstFrame;
	pRoot->m_dwLastFrame = m_dwLastFrame;
	pRoot->m_dwFrameSpeed = m_dwFrameSpeed;
	pRoot->m_dwTicksPerFrame = m_dwTicksPerFrame;

}
