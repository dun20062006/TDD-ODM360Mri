#ifndef    _DEF_H
#define    _DEF_H
#define BitSet(a,b) (a |= (1<<b)) 
#define BitClr(a,b) (a &= ~(1<<b)) 
#define BitCpl(a,b)  a^=1<<b
#define BitTst(a,b)  ((a&(1<<b))>0)
#define SPK_ON    BitSet(PORTA,0) 
#define SPK_OFF     BitClr(PORTA,0)

//�������ֱ���������
#define  POWER1_ON   BitClr(PORTA,1)
#define  POWER1_OFF  BitSet(PORTA,1)
#define  POWER2_ON   BitClr(PORTA,2)
#define  POWER2_OFF  BitSet(PORTA,2)
#define  POWER3_ON   BitClr(PORTA,3)
#define  POWER3_OFF  BitSet(PORTA,3)
#define  POWER4_ON   BitClr(PORTA,4)
#define  POWER4_OFF  BitSet(PORTA,4)
#define  POWER5_ON   BitClr(PORTA,5)
#define  POWER5_OFF  BitSet(PORTA,5)
/*HAO**************************************/
#define  DEFAULTDATA   2//鎵嬫焺榛樿�ゆ不鐤楀€�

#define  PAGE_HANDLECHOOSE1     0//鎵嬫焺閫夋嫨椤�0   涓€浜屼笁鎵嬫焺
#define  PAGE_HANDLECHOOSE2     1//鎵嬫焺閫夋嫨椤�1   鍥涗簲鎵嬫焺
#define  PAGE_HANDLECHOOSE3     2//鎵嬫焺閫夋嫨椤�2   鍥涙墜鏌�?
#define  PAGE_HANDLECHOOSE4     23//鎵嬫焺閫夋嫨椤�3  浜屼笁鍥涙墜鏌�
#define  PAGE_HANDLECHOOSE5     25//鎵嬫焺閫夋嫨椤�4  浜旀墜鏌�?

#define  PAGE_HANDLEONE     4//1鍙锋墜鏌勬不鐤楅�?
#define  PAGE_HANDLETWO     5//2鍙锋墜鏌勬不鐤楅�?
#define  PAGE_HANDLETHREE   6//3鍙锋墜鏌勬不鐤楅�?
#define  PAGE_HANDLEFOUER   7//4鍙锋墜鏌勬不鐤楅�?
#define  PAGE_HANDLEFIVE    8//5鍙锋墜鏌勬不鐤楅�?

#define  PAGE_SETTING  17//鍚庡彴璁剧疆椤�
#define  SNPAGE_PASSWORD_SETTING  18//SN瀵嗙爜杈撳叆椤�
#define  SNPAGE_SETTING  21//SN璁剧疆椤�?
//娌荤枟淇℃伅鍙傛�?
typedef struct
{
 unsigned char SAVE_PRESS;      //淇濆瓨鐨勮礋鍘嬪彉閲�?
 unsigned char SAVE_RF;         //淇濆瓨鐨勫皠棰戝彉閲�?
 unsigned char SAVE_PRESS_IN;   //淇濆瓨鐨勫惛姘旀椂闂村彉閲�
 unsigned char SAVE_PRESS_OUT;  //淇濆瓨鐨勬斁姘旀椂闂村彉閲�
 unsigned char SAVE_LED;        //淇濆瓨鐨凩ED绛夌骇鍙橀�?
 unsigned char SAVE_INFRARED;   //淇濆瓨鐨勭孩澶栫瓑绾у彉閲�?
 unsigned char SAVE_MOTO_SPEED; //淇濆瓨鐨勮浆閫熺瓑绾у彉閲�?
 unsigned char SAVE_MOTO_TOWARD;//淇濆瓨鐨勭數鏈鸿浆鍚戝彉閲�
}Treatment_information;

extern Treatment_information HNDLE_INFORMATION;//鏁存満杩愯�屼娇鐢ㄥ綋鍓嶇殑鍙傛暟

