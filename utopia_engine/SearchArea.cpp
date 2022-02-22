/************************************************
 * TODO Auther: by SR
 * FilePath: \digital designc:\Users\SR\Documents\vscodefile\games\utopia_engine\SearchArea.cpp
 * Date: 2020-05-04 11:06:42
 * LastEditTime: 2020-05-11 17:53:55
 * !今日运势: 吉，无bug
************************************************/
#include"SearchArea.h"
#include<iostream>
using namespace std;
SearchArea::SearchArea(){
    InitAreaInfo();
}

int SearchArea::InitAreaInfo(){
    /************************************************
	 苍髯群峰 莽苍荒原 扼根沼泽 玻璃峡谷 远古遗址 火焰山洞
	************************************************/
    /*
    enum {
		HaleBeardPeak, TheGreatWild,
		RootStrangledMarshes, GrassRockCanyon,
		RuinedCityOfTheAncients, TheFireMaw
	};//6个地区的代号*/

    /*
    //银，石英，橡胶，硅土，蜡，铅
	enum { Silver, Quartz, Gum, Silica, Wax, Lead };//组件名
	int components_number[6]{0,0,0,0,0,0};//组件数量
	
	//冰晶胸甲 雷神手镯 夜光荧丝 无限之秤 熔岩碎片 远古记事
	enum { IcePlate, BraceletOfLos, ShimmeringMoonlace,
		   ScaleOfTheInfinityWurm, TheMoltenSharo, TheAncientRecord};//宝物名
	bool treasure[6]{0,0,0,0,0,0};//宝物获得情况

	//水晶电池 黄金罗盘 占卜透镜 神秘之镜 平衡封印 虚空之门
	enum { CrystalBattery, GoldenChassis, ScryingLens,
		   HermeticMirror, SealOfBalance, VoidGate};//装置名
	bool construct[6]{0,0,0,0,0,0};//装置获得情况
    */

    area[HaleBeardPeak]=AreaInfo{"苍髯群峰", "平衡封印", "银","冰晶胸甲",
        {
            EnemyInfo{"古墓盗贼", {-1,0,0,0,1,1}},
            EnemyInfo{"灯火幽灵", {-1,0,0,0,0,1}},
            EnemyInfo{"复仇鬼影", {-1,-1,0,0,0,1}},
            EnemyInfo{"梦魇鳌蟹", {-1,-1,-1,0,0,1}},
            EnemyInfo{"虚幻无名", {-1,-1,-1,-1,0,1}}
        }
    };
    //下面照搬就行
    area[TheGreatWild]=AreaInfo{"莽苍荒原", "神秘之镜", "石英","雷神手镯",
        {
            EnemyInfo{"宝石巨蟒", {-1,0,0,0,1,1}},
            EnemyInfo{"远古鳄鱼", {-1,-1,0,0,0,1}},
            EnemyInfo{"大陆恶蛟", {-1,-1,0,0,0,1}},
            EnemyInfo{"深海水蛭", {-1,-1,-1,0,0,1}},
            EnemyInfo{"潮汐宿主", {-1,-1,-1,-1,0,1}}
        }
    };
    area[RootStrangledMarshes]=AreaInfo{"扼根沼泽", "虚空之门", "橡胶","夜光荧丝",
        {
            EnemyInfo{"恶魔顽童", {-1,0,0,0,1,1}},
            EnemyInfo{"叛徒术士", {-1,-1,0,0,1,1}},
            EnemyInfo{"火焰巨蜥", {-1,-1,-1,0,1,1}},
            EnemyInfo{"星火元素", {-1,-1,-1,0,0,1}},
            EnemyInfo{"火熔精灵", {-1,-1,-1,-1,0,1}}
        }
    };
    area[GrassRockCanyon]=AreaInfo{"玻璃峡谷", "黄金罗盘", "硅土","无限之秤",
        {
            EnemyInfo{"流氓盗贼", {-1,-1,0,0,1,1}},
            EnemyInfo{"鸦雀影毯", {-1,0,0,0,0,1}},
            EnemyInfo{"倒角野牛", {-1,0,0,0,0,1}},
            EnemyInfo{"草背巨魔", {-1,-1,-1,0,1,1}},
            EnemyInfo{"雷电之王", {-1,-1,-1,-1,0,1}}
        }
    };
    area[RuinedCityOfTheAncients]=AreaInfo{"远古遗址", "占卜透镜", "蜡","远古记事",
        {
            EnemyInfo{"躁动精灵", {-1,0,0,0,1,1}},
            EnemyInfo{"透翅猛禽", {-1,0,0,0,0,1}},
            EnemyInfo{"探触巨蟒", {-1,-1,0,0,0,1}},
            EnemyInfo{"暴戾亚龙", {-1,-1,-1,0,0,1}},
            EnemyInfo{"海中巨蛇", {-1,-1,-1,-1,0,1}}
        }
    };
    area[TheFireMaw]=AreaInfo{"火焰山洞", "水晶电池", "铅","熔岩碎片",
        {
            EnemyInfo{"冰原巨熊", {-1,0,0,0,1,1}},
            EnemyInfo{"流浪匪寇", {-1,0,0,0,0,1}},
            EnemyInfo{"血色恶狼", {-1,-1,0,0,0,1}},
            EnemyInfo{"食马巨鹰", {-1,-1,-1,0,0,1}},
            EnemyInfo{"山极巨人", {-1,-1,-1,-1,0,1}}
        }
    };
    
    return 0;
}

