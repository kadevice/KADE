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
* Bruno Freitas - bruno@brunofreitas.com
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

//set output pin(s)
if (cnt==0)  { bit_clear(PORTC, 0x04); bit_set(DDRC, 0x04);} //PIN A1
if (cnt==1)  { bit_clear(PORTD, 0x01); bit_set(DDRD, 0x01);} //PIN A2
if (cnt==2)  { bit_clear(PORTD, 0x02); bit_set(DDRD, 0x02);} //PIN A3
if (cnt==3)  { bit_clear(PORTD, 0x04); bit_set(DDRD, 0x04);} //PIN A4
if (cnt==4)  { bit_clear(PORTD, 0x08); bit_set(DDRD, 0x08);} //PIN A5
if (cnt==5)  { bit_clear(PORTD, 0x10); bit_set(DDRD, 0x10);} //PIN A6
if (cnt==6)  { bit_clear(PORTD, 0x20); bit_set(DDRD, 0x20);} //PIN A7
if (cnt==7)  { bit_clear(PORTD, 0x40); bit_set(DDRD, 0x40);} //PIN A8
if (cnt==8)  { bit_clear(PORTB, 0x01); bit_set(DDRB, 0x01);} //PIN A9
if (cnt==9)  { bit_clear(PORTB, 0x02); bit_set(DDRB, 0x02);} //PIN A10
if (cnt==10) { bit_clear(PORTB, 0x04); bit_set(DDRB, 0x04);} //PIN B1
if (cnt==11) { bit_clear(PORTB, 0x08); bit_set(DDRB, 0x08);} //PIN B2
if (cnt==12) { bit_clear(PORTB, 0x10); bit_set(DDRB, 0x10);} //PIN B3
if (cnt==13) { bit_clear(PORTB, 0x20); bit_set(DDRB, 0x20);} //PIN B4
if (cnt==14) { bit_clear(PORTB, 0x40); bit_set(DDRB, 0x40);} //PIN B5
if (cnt==15) { bit_clear(PORTD, 0x80); bit_set(DDRD, 0x80);} //PIN B6
if (cnt==16) { bit_clear(PORTC, 0x80); bit_set(DDRC, 0x80);} //PIN B7
if (cnt==17) { bit_clear(PORTC, 0x40); bit_set(DDRC, 0x40);} //PIN B8
if (cnt==18) { bit_clear(PORTC, 0x20); bit_set(DDRC, 0x20);} //PIN B9
if (cnt==19) { bit_clear(PORTC, 0x10); bit_set(DDRC, 0x10);} //PIN B10
