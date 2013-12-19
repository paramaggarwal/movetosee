/*****************
By Param Aggarwal
www.feemo.in

AccPOV
Uses an accelerometer to sense when it is being waved in the air.
Uses Arduino Decimilia and Accelerometer and a custom made shield for the Arduino.
*******************/

// Display goes on PORTD
// GS1 on 10 Sensitivity Selection pins
// GS2 on 11 +- 4g selected here
// SLEEP on 12 and active LOW

int GS1 = 10;
int GS2 = 11;
int SLEEP = 12;

int Y=0; // Temp
int p=0; //Temp

// Tells the microcontroller how to write letters. Little Kid.
// Taken from Sparkfun Library
int text_array[475] = {
0x00,0x00,0x00,0x00,0x00,/*space*/ // is 32 in ASCII
0x00,0xF6,0xF6,0x00,0x00,/*!*/
0x00,0xE0,0x00,0xE0,0x00,/*"*/
0x28,0xFE,0x28,0xFE,0x28,/*#*/
0x00,0x64,0xD6,0x54,0x08,/*$*/
0xC2,0xCC,0x10,0x26,0xC6,/*%*/
0x4C,0xB2,0x92,0x6C,0x0A,/*&*/
0x00,0x00,0xE0,0x00,0x00,/*'*/
0x00,0x38,0x44,0x82,0x00,/*(*/
0x00,0x82,0x44,0x38,0x00,/*)*/
0x88,0x50,0xF8,0x50,0x88,/***/
0x08,0x08,0x3E,0x08,0x08,/*+*/
0x00,0x00,0x05,0x06,0x00,/*,*/
0x08,0x08,0x08,0x08,0x08,/*-*/
0x00,0x00,0x06,0x06,0x00,/*.*/
0x02,0x0C,0x10,0x60,0x80,/*/*/
0x7C,0x8A,0x92,0xA2,0x7C,/*0*/
0x00,0x42,0xFE,0x02,0x00,/*1*/
0x42,0x86,0x8A,0x92,0x62,/*2*/
0x44,0x82,0x92,0x92,0x6C,/*3*/
0x10,0x30,0x50,0xFE,0x10,/*4*/
0xE4,0xA2,0xA2,0xA2,0x9C,/*5*/
0x3C,0x52,0x92,0x92,0x0C,/*6*/
0x80,0x86,0x98,0xE0,0x80,/*7*/
0x6C,0x92,0x92,0x92,0x6C,/*8*/
0x60,0x92,0x92,0x94,0x78,/*9*/
0x00,0x00,0x36,0x36,0x00,/*:*/
0x00,0x00,0x35,0x36,0x00,/*;*/
0x10,0x28,0x44,0x82,0x00,/*<*/
0x28,0x28,0x28,0x28,0x28,/*=*/
0x00,0x82,0x44,0x28,0x10,/*>*/
0x40,0x80,0x8A,0x90,0x60,/*?*/
0x7C,0x82,0xBA,0xBA,0x62,/*@*/
0x3E,0x48,0x88,0x48,0x3E,/*A*/
0xFE,0x92,0x92,0x92,0x6C,/*B*/
0x7C,0x82,0x82,0x82,0x44,/*C*/
0xFE,0x82,0x82,0x82,0x7C,/*D*/
0xFE,0x92,0x92,0x92,0x82,/*E*/
0xFE,0x90,0x90,0x90,0x80,/*F*/
0x7C,0x82,0x82,0x8A,0x4E,/*G*/
0xFE,0x10,0x10,0x10,0xFE,/*H*/
0x82,0x82,0xFE,0x82,0x82,/*I*/
0x84,0x82,0xFC,0x80,0x80,/*J*/
0xFE,0x10,0x28,0x44,0x82,/*K*/
0xFE,0x02,0x02,0x02,0x02,/*L*/
0xFE,0x40,0x20,0x40,0xFE,/*M*/
0xFE,0x60,0x10,0x0C,0xFE,/*N*/
0x7C,0x82,0x82,0x82,0x7C,/*O*/
0xFE,0x90,0x90,0x90,0x60,/*P*/
0x7C,0x82,0x82,0x86,0x7E,/*Q*/
0xFE,0x90,0x98,0x94,0x62,/*R*/
0x64,0x92,0x92,0x92,0x4C,/*S*/
0x80,0x80,0xFE,0x80,0x80,/*T*/
0xFC,0x02,0x02,0x02,0xFC,/*U*/
0xF8,0x04,0x02,0x04,0xF8,/*V*/
0xFC,0x02,0x0C,0x02,0xFC,/*W*/
0xC6,0x28,0x10,0x28,0xC6,/*X*/
0xC0,0x20,0x1E,0x20,0xC0,/*Y*/
0x86,0x8A,0x92,0xA2,0xC2,/*Z*/
0x00,0x00,0xFE,0x82,0x00,/*[*/
0x00,0x00,0x00,0x00,0x00,/*this should be / */
0x80,0x60,0x10,0x0C,0x02,/*]*/
0x20,0x40,0x80,0x40,0x20,/*^*/
0x01,0x01,0x01,0x01,0x01,/*_*/
0x80,0x40,0x20,0x00,0x00,/*`*/
0x04,0x2A,0x2A,0x2A,0x1E,/*a*/
0xFE,0x12,0x22,0x22,0x1C,/*b*/
0x1C,0x22,0x22,0x22,0x14,/*c*/
0x1C,0x22,0x22,0x12,0xFE,/*d*/
0x1C,0x2A,0x2A,0x2A,0x18,/*e*/
0x10,0x7E,0x90,0x80,0x40,/*f*/
0x18,0x25,0x25,0x25,0x1E,/*g*/
0xFE,0x10,0x10,0x10,0x0E,/*h*/
0x00,0x12,0x5E,0x02,0x00,/*i*/
0x02,0x01,0x01,0x11,0x5E,/*j*/
0xFE,0x08,0x08,0x14,0x22,/*k*/
0x00,0x82,0xFE,0x02,0x00,/*l*/
0x3E,0x20,0x1C,0x20,0x1E,/*m*/
0x3E,0x20,0x20,0x20,0x1E,/*n*/
0x1C,0x22,0x22,0x22,0x1C,/*o*/
0x3F,0x24,0x24,0x24,0x18,/*p*/
0x18,0x24,0x24,0x3F,0x01,/*q*/
0x3E,0x10,0x20,0x20,0x10,/*r*/
0x12,0x2A,0x2A,0x2A,0x04,/*s*/
0x00,0x10,0x3C,0x12,0x04,/*t*/
0x3C,0x02,0x02,0x02,0x3E,/*u*/
0x30,0x0C,0x02,0x0C,0x30,/*v*/
0x38,0x06,0x18,0x06,0x38,/*w*/
0x22,0x14,0x08,0x14,0x22,/*x*/
0x38,0x05,0x05,0x05,0x3E,/*y*/
0x22,0x26,0x2A,0x32,0x22,/*z*/
0x00,0x10,0x6C,0x82,0x82,/*{*/
//0x00,0x00,0xFF,0x00,0x00,/*|*/
0x04,0x02,0xFF,0x02,0x04,/*|, arrow*/
0x82,0x82,0x6C,0x10,0x00,/*}*/
0x08,0x10,0x18,0x08,0x10/*~*/
};

