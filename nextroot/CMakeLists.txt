PROJECT(Neoos-nextroot)

MESSAGE(STATUS "Creando el directorio NextRoot ")
INSTALL(DIRECTORY ../grub DESTINATION boot)
INSTALL(DIRECTORY ../include DESTINATION .)
