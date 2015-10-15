#ifndef PRIMSHELLLITE_H
#define PRIMSHELLLITE_H

namespace PrimShell{
	namespace PRIMITIVE{
		int main();
		int Esperacomando();
		int EjecutaString(char* script);
		namespace Commandos{
			void Version();
			void NotFound();
			void Drakaris();
			void Creador();
		}
	}
}

#endif
