// MenuManager.h : 

/* Copyright (c) Prakash Prasad, 2009. */

/* This program is freely distributable without licensing fees 
   and is provided without guarantee or warrantee expressed or 
   implied. This program is -not- in the public domain.

 * Permission to use, copy, modify, and distribute this software for 
 * any purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright notice
 * and this permission notice appear in supporting documentation, and that 
 * the name of Prakash Prasad not be used in advertising
 * or publicity pertaining to distribution of the software without specific,
 * written prior permission. 

 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS"
 * AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL PRAKASH
 * PRASAD  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
 * KIND, OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION,
 * LOSS OF PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF
 * THIRD PARTIES, WHETHER OR NOT PRAKASH PRASAD HAS BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE
 * POSSESSION, USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef __MenuManager_h
#define __MenuManager_h

class MenuManager
{
private:
	int mHoleScore;
	int mTotalScore;
	int mHolePar;
	map<int, Menu> mMenus;
	int activeMenuIndex;

public:
	bool isActive;

	void init(void);
	void init(string courseName, vector<string> holes);
	void ResetScores(void);
	void RearrangeMenus(void);
	void setActiveMenu(int index);
	int getActiveMenu(void);
	void incrementStroke(void);
	void ResetHoleStrokes(void);
	void SetHolePar(int par);
	void updatePower(void);
	int getPower(void);
	int CheckClick(int x, int y);
	void Draw(bool stationary, bool playCurrentHoleOnly);
	void DrawHUD(bool stationary, bool playCurrentHoleOnly);
};

#endif