NEOOS_KERNEL
=====
NEOOS_KERNEL es un kernel construido en GAS (Gnu Asembler) y C++ diseñado para correr en un procesador X86 de 32 bits.

En la carpeta src/start se encuentra el codigo fuente del proyecto.

Al compilar se obtiene un archivo .iso en la carpeta build el cual puede ser ejecutado en una maquina virtual, lanzado con qemu o bien copiado al disco duro de una pc con procesador X86 a 32 bits.

Instalacion de las dependencias
----------
Para poder compilar es necesario instalar previamente:
```bash
sudo apt-get install build-essential;
sudo apt-get install g++;
sudo apt-get install cmake;
sudo apt-get install xorriso;
sudo apt-get install qemu-system-x86;
```
Compilacion
----------
Para compilar es nesesario seguir estos pasos:
```bash
git clone https://github.com/codeneomatrix/NEOOS_KERNEL.git
cd NEOOS_KERNEL;
cd build;
cmake ..;
make;
make DESTDIR=next install;
chmod +x iso.sh;
./iso.sh;
sudo qemu-system-i386 neoos.iso;
```
Ejecucion
----------
Una vez que tenemos el archivo .iso podemos emplear qemu para virtualizar:
```bash
sudo qemu-system-i386 neoos.iso;
```
