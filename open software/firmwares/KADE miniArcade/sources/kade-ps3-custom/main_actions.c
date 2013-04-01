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
*/ 
 
//A, B, X, Y
if (action==5){gamepad_state.square_btn=0xFF;}
if (action==6){gamepad_state.cross_btn=0xFF;}
if (action==7){gamepad_state.circle_btn=0xFF;}
if (action==8){gamepad_state.triangle_btn=0xFF;}

//Autofire
if (autofire==1){
	if(auto_toggle==1){
		if (action==24){gamepad_state.square_btn=0xFF;}
		if (action==25){gamepad_state.cross_btn=0xFF;}
		if (action==26){gamepad_state.circle_btn=0xFF;}
		if (action==27){gamepad_state.triangle_btn=0xFF;}
	}
	//autofire delay
	for(auto_cnt=0;auto_cnt < setting_delay_autofire;auto_cnt++){_delay_ms(1);}
}	

//PS3 Triggers
if (action==9){gamepad_state.l1_btn=0xFF;}   		    //L1
if (action==10){gamepad_state.r1_btn=0xFF;}  		    //R1					
if (action==11){gamepad_state.l2_btn=0xFF;}  		    //L2
if (action==12){gamepad_state.r2_btn=0xFF;}   			//R2
if (action==15){gamepad_state.l3_btn=0xFF;}  		    //L3
if (action==16){gamepad_state.r3_btn=0xFF;}				//R3

//PS3 Special
if (action==13){gamepad_state.select_btn=0xFF;}		//Select
if (action==14){gamepad_state.start_btn=0xFF;}			//Start
if (action==17){gamepad_state.ps_btn=0xFF;}			//PS Button
										
//Left Analog Stick
if (action==18+invert){gamepad_state.l_y_axis = 0x00;} 	//L/Analog Up
if (action==19-invert){gamepad_state.l_y_axis = 0xff;} 	//L/Analog Down
if (action==20){gamepad_state.l_x_axis = 0x00;} 			//L/Analog Left
if (action==21){gamepad_state.l_x_axis = 0xff;} 			//L/Analog Right

//Right Analog Stick
if (action==31+invert){gamepad_state.r_y_axis = 0x00;} 	//R/Analog Up
if (action==32-invert){gamepad_state.r_y_axis = 0xff;} 	//R/Analog Down
if (action==33){gamepad_state.r_x_axis = 0x00;} 			//R/Analog Left
if (action==34){gamepad_state.r_x_axis = 0xff;} 			//R/Analog Right					

//Enter programming mode
if (action==func_program_mode){Jump_To_Bootloader();}	//Program mode
					
