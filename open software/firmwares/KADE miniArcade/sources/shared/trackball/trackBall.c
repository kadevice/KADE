//Thanks to: andrew.nagi@gmail.com .  His USB scroll wheel project was a 
//great reference. initTrackball and readTrackball are adapted from his 
//example at: https://github.com/nagi

#include "common.h"
uint8_t horizSignBit;
uint8_t vertSignBit;
int8_t posVert = 0; 
int8_t posHoriz = 0;

//void initTrackBall(void){
void initTrackBall(int resolution, int rate){
	//init
	send_packet(0xff);
	read_packet(); //Ack
	read_packet(); //Bat
	read_packet(); //Device ID
	
	//Data reporting
	send_packet(0xf4); //Enable data reporting
	read_packet();	   //Ack
	
	//Resolution
	send_packet(0xe8); //Set resolution
	read_packet();     //Ack
	if (resolution==0)     {send_packet(0x00);}  //1 count  per mm
	else if (resolution==1){send_packet(0x01);}  //2 counts per mm
	else if (resolution==2){send_packet(0x02);}  //4 counts per mm
	else if (resolution==3){send_packet(0x03);}  //8 counts per mm
	else {send_packet(0x03);}
	read_packet();     //Ack
	
	//Sample rate
	send_packet(0xf3); //Set sample rate
	read_packet();     //Ack
	if (rate==0)     {send_packet(0x0a);} //10 samples per second
	else if (rate==1){send_packet(0x14);} //20 samples per second
	else if (rate==2){send_packet(0x28);} //40 samples per second
	else if (rate==3){send_packet(0x3c);} //60 samples per second
	else if (rate==4){send_packet(0x50);} //80 samples per second
	else if (rate==5){send_packet(0x64);} //100 samples per second
	else if (rate==6){send_packet(0xc8);} //200 samples per second
	else {send_packet(0xc8);}
	//read_packet();     //Ack

		
	//Mode
	send_packet(0xf0); //Set remote mode
	read_packet(); //Ack
}

void readTrackBall(){	
	send_packet(0xeb);
	read_packet(); //Ack
	for(ps2_i=0;ps2_i<3;ps2_i++){
		ps2data[ps2_i]=read_packet();
	}	
}

void calcMovement(){
	vertSignBit  = (ps2data[0] & 0b00100000) << 2;
	posVert  = ps2data[2];
	ps2_y = posVert;

	horizSignBit = (ps2data[0] & 0b00010000) << 3;
	posHoriz = ps2data[1];
	ps2_x = posHoriz;		
}
