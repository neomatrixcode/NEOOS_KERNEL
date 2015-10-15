
namespace NEO{
	namespace Timer{
			void Install();
			void Fase(int hz);
			void Espera(int ticks);
		}
}
extern "C"
void NEO_Timer_Handler(struct regs* r);

