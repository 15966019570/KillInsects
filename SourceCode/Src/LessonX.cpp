/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#include <Stdio.h>
#include "CommonClass.h"
#include "LessonX.h"
////////////////////////////////////////////////////////////////////////////////
//
//
CGameMain		g_GameMain;

//==============================================================================
//
// ����ĳ�������Ϊ��GameMainLoop����Ϊ��ѭ��������������ÿ֡ˢ����Ļͼ��֮�󣬶��ᱻ����һ�Ρ�

//==============================================================================
//
// ���캯��
CGameMain::CGameMain()
{
	m_iGameState			= 1;
	paizi                   = new CSprite("paizi");
	countdown               = new CTextSprite("countdown");
    kaishi                  = new CSprite("kaishi");

}
//==============================================================================
//
// ��������
CGameMain::~CGameMain()
{
}

//==============================================================================
//
// ��Ϸ��ѭ�����˺���������ͣ�ĵ��ã�����ÿˢ��һ����Ļ���˺�����������һ��
// ���Դ�����Ϸ�Ŀ�ʼ�������С������ȸ���״̬.
// ��������fDeltaTime : �ϴε��ñ��������˴ε��ñ�������ʱ��������λ����
void CGameMain::GameMainLoop( float	fDeltaTime )
{
	switch( GetGameState() )
	{
		// ��ʼ����Ϸ�������һ���������
	case 1:
		{
			GameInit();
			SetGameState(2); // ��ʼ��֮�󣬽���Ϸ״̬����Ϊ������
		}
		break;

		// ��Ϸ�����У����������Ϸ�߼�
	case 2:
    case 3:
    case 4:

		{
			// TODO �޸Ĵ˴���Ϸѭ�������������ȷ��Ϸ�߼�
			if( true )
			{
				GameRun( fDeltaTime );
			}
			else // ��Ϸ������������Ϸ���㺯����������Ϸ״̬�޸�Ϊ����״̬
			{
				SetGameState(0);
				GameEnd();
			}
		}
		break;

		// ��Ϸ����/�ȴ����ո����ʼ
	case 0:
	default:
		break;
	};
}
//=============================================================================
//
// ÿ�ֿ�ʼǰ���г�ʼ���������һ���������
void CGameMain::GameInit()
{
    CSystem::ShowCursor(false);	                                //�������
    m_fRotateTime           = 0.f;
    m_fOldRotation          = paizi->GetSpriteRotation();		//��ȡ���ӵĳ�ʼ�Ƕ�

    countdownTime = 6;		                                    //����ʱʱ��Ϊ5s
    countPassedTime = 0.f;
    countdown->SetSpriteVisible(false);		                    //���õ���ʱ���ɼ�

    m_iMosquitoCount = 15;

}
//=============================================================================
//
// ÿ����Ϸ������
void CGameMain::GameRun( float fDeltaTime )
{
    if(m_iGameState==3){	//m_iGameState Ϊ3ʱ��ִ��
		countPassedTime += fDeltaTime;	//ͳ�ƾ�����ʱ�䣬���洢��countPassedTime
        countdown->SetTextValue(countdownTime -countPassedTime);
		if(countPassedTime >= countdownTime){	//������ʱ�䳬��countdownTime
			countdown->SetSpriteVisible(false);	//����countdown
			countPassedTime = 0;		//���þ�����ʱ�䣬Ϊ��һ����Ϸ��׼��
			m_iGameState = 4;		//�л�g_iGameState 3->4
		}
    }

    if(m_fRotateTime > 0)	{
		m_fRotateTime -= fDeltaTime;	//ÿ����fDeltaTime��������ת��ʱ��Ҳ����fDeltaTime
		if(m_fRotateTime <= 0){	//������0.2s�Ժ�
			paizi->SetSpriteRotation(m_fOldRotation);	//�ָ����ӵĳ�ʼ��ת��
		}
	}

}
//=============================================================================
//
// ������Ϸ����
void CGameMain::GameEnd()
{
}
//ʹ���ӵ�λ�ú����һ��
void CGameMain::OnMouseMove( const float fMouseX, const float fMouseY ){
	if(m_iGameState==4)
        paizi->SetSpritePosition(fMouseX, fMouseY);	//ʹ���ӵ�λ�ú����һ��
}
//
void CGameMain::OnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY ){
	if(iMouseType == MOUSE_LEFT && m_iGameState == 4)	//����������
	{
		paizi->SetSpriteRotation(m_fOldRotation - 20);		//�������ӵ���ת�ǣ�Ϊ��ʼֵ-10
		m_fRotateTime	=	0.2f;	//�Ĵ��ʱ���� 0.2s����0.2s��ָ����ӳ�ʼ�Ƕ�
	}
}

void CGameMain::OnKeyDown( const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress ){
	if( KEY_SPACE == iKey && 2 ==  m_iGameState )	//���¿ո�����Ϸ״̬Ϊ2ʱ
	{
		m_iGameState =	3;	//������Ϸ״̬���뵹��ʱ����3
		countdown->SetSpriteVisible(true);	//��ʾ����ʱ�ı���
		kaishi->SetSpriteVisible(false);		//���ء��ո�ʼ��
	}
}
