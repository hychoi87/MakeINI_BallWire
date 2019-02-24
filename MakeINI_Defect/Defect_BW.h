#pragma once

#include "Resource.h"
#include <iostream>
using namespace std;

extern int BallSizeMethod;
extern int BallSizeKernel ;
extern int NTCBallSizeKernel ;
extern int BallSizeGain ;
extern int BallFindMethod ;
extern int BallAdapSize ;
extern int BallAdapSize2 ;
extern int ChipTop ;
extern int ALNSizeCheck ;
extern int NTCSizeCheck ;
extern int ChipSizeCheck ;
extern int WireCheck ;
extern double CoefficientGain ;
extern int ALNBallSize ;
extern double Version;
extern int BallPositionMargin;
extern double BallFindVal;
extern int WireSweepVal;
extern int ChipInsideWidth;
extern int InsideChipOffest;
extern int ALNPositionCheck;
extern int GoldPadBottomCheck;

extern double ChipBallSizeFail_low;
extern double ChipBallSizeFail_high;
extern double NTCBallSizeFail_low;
extern double NTCBallSizeFail_high;
extern double ALNBallSizeFail_low;
extern double ALNBallSizeFail_high;

extern double ALNBallPOSLeft_low   ;
extern double ALNBallPOSLeft_high  ;
extern double ALNBallPOSRight_low  ;
extern double ALNBallPOSRight_high ;
extern double ALNBallPOSBottom_low ;
extern double ALNBallPOSBottom_high;
// Defect_BW 대화 상자입니다.

class Defect_BW : public CDialog
{
	DECLARE_DYNAMIC(Defect_BW)

public:
	Defect_BW(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Defect_BW();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_BallSizeKernel ;
	int m_NTCBallSizeKernel ;
	int m_BallSizeGain ;
	int m_BallAdapSize ;
	int m_BallAdapSize2 ;
	int m_ChipTop ;
	int m_ALNSizeCheck ;
	int m_NTCSizeCheck ;
	int m_ChipSizeCheck ;
	int m_WireCheck ;
	double m_CoefficientGain ;
	int m_ALNBallSize ;
	double m_Version;
	int m_InsideChipOffest;
	int m_ALNPositionCheck;
	int m_GoldPadBottomCheck;

	int m_BallPositionMargin;
	double m_BallFindVal;
	int m_WireSweepVal;
	int m_ChipInsideWidth;

	double m_ChipBallSizeFail_low;
	double m_ChipBallSizeFail_high;
	double m_NTCBallSizeFail_low;
	double m_NTCBallSizeFail_high;
	double m_ALNBallSizeFail_low;
	double m_ALNBallSizeFail_high;

	double m_ALNBallPOSLeft_low   ;
	double m_ALNBallPOSLeft_high  ;
	double m_ALNBallPOSRight_low  ;
	double m_ALNBallPOSRight_high ;
	double m_ALNBallPOSBottom_low ;
	double m_ALNBallPOSBottom_high;

	afx_msg void OnEnChangeEdit_BW();
	afx_msg void OnCbnSelchangeCombo3();
	int m_BallSizeMethod;
	int m_BallFindMethod;
	afx_msg void OnBnClickedCheck1();
	void PutData();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
