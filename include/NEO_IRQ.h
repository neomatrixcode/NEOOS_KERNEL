
#ifndef NEO_IRQ_H
#define NEO_IRQ_H
#include <NEO_Types.h>

extern "C"{
namespace NEO{
		namespace IRQ{
				extern void UninstallHandler(int irq_code);
				extern void Remap();
				extern void Install();
				extern void IRQ0();
				extern void IRQ1();
				extern void IRQ2();
				extern void IRQ3();
				extern void IRQ4();
				extern void IRQ5();
				extern void IRQ6();
				extern void IRQ7();
				extern void IRQ8();
				extern void IRQ9();
				extern void IRQ10();
				extern void IRQ11();
				extern void IRQ12();
				extern void IRQ13();
				extern void IRQ14();
				extern void IRQ15();
		}
}
}
extern "C"
{
	void NEO_IRQ_Handler(struct regs *r);
	void NEO_IRQ_Common();
	void NEO_IRQ_InstallHandler(int irq_code,void (*handler)(struct regs* r));
}


#endif
