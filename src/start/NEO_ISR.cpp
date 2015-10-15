
#include <NEO_ISR.h>
#include <NEO_Screen.h>
#include <NEO_Error.h>

const char* exception_messages[]=
{
	"Excepcion de Division Entre Cero",
	"Excepcion de Depuración",
	"Excepcion de Interrupción No Enmascarable",
	"Excepcion de Punto de Quiebre",
	"INTO Detectó Excepcion de Desborde",
	"Excepcion de Sobrepaso de Límites",
	"Excepcion de Opcode Inválido",
	"Excepcion de Coprocesador No Instalado",
	"Excepcion de Falta Doble",
	"Coprocesador excepcion reemplazo de segmento",
	"Excepcion de TSS Malo",
	"Excepcion de Segmento No Presente",
	"Excepcion de Falta de Pila",
	"Excepcion de Falta General de Protección",
	"Excepcion de Falta de Pagina",
	"Excepcion de Interrupción Desconocida",
	"Excepcion de Falta de Coprocesador",
	"Excepcion de Verificacion de Alineación (486+)",
	"Excepcion de Verificacion de Máquina (Pentium/586+)",
	"Excepcion reservada por INTEL",
	"Excepcion reservada por INTEL",
	"Excepcion reservada por INTEL",
	"Excepcion reservada por INTEL",
	"Excepcion reservada por INTEL",
	"Excepcion reservada por INTEL",
	"Excepcion reservada por INTEL",
	"Excepcion reservada por INTEL",
	"Excepcion reservada por INTEL",
	"Excepcion reservada por INTEL",
	"Excepcion reservada por INTEL",
	"Excepcion reservada por INTEL",
	"Excepcion reservada por INTEL"
};

extern "C"
void NEO_ISR_Handler(struct regs *r)
{
	if(r->int_no < 32)
	{
		//NEO::Error::Mostrar(exception_messages[r->int_no]);
		NEO::Screen::ColocarColor(NEO_SIDE_FOREGROUND,NEO_COLOR_VERDE);
		NEO::Screen::ColocarString("\n HA OCURRIDO UN ERROR \n");
		NEO::Screen::ColocarString(exception_messages[r->int_no]);

	}
	
	
	for(;;);
}

