
#include <NEO_IDT.h>
#include <NEO_Screen.h>
#include <NEO_Color.h>
#include <NEO_Mem.h>
#include <NEO_ISR.h>
#include <NEO_IRQ.h>

struct NEO::IDT::Entry idt[256];  //se declara una IDT de 256 entradas
struct NEO::IDT::Ptr idtptr;

void NEO::IDT::Flush()
{
	asm volatile("lidtl (idtptr)"); //Carga la IDT definida en 'idtptr', en el procesador.
}
void NEO::IDT::SetGate(uint8_t num,uint32_t base,uint16_t sel, uint8_t flags)
{
	idt[num].base_low=(base & 0xFFFF);
	idt[num].base_high=(base >> 16) & 0xFFFF;

	idt[num].sel=sel;
	idt[num].always0 = 0;
	idt[num].flags=flags;
}
void NEO::IDT::Install()
{
	NEO::Screen::ColocarColor(NEO_SIDE_FOREGROUND,NEO_COLOR_NEGRO);
	NEO::Screen::ColocarString("\nInstalling IDT...");

	idtptr.limit=(sizeof(struct NEO::IDT::Entry)*256)-1;
	idtptr.base=(uint32_t)&idt;

	 /* Limpia la IDT completa, inicializándola a ceros */
	NEO::Mem::Set(&idt,0,sizeof(struct NEO::IDT::Entry)*256);

	// Agrega cualquier ISR nueva a la IDT 	

	NEO::IDT::SetGate(0,(uint32_t)NEO::ISR::ISR0,0x08,0x8E);  //0x8E=10001110
	NEO::IDT::SetGate(1,(uint32_t)NEO::ISR::ISR1,0x08,0x8E);
	NEO::IDT::SetGate(2,(uint32_t)NEO::ISR::ISR2,0x08,0x8E);
	NEO::IDT::SetGate(3,(uint32_t)NEO::ISR::ISR3,0x08,0x8E);
	NEO::IDT::SetGate(4,(uint32_t)NEO::ISR::ISR4,0x08,0x8E);
	NEO::IDT::SetGate(5,(uint32_t)NEO::ISR::ISR5,0x08,0x8E);
	NEO::IDT::SetGate(6,(uint32_t)NEO::ISR::ISR6,0x08,0x8E);
	NEO::IDT::SetGate(7,(uint32_t)NEO::ISR::ISR7,0x08,0x8E);
	NEO::IDT::SetGate(8,(uint32_t)NEO::ISR::ISR8,0x08,0x8E);
	NEO::IDT::SetGate(9,(uint32_t)NEO::ISR::ISR9,0x08,0x8E);
	NEO::IDT::SetGate(10,(uint32_t)NEO::ISR::ISR10,0x08,0x8E);
	NEO::IDT::SetGate(11,(uint32_t)NEO::ISR::ISR11,0x08,0x8E);
	NEO::IDT::SetGate(12,(uint32_t)NEO::ISR::ISR12,0x08,0x8E);
	NEO::IDT::SetGate(13,(uint32_t)NEO::ISR::ISR13,0x08,0x8E);
	NEO::IDT::SetGate(14,(uint32_t)NEO::ISR::ISR14,0x08,0x8E);
	NEO::IDT::SetGate(15,(uint32_t)NEO::ISR::ISR15,0x08,0x8E);
	NEO::IDT::SetGate(16,(uint32_t)NEO::ISR::ISR16,0x08,0x8E);
	NEO::IDT::SetGate(17,(uint32_t)NEO::ISR::ISR17,0x08,0x8E);
	NEO::IDT::SetGate(18,(uint32_t)NEO::ISR::ISR18,0x08,0x8E);
	NEO::IDT::SetGate(19,(uint32_t)NEO::ISR::ISR19,0x08,0x8E);
	NEO::IDT::SetGate(20,(uint32_t)NEO::ISR::ISR20,0x08,0x8E);
	NEO::IDT::SetGate(21,(uint32_t)NEO::ISR::ISR21,0x08,0x8E);
	NEO::IDT::SetGate(22,(uint32_t)NEO::ISR::ISR22,0x08,0x8E);
	NEO::IDT::SetGate(23,(uint32_t)NEO::ISR::ISR23,0x08,0x8E);
	NEO::IDT::SetGate(24,(uint32_t)NEO::ISR::ISR24,0x08,0x8E);
	NEO::IDT::SetGate(25,(uint32_t)NEO::ISR::ISR25,0x08,0x8E);
	NEO::IDT::SetGate(26,(uint32_t)NEO::ISR::ISR26,0x08,0x8E);
	NEO::IDT::SetGate(27,(uint32_t)NEO::ISR::ISR27,0x08,0x8E);
	NEO::IDT::SetGate(28,(uint32_t)NEO::ISR::ISR28,0x08,0x8E);
	NEO::IDT::SetGate(29,(uint32_t)NEO::ISR::ISR29,0x08,0x8E);
	NEO::IDT::SetGate(30,(uint32_t)NEO::ISR::ISR30,0x08,0x8E);
	NEO::IDT::SetGate(31,(uint32_t)NEO::ISR::ISR31,0x08,0x8E);

	/* Apunta el registro interno del procesador a la nueva IDT */
	NEO::IDT::Flush();


	NEO::Screen::ColocarColor(NEO_SIDE_FOREGROUND,NEO_COLOR_VERDE);
	NEO::Screen::ColocarString("done");
}
