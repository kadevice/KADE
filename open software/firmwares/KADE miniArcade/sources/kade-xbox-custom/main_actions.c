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
* Bruno Freitas - bootsector@ig.com.br
* Jon Wilson    - degenatrons@gmail.com
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

//A, B, X, Y
if (action==5){bit_set(gamepad_state.a,0xFF);}
if (action==6){bit_set(gamepad_state.b,0xFF);}
if (action==7){bit_set(gamepad_state.x,0xFF);}
if (action==8){bit_set(gamepad_state.y,0xFF);}

//Autofire
if (autofire==1){
	if(auto_toggle==1){
		if (action==33){bit_set(gamepad_state.a,0xFF);}
		if (action==34){bit_set(gamepad_state.b,0xFF);}
		if (action==35){bit_set(gamepad_state.x,0xFF);}
		if (action==36){bit_set(gamepad_state.y,0xFF);}
	}
	//autofire delay
	for(auto_cnt=0;auto_cnt < setting_delay_autofire;auto_cnt++){_delay_ms(1);}
}

//Left trigger, right trigger
if (action==9){bit_set(gamepad_state.l,0xFF);}
if (action==10){bit_set(gamepad_state.r,0xFF);}

//Black, white
if (action==11){bit_set(gamepad_state.black,0xFF);}
if (action==12){bit_set(gamepad_state.white,0xFF);}

//Start, back
if (action==13){bit_set(gamepad_state.digital_buttons,0x10);}
if (action==14){bit_set(gamepad_state.digital_buttons,0x20);}

//Left thumb, Right thumb
if (action==15){bit_set(gamepad_state.digital_buttons,XBOX_LEFT_STICK);}
if (action==16){bit_set(gamepad_state.digital_buttons,XBOX_RIGHT_STICK);}

//Left analog stick
if (action==(17+invert)){gamepad_state.l_y=32767;}
if (action==(18-invert)){gamepad_state.l_y=-32768;}
if (action==19){gamepad_state.l_x=-32768;}
if (action==20){gamepad_state.l_x=32767;}

//Right analog stick
if (action==(21+invert)){gamepad_state.r_y=32767;}
if (action==(22-invert)){gamepad_state.r_y=-32768;}
if (action==23){gamepad_state.r_x=-32768;}
if (action==24){gamepad_state.r_x=32767;}

//Exit to dash
if (action==26){
	bit_set(gamepad_state.l,0xFF);
	bit_set(gamepad_state.r,0xFF);
	bit_set(gamepad_state.black,0xFF);
	bit_set(gamepad_state.white,0xFF);
}

//check Disable start+back setting
if (setting_disable_sb==1) {
	if((gamepad_state.digital_buttons&0x10)&&(gamepad_state.digital_buttons&0x20)){
		bit_clear(gamepad_state.digital_buttons,0x10);
		bit_clear(gamepad_state.digital_buttons,0x20);						
	}
}

//Exit game
if (action==25){
	bit_set(gamepad_state.digital_buttons,0x10);
	bit_set(gamepad_state.digital_buttons,0x20);
}

//Enter programming mode
if (action==37){
	Jump_To_Bootloader();
}


//Advanced Combos-----------------------------------------
//Combo [A] Back+White
if (action==38){
	bit_set(gamepad_state.digital_buttons,0x20);
	bit_set(gamepad_state.white,0xFF);
}

//Combo [B] Back+Black
if (action==39){
	bit_set(gamepad_state.digital_buttons,0x20);
	bit_set(gamepad_state.black,0xFF);
}

//Combo [C] Back+LT+RT
if (action==40){
	bit_set(gamepad_state.digital_buttons,0x20);
	bit_set(gamepad_state.l,0xFF);
	bit_set(gamepad_state.r,0xFF);
}

//Combo [D] Back+RTh
if (action==41){
	bit_set(gamepad_state.digital_buttons,0x20);
	bit_set(gamepad_state.digital_buttons,XBOX_RIGHT_STICK);
}

//Combo [E] Back+RT+RTh
if (action==42){
	bit_set(gamepad_state.digital_buttons,0x20);
	bit_set(gamepad_state.r,0xFF);						
	bit_set(gamepad_state.digital_buttons,XBOX_RIGHT_STICK);
}

//Combo [F] Back+LT+RTh
if (action==43){
	bit_set(gamepad_state.digital_buttons,0x20);
	bit_set(gamepad_state.l,0xFF);
	bit_set(gamepad_state.digital_buttons,XBOX_RIGHT_STICK);
}

//Combo [G] Back+LTh
if (action==44){
	bit_set(gamepad_state.digital_buttons,0x20);
	bit_set(gamepad_state.digital_buttons,XBOX_LEFT_STICK);
}

//Combo [H] Back+A+B
if (action==45){
	bit_set(gamepad_state.digital_buttons,0x20);
	bit_set(gamepad_state.a,0xFF);
	bit_set(gamepad_state.b,0xFF);
}

//Combo [I] Back+Black+B
if (action==46){
	bit_set(gamepad_state.digital_buttons,0x20);
	bit_set(gamepad_state.black,0xFF);
	bit_set(gamepad_state.b,0xFF);
}