// Displays the text
void display(char c)
{
	int i = (c - 32)*5;
	for ( int temp = i; temp < i + 5; temp++ ) {
		PORTD = text_array[temp]; delayMicroseconds(500);
		PORTD = 0x00; delay(3);
	}
	PORTD = 0x00; delay(3);
}

void setup()
{
	pinMode(0,OUTPUT); // Set display as OUTPUT
	pinMode(1,OUTPUT);
	pinMode(2,OUTPUT);
	pinMode(3,OUTPUT);
	pinMode(4,OUTPUT);
	pinMode(5,OUTPUT);
	pinMode(6,OUTPUT);
	pinMode(7,OUTPUT);
	pinMode(8,OUTPUT);
	pinMode(9,OUTPUT);
	pinMode(10,OUTPUT);
	pinMode(11,OUTPUT);
	pinMode(12,OUTPUT);
	pinMode(13,OUTPUT);

	digitalWrite(GS1,HIGH); // Sensitivity Select
	digitalWrite(GS2,LOW);
	digitalWrite(SLEEP,HIGH); // Don't let the Accelerometer sleep !!!
}

void loop()
{
	Y = analogRead(1); // Read the sensor...
	if ( Y > 650)
	{
		p++;
		if(p=2) // Take alternate acceleration...
		{
			p=0;
			delay(60); // Wait a moment before starting

			display('P'); // Paaaaraaammm...
			display('a');
			display('r');
			display('a');
			display('m');
			display(':');
			display('-');
			display(')');
			display(' ');
		}
	}
}
