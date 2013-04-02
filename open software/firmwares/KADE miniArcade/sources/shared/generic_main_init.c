/*
     .k8GOGGNqkSFS5XkqXPSkSkkqXXFS5kSkSS15U22F2515U2uujuu1U1u2U1U2uUuFS.     
   :0qE     JS5uuJuuFFX51jU2SSk12jU2SSXF5uuu15SFS5k12ujj21S5kFS5S12jJYu11    
  5XS:        1UYYLu.   vUUX    U22r     SUF         SUF           ;YYLuU5   
 1F5i  NNSkS7  2uLJui   51u     S5.      .PX         .XX           LJvLLu1.  
 kUk  0iLk5FFu vuYY2:   5F    Xkk7        78    E0    i0    GEXPXk2uLLvLLuk  
X25, 8O   2kX0  5YJUi   M    555    PkXk   i    q1FU   7    ONNkP12YLvLvLYS  
S25  8888  888  5uY5         FuS    PS50   .    FuUU   7          uJvLvLLJ2i 
kUF             SJjU.      P02UF    P25k   .    Su2Y   v          2LLvLvLL17 
S21  XJj88  0u  1uY2.        X2k           .    k11E   v    7;ii:JuJvLvLvJ2: 
2257 jqv   Pqq  1LJur         PP.          7    EX:    q    OqqXP51JYvLvYYS.  
 X2F  kXkXSXk  kJYLU:   O     ,Z    0PXZ   i    ii    q0    i:::,,.jLLvLLuF'  
 ik1k  ;qkPj  .uJvYu:   UN      :   XU2F   :         S5S           iJLLvjUF8   
  :PSq       72uLLLui   uSi    .;   2uY1   r.       72j1           LYYLYJSU88
    XqE2   rP12juJuu1FX55U5FqXXSXkXF1juUkkPSXSPXPXPF1Jju5FkFSFXFSF5uujUu5j28V 
      .uGOZESS5S5SFkkPkPkXkPXqXPXqXXFkSkkPXPXPkqSkSS1521252121U2u2u12Suv7   

*
* KADE - Kick Ass Dynamic Encoder
*
* Copyright (c) 2013 
* Jon Wilson    - degenatrons@gmail.com
* Bruno Freitas - bootsector@ig.com.br
* Kevin Mackett - kevin@sharpfork.com
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
* ADDITIONAL TERMS per GNU GPL Section 7
* No trademark or publicity rights are granted. This license does NOT give you 
* any right, title or interest in the KADE brand. You may not distribute any 
* modification of this program using the KADE name or KADE logo or claim any 
* affiliation or association with KADE or the KADE development team.
*
* Any propagation or conveyance of this program must include this copyright 
* notice and these terms.
*
* You may not misrepresent the origins of this program; modified versions of the 
* program must be marked as such and not identified as the original program.
*/ 

//dpad and pad restrictions
uint8_t dpad_u, dpad_d, dpad_l, dpad_r;
uint8_t	u=0, d=0, l=0, r=0, pu=0, pd=0, pl=0, pr=0;
	
//pin assignments and button states
uint8_t ass[40], action, state[20];
uint8_t	pos=0, cnt=0;

//Define additional eeprom bytes for this firmware
uint8_t byte_delay_setting  = 41;
uint8_t byte_delay_autofire = 42;
	
//Additional eeprom bytes for trackball settings
uint8_t byte_enable_tb1    = 43;
uint8_t byte_enable_tb2    = 44;	
uint8_t byte_tb1_counts    = 45;
uint8_t byte_tb1_samples   = 46;
uint8_t byte_tb1_trackball = 47;
uint8_t byte_tb1_spinner   = 48;
uint8_t byte_tb1_mouse     = 49;
uint8_t byte_tb2_counts    = 50;
uint8_t byte_tb2_samples   = 51;
uint8_t byte_tb2_trackball = 52;
uint8_t byte_tb2_spinner   = 53;
uint8_t byte_tb2_mouse     = 54;
	
//Additional eeprom bytes for trackball button assignments
uint8_t byte_tb1_stick     = 55;	
uint8_t byte_tb1_but1      = 56;	
uint8_t byte_tb1_but2      = 57;	
uint8_t byte_tb1_but3      = 58;	
uint8_t byte_tb1_but1s     = 59;	
uint8_t byte_tb1_but2s     = 60;	
uint8_t byte_tb1_but3s     = 61;	
uint8_t byte_tb2_stick     = 62;	
uint8_t byte_tb2_but1      = 63;	
uint8_t byte_tb2_but2      = 64;	
uint8_t byte_tb2_but3      = 65;	
uint8_t byte_tb2_but1s     = 66;	
uint8_t byte_tb2_but2s     = 67;	
uint8_t byte_tb2_but3s     = 68;	
	