//娌荤枟鐘舵€�?
typedef struct
{
 unsigned char HANDLE_ID;       //鎵嬫焺ID
 unsigned char WORK_STATE;      //鎵嬫焺鍚�鍋滅姸鎬�
 unsigned char WORK_SAVE_STATE;  //娌荤枟鍙傛暟淇濆瓨鍊糀BC
 unsigned char WORK_SAVE_MOTO_TOWARD;  //鐢垫満杞�鍚�
 unsigned char WORK_PAGE;       //鏁存満宸ヤ綔椤�?
}Treatment_state;

extern Treatment_state MACHINE_STATE;

//鍚庡彴璁剧疆淇℃�?
typedef struct
{
 unsigned char softwareVersion[16];//杞�浠剁増鏈�鍙凤紙杩�鏂囧睆锛�?
 unsigned char hardwareVersion[16];//纭�浠剁増鏈�鍙凤紙涓绘澘锛�?
 unsigned char hexVersion[16];//鍥轰欢鐗堟湰鍙凤紙涓绘澘绋嬪簭锛�?
 unsigned char snNumber[16];//浠�鍣ㄥ簭鍒楀彿锛堜骇鍝佸敮涓€鏍囪瘑锛�

 unsigned char SET_HANDLEONE;   //1鍙锋墜鏌勯€変腑
 unsigned char SET_HANDLETWO;   //2鍙锋墜鏌勯€変腑 榛樿�ら€変腑涓嶅彲鏇存�?
 unsigned char SET_HANDLETHREE; //3鍙锋墜鏌勯€変腑 榛樿�ら€変腑涓嶅彲鏇存�?
 unsigned char SET_HANDLEFOUR;  //4鍙锋墜鏌勯€変腑 榛樿�ら€変腑涓嶅彲鏇存�?
 unsigned char SET_HANDLEFIVE;  //5鍙锋墜鏌勯€変腑 
 unsigned char SET_WORKTIME;    //娌荤枟鏃堕棿
 unsigned char SET_WORKPOWER;   //娌荤枟鑳介噺绛夌�? 

}Set_information;

extern Set_information SettingDdata;//鍚庡彴娌荤枟鍙傛�?

//鏃堕棿淇℃伅
typedef struct
{
 unsigned char year;
 unsigned char month;
 unsigned char day;
 unsigned char week;
 unsigned char hour;
 unsigned char miniute;
 unsigned char second;
 unsigned char ext;
}DATE_STRUCT;
extern DATE_STRUCT DwinDate;

//杩�鏂囧睆鐩稿叧
#define ADDR_BOOTINGBAR           0x1000//鍚�鍔ㄨ繘搴︽潯
#define ADDR_BOOTINGINFO          0x1002//鍚�鍔ㄦ樉绀轰俊鎭�

//0x6666鎸夐敭閿�鍊艰繑鍥炲€�
#define ADDR_KEY_BACK_HANDLEONE          0x0000//鎵嬫�?1鍙烽€夋嫨鎸夐敭杩斿洖鍊�?
#define ADDR_KEY_BACK_HANDLETWO          0x0001//鎵嬫�?2鍙烽€夋嫨鎸夐敭杩斿洖鍊�?
#define ADDR_KEY_BACK_HANDLETHREE        0x0002//鎵嬫�?3鍙烽€夋嫨鎸夐敭杩斿洖鍊�?
#define ADDR_KEY_BACK_HANDLEFOUR         0x0003//鎵嬫�?4鍙烽€夋嫨鎸夐敭杩斿洖鍊�?
#define ADDR_KEY_BACK_HANDLEFIVE         0x0004//鎵嬫�?5鍙烽€夋嫨鎸夐敭杩斿洖鍊�?
#define ADDR_KEY_BACK_ONOFF              0x0010//娌荤枟鍚�鍋滄寜閿�杩斿洖鍊�?
#define ADDR_KEY_BACK_SAVE               0x0011//褰撳墠娌荤枟鍙傛暟淇濆瓨鎸夐敭杩斿洖鍊�
#define ADDR_KEY_BACK_SAVE_A             0x0012//娌荤枟鍙傛暟淇濆瓨A鎸夐敭杩斿洖鍊�
#define ADDR_KEY_BACK_SAVE_B             0x0013//娌荤枟鍙傛暟淇濆瓨B鎸夐敭杩斿洖鍊�
#define ADDR_KEY_BACK_SAVE_C             0x0014//娌荤枟鍙傛暟淇濆瓨C鎸夐敭杩斿洖鍊�
#define ADDR_KEY_BACK_MOTO_SPEED         0x0015//鐢垫満杞�閫熺瓑绾у彉閲忔寜閿�杩斿洖鍊�?
#define ADDR_KEY_BACK_MOTO_TOWARD_LEFT   0x0016//鐢垫満杞�鍚戝乏杞�鍙橀噺鎸夐敭杩斿洖鍊�?
#define ADDR_KEY_BACK_MOTO_TOWARD_RIGHT  0x0017//鐢垫満杞�鍚戝彸杞�鍙橀噺鎸夐敭杩斿洖鍊�?
#define ADDR_KEY_BACK_MOTO_TOWARD_IN     0x0018//鐢垫満杞�鍚戝唴杞�鍙橀噺鎸夐敭杩斿洖鍊�?
#define ADDR_KEY_BACK_MOTO_TOWARD_OUT    0x0019//鐢垫満杞�鍚戝�栬浆鍙橀噺鎸夐敭杩斿洖鍊�?

