/************************************************
 * TODO Auther: by SR
 * FilePath: \digital designc:\Users\SR\Documents\vscodefile\games\utopia_engine\SearchArea.cpp
 * Date: 2020-05-04 11:06:42
 * LastEditTime: 2020-05-11 17:53:55
 * !��������: ������bug
************************************************/
#include"SearchArea.h"
#include<iostream>
using namespace std;
SearchArea::SearchArea(){
    InitAreaInfo();
}

int SearchArea::InitAreaInfo(){
    /************************************************
	 ����Ⱥ�� ç�Ի�ԭ ������� ����Ͽ�� Զ����ַ ����ɽ��
	************************************************/
    /*
    enum {
		HaleBeardPeak, TheGreatWild,
		RootStrangledMarshes, GrassRockCanyon,
		RuinedCityOfTheAncients, TheFireMaw
	};//6�������Ĵ���*/

    /*
    //����ʯӢ���𽺣�����������Ǧ
	enum { Silver, Quartz, Gum, Silica, Wax, Lead };//�����
	int components_number[6]{0,0,0,0,0,0};//�������
	
	//�����ؼ� �������� ҹ��ӫ˿ ����֮�� ������Ƭ Զ�ż���
	enum { IcePlate, BraceletOfLos, ShimmeringMoonlace,
		   ScaleOfTheInfinityWurm, TheMoltenSharo, TheAncientRecord};//������
	bool treasure[6]{0,0,0,0,0,0};//���������

	//ˮ����� �ƽ����� ռ��͸�� ����֮�� ƽ���ӡ ���֮��
	enum { CrystalBattery, GoldenChassis, ScryingLens,
		   HermeticMirror, SealOfBalance, VoidGate};//װ����
	bool construct[6]{0,0,0,0,0,0};//װ�û�����
    */

    area[HaleBeardPeak]=AreaInfo{"����Ⱥ��", "ƽ���ӡ", "��","�����ؼ�",
        {
            EnemyInfo{"��Ĺ����", {-1,0,0,0,1,1}},
            EnemyInfo{"�ƻ�����", {-1,0,0,0,0,1}},
            EnemyInfo{"�����Ӱ", {-1,-1,0,0,0,1}},
            EnemyInfo{"������з", {-1,-1,-1,0,0,1}},
            EnemyInfo{"�������", {-1,-1,-1,-1,0,1}}
        }
    };
    //�����հ����
    area[TheGreatWild]=AreaInfo{"ç�Ի�ԭ", "����֮��", "ʯӢ","��������",
        {
            EnemyInfo{"��ʯ����", {-1,0,0,0,1,1}},
            EnemyInfo{"Զ������", {-1,-1,0,0,0,1}},
            EnemyInfo{"��½����", {-1,-1,0,0,0,1}},
            EnemyInfo{"�ˮ��", {-1,-1,-1,0,0,1}},
            EnemyInfo{"��ϫ����", {-1,-1,-1,-1,0,1}}
        }
    };
    area[RootStrangledMarshes]=AreaInfo{"�������", "���֮��", "��","ҹ��ӫ˿",
        {
            EnemyInfo{"��ħ��ͯ", {-1,0,0,0,1,1}},
            EnemyInfo{"��ͽ��ʿ", {-1,-1,0,0,1,1}},
            EnemyInfo{"�������", {-1,-1,-1,0,1,1}},
            EnemyInfo{"�ǻ�Ԫ��", {-1,-1,-1,0,0,1}},
            EnemyInfo{"���۾���", {-1,-1,-1,-1,0,1}}
        }
    };
    area[GrassRockCanyon]=AreaInfo{"����Ͽ��", "�ƽ�����", "����","����֮��",
        {
            EnemyInfo{"��å����", {-1,-1,0,0,1,1}},
            EnemyInfo{"ѻȸӰ̺", {-1,0,0,0,0,1}},
            EnemyInfo{"����Ұţ", {-1,0,0,0,0,1}},
            EnemyInfo{"�ݱ���ħ", {-1,-1,-1,0,1,1}},
            EnemyInfo{"�׵�֮��", {-1,-1,-1,-1,0,1}}
        }
    };
    area[RuinedCityOfTheAncients]=AreaInfo{"Զ����ַ", "ռ��͸��", "��","Զ�ż���",
        {
            EnemyInfo{"�궯����", {-1,0,0,0,1,1}},
            EnemyInfo{"͸������", {-1,0,0,0,0,1}},
            EnemyInfo{"̽������", {-1,-1,0,0,0,1}},
            EnemyInfo{"��������", {-1,-1,-1,0,0,1}},
            EnemyInfo{"���о���", {-1,-1,-1,-1,0,1}}
        }
    };
    area[TheFireMaw]=AreaInfo{"����ɽ��", "ˮ�����", "Ǧ","������Ƭ",
        {
            EnemyInfo{"��ԭ����", {-1,0,0,0,1,1}},
            EnemyInfo{"���˷˿�", {-1,0,0,0,0,1}},
            EnemyInfo{"Ѫɫ����", {-1,-1,0,0,0,1}},
            EnemyInfo{"ʳ���ӥ", {-1,-1,-1,0,0,1}},
            EnemyInfo{"ɽ������", {-1,-1,-1,-1,0,1}}
        }
    };
    
    return 0;
}

