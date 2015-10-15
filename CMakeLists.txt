PROJECT(Neoos)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
SET(CMAKE_INSTALL_PREFIX "")

ADD_SUBDIRECTORY(src) #Build components and install its into /next
ADD_SUBDIRECTORY(nextroot) #Copy files from grub and include to /
ADD_SUBDIRECTORY(iso) #Creacion del ISO
MESSAGE("make DESTDIR=next install")
MESSAGE("./iso.sh")

