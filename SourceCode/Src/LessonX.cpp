/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#include <Stdio.h>
#include "CommonClass.h"
#include "LessonX.h"

#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;
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
    score                   = new CTextSprite("score");
	gameTime                = new CTextSprite("gameTime");

    mapState                = false;
	map1                    = new CSprite("Map1");
	map2                    = new CSprite("Map2");
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

    countdownTime           = 6;		                        //����ʱʱ��Ϊ5s
    countPassedTime         = 0.f;
    countdown->SetSpriteVisible(false);
    //���õ���ʱ���ɼ�

    m_iMosquitoCount        = 15;

    m_iGameScore            = 0;                                //��ʼ���÷�

	m_fGameTime             = 30.f;		                        //��ʼ����Ϸʱ��Ϊ30s

	m_fAppearTime = 0.5f;
    m_fScreenLeft = CSystem::GetScreenLeft();
    m_fScreenRight = CSystem::GetScreenRight();
    m_fScreenBottom = CSystem::GetScreenBottom();
    m_fScreenTop = CSystem::GetScreenTop();

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
			//MakeSprite_NoFly();//���ɷɳ�
			countPassedTime = 0;		//���þ�����ʱ�䣬Ϊ��һ����Ϸ��׼��
			m_iGameState = 4;		//�л�g_iGameState 3->4
		}
    }else if(m_iGameState==4){
        m_fGameTime -= fDeltaTime;
		if(m_fGameTime > 0){
			gameTime->SetTextValue(m_fGameTime);	//����Ϸʱ��δ����������ʾʣ�����Ϸʱ��
			MakeSprite_Fly(fDeltaTime);//���ɷɳ�
		}else{
			m_iGameState = 2;		//����Ϸʱ����������g_iGameState 2->0��ת��
			//ʵ�ֵ�ͼ�л�
			map1->SetSpriteVisible(mapState);
			mapState=!mapState;
			map2->SetSpriteVisible(mapState);
			kaishi->SetSpriteVisible(true);            //��ʾ���ո�ʼ��
			m_fGameTime = 0;
			gameTime->SetTextValue(m_fGameTime);
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
	if(m_iGameState == 4)
        paizi->SetSpritePosition(fMouseX, fMouseY);	//ʹ���ӵ�λ�ú����һ��
}
//
void CGameMain::OnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY ){
	if(iMouseType == MOUSE_LEFT && m_iGameState == 4)	//����������
	{
		paizi->SetSpriteRotation(m_fOldRotation - 20);		//�������ӵ���ת�ǣ�Ϊ��ʼֵ-10
		m_fRotateTime	=	0.2f;	//�Ĵ��ʱ���� 0.2s����0.2s��ָ����ӳ�ʼ�Ƕ�
        		//�����ж������Ƿ񱻻���
		float fX,fY;
		for(int i=0;i<m_mosquitos.size();i++){		//����vector�е�����
			fX = m_mosquitos[i]->cs->GetSpritePositionX();	//��ȡ�������ڵĺ�����
			fY = m_mosquitos[i]->cs->GetSpritePositionY();	//��ȡ�������ڵ�������
			if(paizi->IsPointInSprite(fX,fY))			//�ж������Ƿ������ӵķ�Χ��
			{
				m_mosquitos[i]->cs->DeleteSprite();	//ɾ��������
				if(m_mosquitos[i]->speed<25){//ÿ�򵽵ķɳ���ٶȼӷ�
                    m_iGameScore+= m_mosquitos[i]->speed/5;
                }else {
                    m_iGameScore+= (m_mosquitos[i]->speed/5 + m_mosquitos[i]->speed/10);
                }
				score->SetTextValue(m_iGameScore);
                break;
			}
		}
	}
}