int SearchArea::GetIcePlate(){//��ñ����ؼ�,���˹�������1����СΪ1
    area[HaleBeardPeak]=AreaInfo{"����Ⱥ��", "ƽ���ӡ", "��","�����ؼ�",
        {
            EnemyInfo{"��Ĺ����", {-1,0,0,0,1,1}},
            EnemyInfo{"�ƻ�����", {-1,0,0,0,0,1}},
            EnemyInfo{"�����Ӱ", {-1,0,0,0,0,1}},
            EnemyInfo{"������з", {-1,-1,0,0,0,1}},
            EnemyInfo{"�������", {-1,-1,-1,0,0,1}}
        }
    };
    //�����հ����
    area[TheGreatWild]=AreaInfo{"ç�Ի�ԭ", "����֮��", "ʯӢ","��������",
        {
            EnemyInfo{"��ʯ����", {-1,0,0,0,1,1}},
            EnemyInfo{"Զ������", {-1,0,0,0,0,1}},
            EnemyInfo{"��½����", {-1,-1,0,0,0,1}},
            EnemyInfo{"�ˮ��", {-1,-1,0,0,0,1}},
            EnemyInfo{"��ϫ����", {-1,-1,-1,0,0,1}}
        }
    };
    area[RootStrangledMarshes]=AreaInfo{"�������", "���֮��", "��","ҹ��ӫ˿",
        {
            EnemyInfo{"��ħ��ͯ", {-1,0,0,0,1,1}},
            EnemyInfo{"��ͽ��ʿ", {-1,0,0,0,1,1}},
            EnemyInfo{"�������", {-1,-1,0,0,1,1}},
            EnemyInfo{"�ǻ�Ԫ��", {-1,-1,0,0,0,1}},
            EnemyInfo{"���۾���", {-1,-1,-1,0,0,1}}
        }
    };
    area[GrassRockCanyon]=AreaInfo{"����Ͽ��", "�ƽ�����", "����","����֮��",
        {
            EnemyInfo{"��å����", {-1,0,0,0,1,1}},
            EnemyInfo{"ѻȸӰ̺", {-1,0,0,0,0,1}},
            EnemyInfo{"����Ұţ", {-1,0,0,0,0,1}},
            EnemyInfo{"�ݱ���ħ", {-1,-1,0,0,1,1}},
            EnemyInfo{"�׵�֮��", {-1,-1,-1,0,0,1}}
        }
    };
    area[RuinedCityOfTheAncients]=AreaInfo{"Զ����ַ", "ռ��͸��", "��","Զ�ż���",
        {
            EnemyInfo{"�궯����", {-1,0,0,0,1,1}},
            EnemyInfo{"͸������", {-1,0,0,0,0,1}},
            EnemyInfo{"̽������", {-1,0,0,0,0,1}},
            EnemyInfo{"��������", {-1,-1,0,0,0,1}},
            EnemyInfo{"���о���", {-1,-1,-1,0,0,1}}
        }
    };
    area[TheFireMaw]=AreaInfo{"����ɽ��", "ˮ�����", "Ǧ","������Ƭ",
        {
            EnemyInfo{"��ԭ����", {-1,0,0,0,1,1}},
            EnemyInfo{"���˷˿�", {-1,0,0,0,0,1}},
            EnemyInfo{"Ѫɫ����", {-1,0,0,0,0,1}},
            EnemyInfo{"ʳ���ӥ", {-1,-1,0,0,0,1}},
            EnemyInfo{"ɽ������", {-1,-1,-1,0,0,1}}
        }
    };
    
    return 0;
}

