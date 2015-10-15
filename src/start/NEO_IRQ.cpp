
#include <NEO_IRQ.h>
#include <NEO_Ports.h>
#include <NEO_IDT.h>
#include <NEO_ISR.h>
#include <NEO_Screen.h>

/* Este arreglo es de hecho un arreglo de punteros de funciones. Usamos
*  esto para manipular manejadores de IRQs personalizados para un IRQ dado */
void *irq[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

extern "C"
// Esto instala un manejador de IRQs personalizado para la IRQ dada 

void NEO_IRQ_InstallHandler(int irq_code,void (*handler)(struct regs* r))
{
	irq[irq_code]=(void *)handler;
}
/* Esto limpia el manejador para una IRQ dada */
void NEO::IRQ::UninstallHandler(int irq_code)
{
	irq[irq_code]=0;
}
void NEO::IRQ::Install()
{
	NEO::Screen::ColocarColor(NEO_SIDE_FOREGROUND,NEO_COLOR_NEGRO);
	NEO::Screen::ColocarString("\nInstalling IRQ...");

	NEO::IRQ::Remap();

	NEO::IDT::SetGate(32,(uint32_t)NEO::IRQ::IRQ0,0x08,0x8E);
	NEO::IDT::SetGate(33,(uint32_t)NEO::IRQ::IRQ1,0x08,0x8E);
	NEO::IDT::SetGate(34,(uint32_t)NEO::IRQ::IRQ2,0x08,0x8E);
	NEO::IDT::SetGate(35,(uint32_t)NEO::IRQ::IRQ3,0x08,0x8E);
	NEO::IDT::SetGate(36,(uint32_t)NEO::IRQ::IRQ4,0x08,0x8E);
	NEO::IDT::SetGate(37,(uint32_t)NEO::IRQ::IRQ5,0x08,0x8E);
	NEO::IDT::SetGate(38,(uint32_t)NEO::IRQ::IRQ6,0x08,0x8E);
	NEO::IDT::SetGate(39,(uint32_t)NEO::IRQ::IRQ7,0x08,0x8E);
	NEO::IDT::SetGate(40,(uint32_t)NEO::IRQ::IRQ8,0x08,0x8E);
	NEO::IDT::SetGate(41,(uint32_t)NEO::IRQ::IRQ9,0x08,0x8E);
	NEO::IDT::SetGate(42,(uint32_t)NEO::IRQ::IRQ10,0x08,0x8E);
	NEO::IDT::SetGate(43,(uint32_t)NEO::IRQ::IRQ11,0x08,0x8E);
	NEO::IDT::SetGate(44,(uint32_t)NEO::IRQ::IRQ12,0x08,0x8E);
	NEO::IDT::SetGate(45,(uint32_t)NEO::IRQ::IRQ13,0x08,0x8E);
	NEO::IDT::SetGate(46,(uint32_t)NEO::IRQ::IRQ14,0x08,0x8E);
	NEO::IDT::SetGate(47,(uint32_t)NEO::IRQ::IRQ15,0x08,0x8E);

	NEO::Screen::ColocarColor(NEO_SIDE_FOREGROUND,NEO_COLOR_VERDE);
	NEO::Screen::ColocarString("done");

//	ND::IDT::Flush();

//	asm volatile("sti");
}

/* Normalmente, las IRQs 0 a 7 están mapeadas a las entradas 8 a 15. Esto
*  es un problema en Modo Protegido, ¡porque la entrada de la IDT 8 es la
*  Falta Doble! Sin remapear, cada vez que el IRQ 0 se gatille, obtienes una
*  Excepción de Falta Doble, que NO ES lo que realmente pasó. Enviamos comandos
*  al Controlador Programable de Interrupciones (PICs - también llamados los 8259)
*  a fin de remapear las IRQs 0 a 15 a las entradas de la IDT 32 a 47 */

void NEO::IRQ::Remap()
{

#define PIC1 0x20
#define PIC2 0xA0

	NEO::Ports::OutputB(PIC1, 0x11); /* accedmos al indice 0x11 del puerto 0x20 */
	NEO::Ports::OutputB(PIC2, 0x11); /* accedmos al indice 0x11 del puerto 0xA0 */

	NEO::Ports::OutputB(PIC1 + 1, 0x20); /* le decimos al pic1 que inicie en 32 o 0x21 */
	NEO::Ports::OutputB(PIC2 + 1, 0x28); /* le decimos al pic1 que inicie en 40 o 0x28 */

	NEO::Ports::OutputB(PIC1 + 1, 0x04); /* conectamos pic1 con pic2 */
	NEO::Ports::OutputB(PIC2 + 1, 0x02); /* conectamos pic2 con pic1 */

	NEO::Ports::OutputB(PIC1 + 1, 0x01); /* escribimos comandos en PICM */
	NEO::Ports::OutputB(PIC2 + 1, 0x01); /* escribimos comandos en PICS */

	NEO::Ports::OutputB(PIC1 + 1, 0x01); /* habilitamos los IRQs en PICM */
	NEO::Ports::OutputB(PIC2 + 1, 0x01); /* habilitamos los IRQs en PICS */

	/* disable all IRQs */
//	NEO::Ports::OutputB(PIC1 + 1, 0xFF); /* deshabilitamos todos los IRQs en PICM */
//	NEO::Ports::OutputB(PIC2 + 1, 0xFF); /* deshabilitamos todos los IRQs en PICS */
	NEO::Ports::OutputB(PIC1 + 1, 0x00); /*terminamos la introduccion de comandos*/
	NEO::Ports::OutputB(PIC2 + 1, 0x00); /*terminamos la introduccion de comandos*/
}

extern "C"
/* Cada uno de los ISRs de las IRQs apunta a esta función,
*  en lugar de 'fault_handler' . Los Controladores
*  de IRQ necesitan saber cuando estás dándoles servicio, así
*  que necesitas enviar un comando de "Fin de Interrupción"
*  (End of Interrupt o EOI), que tiene el valor 0x20. Hay dos
*  chips 8259: El primero existe en 0x20, el segundo existe en 0xA0.
*  Si el segundo controlador (una IRQ de 8 a 15) recibe una interrupción,
*  necesitas reconocer la interrupción en AMBOS controladores; de lo
*  contrario, solamente envías un comando EOI al primer controlador. Si
*  no envías un EOI, no lanzaras más IRQs */

void NEO_IRQ_Handler(struct regs *r)
{
	/* Este es un puntero de función en blanco */
	void (*handler)(struct regs *r);

	/* Descubrir si tenemos un manejador personalizado para correr
    *  esta IRQ, y luego, finalmente, correrla */
	handler = (void (*)(struct regs *r))irq[r->int_no - 0x20];
	if(handler != 0)
	{
		handler(r);
	}

	/* Si la entrada de la IDT que fue invocada era mayor que 40,
    *  (lo que significa IRQs 8 a 15), entonces necesitamos enviar un EOI
    *  al controlador esclavo */
	if(r->int_no >= 0x28)
	{
		NEO::Ports::OutputB(0xA0,0x20);
	}
	/* En cualquier caso, necesitamos enviar un EOI al controlador
    *  Maestro de interrupciones también */
	NEO::Ports::OutputB(0x20,0x20);
}

extern "C"{
void NEO_IRQ_Common()
{
	asm volatile(
	"popl %ebp	   \n"	
	"pushal	   \n"
	"pushl	%ds\n"//ds
	"pushl	%es\n"//es
	"pushl	%fs\n"//fs
	"pushl	%gs\n"//gs
	"movw $0x10, %ax \n"
	"movw %ax, %ds \n"
	"movw %ax, %es \n"
	"movw %ax, %fs \n"
	"movw %ax, %gs \n"
	"pushl %esp \n"
	"movl $NEO_IRQ_Handler, %eax \n"
	"call *%eax \n"
	"popl %esp \n"
	"popl %gs \n"
	"popl %fs \n"
	"popl %es \n"
	"popl %ds \n"
	"popal    \n"
	"add $0x8, %esp \n"
	"sti	\n"
	"iret \n"
	"sti \n"   //REACTIVAMOS LAS INTERUCCIONES
	);
}

void NEO::IRQ::IRQ0()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli	\n"
	"pushl	$0x00\n" // NINGUN IRQ guardan un código de error en la pila
	"pushl	$0x20\n" // INICIAMOS EN 32
	"jmp NEO_IRQ_Common"
	);
}

