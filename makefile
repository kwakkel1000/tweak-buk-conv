CC = g++
CFLAGS = -march=native -O0 -pipe
CXXFLAGS = $(CFLAGS) -fPIC -g -Wall
MYSQLFLAGS = -L/usr/include/mysql -lmysqlclient -I/usr/include/mysql
BOOSTLIB = -lboost_thread
LIBS = -ldl $(BOOSTLIB)
MAKEFLAGS = -j

SRCDIR=src/
MODULEDIR=$(SRCDIR)modules/
LIBDIR=.libs/
EXECUTABLE=tweak-buk-conv

allfunctions = tweakbukconv TweakZoneConvert.so

main_objects = $(SRCDIR)main.o \
	$(SRCDIR)tweakbukconv.o \
	$(SRCDIR)Database.o \
	$(SRCDIR)ConfigReader.o
admin_objects = $(MODULEDIR)Admin.o
tweakconvert_objects = $(MODULEDIR)ModuleBase.o $(MODULEDIR)TweakZoneConvert.o $(MODULEDIR)Zone.o
test_objects = $(MODULEDIR)ModuleBase.o $(MODULEDIR)Test.o

default: tweakbukconv

tweakbukconv: $(main_objects)
	$(CC) -rdynamic -o $(EXECUTABLE) $(main_objects) $(MYSQLFLAGS) $(LIBS)
Admin.so: $(admin_objects)
	$(CC) -shared -Wl -o $(LIBDIR)$(@) $(admin_objects)
TweakZoneConvert.so: $(tweakconvert_objects)
	$(CC) -shared -Wl -o $(LIBDIR)$(@) $(tweakconvert_objects)

all: $(allfunctions)
Debug: all
Release: all

clean:
	rm -f $(LIBDIR)*.so $(SRCDIR)*.o $(MODULEDIR)*.o $(EXECUTABLE)

cleanAdmin:
	rm -f $(LIBDIR)Admin.so $(admin_objects)

cleanTweakConvert:
	rm -f $(LIBDIR)TweakZoneConvert.so $(tweakconvert_objects)

radmin: cleanAdmin Admin.so

rtweakconv: cleanTweakConvert TweakZoneConvert.so