#define ADDR_KEY_BACK_FAT_SUGGEST1       0x0020//鐖嗚剛鎺ㄨ崘鍊�1鎸夐敭杩斿洖鍊�
#define ADDR_KEY_BACK_FAT_SUGGEST2       0x0021//鐖嗚剛鎺ㄨ崘鍊�2鎸夐敭杩斿洖鍊�
#define ADDR_KEY_BACK_FAT_SUGGEST3       0x0022//鐖嗚剛鎺ㄨ崘鍊�3鎸夐敭杩斿洖鍊�
#define ADDR_KEY_BACK_FAT_SUGGEST4       0x0023//鐖嗚剛鎺ㄨ崘鍊�4鎸夐敭杩斿洖鍊�
#define ADDR_KEY_BACK_FAT_SUGGEST5       0x0024//鐖嗚剛鎺ㄨ崘鍊�5鎸夐敭杩斿洖鍊�
#define ADDR_KEY_BACK_FAT_SUGGEST6       0x0025//鐖嗚剛鎺ㄨ崘鍊�6鎸夐敭杩斿洖鍊�
#define ADDR_KEY_BACK_FAT_SUGGEST7       0x0026//鐖嗚剛鎺ㄨ崘鍊�7鎸夐敭杩斿洖鍊�

#define ADDR_KEY_SET_SN                  0x0030//鍚庡彴璁剧疆椤甸暱鎸塖N鎸夐敭杩斿洖鍊�
#define ADDR_KEY_SET_HANDLEONE           0x0031//鍚庡彴璁剧疆椤垫墜鏌�?1鍙烽€夋嫨鎸夐敭杩斿洖鍊�?
#define ADDR_KEY_SET_HANDLETWO           0x0032//鍚庡彴璁剧疆椤垫墜鏌�?2鍙烽€夋嫨鎸夐敭杩斿洖鍊�?
#define ADDR_KEY_SET_HANDLETHREE         0x0033//鍚庡彴璁剧疆椤垫墜鏌�?3鍙烽€夋嫨鎸夐敭杩斿洖鍊�?
#define ADDR_KEY_SET_HANDLEFOUR          0x0034//鍚庡彴璁剧疆椤垫墜鏌�?4鍙烽€夋嫨鎸夐敭杩斿洖鍊�?
#define ADDR_KEY_SET_HANDLEFIVE          0x0035//鍚庡彴璁剧疆椤垫墜鏌�?5鍙烽€夋嫨鎸夐敭杩斿洖鍊�?
#define ADDR_KEY_SET_SAVE                0x0036//鍚庡彴璁剧疆椤佃�剧疆淇濆瓨閿�


