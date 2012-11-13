#
# IMCFGLAST needed ? 
#
# want to include
# 	ImageMagick-6.8.0-4/Magick++/lib/.libs/	for libMagick++.so
# 	ImageMagick-6.8.0-4/magick/.libs/ 	for libMagickCore.so


# Bullet Physics Engine
BSROOT=$(shell readlink -f ./bullet)
BSRCROOT=$(shell readlink -f ./bullet/src)
BSD=$(BSRCROOT)/BulletDynamics/libBulletDynamics.a 
BSC=$(BSRCROOT)/BulletCollision/libBulletCollision.a 
BSL=$(BSRCROOT)/LinearMath/libLinearMath.a 
BSS=$(BSRCROOT)/BulletSoftBody/libBulletSoftBody.a
BULLET_CMAKE_CACHELISTFILE=$(BSROOT)/CMakeLists.txt
BULLET_MAKEFILE  =  $(BSROOT)/Makefile

# Assimp
LIBDIRASSIMP=-Lassimp/lib/
ASSIMPINCLUDEDIR_ECC=/usr/local/include/assimp
ASSIMPINCLUDE=-I$(ASSIMPINCLUDEDIR_ECC) # ecc assimp include files

# Mesh Objects
BALL=obj/ball.obj
BOARD=obj/board.obj
MeshAll=$(BALL) $(BORAD)

# Shaders
VSHADER=src/shader.vert
FSHADER=src/shader.frag
VSHADER2=src/shader2.vert
FSHADER2=src/shader2.frag

INITSCRIPT = bin/init.sh

OBJECTS = bin/lighting_technique.o bin/InitShader.o bin/technique.o bin/math_3d.o bin/texture.o 

# ImageMagick
IMROOT=$(shell readlink -f imagemagick)
IMLPATH=$(IMROOT)/Magick++/lib/
IMLIB=$(IMROOT)/Magick++/lib
IMBIN=$(IMROOT)/Magick++/bin
	# IMCFG=`$(IMBIN)/Magick++-config --cppflags --cxxflags --ldflags --libs`
# ImageMagick : Object
IMBLOB=$(IMLIB)/Blob.o
IMIMAGE=$(IMLIB)/Image.o
IMOBJECTS = $(IMBLOB) $(IMIMAGE)
# ImageMagick : PKG_CONFIG_PATH
# The find command below finds all the .pc files under imagemagick
# 	find imagemagick/ -name "*.pc" 
PKG_CONFIG_PATH = $(IMROOT)/Magick++/lib
PKG_CONFIG_PATH := $(PKG_CONFIG_PATH):$(IMROOT)/magick
PKG_CONFIG_PATH := $(PKG_CONFIG_PATH):$(IMROOT)/wand
# ImageMagick : Config
DEP = $(IMOBJECTS)
IMCFGLAST=`$(IMBIN)/Magick++-config --ldflags --libs`
IMCFG=`$(IMROOT)/bin/Magick++-config --cppflags --cxxflags --cxxflags --ldflags --libs`
# ImageMagick : Include
IMINCLUDE=-I$(IMROOT)/Magick++/lib -I$(IMROOT)
# ImageMagick : Lib and LibDir
IMLIBS=-lMagick++ -lMagickCore -lMagickWand
IMLIBDIR=-L$(IMROOT)/Magick++/lib/.libs -L$(IMROOT)/magick/.libs -L$(IMROOT)/utilities/.libs -L$(IMROOT)/Magick++/lib/.libs -L$(IMROOT)/magick/.libs -L$(IMROOT)/wand/.libs


# Compiler and its Options
CC=g++
CXXFLAGS=-g -Wall -std=c++0x # -fpermissive