int SearchArea::GetIcePlate(){//获得冰晶胸甲,敌人攻击力减1，最小为1
    area[HaleBeardPeak]=AreaInfo{"苍髯群峰", "平衡封印", "银","冰晶胸甲",
        {
            EnemyInfo{"古墓盗贼", {-1,0,0,0,1,1}},
            EnemyInfo{"灯火幽灵", {-1,0,0,0,0,1}},
            EnemyInfo{"复仇鬼影", {-1,0,0,0,0,1}},
            EnemyInfo{"梦魇鳌蟹", {-1,-1,0,0,0,1}},
            EnemyInfo{"虚幻无名", {-1,-1,-1,0,0,1}}
        }
    };
    //下面照搬就行
    area[TheGreatWild]=AreaInfo{"莽苍荒原", "神秘之镜", "石英","雷神手镯",
        {
            EnemyInfo{"宝石巨蟒", {-1,0,0,0,1,1}},
            EnemyInfo{"远古鳄鱼", {-1,0,0,0,0,1}},
            EnemyInfo{"大陆恶蛟", {-1,-1,0,0,0,1}},
            EnemyInfo{"深海水蛭", {-1,-1,0,0,0,1}},
            EnemyInfo{"潮汐宿主", {-1,-1,-1,0,0,1}}
        }
    };
    area[RootStrangledMarshes]=AreaInfo{"扼根沼泽", "虚空之门", "橡胶","夜光荧丝",
        {
            EnemyInfo{"恶魔顽童", {-1,0,0,0,1,1}},
            EnemyInfo{"叛徒术士", {-1,0,0,0,1,1}},
            EnemyInfo{"火焰巨蜥", {-1,-1,0,0,1,1}},
            EnemyInfo{"星火元素", {-1,-1,0,0,0,1}},
            EnemyInfo{"火熔精灵", {-1,-1,-1,0,0,1}}
        }
    };
    area[GrassRockCanyon]=AreaInfo{"玻璃峡谷", "黄金罗盘", "硅土","无限之秤",
        {
            EnemyInfo{"流氓盗贼", {-1,0,0,0,1,1}},
            EnemyInfo{"鸦雀影毯", {-1,0,0,0,0,1}},
            EnemyInfo{"倒角野牛", {-1,0,0,0,0,1}},
            EnemyInfo{"草背巨魔", {-1,-1,0,0,1,1}},
            EnemyInfo{"雷电之王", {-1,-1,-1,0,0,1}}
        }
    };
    area[RuinedCityOfTheAncients]=AreaInfo{"远古遗址", "占卜透镜", "蜡","远古记事",
        {
            EnemyInfo{"躁动精灵", {-1,0,0,0,1,1}},
            EnemyInfo{"透翅猛禽", {-1,0,0,0,0,1}},
            EnemyInfo{"探触巨蟒", {-1,0,0,0,0,1}},
            EnemyInfo{"暴戾亚龙", {-1,-1,0,0,0,1}},
            EnemyInfo{"海中巨蛇", {-1,-1,-1,0,0,1}}
        }
    };
    area[TheFireMaw]=AreaInfo{"火焰山洞", "水晶电池", "铅","熔岩碎片",
        {
            EnemyInfo{"冰原巨熊", {-1,0,0,0,1,1}},
            EnemyInfo{"流浪匪寇", {-1,0,0,0,0,1}},
            EnemyInfo{"血色恶狼", {-1,0,0,0,0,1}},
            EnemyInfo{"食马巨鹰", {-1,-1,0,0,0,1}},
            EnemyInfo{"山极巨人", {-1,-1,-1,0,0,1}}
        }
    };
    
    return 0;
}

