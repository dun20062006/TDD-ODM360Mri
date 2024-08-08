NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                        func_lit   008C   0060 =     96. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       008C  __func_lit_start
       00EC  __func_lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             lit   00EC   0957 =   2391. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       00EC  __lit_start
       00EC  _Color
       00F0  _Color1
       00F4  _pxy
       0134  _temp_text
       013C  _user_type
       0154  _Main_Key
       0184  _Start_Key
       01CC  _Time_Key
       0234  _Sound_Key
       024C  _Language_Key
       02D4  _Back_Key
       02F4  _USB_Key
       030C  _Card_Key
       038C  _System_Key
       03DC  _Count_Key
       03EC  _Option_Key
       0414  _Handpiece_Key
       04C4  _CardSet_Key
       04DC  _VerSet_Key
       04F4  _Reset_Key
       050C  _Paras_Key
       052C  _Work_Key
       05C4  _UL_Key
       05E4  _Intensity_Tab
       0608  _Intensity_Max
       0611  _hand
       0615  _Ver
       061F  _HARDVer
       062A  _HEXVer
       0635  _filename
       063F  _filename1
       0646  _usbtext
       0651  _ERR_USR_COUNNECT
       0684  _ERR_DISK_DISCON
       06B7  _ERR_SUCCESS
       06C0  _ERR_STATUS_ERR
       06F5  _ERR_FAT_ERROR
       0719  _ERR_DISK_FULL
       0754  _ERR_MISS_DIR
       077F  _ERR_FILE_CLOSE
       07BB  _ERR_OPEN_DIR
       07DA  _ERR_MISS_FILE
       0821  _ERR_USB_DISK_ERR
       0843  uart.c:CRCHigh
       0943  uart.c:CRCLow
       0A43  __lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   0A43   02E4 =    740. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0A43  __idata_start
       0D27  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0D28   7EA4 =  32420. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0694  __start
       0694  __text_start
       06B6  _exit
       06B7  _delay_ms
       06CC  _DataSynchronization
       0732  _ItoA
       0756  _LtoA
       07CC  _DisCount
       0891  _Dis_pressure
       0892  _DisFunctionKey
       090A  _DisWelcome
       0952  _DisIntensity
       0982  _HandpieceSet
       099D  _ModeSet
       09FA  _IntensitySet
       0A52  _DisMode
       0A53  _DisWork
       0A55  _DisMV
       0A56  _GetKeyID
       0A87  _MainKeyDown
       0AE9  _MainKeyUp
       0B54  _StartKeyDown
       0EC3  _StartKeyUp
       0EEB  _TimeKeyDown
       110B  _TimeKeyUp
       1224  _SoundKeyDown
       12B4  _SoundKeyUP
       12C3  _LanguageKeyDown
       1340  _LanguageKeyUp
       134D  _BackKeyDown
       13EC  _BackKeyUp
       1405  _USBKeyDown
       1444  _USBKeyUp
       1493  _CardKeyDown
       17D5  _CardKeyUp
       18D4  _PasswordKeyDown
       1B17  _PasswordKeyUp
       1B59  _SystemKeyDown
       1F78  _SystemKeyUp
       1F87  _ClearCountKeyDown
       201F  _ClearCountKeyUp
       207C  _ParmKeyDown
       207D  _ParmKeyUp
       212F  _OptionKeyDown
       21A6  _OptionKeyUp
       21D6  _CardSetKeyDown
       220C  _CardSetKeyUp
       221C  _PassSetKeyDown
       2487  _PassSetKeyUp
       24C6  _HandpieceKey
       2664  _WorkKeyDown
       2665  _WorkKeyUp
       277F  _ULKeyDown
       29D4  _ULKeyUP
       2A94  _ParasKeyDown
       2B34  _ParasKeyUp
       2B44  _VersionKeyDown
       2B93  _VersionKeyUp
       2BA3  _ResetKeyDown
       2BF3  _ResetKeyUp
       2C2A  _Key
       2D3A  _uart0_init
       2D47  _uart1_init
       2D58  _timer0_init
       2D61  _timer1_init
       2D7D  _adc_init
       2D86  _timer2_init
       2D8D  _timer3_init
       2DAE  _port_init
       2DC8  _init_devices
       2DE6  _cartoon
       2DF4  _DisVer
       2E51  _init_system
       2F84  _Delay_MS
       2F91  _Delay_10MS
       2F9B  _start_pwm
       2FA0  _stop_pwm
       2FA6  _out_pulse
       2FB6  _sound
       2FC3  _water_count
       3006  _timer0_comp_isr
       30B9  _timer1_compc_isr
       30BA  _timer2_comp_isr
       30C3  _timer2_ovf_isr
       318C  _timer3_compc_isr
       3198  _timer3_ovf_isr
       31A5  _adc_isr
       31A6  _main
       31B4  _Init_Task
       3201  _Add_Task
       325F  _Delete_Task
       32BE  _Report_Status
       32BF  _Updata
       3389  _Dispartch_Task
       33D8  _uart0_rx_isr
       3472  _uart1_rx_isr
       3501  _uart0_tx_isr
       352A  _uart1_tx_isr
       3556  _WaitTX
       3570  _WaitRX
       3586  _DefaultSetting
       35CF  _CheckCRC16
       3601  _DwinToPage
       366D  _DwinWriteWord
       36D0  _DwinWriteLongWords
       374E  _Key_Password
       38C2  _TASK_SendToDwin
       3D94  _TASK_PROCESSING
       3E1A  _GetChecking
       3E5C  _GetCheckingOr
       3ED8  _ShakeHands
       3F03  _set_color
       3F04  _set_text_xy
       3F05  _get_color
       3F06  _cursor
       3F07  _print_text
       3F08  _print_texts
       3F09  _print_consttexts
       3F0A  _textsize_enable
       3F0B  _textsize_disable
       3F0C  _Painting_dot
       3F0D  _Painting_dots
       3F0E  _Painting_line
       3F0F  _Set_screen
       3F10  _clear_screen
       3F11  _Chack_screen
       3F12  _PicRam
       3F13  _dis_pic
       3F14  _cut_pic
       3F15  _buzzer
       3F40  _clock_off
       3F41  _get_time
       3F42  _clock_on
       3F43  _clock_set
       3F44  _send_pic
       3F45  _save_pic
       3F46  _USB_info
       3F47  _CMD_GetVer
       3F62  _CMD_DiskReady
       3F7D  _CMD_File
       3FE7  _CMD_ByteLocate
       4041  _CMD_ByteRead
       405E  _CMD_ByteWrite
       40B8  _CMD_RESET
       40D3  _GetUSB
       40EB  _Up_Pic
       422A  _dispose_data
       430F  _Send_Data
       4333  _Send_Data8
       437A  _Send_command
       439E  _Send_EN
       43C2  _memcpy
       43D0  _memset
       43DB  _strcpy
       43E4  push_arg4
       43E6  push_arg2
       43E9  mod16s
       43ED  div16s
       4407  mod16u
       4409  div16u
       440A  xdiv16u
       4423  div32u
       4425  mod32u
       4429  div32s
       442B  mod32s
       4457  long_div_prolog
       446A  long_div_epilog
       447A  tst_R16_R19
       447F  tst_R24_R27
       4484  neg_R24_R27
       448D  mod8u
       448F  div8u
       4490  xdiv8u
       44A5  empy16s
       44B5  empy32s
       44B5  empy32u
       44E9  pop_xgset00FC
       44F0  pop_xgset30FC
       44F9  pop_xgsetF0FC
       4504  push_xgsetF0FC
       4506  push_xgset30FC
       4508  push_xgset00FC
       450A  push_xgset003C
       450F  push_xgset300C
       4514  pop_xgset300C
       4519  push_xgsetF000
       451E  pop_xgsetF000
       4523  push_xgsetF00C
       452A  pop_xgsetF00C
       4531  push_xgset303C
       4538  pop_xgset303C
       453F  push_xgsetF03C
       4548  pop_xgsetF03C
       4551  xicallx
       455A  neg32
       4563  long_prolog
       4571  long_epilog
       457C  tstzero1
       4582  tstzero2
       4588  lsl8
       458E  lsr32
       459A  _EEPROMread
       45A1  _EEPROMwrite
       45B0  _EEPROMReadBytes
       45CB  _EEPROMWriteBytes
       45E6  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0100   02E4 =    740. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0100  __data_start
       0100  _UL_workdate
       0101  _POWER_LEVEL
       0102  app.c:count1
       0103  app.c:count2
       0104  app.c:count3
       0105  app.c:time
       0106  app.c:Cnt
       0107  app.c:ID
       0109  app.c:count
       010B  _water
       010C  _Menu
       010D  _MC
       010E  _MV
       010F  _Clk
       0110  _Work
       0111  _HandID
       0112  _Hand_Event
       0113  _Foot_Event
       0114  _DisPage
       0115  _KeyID
       0116  _BackSet
       0117  _VerSet
       0118  _WorktimeSet
       0119  _PressureSet
       011A  _Function_Count
       011B  _Function_Ptr
       011C  _DelayMs
       011E  _Page_ptr
       011F  _SoundSet
       0120  _Sound_Count
       0121  _ClockSet
       0122  _Language
       0123  _password
       012B  _SNpassword
       0133  _R_buf
       022D  _R_buf1
       0291  _T_buf
       038B  _R_count
       038C  _R_count1
       038D  _R_Check
       038E  _R_full
       038F  _R_full1
       0390  _T_ptr
       0391  _T_count
       0392  _Event_count
       0393  _CardSet
       0394  _Card_Event
       0395  _Card_Info
       0396  _Card_Command
       0397  _Card_ID
       0398  _User_ID
       0399  _Card_Type
       039A  _User_Type
       039B  _Card_Counter
       039D  _User_Counter
       039F  _Card_Data
       03A3  _Touch_Event
       03A4  _Touch_Buf
       03A5  _Touch_ID
       03A7  _w_buf
       03A9  _SetID
       03AB  _text_ptr
       03AC  _datetime
       03B3  _Intensity
       03BC  _Handpiece
       03BD  _Mode
       03BE  _lcd_ver
       03C2  Init.c:x
       03C3  isr.c:w_cnt
       03C5  isr.c:w_bit
       03C7  isr.c:count
       03C9  isr.c:xf
       03CB  isr.c:count:1
       03CC  _RTX
       03CD  _DwinCmd
       03CE  _DwinAddr
       03D0  _DwinData
       03D2  _Dwindata2
       03D4  _DIWEN_RECEICEDATA_STATE
       03E4  __data_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             bss   03E4   04C4 =   1220. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       03E4  __bss_start
       03E4  app.c:enter_mode_num
       03E6  _Touch_Y
       03E8  _Touch_X
       03EA  _Text1
       03FE  _Text
       0430  _SNInput
       0440  _passwordInput
       0448  _RX2Countertail
       0449  _RX2Counterhead
       044A  _RX2Data
       0576  _RX1Countertail
       0577  _RX1Counterhead
       0578  _RX1Data
       07D0  _RfPer
       07D1  _Work_counter
       07D3  _Total_counter
       07D7  _Function_Buf
       07E0  _Function_Tab
       07E9  _PasswordTab
       07EF  _Last_error_code
       07F0  _Error_tick_const
       07F2  _Error_code
       07F3  _Tasks
       084B  _SAVE_FAT_FLAME
       084C  _DwinDate
       0854  _SettingDdata
       089B  _MACHINE_STATE
       08A0  _HNDLE_INFORMATION
       08A8  __bss_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0084 =    132. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

C:\iccv7avr\lib\crtatmega.o	[ crtatmega.s ]
app.o	[ app.c ]
def.o	[ def.c ]
Init.o	[ Init.c ]
isr.o	[ isr.c ]
main.o	[ main.c ]
task.o	[ task.c ]
uart.o	[ uart.c ]
<library>	[ memcpy.s, memset.s, strcpy.s, asave.s, div16s.s, div16u.s, div32.s, div8u.s, emul16s.s, emul32.s, gpop3.s ]
[ gpop4.s, gpop5.s, gpush.s, gpushx.s, gpushy.s, gpushz.s, gpusha.s, gpushb.s, icallx.s, lneg.s, longutil.s ]
[ lsl8.s, lsr32.s, eepromr.s, eepromw.s, eepromrbytes.s, eepromwbytes.s ]

User Global Definitions

ram_end = 0x10ff
hwstk_size = 0x80

User Base Address Definitions

func_lit = 0x8c
data = 0x100
eeprom:0.4096