#define ADDR_KEY_BACK_GPRESS_MIN       0x0100//璐熷帇绛夌骇婊戝姩鏉℃寜閿�杩斿洖鍊艰寖鍥存渶灏�?
#define ADDR_KEY_BACK_GPRESS_MAX       0x010a//璐熷帇绛夌骇婊戝姩鏉℃寜閿�杩斿洖鍊艰寖鍥存渶澶�?
#define ADDR_KEY_BACK_RF_MIN           0x0110//RF绛夌骇婊戝姩鏉℃寜閿�杩斿洖鍊艰寖鍥存渶灏�
#define ADDR_KEY_BACK_RF_MAX           0x011a//RF绛夌骇婊戝姩鏉℃寜閿�杩斿洖鍊艰寖鍥存渶澶�
#define ADDR_KEY_BACK_GPRESS_IN_MIN    0x0120//鍚告皵绛夌骇婊戝姩鏉℃寜閿�杩斿洖鍊艰寖鍥存渶灏�?
#define ADDR_KEY_BACK_GPRESS_IN_MAX    0x012a//鍚告皵绛夌骇婊戝姩鏉℃寜閿�杩斿洖鍊艰寖鍥存渶澶�?
#define ADDR_KEY_BACK_GPRESS_OUT_MIN   0x0130//鏀炬皵绛夌骇婊戝姩鏉℃寜閿�杩斿洖鍊艰寖鍥存渶灏�
#define ADDR_KEY_BACK_GPRESS_OUT_MAX   0x013a//鏀炬皵绛夌骇婊戝姩鏉℃寜閿�杩斿洖鍊艰寖鍥存渶澶�
#define ADDR_KEY_BACK_LED_MIN          0x0140//LED绛夌骇婊戝姩鏉℃寜閿�杩斿洖鍊艰寖鍥存渶灏�
#define ADDR_KEY_BACK_LED_MAX          0x014a//LED绛夌骇婊戝姩鏉℃寜閿�杩斿洖鍊艰寖鍥存渶澶�
#define ADDR_KEY_BACK_INFRARED_MIN     0x0150//绾㈠�栫瓑绾ф粦鍔ㄦ潯鎸夐敭杩斿洖鍊艰寖鍥存渶灏�
#define ADDR_KEY_BACK_INFRARED_MAX     0x015a//绾㈠�栫瓑绾ф粦鍔ㄦ潯鎸夐敭杩斿洖鍊艰寖鍥存渶澶�

#define ADDR_KEY_BACK_HANDLEONETREATING       0x0161//1鍙锋墜鏌勬不鐤楅〉杩斿洖閿�杩斿洖鍊�?
#define ADDR_KEY_BACK_HANDLETWOTREATING       0x0162//2鍙锋墜鏌勬不鐤楅〉杩斿洖閿�杩斿洖鍊�?
#define ADDR_KEY_BACK_HANDLETHREETREATING     0x0163//3鍙锋墜鏌勬不鐤楅〉杩斿洖閿�杩斿洖鍊�?
#define ADDR_KEY_BACK_HANDLEFOURTREATING      0x0164//4鍙锋墜鏌勬不鐤楅〉杩斿洖閿�杩斿洖鍊�?
#define ADDR_KEY_BACK_HANDLEFIVETREATING      0x0165//5鍙锋墜鏌勬不鐤楅〉杩斿洖閿�杩斿洖鍊�?
#define ADDR_KEY_BACK_SETING                  0x0166//鍚庡彴璁剧疆椤佃繑鍥為敭杩斿洖鍊�?
#define ADDR_KEY_BACK_PASSWORD                0x0167//瀵嗙爜杩斿洖閿�杩斿洖鍊�?

#define ADDR_KEY_BACK_HANDLECHOOSE1           0x0171//鎵嬫焺閫夋嫨椤典竴椤靛乏鍙抽敭杩斿洖鍊�
#define ADDR_KEY_BACK_HANDLECHOOSE2           0x0172//鎵嬫焺閫夋嫨椤典簩椤靛乏鍙抽敭杩斿洖鍊�


#define ADDR_BOOTINGPRESSDATA         0x3666//璐熷帇鍙橀�?
#define ADDR_BOOTINGRF                0x3667//灏勯�戝彉閲�?
#define ADDR_BOOTINGPRESS_INDATA      0x3668//鍚告皵鏃堕棿鍙橀�?
#define ADDR_BOOTINGPRESS_OUTDATA     0x3669//鏀炬皵鏃堕棿鍙橀�?
#define ADDR_BOOTINGLEDDATA           0x3670//LED绛夌骇鍙橀�?
#define ADDR_BOOTINGINFRAREDDATA      0x3671//绾㈠�栫瓑绾у彉閲�?
#define ADDR_BOOTINGMOTO_SPEEDDATA    0x3672//鐢垫満杞�閫熺瓑绾у彉閲�?
#define ADDR_BOOTINGMOTO_TOWARDDATA   0x3673//鐢垫満杞�鍚戝彉閲�?
#define ADDR_BOOTINGHANDLE_ON_OFFDATA 0x3674//鎵嬫焺鍚�鍋滃彉閲�
#define ADDR_BOOTINGSAVE_ADATA        0x3675//娌荤枟鍙傛暟淇濆瓨A鍙橀�?
#define ADDR_BOOTINGSAVE_BDATA        0x3676//娌荤枟鍙傛暟淇濆瓨B鍙橀�?
#define ADDR_BOOTINGSAVE_CDATA        0x3677//娌荤枟鍙傛暟淇濆瓨C鍙橀�?
#define ADDR_BOOTINGMOTO_TOWARD_LEFTDATA    0x3678//鐢垫満杞�鍚戝乏杞�鍙橀�?
#define ADDR_BOOTINGMOTO_TOWARD_RIGHTDATA   0x3679//鐢垫満杞�鍚戝彸杞�鍙橀�?
#define ADDR_BOOTINGMOTO_TOWARD_INDATA      0x367a//鐢垫満杞�鍚戝唴杞�鍙橀�?
#define ADDR_BOOTINGMOTO_TOWARD_OUTDATA     0x367b//鐢垫満杞�鍚戝�栬浆鍙橀�?
#define ADDR_BOOTINGM_POWERON_GIF           0x367c//鍚�鍋滃姩鐢绘紨绀�?
#define ADDR_BOOTING_FAT_UP_DOWNDATA        0x3680//鐖嗚剛鑳介噺鍙橀�?

#define ADDR_KEY_SET_HANDLEONEDATA          0x3681//鍚庡彴璁剧疆椤垫墜鏌�?1鍙烽€夋嫨鍙橀�?
#define ADDR_KEY_SET_HANDLETWODATA          0x3682//鍚庡彴璁剧疆椤垫墜鏌�?2鍙烽€夋嫨鍙橀�?
#define ADDR_KEY_SET_HANDLETHREEDATA        0x3683//鍚庡彴璁剧疆椤垫墜鏌�?3鍙烽€夋嫨鍙橀�?
#define ADDR_KEY_SET_HANDLEFOURDATA         0x3684//鍚庡彴璁剧疆椤垫墜鏌�?4鍙烽€夋嫨鍙橀�?
#define ADDR_KEY_SET_HANDLEFIVEDATA         0x3685//鍚庡彴璁剧疆椤垫墜鏌�?5鍙烽€夋嫨鍙橀�?
#define ADDR_KEY_SET_WORKTIMEDATA           0x3686//鍚庡彴璁剧疆椤垫不鐤楁椂闂村彉閲�?
#define ADDR_KEY_SET_WORKPOWERDATA          0x3687//鍚庡彴璁剧疆椤垫不鐤楄兘閲忕櫨鍒嗘瘮鍙橀�?


