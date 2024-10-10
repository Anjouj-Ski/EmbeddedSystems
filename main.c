#include "main.h"
#include "keypad.h"

void delay(int n)
{
	for(int i=0; i<n; i++){
		for(int j=0; j<64000;j++)
			asm("nop");
	}
}

int main(void) {
	keypad();

}