void CGameMain::OnKeyDown( const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress ){
	if( KEY_SPACE == iKey && 2 ==  m_iGameState )	//���¿ո�����Ϸ״̬Ϊ2ʱ
	{
		m_iGameState =	3;	//������Ϸ״̬���뵹��ʱ����3
		countdown->SetSpriteVisible(true);	//��ʾ����ʱ�ı���
		kaishi->SetSpriteVisible(false);		//���ء��ո�ʼ��
        m_iGameScore = 0.f;		//��ʼ����һ����Ϸ����
		m_fGameTime = 30.f;		//��ʼ����һ����Ϸʱ��
		score->SetTextValue(m_iGameScore);
		gameTime->SetTextValue(m_fGameTime);
		for(int i=0;i<m_mosquitos.size();i++){	//ɾ����һ����Ϸ��ʣ�������
			m_mosquitos[i]->cs->DeleteSprite();
		}
		m_mosquitos.clear();	//���vector
	}
}
/*
void CGameMain::MakeSprite_NoFly(){
    int minX		=	CSystem::GetScreenLeft() + 5;
    int maxX		=	CSystem::GetScreenRight() - 5;
    int minY		=	CSystem::GetScreenBottom() - 5;
    int maxY		=	CSystem::GetScreenTop() + 5;
    int	iPosX = 0, iPosY = 0;		//��������ĺ�������λ��
	int iLoop;	//ѭ�����Ʊ���
	for( iLoop = 0; iLoop < m_iMosquitoCount; iLoop++ )
	{
		char *szName = CSystem::MakeSpriteName("wenzi",iLoop);	//����iLoop������ͬ��������
		CSprite *wenzi = new CSprite(szName);
		wenzi->CloneSprite("wenziTemplate");	//����wenziTemplate
		iPosX	=	CSystem::RandomRange(minX, maxX);		//�������X����
		iPosY	=	CSystem::RandomRange(minY, maxY);		//�������Y����
		wenzi->SetSpritePosition(iPosX,iPosY);  //���ò������ӵ�λ��
		m_mosquitos.push_back(wenzi);		//ѹ��vector�м��й���
	}
}*/

void CGameMain::MakeSprite_Fly( float fDeltaTime ){
    m_fAppearTime -= fDeltaTime;	//����ɳ��ʣ�����ʱ��
    if(m_fAppearTime<0){	//ʱ�䵽�����Բ����ɳ�
		m_fAppearTime = 0.5f;		//���ò����ɳ��ʱ��
		int iDir = CSystem::RandomRange(0,3);	//���һ������
		float fposX,fposY;
        switch(iDir){
		case 0:		//top
			fposX = CSystem::RandomRange(m_fScreenLeft-5.f, m_fScreenRight+5.f);
			fposY = CSystem::RandomRange(m_fScreenTop-5.f, m_fScreenTop+5.f);
			break;
		case 1:		//bottom
			fposX = CSystem::RandomRange(m_fScreenLeft-5.f, m_fScreenRight+5.f);
			fposY =	CSystem::RandomRange(m_fScreenBottom, m_fScreenBottom+5.f);
			break;
		case 2:		//left
			fposX = CSystem::RandomRange(m_fScreenLeft-5.f,m_fScreenLeft);
			fposY = CSystem::RandomRange(m_fScreenTop-5.f, m_fScreenBottom+5.f);
			break;
		case 3:		//right
			fposX = CSystem::RandomRange(m_fScreenRight, m_fScreenRight+5.f);
			fposY = CSystem::RandomRange(m_fScreenTop-5.f, m_fScreenBottom+5.f);
			break;
        }
        srand((unsigned)time(0));
        int randTemplate = (rand() % (2-0+1))+ 0;//ʹ�� (rand() % (b-a+1))+ a��ȡ�� [a,b] ���������
		Mosquito *m = new Mosquito;	//��̬����ռ�
		m->speed = CSystem::RandomRange(10, 40);		//����ٶ�
		switch(randTemplate){
        case 0:
            m->szName = CSystem::MakeSpriteName("wenzi",m_iMosquitoCount++);		//����
            m->cs = new CSprite(m->szName);	//���Ӿ���ָ��Ҳ������struct������
            m->cs ->CloneSprite("wenziTemplate");	//��������
            break;
        case 1:
            m->szName = CSystem::MakeSpriteName("maggot",m_iMosquitoCount++);		//����
            m->cs = new CSprite(m->szName);	//���Ӿ���ָ��Ҳ������struct������
            m->cs ->CloneSprite("maggotTemplate");	//��������
            break;
        case 2:
            m->szName = CSystem::MakeSpriteName("ufo",m_iMosquitoCount++);		//����
            m->cs = new CSprite(m->szName);	//���Ӿ���ָ��Ҳ������struct������
            m->cs ->CloneSprite("ufoTemplate");	//��������
            break;
		}
		m->cs ->SetSpritePosition(fposX, fposY);
        m->next = NULL;
		float fDesX = CSystem::RandomRange(m_fScreenLeft+15.f, m_fScreenRight-15.f);
		float fDesY =  CSystem::RandomRange(m_fScreenTop+15.f, m_fScreenBottom-15.f);
		m->cs ->SpriteMoveTo(fDesX, fDesY, m->speed, false);
		m_mosquitos.push_back(m);		//ѹ��vector�м��й���
	}
}