int SearchArea::GetTheMoltenSharo(){//���������Ƭ,hit��1
     area[HaleBeardPeak]=AreaInfo{"����Ⱥ��", "ƽ���ӡ", "��","�����ؼ�",
        {
            EnemyInfo{"��Ĺ����", {-1,0,0,1,1,1}},
            EnemyInfo{"�ƻ�����", {-1,0,0,0,1,1}},
            EnemyInfo{"�����Ӱ", {-1,-1,0,0,1,1}},
            EnemyInfo{"������з", {-1,-1,-1,0,1,1}},
            EnemyInfo{"�������", {-1,-1,-1,-1,1,1}}
        }
    };
    //�����հ����
    area[TheGreatWild]=AreaInfo{"ç�Ի�ԭ", "����֮��", "ʯӢ","��������",
        {
            EnemyInfo{"��ʯ����", {-1,0,0,1,1,1}},
            EnemyInfo{"Զ������", {-1,-1,0,0,1,1}},
            EnemyInfo{"��½����", {-1,-1,0,0,1,1}},
            EnemyInfo{"�ˮ��", {-1,-1,-1,0,1,1}},
            EnemyInfo{"��ϫ����", {-1,-1,-1,-1,1,1}}
        }
    };
    area[RootStrangledMarshes]=AreaInfo{"�������", "���֮��", "��","ҹ��ӫ˿",
        {
            EnemyInfo{"��ħ��ͯ", {-1,0,0,1,1,1}},
            EnemyInfo{"��ͽ��ʿ", {-1,-1,0,1,1,1}},
            EnemyInfo{"�������", {-1,-1,-1,1,1,1}},
            EnemyInfo{"�ǻ�Ԫ��", {-1,-1,-1,0,1,1}},
            EnemyInfo{"���۾���", {-1,-1,-1,-1,1,1}}
        }
    };
    area[GrassRockCanyon]=AreaInfo{"����Ͽ��", "�ƽ�����", "����","����֮��",
        {
            EnemyInfo{"��å����", {-1,-1,0,1,1,1}},
            EnemyInfo{"ѻȸӰ̺", {-1,0,0,0,1,1}},
            EnemyInfo{"����Ұţ", {-1,0,0,0,1,1}},
            EnemyInfo{"�ݱ���ħ", {-1,-1,-1,1,1,1}},
            EnemyInfo{"�׵�֮��", {-1,-1,-1,-1,1,1}}
        }
    };
    area[RuinedCityOfTheAncients]=AreaInfo{"Զ����ַ", "ռ��͸��", "��","Զ�ż���",
        {
            EnemyInfo{"�궯����", {-1,0,0,1,1,1}},
            EnemyInfo{"͸������", {-1,0,0,0,1,1}},
            EnemyInfo{"̽������", {-1,-1,0,0,1,1}},
            EnemyInfo{"��������", {-1,-1,-1,0,1,1}},
            EnemyInfo{"���о���", {-1,-1,-1,-1,1,1}}
        }
    };
    area[TheFireMaw]=AreaInfo{"����ɽ��", "ˮ�����", "Ǧ","������Ƭ",
        {
            EnemyInfo{"��ԭ����", {-1,0,0,1,1,1}},
            EnemyInfo{"���˷˿�", {-1,0,0,0,1,1}},
            EnemyInfo{"Ѫɫ����", {-1,-1,0,0,1,1}},
            EnemyInfo{"ʳ���ӥ", {-1,-1,-1,0,1,1}},
            EnemyInfo{"ɽ������", {-1,-1,-1,-1,1,1}}
        }
    };
    return 0;
}

