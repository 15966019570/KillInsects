/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#ifndef _LESSON_X_H_
#define _LESSON_X_H_
//
#include <Windows.h>
#include <vector>
using namespace std;

/////////////////////////////////////////////////////////////////////////////////
//
// ��Ϸ�ܹ��ࡣ��������Ϸ��ѭ������Ϸ��ʼ���������ȹ���
class	CGameMain
{
private:
	int				m_iGameState;		// ��Ϸ״̬��0���������ߵȴ���ʼ��1����ʼ����2��ʾδ��ʼ����ʱ���Ӳ�������ƶ�����3 ��ʾ����ʱ�׶Σ� 4��ʾ��ʼ���ӿ���������ƶ����Ĵ�
    float			m_fRotateTime;		// �������º���븴λ�������ʱ��
    float			m_fOldRotation;		// ���ӵĳ�ʼ�Ƕ�
    CSprite		    *paizi;

    int				countdownTime ;	    //����ʱʱ��
	float			countPassedTime;	//����ʱ������ʱ��
	CTextSprite		*countdown;		    //����ʱ�����־���
    CSprite			*kaishi;			//���ո�ʼ������


    vector<CSprite*>m_mosquitos;
    int				m_iMosquitoCount;

public:
	CGameMain();                        //���캯��
	~CGameMain();                       //��������

	// Get����
	int				GetGameState()											{ return m_iGameState; }

	// Set����
	void			SetGameState( const int iState )				{ m_iGameState	=	iState; }

	// ��Ϸ��ѭ����
	void			GameMainLoop( float	fDeltaTime );
	void			GameInit();
	void			GameRun( float fDeltaTime );
	void			GameEnd();

	void			OnMouseMove( const float fMouseX, const float fMouseY );
	void			OnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY );

    void            OnKeyDown( const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress );

    void            MakeSprite();
};

/////////////////////////////////////////////////////////////////////////////////
//
extern CGameMain	g_GameMain;

#endif // _LESSON_X_H_