#define ADDR_BOOTINGPRESSLINE         0x3766//璐熷帇婊戝姩鏉�
#define ADDR_BOOTINGRFLINE            0x3767//灏勯�戞粦鍔ㄦ潯
#define ADDR_BOOTINGPRESS_INLINE      0x3768//鍚告皵鏃堕棿婊戝姩鏉�?
#define ADDR_BOOTINGPRESS_OUTLINE     0x3769//鏀炬皵鏃堕棿婊戝姩鏉�
#define ADDR_BOOTINGLEDLINE           0x3770//LED绛夌骇婊戝姩鏉�
#define ADDR_BOOTINGINFRAREDLINE      0x3771//绾㈠�栫瓑绾ф粦鍔ㄦ潯
#define ADDR_BOOTINGMOTO_SPEEDLINE    0x3772//鐢垫満杞�閫熺瓑绾ф粦鍔ㄦ潯


#define ADDR_HANDCHOOSE               0x4200//鎵嬫焺閫夋嫨
#define ADDR_HANDPARAMETER            0x4300//鎵嬫焺鍙傛暟璁剧�?
#define ADDR_HANDWORK                 0x4301//鎵嬫焺鍚�鍋�?
#define ADDR_HAND40KWORK              0x4401//鐖嗚剛鎵嬫焺鍚�鍋�
#define ADDR_HAND40KPARAMETER         0x4400//鐖嗚剛鎵嬫焺鑳介噺绛夌骇
#define ADDR_HANDPARAMETER_SAVE       0x4500//鍚庡彴鑳介噺璁剧�?
#define ADDR_HANDPARAMETER_READ       0x4501//鍚庡彴鍙傛暟璇诲�?


#define ADDR_HANDPARAMETER_TO_ANDROID 0x4600//鎵嬫焺鍚戜笂浣嶆満鍚屾�ュ弬鏁拌�锋眰
#define ADDR_HANDWORK_TO_ANDROID      0x4601//鎵嬫焺鍚戜笂浣嶆満鍚�鍋滆�锋�?


#define ADDR_BOOTINGPRESSKEY          0x4666//璐熷帇澧為噺璋冭妭閿�鍊�?
#define ADDR_BOOTINGRFKEY             0x4667//灏勯�戝�為噺璋冭妭閿�鍊�
#define ADDR_BOOTINGPRESS_INKEY       0x4668//鍚告皵鏃堕棿澧為噺璋冭妭閿�鍊�
#define ADDR_BOOTINGPRESS_OUTKEY      0x4669//鏀炬皵鏃堕棿澧為噺璋冭妭閿�鍊�?
#define ADDR_BOOTINGLEDKEY            0x4670//LED澧為噺璋冭妭閿�鍊�
#define ADDR_BOOTINGINFRAREDKEY       0x4671//绾㈠�栧�為噺璋冭妭閿�鍊�
#define ADDR_BOOTINGMOTO_SPEEDKEY     0x4672//鐢垫満杞�閫熷�為噺璋冭妭閿�鍊�
#define ADDR_BOOTINGMOTO_TOWARDKEY    0x4673//鐢垫満杞�鍚戝�為噺璋冭妭閿�鍊�
#define ADDR_BOOTING_FAT_UP_KEY       0x4674//鐖嗚剛鑳介噺澧為噺璋冭妭閿�鍊�
#define ADDR_BOOTING_WORKTIME_KEY     0x4675//鍚庡彴娌荤枟鏃堕棿澧為噺璋冭妭閿�鍊�?
#define ADDR_BOOTING_WORKPOWER_KEY    0x4676//鍚庡彴鑳介噺鐧惧垎姣斿�為噺璋冭妭閿�鍊�?

#define ADDR_BOOTING_PASSWORD         0x5000//鍚庡彴瀵嗙爜閿�鐩樺湴鍧€
#define ADDR_BOOTING_PASSWORDERR      0x5100//鍚庡彴瀵嗙爜閿欒��鎻愮ず鍦板�?
#define ADDR_BOOTING_PASSWORDDISPLAY  0x5200//鍚庡彴瀵嗙爜鏄剧ず鍦板�?

#define ADDR_BOOTING_softwareVersion    0x5300//杩�鏂囪蒋浠剁増鏈�鏂囨湰鏄剧ず鍦板�?
#define ADDR_BOOTING_hardwareVersion    0x5400//纭�浠剁増鏈�鏂囨湰鏄剧ず鍦板潃
#define ADDR_BOOTING_hexVersion         0x5500//杞�浠剁増鏈�鏂囨湰鏄剧ず鍦板潃
#define ADDR_BOOTING_snNumber           0x5600//SN鏄剧ず鍦板潃

