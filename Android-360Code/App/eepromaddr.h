#ifndef  __EEPR0MADDR_H
#define  __EEPROMADDR_H
#define SoundSetAddr 9
#define ClockSetAddr 10
#define LanguageAddr 11
#define CardSetAddr  12
#define UserIDAddr   13
#define WaterSetAddr 14
#define VerDisAddr   15
#define WorktimeAddr 16
#define PressureAddr 17
#define TempBAddr    21
#define CounterAddr  25
#define HandpieceModeAddr    40
#define FunctionAddr 50    //9 bit
#define BackSetAddr  60
#define PasswordAddr 70
#define IntensityAddr  80    //36bit
#define RfPerAddr      120   //1 bit

#define softwareVersionAddr   130   //16bit
#define hardwareVersionAddr   146   //16bit
#define hexVersionAddr        162   //16bit
#define snNumberAddr          178   //16bit

#define SET_HANDLEONEAddr     195   //1bit
#define SET_HANDLETWOAddr     196   //1bit
#define SET_HANDLETHREEAddr   197   //1bit
#define SET_HANDLEFOURAddr    198   //1bit
#define SET_HANDLEFIVEAddr    199   //1bit
#define SET_WORKTIMEAddr      200   //1bit
#define SET_WORKPOWERAddr     201   //1bit

#define HNDLE_INFORMATION_AAddr 210   //40 bit
#define HNDLE_INFORMATION_BAddr 250   //40 bit
#define HNDLE_INFORMATION_CAddr 290   //40 bit

#define FAT_FLAME_AAddr 331   //1 bit
#define FAT_FLAME_BAddr 332   //1 bit
#define FAT_FLAME_CAddr 333   //1 bit

#endif