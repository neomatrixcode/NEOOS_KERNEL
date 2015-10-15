PROJECT(Neoos-iso)

MESSAGE(STATUS "script para generar el ISO------------------------>>>> ")
FILE(WRITE iso.sh "#!/bin/bash\n grub-mkrescue --compress=xz --product-name=Neoos --product-version=0.1.0 -o neoos.iso next")
INSTALL(PROGRAMS iso.sh DESTINATION ..)
