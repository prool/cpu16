// Assembler

#define STOP ram[counter++]=0x00

#define NOP ram[counter++]=0xFF

#define MOVB_IMM_RD1(imm) ram [counter++]=0x01; ram [counter++]=(unsigned char)(imm)
#define MOV_IMM_RD1(imm) ram [counter++]=0x02; ram [counter++]=(unsigned char)(imm); ram [counter++]=(unsigned short int)(imm)>>8

#define MOV_RD1_RA1 ram[counter++]=0x03
#define MOV_RD1_RA2 ram[counter++]=0x08
#define MOVB_RD1_MRA1 ram[counter++]=0x04
#define MOVB_RD1_MRA2 ram[counter++]=0x0E
#define MOVB_MRA1_RD1 ram[counter++]=0x0F
#define MOVB_MRA2_RD1 ram[counter++]=0x10
#define MOV_RA1_RD1 ram[counter++]=0x05
#define MOV_RA2_RD1 ram[counter++]=0x13
#define MOV_RD2_RD1 ram[counter++]=0x06
#define MOV_RD1_RD2 ram[counter++]=0x07

#define INC_RD1 ram[counter++]=0x09
#define DEC_RD1 ram[counter++]=0x0A
#define TST_RD1 ram[counter++]=0x11
#define TSTB_RD1 ram[counter++]=0x12

#define JMP(imm) ram [counter++]=0x0B; ram [counter++]=(unsigned char)(imm); ram [counter++]=(unsigned short int)(imm)>>8
#define JZ(imm) ram [counter++]=0x0C; ram [counter++]=(unsigned char)(imm); ram [counter++]=(unsigned short int)(imm)>>8
#define JNZ(imm) ram [counter++]=0x0D; ram [counter++]=(unsigned char)(imm); ram [counter++]=(unsigned short int)(imm)>>8

#define ASCIIZ(str) cc=str; while(*cc) {ram[counter++]=*cc++;} ram[counter++]=0