int SearchArea::GetIcePlateAndTheMoltenSharo(){//��ñ����ؼ׺�������Ƭ
     area[HaleBeardPeak]=AreaInfo{"����Ⱥ��", "ƽ���ӡ", "��","�����ؼ�",
        {
            EnemyInfo{"��Ĺ����", {-1,0,0,1,1,1}},
            EnemyInfo{"�ƻ�����", {-1,0,0,0,1,1}},
            EnemyInfo{"�����Ӱ", {-1,0,0,0,1,1}},
            EnemyInfo{"������з", {-1,-1,0,0,1,1}},
            EnemyInfo{"�������", {-1,-1,-1,0,1,1}}
        }
    };
    //�����հ����
    area[TheGreatWild]=AreaInfo{"ç�Ի�ԭ", "����֮��", "ʯӢ","��������",
        {
            EnemyInfo{"��ʯ����", {-1,0,0,1,1,1}},
            EnemyInfo{"Զ������", {-1,0,0,0,1,1}},
            EnemyInfo{"��½����", {-1,0,0,0,1,1}},
            EnemyInfo{"�ˮ��", {-1,-1,0,0,1,1}},
            EnemyInfo{"��ϫ����", {-1,-1,-1,0,1,1}}
        }
    };
    area[RootStrangledMarshes]=AreaInfo{"�������", "���֮��", "��","ҹ��ӫ˿",
        {
            EnemyInfo{"��ħ��ͯ", {-1,0,0,1,1,1}},
            EnemyInfo{"��ͽ��ʿ", {-1,0,0,1,1,1}},
            EnemyInfo{"�������", {-1,-1,0,1,1,1}},
            EnemyInfo{"�ǻ�Ԫ��", {-1,-1,0,0,1,1}},
            EnemyInfo{"���۾���", {-1,-1,-1,0,1,1}}
        }
    };
    area[GrassRockCanyon]=AreaInfo{"����Ͽ��", "�ƽ�����", "����","����֮��",
        {
            EnemyInfo{"��å����", {-1,0,0,1,1,1}},
            EnemyInfo{"ѻȸӰ̺", {-1,0,0,0,1,1}},
            EnemyInfo{"����Ұţ", {-1,0,0,0,1,1}},
            EnemyInfo{"�ݱ���ħ", {-1,-1,0,1,1,1}},
            EnemyInfo{"�׵�֮��", {-1,-1,-1,0,1,1}}
        }
    };
    area[RuinedCityOfTheAncients]=AreaInfo{"Զ����ַ", "ռ��͸��", "��","Զ�ż���",
        {
            EnemyInfo{"�궯����", {-1,0,0,1,1,1}},
            EnemyInfo{"͸������", {-1,0,0,0,1,1}},
            EnemyInfo{"̽������", {-1,0,0,0,1,1}},
            EnemyInfo{"��������", {-1,-1,0,0,1,1}},
            EnemyInfo{"���о���", {-1,-1,-1,0,1,1}}
        }
    };
    area[TheFireMaw]=AreaInfo{"����ɽ��", "ˮ�����", "Ǧ","������Ƭ",
        {
            EnemyInfo{"��ԭ����", {-1,0,0,1,1,1}},
            EnemyInfo{"���˷˿�", {-1,0,0,0,1,1}},
            EnemyInfo{"Ѫɫ����", {-1,0,0,0,1,1}},
            EnemyInfo{"ʳ���ӥ", {-1,-1,0,0,1,1}},
            EnemyInfo{"ɽ������", {-1,-1,-1,0,1,1}}
        }
    };
    return 0;
}