#define ADDR_BOOTING_SNPASSWORD         0x6000//SN瀵嗙爜閿�鐩樺湴鍧€
#define ADDR_BOOTING_SNPASSWORDERR      0x6100//SN瀵嗙爜閿欒��鎻愮ず鍦板�?
#define ADDR_BOOTING_SNPASSWORDDISPLAY  0x6200//SN瀵嗙爜鏄剧ず鍦板�?

#define ADDR_BOOTING_SNDISPLAYKEY       0x7000//SN杈撳叆閿�鐩樺湴鍧€
#define ADDR_BOOTING_SNDISPLAY          0x7200//SN杈撳叆鏄剧ず鍦板�?


#define ADDR_BOOTING_SNPASSWORDEND    0x8000//SN瀵嗙爜杈撳叆纭�璁�
#define ADDR_BOOTING_PASSWORDEND      0x8020//鍚庡彴瀵嗙爜杈撳叆纭�璁�
#define ADDR_BOOTING_SNEND            0x8040//SN杈撳叆淇�鏀圭‘璁�?

/*HAO**************************************/

#define LED2_ON      BitClr(PORTB,0)
#define LED2_OFF     BitSet(PORTB,0)
#define LED3_ON      BitClr(PORTE,7)
#define LED3_OFF     BitSet(PORTE,7)
#define LD2_ON       BitClr(PORTB,1)
#define LD2_OFF      BitSet(PORTB,1)
#define RF1_ON       BitClr(PORTB,2)
#define RF1_OFF      BitSet(PORTB,2)
#define RF2_ON       BitClr(PORTB,3)
#define RF2_OFF      BitSet(PORTB,3)
#define RF3_ON       BitClr(PORTB,4)
#define RF3_OFF      BitSet(PORTB,4)
#define RF4_ON       BitClr(PORTB,5)
#define RF4_OFF      BitSet(PORTB,5)
#define RFE_OFF      BitClr(PORTB,6)
#define RFE_ON       BitSet(PORTB,6)
#define RFM_OFF      BitSet(PORTB,7)
#define RFM_ON       BitClr(PORTB,7)
#define MD_OFF       BitClr(PORTE,5)
#define MD_ON        BitSet(PORTE,5)
#define XF_ON        BitClr(PORTG,1)
#define XF_OFF       BitSet(PORTG,1)
#define FOOT         BitTst(PINE,3)
#define TXD          BitSet(PORTD,1)
#define RXD          BitClr(PORTD,1)


#define KEY_NULL     0
#define KEY_DOWN     1
#define KEY_KEEP     2
#define KEY_UP       3
#define TOUCH_NULL   0
#define TOUCH_DOWN   1
#define TOUCH_KEEP   2
#define TOUCH_UP     3
#define FOOT_NULL    0
#define FOOT_DOWN    1
#define FOOT_KEEP    2
#define FOOT_UP      3
#define TRUE         1
#define FALSE        0

//function define
#define NULLMODE     0
#define RFMODE       1
#define IPLMODE      2
#define ELIGHTMODE   3
#define LPULSEMODE   4
#define LASER1MODE   5
#define LASER2MODE   6

#define WELCOMEPAGE  0
#define STARTPAGE    1
#define TIMEPAGE     2
#define TOUCHPAGE    3
#define SOUNDPAGE    4
#define LANGUAGEPAGE 5
#define BACKPAGE     6
#define USBPAGE      7
#define CARDPAGE     8
#define PASSWORDPAGE 9
#define SYSTEMPAGE   10
#define WORKTIMEPAGE 11    
#define OPTIONPAGE   12  
#define PARASPAGE     13  
#define HANDPAGE     14 
#define VERSIONPAGE    15
#define PARMPAGE     16
#define ICCARDPAGE   17
#define RESETPAGE    18  
#define PASSSETPAGE  19 
#define HANDSETPAGE  20
#define WORKPAGE     21
#define MVPAGE       22
#define ultrasonicpage 23

