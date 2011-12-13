#define MODE PIN_B4
#define INC PIN_B5
#define DEC PIN_B6

//#define MODE PIN_B4
//#define INC PIN_B5
//#define DEC PIN_B6


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

/*
  Inicia os valores do clock e inicia o timer para contar os minutos;
*/

void initState();

void minuteElapsed();
void checkAlarm();
int getHourMin();
int getHourTime();
int getAlarmMin();
int getAlarmHour();
void changeMode();
void blinkDisplay(ClockState state);
void incClock();


