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

//read KADE pin states into an array
#include "../shared/state.c"				

//set shifted status and detect shift lock (double click)
#include "../shared/shift.c"		

//set flags for various inputs
invert=0;
restrict4=0;
autofire=0;		
		
//dpad: up, down, left, right flags
//previous value retained for reference when restricting (2-way or 4-way)
u=0; d=0; l=0; r=0;
pu=u; pd=d; pl=l; pr=r;
uint8_t dp_pp=0, dp_lp=0, set;

//pre-loop to deal with any switches/toggles		
for(cnt=0;cnt<20;cnt++) {
	if (!(state[cnt])) {
	
		//there is input on this pin, also account for shifted input
		pos = cnt;
		if (shift==1){pos=pos+20;}
				
		if ((ass[cnt]==func_invert_y_axis)||(ass[pos]==func_invert_y_axis)){invert=1;}
		if ((ass[cnt]==func_restrict_4way)||(ass[pos]==func_restrict_4way)){restrict4=1;}
		
		if (ass[pos]==func_autofire_1){autofire=1;}
		if (ass[pos]==func_autofire_2){autofire=1;}
		if (ass[pos]==func_autofire_3){autofire=1;}
		if (ass[pos]==func_autofire_4){autofire=1;}
		
		if (ass[pos]==func_dpad_up)   {u=1;}
		if (ass[pos]==func_dpad_down) {d=1;}				
		if (ass[pos]==func_dpad_left) {l=1;}
		if (ass[pos]==func_dpad_right){r=1;}
	}
			
	//Show the shift status LED(s) and power up externals with delay
	if (ass[cnt]==func_ext_shift_led){
		led_active = shift;
		#include "../shared/showleds.c"								
	}
}			

//autofire toggle
if(autofire==1){
	auto_toggle = auto_toggle * -1;
}


//Handle dpad and restricted movement
if (default_restrict == 1){
	dpad_u=0; dpad_d=0; dpad_l=0; dpad_r=0;
	if(restrict4==0){
		dpad_u = u;
		dpad_d = d;
		dpad_l = l;
		dpad_r = r;
	} else {
		//Restrict Dpad to 4-way operation.  
		//Movement is based on weighting of directions compared to current position
		set=0;
		if ((u==pu)&&(d==pd)&&(l==pl)&&(r==pr)){ dp_pp = dp_lp; }						
		dp_lp=dp_pp;
				
		if(dp_pp==1){
			if ((d==1)&&(set==0)){dpad_d=1; dp_pp=2; set=1;}
			if ((l==1)&&(set==0)){dpad_l=1; dp_pp=3; set=1;}
			if ((r==1)&&(set==0)){dpad_r=1; dp_pp=4; set=1;}											
			if ((u==1)&&(set==0)){dpad_u=1; dp_pp=1; set=1;}
		}						
		if(dp_pp==2){
			if ((u==1)&&(set==0)){dpad_u=1; dp_pp=1; set=1;}
			if ((l==1)&&(set==0)){dpad_l=1; dp_pp=3; set=1;}
			if ((r==1)&&(set==0)){dpad_r=1; dp_pp=4; set=1;}											
			if ((d==1)&&(set==0)){dpad_d=1; dp_pp=2; set=1;}
		}						
		if(dp_pp==3){
			if ((r==1)&&(set==0)){dpad_r=1; dp_pp=4; set=1;}											
			if ((u==1)&&(set==0)){dpad_u=1; dp_pp=1; set=1;}
			if ((d==1)&&(set==0)){dpad_d=1; dp_pp=2; set=1;}
			if ((l==1)&&(set==0)){dpad_l=1; dp_pp=3; set=1;}
		}						
		if((dp_pp==4)||(dp_pp==0)){
			if ((l==1)&&(set==0)){dpad_l=1; dp_pp=3; set=1;}
			if ((u==1)&&(set==0)){dpad_u=1; dp_pp=1; set=1;}
			if ((d==1)&&(set==0)){dpad_d=1; dp_pp=2; set=1;}
			if ((r==1)&&(set==0)){dpad_r=1; dp_pp=4; set=1;}											
		}				
	}
}

//Handle trackballs and mice
if (setting_enable_tb1==1){
	readTrackBall();		
	calcMovement();				
}
