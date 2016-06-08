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