int SearchArea::GetTheMoltenSharo(){//获得熔岩碎片,hit加1
     area[HaleBeardPeak]=AreaInfo{"苍髯群峰", "平衡封印", "银","冰晶胸甲",
        {
            EnemyInfo{"古墓盗贼", {-1,0,0,1,1,1}},
            EnemyInfo{"灯火幽灵", {-1,0,0,0,1,1}},
            EnemyInfo{"复仇鬼影", {-1,-1,0,0,1,1}},
            EnemyInfo{"梦魇鳌蟹", {-1,-1,-1,0,1,1}},
            EnemyInfo{"虚幻无名", {-1,-1,-1,-1,1,1}}
        }
    };
    //下面照搬就行
    area[TheGreatWild]=AreaInfo{"莽苍荒原", "神秘之镜", "石英","雷神手镯",
        {
            EnemyInfo{"宝石巨蟒", {-1,0,0,1,1,1}},
            EnemyInfo{"远古鳄鱼", {-1,-1,0,0,1,1}},
            EnemyInfo{"大陆恶蛟", {-1,-1,0,0,1,1}},
            EnemyInfo{"深海水蛭", {-1,-1,-1,0,1,1}},
            EnemyInfo{"潮汐宿主", {-1,-1,-1,-1,1,1}}
        }
    };
    area[RootStrangledMarshes]=AreaInfo{"扼根沼泽", "虚空之门", "橡胶","夜光荧丝",
        {
            EnemyInfo{"恶魔顽童", {-1,0,0,1,1,1}},
            EnemyInfo{"叛徒术士", {-1,-1,0,1,1,1}},
            EnemyInfo{"火焰巨蜥", {-1,-1,-1,1,1,1}},
            EnemyInfo{"星火元素", {-1,-1,-1,0,1,1}},
            EnemyInfo{"火熔精灵", {-1,-1,-1,-1,1,1}}
        }
    };
    area[GrassRockCanyon]=AreaInfo{"玻璃峡谷", "黄金罗盘", "硅土","无限之秤",
        {
            EnemyInfo{"流氓盗贼", {-1,-1,0,1,1,1}},
            EnemyInfo{"鸦雀影毯", {-1,0,0,0,1,1}},
            EnemyInfo{"倒角野牛", {-1,0,0,0,1,1}},
            EnemyInfo{"草背巨魔", {-1,-1,-1,1,1,1}},
            EnemyInfo{"雷电之王", {-1,-1,-1,-1,1,1}}
        }
    };
    area[RuinedCityOfTheAncients]=AreaInfo{"远古遗址", "占卜透镜", "蜡","远古记事",
        {
            EnemyInfo{"躁动精灵", {-1,0,0,1,1,1}},
            EnemyInfo{"透翅猛禽", {-1,0,0,0,1,1}},
            EnemyInfo{"探触巨蟒", {-1,-1,0,0,1,1}},
            EnemyInfo{"暴戾亚龙", {-1,-1,-1,0,1,1}},
            EnemyInfo{"海中巨蛇", {-1,-1,-1,-1,1,1}}
        }
    };
    area[TheFireMaw]=AreaInfo{"火焰山洞", "水晶电池", "铅","熔岩碎片",
        {
            EnemyInfo{"冰原巨熊", {-1,0,0,1,1,1}},
            EnemyInfo{"流浪匪寇", {-1,0,0,0,1,1}},
            EnemyInfo{"血色恶狼", {-1,-1,0,0,1,1}},
            EnemyInfo{"食马巨鹰", {-1,-1,-1,0,1,1}},
            EnemyInfo{"山极巨人", {-1,-1,-1,-1,1,1}}
        }
    };
    return 0;
}

