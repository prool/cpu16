// out string to screen

MOV_IMM_RD1(0x1000); // addr of string
MOV_RD1_RA1;

MOV_IMM_RD1(SCREEN);
MOV_RD1_RA2;

// label
label=counter;

MOVB_MRA1_RD1;
TSTB_RD1;
JZ (0x2000); // JZ exit
MOVB_RD1_MRA2;

MOV_RA1_RD1; // RA1++
INC_RD1;
MOV_RD1_RA1;

MOV_RA2_RD1; // RA2++
INC_RD1;
MOV_RD1_RA2;

JMP(label);

STOP;

counter=0x1000;
ASCIIZ("Prool PC1 on Prool CPU-16 processor: github.com/prool/cpu16 ");

counter=0x2000;
// label 'exit' here
STOP;