void NEO::IRQ::IRQ1()
{
	asm volatile(
	"popl %ebp	\n"	
	"cli	\n"
	"pushl	$0x00\n"
	"pushl	$0x21\n"
	"jmp NEO_IRQ_Common"
	);
}
void NEO::IRQ::IRQ2()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli	\n"
	"pushl	$0x00\n"
	"pushl	$0x22\n"
	"jmp NEO_IRQ_Common"
	);
}
void NEO::IRQ::IRQ3()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli	\n"
	"pushl	$0x00\n"
	"pushl	$0x23\n"
	"jmp NEO_IRQ_Common"
	);
}
void NEO::IRQ::IRQ4()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli	\n"
	"pushl	$0x00\n"
	"pushl	$0x24\n"
	"jmp NEO_IRQ_Common"
	);
}
void NEO::IRQ::IRQ5()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli	\n"
	"pushl	$0x00\n"
	"pushl	$0x25\n"
	"jmp NEO_IRQ_Common"
	);
}
void NEO::IRQ::IRQ6()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli	\n"
	"pushl	$0x00\n"
	"pushl	$0x26\n"
	"jmp NEO_IRQ_Common"
	);
}
void NEO::IRQ::IRQ7()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli	\n"
	"pushl	$0x00\n"
	"pushl	$0x27\n"
	"jmp NEO_IRQ_Common"
	);
}
void NEO::IRQ::IRQ8()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli	\n"
	"pushl	$0x00\n"
	"pushl	$0x28\n"
	"jmp NEO_IRQ_Common"
	);
}
void NEO::IRQ::IRQ9()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli	\n"
	"pushl	$0x00\n"
	"pushl	$0x29\n"
	"jmp NEO_IRQ_Common"
	);
}
void NEO::IRQ::IRQ10()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli	\n"
	"pushl	$0x00\n"
	"pushl	$0x2A\n"
	"jmp NEO_IRQ_Common"
	);
}
void NEO::IRQ::IRQ11()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli	\n"
	"pushl	$0x00\n"
	"pushl	$0x2B\n"
	"jmp NEO_IRQ_Common"
	);
}
void NEO::IRQ::IRQ12()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli	\n"
	"pushl	$0x00\n"
	"pushl	$0x2C\n"
	"jmp NEO_IRQ_Common"
	);
}
void NEO::IRQ::IRQ13()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli	\n"
	"pushl	$0x00\n"
	"pushl	$0x2D\n"
	"jmp NEO_IRQ_Common"
	);
}
void NEO::IRQ::IRQ14()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli	\n"
	"pushl	$0x00\n"
	"pushl	$0x2E\n"
	"jmp NEO_IRQ_Common"
	);
}
void NEO::IRQ::IRQ15()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli	\n"
	"pushl	$0x00\n"
	"pushl	$0x2F\n"
	"jmp NEO_IRQ_Common"
	);
}
}