//handle shift and shift lock
uint8_t shift=0, shift_last=0, shift_count=0, shift_lock=0;

//handle autofire
uint8_t setting_delay_autofire=15, autofire, auto_toggle=1, auto_cnt;
	
//handle settings
uint8_t setting_delay_power=0;
uint8_t led_active=0, delay_power=0;
uint8_t invert, restrict4;

//trackball settings
uint8_t setting_enable_tb1;
uint8_t setting_enable_tb2;	
uint8_t setting_tb1_counts;
uint8_t setting_tb1_samples;
uint8_t setting_tb1_trackball;
uint8_t setting_tb1_spinner;
uint8_t setting_tb1_mouse;
uint8_t setting_tb2_counts;
uint8_t setting_tb2_samples;
uint8_t setting_tb2_trackball;
uint8_t setting_tb2_spinner;
uint8_t setting_tb2_mouse;

//trackball button assignments
uint8_t setting_tb1_stick;
uint8_t setting_tb1_but1;
uint8_t setting_tb1_but2;
uint8_t setting_tb1_but3;
uint8_t setting_tb1_but1s;
uint8_t setting_tb1_but2s;
uint8_t setting_tb1_but3s;
uint8_t setting_tb2_stick;
uint8_t setting_tb2_but1;
uint8_t setting_tb2_but2;
uint8_t setting_tb2_but3;
uint8_t setting_tb2_but1s;
uint8_t setting_tb2_but2s;
uint8_t setting_tb2_but3s;
//Flash LEDs
#include "..\shared\disco.c"

//read first 40 eeprom into an array (pins + shifted pins)
for(cnt=0;cnt<40;cnt++){	
	ass[cnt]=read_eeprom_byte(cnt);

	//set output pins
	if ((ass[cnt]==func_ext_shift_led)||(ass[cnt]==func_ext_power_led)){
		#include "..\shared\outputs.c"		
	}
	if (ass[cnt]==func_ext_power_led){
		delay_power=1;
	}	
}

//Read other settings from eeprom 
setting_delay_power=read_eeprom_byte(byte_delay_setting);
setting_delay_autofire=read_eeprom_byte(byte_delay_autofire);

setting_enable_tb1=read_eeprom_byte(byte_enable_tb1);
setting_enable_tb2=read_eeprom_byte(byte_enable_tb2);
setting_tb1_counts=read_eeprom_byte(byte_tb1_counts);
setting_tb1_samples=read_eeprom_byte(byte_tb1_samples);
setting_tb1_trackball=read_eeprom_byte(byte_tb1_trackball);
setting_tb1_spinner=read_eeprom_byte(byte_tb1_spinner);
setting_tb1_mouse=read_eeprom_byte(byte_tb1_mouse);
setting_tb2_counts=read_eeprom_byte(byte_tb2_counts);
setting_tb2_samples=read_eeprom_byte(byte_tb2_samples);
setting_tb2_trackball=read_eeprom_byte(byte_tb2_trackball);
setting_tb2_spinner=read_eeprom_byte(byte_tb2_spinner);
setting_tb2_mouse=read_eeprom_byte(byte_tb2_mouse);

setting_tb1_stick=read_eeprom_byte(byte_tb1_stick);
setting_tb1_but1=read_eeprom_byte(byte_tb1_but1);
setting_tb1_but2=read_eeprom_byte(byte_tb1_but2);
setting_tb1_but3=read_eeprom_byte(byte_tb1_but3);
setting_tb1_but1s=read_eeprom_byte(byte_tb1_but1s);
setting_tb1_but2s=read_eeprom_byte(byte_tb1_but2s);
setting_tb1_but3s=read_eeprom_byte(byte_tb1_but3s);
setting_tb2_stick=read_eeprom_byte(byte_tb1_stick);
setting_tb2_but1=read_eeprom_byte(byte_tb1_but1);
setting_tb2_but2=read_eeprom_byte(byte_tb1_but2);
setting_tb2_but3=read_eeprom_byte(byte_tb1_but3);
setting_tb2_but1s=read_eeprom_byte(byte_tb1_but1s);
setting_tb2_but2s=read_eeprom_byte(byte_tb1_but2s);
setting_tb2_but3s=read_eeprom_byte(byte_tb1_but3s);

//prevent crazy autofire setting
if (setting_delay_autofire < 5){ setting_delay_autofire = 15;}
if (setting_delay_autofire > 250){ setting_delay_autofire = 250;}

//wait for specified delay time (allow time for led flash)
if ((delay_power==1)&&(setting_delay_power>0)){
	for(cnt=0;cnt<=setting_delay_power-1;cnt++){
		_delay_ms(1000);
	}
	led_active=1;
	for(cnt=0;cnt<40;cnt++){	
		if (ass[cnt]==func_ext_power_led){
			#include "..\shared\showleds.c"
		}
	}
}
