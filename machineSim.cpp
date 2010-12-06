#include <cstdio>
#include <iostream>
#define DEBUG 1
#define STK_BASE 65535
using namespace std;
int main()
{
// The load file for our machine will consist of pairs of
// numbers separated by a space. The first number indicates 
// a memory location. The second number indicates an instruction.
// The load file is terminated by a -1 in the location place
// and the place where execution is to begin in the instruction
// place. All input data will follow the load file termination line.
// So in our simulation the load information and the input data
// are in the same file.
  unsigned int mem[STK_BASE+1];//smaller memory that address size 
  int acc=0;
  unsigned int pc;
  unsigned int sp; 
  unsigned int loc, inst;
  unsigned int address;
  scanf("%x %x", &loc,&inst);
  while(loc!=-1){
     printf("Location: %x     Instruction: %x\n",loc,inst);
     mem[loc]=inst;  // loads the instruction into memory
     scanf("%x %x", &loc,&inst);
  }
  pc=inst;
  sp=STK_BASE; //bottom of memory
  printf("Execution will start in location: %x\n",inst);
  // Your machine simulator starts here. 
 while ((mem[pc] & 0xff000000 )!= 0) { //end if halt op code
    // decode instruction
    // switch based on opcode
    switch (mem[pc] & 0xff000000) {
     case 0x01000000 : // add
          address = mem[pc] & 0x00ffffff;
          acc = acc + mem[address]; 
          #if DEBUG 
						printf("Debug-> ADD     stack: %d  acc: %d  address: %x  pc: %x  sp: %x\n",mem[sp],acc,address,pc,sp);
          #endif
          pc++; 
          break;
     case 0x02000000 : // subtract
          address = mem[pc] & 0x00ffffff;
          acc = acc - mem[address]; 
          #if DEBUG 
						printf("Debug-> SUB     stack: %d  acc: %d  address: %x  pc: %x  sp: %x\n",mem[sp],acc,address,pc,sp);
          #endif
          pc++; 
          break;
      case 0x03000000 : // write word
          address = mem[pc] & 0x00ffffff;
          printf("%x\n",mem[address]);
          #if DEBUG
						printf("Debug-> WRITE   stack: %d  acc: %d  address: %x  pc:%x  sp: %x\n",mem[sp],acc,address,pc,sp);
          #endif
          pc++;
          break;
      case 0x04000000 : // read word
          address = mem[pc] & 0x00ffffff;
					scanf("%x", &mem[address]);
          #if DEBUG
						printf("Debug-> READ    stack: %d  acc: %d  address: %x  pc:%x  sp: %x\n",mem[sp],acc,address,pc,sp);
          #endif
          pc++;
          break;
      case 0x05000000 : // load
          address = mem[pc] & 0x00ffffff;
          acc = mem[address];
          #if DEBUG
						printf("Debug-> LOAD    stack: %d  acc: %d  address: %x  pc: %x  sp: %x\n",mem[sp],acc,address,pc,sp);
          #endif
          pc++;
          break;
      case 0x06000000 : // store
          address = mem[pc] & 0x00ffffff;
          mem[address] = acc;
          #if DEBUG
						printf("Debug-> STORE   stack: %d  acc: %d  address: %x  pc:%x  sp: %x\n",mem[sp],acc,address,pc,sp);
          #endif
          pc++;
          break;
			case 0x07000000 : // goto
					address = mem[pc] & 0x00ffffff;
					pc = address;
          #if DEBUG
						printf("Debug-> GOTO    stack: %d  acc: %d  address: %x  pc: %x  sp: %x\n",mem[sp],acc,address,pc,sp);
          #endif
					break;
			case 0x08000000 : // bp
					address = mem[pc] & 0x00ffffff;
					if (acc > 0)
						pc = address;
					else
						pc++;
          #if DEBUG
						printf("Debug-> BP      stack: %d  acc: %d  address: %x  pc: %x  sp: %x\n",mem[sp],acc,address,pc,sp);
          #endif
					break;
			case 0x09000000 : // bn
					address = mem[pc] & 0x00ffffff;
					if (acc < 0)
						pc = address;
					else
						pc++;
          #if DEBUG
						printf("Debug-> BN      stack: %d  acc: %d  address: %x  pc: %x  sp: %x\n",mem[sp],acc,address,pc,sp);
          #endif
					break;
			case 0x0a000000 : // bz
					address = mem[pc] & 0x00ffffff;
					if (acc == 0)
						pc = address;
					else
						pc++;
          #if DEBUG
						printf("Debug-> BZ      stack: %d  acc: %d  address: %x  pc: %x  sp: %x\n",mem[sp],acc,address,pc,sp);
          #endif
					break;
			case 0x0b000000 : // gosub
					sp--;
					mem[sp] = pc+1;
          #if DEBUG
						printf("Debug-> GoSub   stack: %d  acc: %d  address: %x  pc: %x  sp: %x\n",mem[sp],acc,address,pc,sp);
          #endif
					pc++;
					break;
			case 0x0c000000 : // retsub
          #if DEBUG
						printf("Debug-> RetSub  stack: %d  acc: %d  address: %x  pc: %x  sp: %x\n",mem[sp],acc,address,pc,sp);
          #endif
					pc = mem[sp];
					if (sp < STK_BASE) sp++;
					else {
						printf("No address on Stack\n");
						pc++;
					}
					break;
			case 0x0d000000 : // push
					address = mem[pc] & 0x00ffffff;
					sp--;
					mem[sp] = mem[address];
          #if DEBUG
						printf("Debug-> PUSH    stack: %d  acc: %d  address: %x  pc: %x  sp: %x\n",mem[sp],acc,address,pc,sp);
          #endif
					pc++;
					break;
			case 0x0e000000 : // pop
					if (sp < STK_BASE) sp++;
					else {
						pc++;
						printf("Nothing to Pop\n");
					}
          #if DEBUG
						printf("Debug-> POP     stack: %d  acc: %d  address: %x  pc: %x  sp: %x\n",mem[sp],acc,address,pc,sp);
          #endif
					break;
			case 0x0f000000 : // top
					address = mem[pc] & 0x00ffffff;
					mem[address] = mem[sp];
          #if DEBUG
						printf("Debug-> TOP     stack: %d  acc: %d  address: %x  pc: %x  sp: %x\n",mem[sp],acc,address,pc,sp);
          #endif
					pc++;
					break;
			case 0x10000000 : // mult
					address = mem[pc] & 0x00ffffff;
					acc = acc * mem[address];
          #if DEBUG
						printf("Debug-> MULT    stack: %d  acc: %d  address: %x  pc: %x  sp: %x\n",mem[sp],acc,address,pc,sp);
          #endif
					pc++;
					break;
			case 0x11000000 : // div
					address = mem[pc] & 0x00ffffff;
					acc = acc / mem[address];
          #if DEBUG
						printf("Debug-> DIV     stack: %d  acc: %d  address: %x  pc: %x  sp: %x\n",mem[sp],acc,address,pc,sp);
          #endif
					pc++;
					break;
			case 0x12000000 : // rem
					address = mem[pc] & 0x00ffffff;
					acc = acc % mem[address];
          #if DEBUG
						printf("Debug-> REM     stack: %d  acc: %d  address: %x  pc: %x  sp: %x\n",mem[sp],acc,address,pc,sp);
          #endif
					pc++;
					break;
			case 0x13000000 : // increment accumulator
					acc++;
          #if DEBUG
						printf("Debug-> INC     stack: %d  acc: %d  address: %x  pc: %x  sp: %x\n",mem[sp],acc,address,pc,sp);
          #endif
					pc++;
					break;
			case 0x14000000 : // decrement accumulator
					acc--;
          #if DEBUG
						printf("Debug-> DEC     stack: %d  acc: %d  address: %x  pc: %x  sp: %x\n",mem[sp],acc,address,pc,sp);
          #endif
					pc++;
					break;
			case 0x15000000 : // increment address
					address = mem[pc] & 0x00ffffff;
					mem[address]++;
          #if DEBUG
						printf("Debug-> INCM    stack: %d  acc: %d  address: %x  pc: %x  sp: %x\n",mem[sp],acc,address,pc,sp);
          #endif
					pc++;
					break;
			case 0x16000000 : // decrement address
					address = mem[pc] & 0x00ffffff;
					mem[address]--;
          #if DEBUG
						printf("Debug-> DECM    stack: %d  acc: %d  address: %x  pc: %x  sp: %x\n",mem[sp],acc,address,pc,sp);
          #endif
					pc++;
					break;
			case 0x17000000 : // Clear the Stack
					sp = STK_BASE;
          #if DEBUG
						printf("Debug-> CLEAR   stack: %d  acc: %d  address: %x  pc: %x  sp: %x\n",mem[sp],acc,address,pc,sp);
          #endif
					pc++;
					break;
     default:
            printf("Not a valid instruction.\n");
            pc++; 
   }
 }
 return 0;
}