## Make Main
# $(IMCFG) 
bin/j7.out : src/j7.cpp $(OBJECTS) $(BSD) $(BSC) $(BSL) $(BSS)
	# if [ ! -r "$(IMROOT)/Makefile" ] ; then\
	# 	echo "IMROOT Makefile does not exist";\
	# 	cd $(IMROOT); ./configure ; make;\
	# else\
	# 	echo "IMROOT Makefile exists";\
	# fi
	cd $(IMROOT); ./configure ; make;\
	$(CC) $(LIBDIR) $(INCLUDEDIR) $(CXXFLAGS) $^ $(LIBS) -o $@ # $(IMCFGLAST) 

run2 : bin/j7.out
	. $(INITSCRIPT) && ./$< $(BALL) $(BOARD) $(VSHADER2) $(FSHADER2)

run : bin/j7.out
	. $(INITSCRIPT) && ./$< $(BALL) $(BOARD) $(VSHADER) $(FSHADER)

# Bullet Library Compilation
$(BSD) $(BSC) $(BSL) $(BSS) :
	cd $(BSROOT) ; cmake . -G "Unix Makefiles" && make ; cd ..


# Objects

bin/texture.o : src/texture.cpp
	$(CC) $(IMCFG) $(INCLUDEDIR) $(CXXFLAGS) -c  $^ -o $@

bin/InitShader.o : src/InitShader.cpp 
	$(CC) -c $(CXXFLAGS) $^ -o $@

# Lighting Lib

bin/technique.o : src/technique.cpp
	$(CC)	 -c $(CXXFLAGS) src/technique.cpp -o $@

bin/lighting_technique.o : src/lighting_technique.cpp 
	$(CC) -c $^ -o $@ 

bin/math_3d.o : src/math_3d.cpp
	$(CC) -c $^ -o $@ 

# Aggregation 
# Libs
	# LPATH=-Wl,-rpath=lib # embed dynamic library (in ./lib) references into executable
LIBS= -lglut -lGLEW -lGL -lGLU -lassimp $(BSD) $(BSC) $(BSL) $(BSS) $(IMLIBS)
LIBDIR = $(LIBDIRASSIMP) $(IMLIBDIR)
# Include Headers
INCLUDEDIR= -I./assimp/ -Ibullet/src -I./assimp/include/assimp $(ASSIMPINCLUDE) $(IMINCLUDE) -Isrc 

# Make Debug
makedebug : 
	@echo "ImageMatickRoot=$(IMROOT)"
	@echo "PKG_CONFIG_PATH=$(PKG_CONFIG_PATH)"
	@echo "IMCFG="$(IMCFG)
	@echo "IMCFGLAST="$(IMCFGLAST)
	@echo "IMLIB="$(IMLIB)
	@echo "LD_LIBRARY_PATH="$(LD_LIBRARY_PATH)

IMMakefile = $(shell readlink -f imagemagick/Makefile)
ImageMagick : $(IMMakefile)
	cd $(IMROOT) ; ./configure && make ; cd ..





## Old Below 

j6.out: j6.cpp libbullet libassimp
	$(CC) $(LPATH) $(LIBDIR) $(INCLUDEDIR) $(CXXFLAGS) j6.cpp $(LIBS) -o j6.out  && . ./init.sh && ./j6.out

bullethello.out: bullethello.cpp 
	g++ $(LPATH) $(LIBDIR) $(INCLUDEDIR) $(CXXFLAGS) bullethello.cpp $(LIBS) -o bullethello.out  && ./bullethello.out

# .PHONY : libbullet
# libbullet : bullet/Makefile
# 	cd bullet && make && cd .. && echo "bullet lib done" ; \

# libbullet/Makefile : bullet/Makefile
# 	cd bullet && cmake . -G "Unix Makefiles" && cd ..

.PHONY : assimp
libassimp : assimp/Makefile
	cd assimp && make && cd ..

assimp/Makefile : assimp/CMakeLists.txt
	cd assimp && cmake -G 'Unix Makefiles' 

clean: 
	rm bin/*.out bin/*.o bin/j7.out ; cd bullet ; make clean ; cd .. 