int SearchArea::GetIcePlateAndTheMoltenSharo(){//获得冰晶胸甲和熔岩碎片
     area[HaleBeardPeak]=AreaInfo{"苍髯群峰", "平衡封印", "银","冰晶胸甲",
        {
            EnemyInfo{"古墓盗贼", {-1,0,0,1,1,1}},
            EnemyInfo{"灯火幽灵", {-1,0,0,0,1,1}},
            EnemyInfo{"复仇鬼影", {-1,0,0,0,1,1}},
            EnemyInfo{"梦魇鳌蟹", {-1,-1,0,0,1,1}},
            EnemyInfo{"虚幻无名", {-1,-1,-1,0,1,1}}
        }
    };
    //下面照搬就行
    area[TheGreatWild]=AreaInfo{"莽苍荒原", "神秘之镜", "石英","雷神手镯",
        {
            EnemyInfo{"宝石巨蟒", {-1,0,0,1,1,1}},
            EnemyInfo{"远古鳄鱼", {-1,0,0,0,1,1}},
            EnemyInfo{"大陆恶蛟", {-1,0,0,0,1,1}},
            EnemyInfo{"深海水蛭", {-1,-1,0,0,1,1}},
            EnemyInfo{"潮汐宿主", {-1,-1,-1,0,1,1}}
        }
    };
    area[RootStrangledMarshes]=AreaInfo{"扼根沼泽", "虚空之门", "橡胶","夜光荧丝",
        {
            EnemyInfo{"恶魔顽童", {-1,0,0,1,1,1}},
            EnemyInfo{"叛徒术士", {-1,0,0,1,1,1}},
            EnemyInfo{"火焰巨蜥", {-1,-1,0,1,1,1}},
            EnemyInfo{"星火元素", {-1,-1,0,0,1,1}},
            EnemyInfo{"火熔精灵", {-1,-1,-1,0,1,1}}
        }
    };
    area[GrassRockCanyon]=AreaInfo{"玻璃峡谷", "黄金罗盘", "硅土","无限之秤",
        {
            EnemyInfo{"流氓盗贼", {-1,0,0,1,1,1}},
            EnemyInfo{"鸦雀影毯", {-1,0,0,0,1,1}},
            EnemyInfo{"倒角野牛", {-1,0,0,0,1,1}},
            EnemyInfo{"草背巨魔", {-1,-1,0,1,1,1}},
            EnemyInfo{"雷电之王", {-1,-1,-1,0,1,1}}
        }
    };
    area[RuinedCityOfTheAncients]=AreaInfo{"远古遗址", "占卜透镜", "蜡","远古记事",
        {
            EnemyInfo{"躁动精灵", {-1,0,0,1,1,1}},
            EnemyInfo{"透翅猛禽", {-1,0,0,0,1,1}},
            EnemyInfo{"探触巨蟒", {-1,0,0,0,1,1}},
            EnemyInfo{"暴戾亚龙", {-1,-1,0,0,1,1}},
            EnemyInfo{"海中巨蛇", {-1,-1,-1,0,1,1}}
        }
    };
    area[TheFireMaw]=AreaInfo{"火焰山洞", "水晶电池", "铅","熔岩碎片",
        {
            EnemyInfo{"冰原巨熊", {-1,0,0,1,1,1}},
            EnemyInfo{"流浪匪寇", {-1,0,0,0,1,1}},
            EnemyInfo{"血色恶狼", {-1,0,0,0,1,1}},
            EnemyInfo{"食马巨鹰", {-1,-1,0,0,1,1}},
            EnemyInfo{"山极巨人", {-1,-1,-1,0,1,1}}
        }
    };
    return 0;
}
