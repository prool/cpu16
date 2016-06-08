// Simply fictional processor Prool CPU16 emulator

#include <stdio.h>

#define MAXADR (64*1024)
#define SCREEN (MAXADR-(80*25))

int trace; // trace mode
unsigned short int label;

// registers
short unsigned int IP; // IP - instruction pointer
short unsigned int RD1; // data register #1
short unsigned int RD2; // data register #2
short unsigned int RA1; // address register #1
unsigned char opcode; // operation code

// flags
unsigned char f_stop;
unsigned char f_invalid_opcode;
unsigned char f_zero;

unsigned char ram [MAXADR]; // RAM

void init(void)
{
int i,j;
int counter;

// init ram

for (i=0;i<MAXADR;i++)
	ram[i]=0;

// program code
counter=0;

ram[counter++]=0x02; // screen -> RD1
ram[counter++]=0x30;
ram[counter++]=0xf8;

ram[counter++]=0x03; // RD1 -> RA1

// 25*80 = 2000 = 0x07D0

ram[counter++]=0x02; // counter -> RD1
ram[counter++]=0xD0; // counter -> RD1
ram[counter++]=0x07; // counter -> RD1

ram[counter++]=0x07; // RD1 -> RD2

// loop: IP=8
label=counter;

ram[counter++]=0x01; // ' ' -> RD1
ram[counter++]=0x20;

ram[counter++]=0x04; // RD1 -> (RA1)

ram[counter++]=0x05; //  RA1 -> RD1
ram[counter++]=0x09; //  INC RD1
ram[counter++]=0x03; //  RD1 -> RA1

ram[counter++]=0x06; //  RD2 -> RD1
ram[counter++]=0x0A; //  DEC RD1
ram[counter++]=0x07; //  RD1 -> RD2

ram[counter++]=0x0C; //  JZ exit
ram[counter++]=0x18; //  JZ exit
ram[counter++]=0x00; //  JZ exit

ram[counter++]=0x0B; //  JMP loop
ram[counter++]=0x07; //  
ram[counter++]=0x00; //  

// exit: IP=18

//ram[SCREEN]='<';
//ram[MAXADR-1]='>';

IP=0;
RD1=0;
RA1=0;
f_stop=0;
f_invalid_opcode=0;
f_zero=0;
}

void cls0(void)
{
printf("\033[2J");
}

void cls(void)
{
//printf("\033[2J");
printf("\033[1;1H");
}

void draw_screen(void)
{
int i,j;
unsigned short int adr;
unsigned char c;

cls();
adr=SCREEN;
for (i=0;i<25;i++)
	{
	for (j=0;j<80;j++)
		{
		c = ram[adr++];
		if (c==0) c='.';
		printf("%c", c);
		}
	switch(i)
		{
		case 0: printf(" Prool Computer\n"); break;
		case 1: printf(" IP= %04X\n", IP); break;
		case 2: printf(" RD1=%04X\n", RD1); break;
		case 3: printf(" RD2=%04X\n", RD2); break;
		case 4: printf(" RA1=%04X\n", RA1); break;
		case 5: printf(" opcode=%02X\n", opcode); break;
		case 6: printf(" f_zero=%01X\n", f_zero); break;
		case 7: if (f_invalid_opcode) printf(" INV OP\n"); else printf("\n"); break;
		default: printf("\n");
		}
	}
if (trace) {printf(" TRACE. PRESSANYKEY "); getchar();}
}

void main(int argc, char *argv[])
{
int i,j;
unsigned char c;
unsigned short int adr;

if (argc==2) trace=1; else trace=0;

cls0();

init();

draw_screen();

// CPU loop

while(f_stop==0)
	{
	opcode=ram[IP++];
	switch (opcode)
		{
		case 0x00: // STOP
			f_stop=1;
			break;
		case 0x01: // immediate byte -> RD1
			RD1=(RD1&0xFF00) | ram[IP++];
			break;
		case 0x02: // immediate word -> RD1
			RD1=ram[IP++];
			RD1=RD1 | (ram[IP++]<<8);
			break;
		case 0x03: // word RD1 -> RA1
			RA1=RD1;
			break;
		case 0x04: // byte RD1 -> (RA1)
			ram[RA1]=(char) (0xFF & RD1);
			break;
		case 0x05: // word RA1 -> RD1
			RD1=RA1;
			break;
		case 0x06: // word RD2 -> RD1
			RD1=RD2;
			break;
		case 0x07: // word RD1 -> RD2
			RD2=RD1;
			break;
		case 0x09: // INC RD1
			RD1++;
			break;
		case 0x0A: // DEC RD1
			RD1--;
			if (RD1==0) f_zero=1; else f_zero=0;
			break;
		case 0x0B: // JMP immediate
			c=ram[IP++];
			adr=(ram[IP++]<<8) | c;
			IP=adr;
			break;
		case 0x0C: // JZ immediate
			c=ram[IP++];
			adr=(ram[IP++]<<8) | c;
			if (f_zero) IP=adr;
			break;
		case 0x0D: // JNZ immediate
			c=ram[IP++];
			adr=(ram[IP++]<<8) | c;
			if (f_zero==0) IP=adr;
			break;
		case 0xFF: break; // NOP
		default: // invalid opcode
			f_stop=1;
			f_invalid_opcode=1;
		}
	draw_screen();
	}
printf("STOPPED\n");
}
