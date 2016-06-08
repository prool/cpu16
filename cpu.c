// Simply fictional processor Prool CPU16 emulator

#include <stdio.h>

#define MAXADR (64*1024)
#define SCREEN (MAXADR-(80*25))

// registers
short unsigned int IP; // IP - instruction pointer
short unsigned int RD1; // data register #1
short unsigned int RA1; // address register #1
unsigned char opcode; // operation code

// flags
unsigned char f_stop;
unsigned char f_invalid_opcode;

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
// output symbol ' ' to first position of screen
ram[counter++]=0x02; // screen addr -> RD1
ram[counter++]=0x30;
ram[counter++]=0xf8;
ram[counter++]=0x03; // RD1 -> RA1
ram[counter++]=0x01; // ' ' -> RD1
ram[counter++]=0x20;
ram[counter++]=0x04; // RD1 -> (RA1)
ram[counter++]=0x00; // STOP

//ram[SCREEN]='<';
//ram[MAXADR-1]='>';

IP=0;
RD1=0;
RA1=0;
f_stop=0;
f_invalid_opcode=0;

}

void cls(void)
{
printf("\033[2J");
//setpos(1,1);
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
		case 3: printf(" RA1=%04X\n", RA1); break;
		case 4: printf(" opcode=%02X\n", opcode); break;
		case 5: if (f_invalid_opcode) printf(" INV OP\n"); else printf("\n"); break;
		default: printf("\n");
		}
	}
}

void main(void)
{
int i,j;

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
		case 0x03: // RD1 word -> RA1
			RA1=RD1;
			break;
		case 0x04: // byte RD1 -> (RA1)
			ram[RA1]=(char) (0xFF & RD1);
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