extern unsigned char water;
extern unsigned char Menu;
extern unsigned char MC;
extern unsigned char MV;
extern unsigned char Work;
extern unsigned char HandID;
extern unsigned char Hand_Event;
extern unsigned char Foot_Event;
extern unsigned char PasswordTab[6];
extern unsigned char DisPage;
extern unsigned char KeyID;
extern unsigned char BackSet;
extern unsigned char VerSet;
extern unsigned char WorktimeSet;
extern unsigned char PressureSet;
extern unsigned char Function_Tab[9];
extern unsigned char Function_Buf[9];
extern unsigned char Function_Count;
extern unsigned char Function_Ptr;
extern unsigned int  DelayMs;
extern unsigned char Page_ptr;
extern unsigned char SoundSet;
extern unsigned char Sound_Count;

extern unsigned long Total_counter;
extern unsigned int  Work_counter;
extern unsigned char ClockSet;
extern unsigned char Clk;
extern unsigned char Language;
extern unsigned char RfPer;
extern unsigned char Text[50];
extern unsigned char Text1[20];
extern unsigned char R_buf[20];
extern unsigned char R_buf1[20];
extern unsigned char T_buf[200];
extern unsigned char R_count;
extern unsigned char R_count1;
extern unsigned char R_Check;
extern unsigned char R_full;
extern unsigned char R_full1;
extern unsigned char T_ptr;
extern unsigned char T_count;
extern unsigned char Event_count;

extern unsigned char CardSet;
extern unsigned char Card_Event;
extern unsigned char Card_Info;
extern unsigned char Card_Command;
extern unsigned int  User_Counter;
extern unsigned char Card_ID;
extern unsigned char User_ID;
extern unsigned char Card_Type;
extern unsigned char User_Type;
extern unsigned int  Card_Counter;
extern unsigned char Card_Data[4];
extern unsigned char Touch_Event;
extern unsigned char Touch_Buf;
extern unsigned int  Touch_ID;
extern unsigned int  Touch_X;
extern unsigned int  Touch_Y;
extern unsigned int  w_buf;
extern unsigned int SetID;
extern unsigned char text_ptr;
extern unsigned char datetime[7];
extern unsigned char Intensity[7];
extern unsigned char Handpiece;
extern unsigned char Mode;
extern const struct KEY Main_Key[6];
extern const struct KEY Start_Key[9];
extern const struct KEY Time_Key[13];
extern const struct KEY Sound_Key[3];
extern const struct KEY Language_Key[15];
extern const struct KEY Back_Key[4];
extern const struct KEY USB_Key[3];
extern const struct KEY Card_Key[16];
extern const struct KEY System_Key[10];
extern const struct KEY Count_Key[2];
extern const struct KEY Option_Key[5];
extern const struct KEY Handpiece_Key[22];
extern const struct KEY CardSet_Key[3];
extern const struct KEY VerSet_Key[3];
extern const struct KEY Reset_Key[3];
extern const struct KEY Paras_Key[4];
extern const struct KEY Work_Key[19];
extern const struct KEY UL_Key[4];
extern const unsigned char Intensity_Tab[5][9];
extern const unsigned char Intensity_Max[9];
extern const unsigned char hand[4];

/***HAO**********************************************/
extern unsigned char RX1Data[20][30];
extern unsigned char RX1Counterhead;//
extern unsigned char RX1Countertail;
extern unsigned char RX2Data[10][30];
extern unsigned char RX2Counterhead;//
extern unsigned char RX2Countertail;
extern unsigned char passwordInput[8];//杈撳叆瀵嗙�?
extern unsigned char password[8];//棰勮�惧瘑鐮�?
extern unsigned char SNpassword[8];//棰勮�惧瘑鐮�?
extern unsigned char SNInput[16];//杈撳叆SN
extern void Key_Password(unsigned char key);
extern unsigned char DIWEN_RECEICEDATA_STATE;
extern unsigned char SAVE_FAT_FLAME;//鐖嗚剛鑳介噺绛夌�?
/***HAO*********************************************/
#endif