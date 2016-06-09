// program code

// clear screen 

counter=0;
MOV_IMM_RD1(SCREEN);
MOV_RD1_RA1;

MOV_IMM_RD1(25*80);
MOV_RD1_RD2;

// loop: IP=8
label=counter;

MOVB_IMM_RD1(' ');
MOVB_RD1_MRA1;

MOV_RA1_RD1;
INC_RD1;
MOV_RD1_RA1;

MOV_RD2_RD1;
DEC_RD1;
MOV_RD1_RD2;

JZ(0x18);

JMP(label);
// exit label, ip=0x18
STOP;
