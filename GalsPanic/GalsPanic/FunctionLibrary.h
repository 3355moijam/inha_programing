#pragma once

#define SWAP(a,b,temp) {temp = a, a = b, b = temp;}

void DrawGrid(HDC hdc, int x1, int y1, int x2, int y2, int interval);

void DrawCircle(HDC hdc, int centerX, int centerY, int radius);

void DrawCircle(HDC hdc, POINT center, int radius);

BOOL MoveToEx(HDC hdc, POINT to);

BOOL LineTo(HDC hdc, POINT to);

bool IsBetweenPt(POINT& target, POINT& p1, POINT& p2, int mode = 0);

bool operator==(const POINT& lhs, const POINT& rhs);

bool operator!=(const POINT& lhs, const POINT& rhs);

POINT operator-(const POINT& lhs, const POINT& rhs);

HRGN CreatePolyVectorRgn(polygon &poly, int iMode = WINDING);

BOOL PtInRegion(HRGN &hrgn, POINT &target);

bool PtOnPoly(polygon& poly, POINT & target);

int PtDistance(const POINT & p1, const POINT & p2);

bool PtInPoly(const polygon& poly, POINT & target);

double getPolyArea(const polygon& poly);