extern "C"{
void NEO_ISR_Common()
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
	"movl $NEO_ISR_Handler, %eax \n"
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

void NEO::ISR::ISR0()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli \n"
	"pushl $0x00 \n"  //codigo de error devuelto 
	"pushl $0x00\n"  //identifica la descripcion
	"jmp NEO_ISR_Common \n"
	);
}
void NEO::ISR::ISR1()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli \n"
	"pushl $0x00 \n"
	"pushl $0x01 \n"
	"jmp NEO_ISR_Common \n"
	);
}
void NEO::ISR::ISR2()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli \n"
	"pushl $0x00 \n"
	"pushl $0x02 \n"
	"jmp NEO_ISR_Common \n"
	);
}
void NEO::ISR::ISR3()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli \n"
	"pushl $0x00 \n"
	"pushl $0x03 \n"
	"jmp NEO_ISR_Common \n"
	);
}
void NEO::ISR::ISR4()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli \n"
	"pushl $0x00 \n"
	"pushl $0x04 \n"
	"jmp NEO_ISR_Common \n"
	);
}
void NEO::ISR::ISR5()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli \n"
	"pushl $0x00 \n"
	"pushl $0x05 \n"
	"jmp NEO_ISR_Common \n"
	);
}
void NEO::ISR::ISR6()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli \n"
	"pushl $0x00 \n"
	"pushl $0x06 \n"
	"jmp NEO_ISR_Common \n"
	);
}
void NEO::ISR::ISR7()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli \n"
	"pushl $0x00 \n"
	"pushl $0x07 \n"
	"jmp NEO_ISR_Common \n"
	);
}
void NEO::ISR::ISR8()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli \n"
					 //esta exepcion si retorna un codigo de error 
	"pushl $0x08 \n" //identifica la descripcion 
	"jmp NEO_ISR_Common \n"
	);
}
void NEO::ISR::ISR9()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli \n"
	"pushl $0x00 \n"
	"pushl $0x09 \n"
	"jmp NEO_ISR_Common \n"
	);
}
void NEO::ISR::ISR10()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli \n"
	"pushl $0x0A \n"
	"jmp NEO_ISR_Common \n"
	);
}
void NEO::ISR::ISR11()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli \n"
	"pushl $0x0B \n"
	"jmp NEO_ISR_Common \n"
	);
}
void NEO::ISR::ISR12()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli \n"
	"pushl $0x0C \n"
	"jmp NEO_ISR_Common \n"
	);
}
void NEO::ISR::ISR13()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli \n"
	"pushl $0x0D \n"
	"jmp NEO_ISR_Common \n"
	);
}
void NEO::ISR::ISR14()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli \n"
	"pushl $0x0E \n"
	"jmp NEO_ISR_Common \n"
	);
}
void NEO::ISR::ISR15()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli \n"
	"pushl $0x00 \n"
	"pushl $0x0F \n"
	"jmp NEO_ISR_Common \n"
	);
}
void NEO::ISR::ISR16()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli \n"
	"pushl $0x00 \n"
	"pushl $0x10 \n"
	"jmp NEO_ISR_Common \n"
	);
}
void NEO::ISR::ISR17()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli \n"
	"pushl $0x00 \n"
	"pushl $0x11 \n"
	"jmp NEO_ISR_Common \n"
	);
}
void NEO::ISR::ISR18()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli \n"
	"pushl $0x00 \n"
	"pushl $0x12 \n"
	"jmp NEO_ISR_Common \n"
	);
}
void NEO::ISR::ISR19()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli \n"
	"pushl $0x00 \n"
	"pushl $0x13 \n"
	"jmp NEO_ISR_Common \n"
	);
}
void NEO::ISR::ISR20()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli \n"
	"pushl $0x00 \n"
	"pushl $0x14 \n"
	"jmp NEO_ISR_Common \n"
	);
}
void NEO::ISR::ISR21()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli \n"
	"pushl $0x00 \n"
	"pushl $0x15 \n"
	"jmp NEO_ISR_Common \n"
	);
}
void NEO::ISR::ISR22()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli \n"
	"pushl $0x00 \n"
	"pushl $0x16 \n"
	"jmp NEO_ISR_Common \n"
	);
}
void NEO::ISR::ISR23()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli \n"
	"pushl $0x00 \n"
	"pushl $0x17 \n"
	"jmp NEO_ISR_Common \n"
	);
}
void NEO::ISR::ISR24()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli \n"
	"pushl $0x00 \n"
	"pushl $0x18 \n"
	"jmp NEO_ISR_Common \n"
	);
}
void NEO::ISR::ISR25()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli \n"
	"pushl $0x00 \n"
	"pushl $0x19 \n"
	"jmp NEO_ISR_Common \n"
	);
}
void NEO::ISR::ISR26()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli \n"
	"pushl $0x00 \n"
	"pushl $0x1A \n"
	"jmp NEO_ISR_Common \n"
	);
}
void NEO::ISR::ISR27()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli \n"
	"pushl $0x00 \n"
	"pushl $0x1B \n"
	"jmp NEO_ISR_Common \n"
	);
}
void NEO::ISR::ISR28()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli \n"
	"pushl $0x00 \n"
	"pushl $0x1C \n"
	"jmp NEO_ISR_Common \n"
	);
}
void NEO::ISR::ISR29()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli \n"
	"pushl $0x00 \n"
	"pushl $0x1D \n"
	"jmp NEO_ISR_Common \n"
	);
}
void NEO::ISR::ISR30()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli \n"
	"pushl $0x00 \n"
	"pushl $0x1E \n"
	"jmp NEO_ISR_Common \n"
	);
}
void NEO::ISR::ISR31()
{
	asm volatile(
	"popl %ebp	   \n"	
	"cli \n"
	"pushl $0x00 \n"
	"pushl $0x1F \n"
	"jmp NEO_ISR_Common \n"
	);
}
}
