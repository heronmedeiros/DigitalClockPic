#include <16F874.h>
#use delay (clock=1000000)
#fuses XT,NOWDT,NOPUT

//Bloco das estruturas, variáveis e constantes

#define MODE PIN_B4
#define INC PIN_B5
#define CHANGE PIN_B6

const byte DEZENA[10]
{
	0b00000000,
    0b00010000,
    0b00100000,
    0b00110000,
    0b01000000,
    0b01010000,
    0b01100000,
    0b01110000,
    0b10000000,
    0b10010000,
}

const byte UNIDADE[10]
{
	0b00000000,
    0b00000001,
    0b00000010,
    0b00000011,
    0b00000100,
    0b00000101,
    0b00000110,
    0b00000111,
    0b00001000,
    0b00001001,
}

/*
  Exemplo: 12 == DEZENA[1] | UNIDADE[2];
*/

enum StateClock
{
	Normal, ModeTime, ModeAlarm 
};

struct Clock 
{
    int countMinUnit;
    int countMinDec;
	int countHoursUnit;
    int countHoursDec;
	int countAlarmMinUnit;
    int countAlarmMinDec;
	int countAlarmHoursUnit;
    int countAlarmHoursDec;
	StateClock state;
};

Clock clock;
//FIM DO BLOCK

void initState()
{
	clock.countMinUnit = 0;
	clock.countMinDec = 0;
	clock.countHourUnit = 0;	
	clock.countHourDec = 0;
	clock.timeToAlarm = 0;
	clock.state = Normal;   
}

void minuteElapsed()
{
	if (clock.state == ModeTime)
		return;
	if (clock.countMinUnit < 9)
	{
		clock.countMinUnit++;
		return;
	}
	else if (clock.countMinDec < 5)
	{
		clock.countMinDec++;
		clock.countMinUnit = 0;
	}
	else if (clock.countHourUnit < 9)
	{
		clock.countMinUnit = 0;
		clock.countMinDec = 0;
		clock.countHourUnit++;	
	}
	else if (clock.countHourDec < 5)
	{
		clock.countMinUnit = 0;
		clock.countMinDec = 0;
		clock.countHourUnit = 0;	
		clock.countHourDec++;
	}
	else 
	{
		clock.countMinUnit = 0;
		clock.countMinDec = 0;
		clock.countHourUnit = 0;	
		clock.countHourDec = 0;
	}
}

int retornaMinuto()
{
	return DEZENA[clock.countMinDec] | UNIDADE[clock.countMinUnit];
}

int retornaHora()
{
	return DEZENA[clock.countHourDec] | UNIDADE[clock.countHourUnit];
}

void changeMode()
{
	switch(clock.state)
	{
		case Normal:
			clock.state = ModeTime;
			break;
		case ModeTime:
			clock.state = ModeAlarm;
			break;
		case ModeAlarm:
			clock.state = Normal;
			break;
	}
}

void incClock()
{
	switch (clock.state)
	{
		case ModeTime:
			
	}
}

#int_rb
void trata_rb()
{
	int x;
	if (input(MODE) == 0)
	{
		changeMode(); 	
	}
	if (input(INC) == 0)
	{
		incClock(); 	
	}
	if (input(DEC) == 0)
	{
		decClock();	
	}
    x = input_b();
}

main()
{

}
