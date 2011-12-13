#include <16F874.h>
#include "DigitalClock.h"
#use delay (clock=1000000)
#fuses XT,NOWDT,NOPUT

//Bloco das estruturas, variáveis e constantes

enum StateClock
{
	Normal, 
	ModeTimeMinUnit, ModeTimeMinDec, 
	ModeTimeHourUnit, ModeTimeHourDec, 
	
	ModeAlarmMinUnit, ModeAlarmMinDec, 
	ModeAlarmHourUnit, ModeAlarmHourDec,
	

	//modos do alarme: ativo ou nao
	ModeAlarmActived
};

struct Clock 
{
	//variáveis do relógio digital em suas unidades e dezenas de acordo com minutos e horas
	int timeMinUnit;
	int timeMinDec;
	int timeHoursUnit;
	int timeHoursDec;


	//variáveis do alarme do relógio digital em suas unidades e dezenas de acordo com minutos e horas
	int alarmMinUnit;
	int alarmMinDec;
	int alarmHourUnit;
	int alarmHourDec;
	
	
	//valor do estado de máquina do relógio- seleciona os modos do relógio
	StateClock state;
	

	//Se o alarme esta ativo o nao
	bool alarmActived;
};

//
//struct ClockAlarm
//{
//	//variáveis do alarme do relógio digital em suas unidades e dezenas de acordo com minutos e horas
//	int alarmMinUnit;
//	int alarmMinDec;
//	int alarmHourUnit;
//	int alarmHourDec;
//	//valor do estado de máquina do relógio- seleciona os modos do relógio
//
//	//Se o alarme esta ativo
//	bool alarmActived;
//}
//struct Alarm
//{
//	ClockAlarm alarm;
//}

Clock clock;

int vtimer = 0, seconds = 0;

// piscara os leds caso true
bool fireAlarmeState;
//FIM DO BLOCK

int getClockMin()
{
	return DEZENA[clock.countMinDec] | UNIDADE[clock.countMinUnit];
}

int getClockHour()
{
	return DEZENA[clock.countHourDec] | UNIDADE[clock.countHourUnit];
}

int getAlarmMin()
{
	return DEZENA[clock.countMinDec] | UNIDADE[clock.countMinUnit];
}

int getAlarmHour()
{
	return DEZENA[clock.countHourDec] | UNIDADE[clock.countHourUnit];
}

void initState()
{
	clock.timeMinUnit = 0;
	clock.timeMinDec = 0;
	clock.timeHourUnit = 0;	
	clock.timeHourDec = 0;


	clock.alarmMinUnit = 0;
	clock.alarmMinDec = 0;
	clock.alarmHourUnit = 0;
	clock.alarmHourDec = 0;
	clock.alarmActived = false;

	clock.state = Normal;
	fireAlarmState = false;


	//definicoes do PIC
    setup_timer_0(RTCC_INTERNAL | RTCC_DIV_16); 
    set_timer0(131); 
    enable_interrupts(global | int_timer0);
}

void minuteElapsed()
{
	if (clock.timeMinUnit < 9)
	{
		clock.timeMinUnit++;
		return;
	}
	else if (clock.timeMinDec < 5)
	{
		clock.timeMinDec++;
		clock.timeMinUnit = 0;
	}
	else if (clock.timeHourUnit < 9)
	{
		clock.timeMinUnit = 0;
		clock.timeMinDec = 0;
		clock.timeHourUnit++;	
	}
	else if (clock.timeHourDec < 5)
	{
		clock.timeMinUnit = 0;
		clock.timeMinDec = 0;
		clock.timeHourUnit = 0;	
		clock.timeHourDec++;
	}
	else 
	{
		clock.timeMinUnit = 0;
		clock.timeMinDec = 0;
		clock.timeHourUnit = 0;	
		clock.timeHourDec = 0;
	}

	// checa se o alarme está ativo
	if (alarmActived)
	{
		checkAlarm();
	}
}

void checkAlarm()
{
	// checa se esta na hora do alarm.
	if (getAlarmHour() == getClockHour())
		return;
	
	if (getAlarmMin() == getClockMin())
		return;
}

void fireAlarm()
{
	while(fireAlarmState)
	{
		// alarma \o/
		// Acende os leds;
		// apaga os leds
	}
	
}

void changeMode()
{
	switch(clock.state)
	{
		case Normal:
			clock.state = ModeTimeMinUnit;
			break;
		case ModeTimeMinUnit:
			clock.state = ModeTimeMinDec;
			break;
		case ModeTimeMinDec:
			clock.state = ModeTimeHourUnit;
			break;
		case ModeTimeHourUnit:
			clock.state = ModeTimeHourDec;
			break;
		case ModeTimeHourDec:
			clock.state = ModeAlarmMinUnit;
			break;
		case ModeAlarmMinUnit:
			clock.state = ModeTimeMinDec;
			break;
		case ModeAlarmMinDec:
			clock.state = ModeTimeHourUnit;
			break;
		case ModeAlarmHourUnit:
			clock.state = ModeTimeHourDec;
			break;
		case ModeAlarmHourDec:
			clock.state = ModeAlarmActived;
			break;
		case ModeAlarmActived:
			clock.state = Normal;
			break;
	}
	blinkDisplay(clock.state);
}

void blinkLeds(int[] pins)
{
	// piscar o led do mod
}

void blinkDisplay(ClockState state)
{
	// todo: funcao que pisca o display que queremos mudar
}

void incClock()
{
	switch (clock.state)
	{
		case ModeTimeMinUnit:
			clock.timeMinUnit++;
			break;
		case ModeTimeMinDec:
			clock.timeMinDec++;
			break;
		case ModeTimeHourMin:
			clock.time
	}
}

#int_timer0
void trata_timer0() 
{ 
    set_timer0(131 + get_timer0());
    vtimer++; 
    if (vtimer == 125)
	{
       vtimer = 0; 
       seconds++;
	   if (seconds > 59)
	   {
			fireAlarmState = false;
			seconds = 0;
			minuteElapsed();
	   }
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

void main()
{
	initState();	
}
