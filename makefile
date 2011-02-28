CC = g++
CFLAGS = -march=native -pipe #-O#n for nondebug
CXXFLAGS = $(CFLAGS) -fPIC -Wall -g #-g << debugging
MYSQLFLAGS = -L/usr/include/mysql -lmysqlclient -I/usr/include/mysql #depends on arch
BOOSTLIB = -lboost_thread #depends on arch
LIBS = -ldl $(BOOSTLIB)
MAKEFLAGS = -j5 #-j#n for threaded compiling

SRCDIR=src/
MODULEDIR=$(SRCDIR)modules/
LIBDIR=.libs/
EXECUTABLE=tweak-buk-conv

allfunctions = tweakbukconv TweakZoneConvert.so

main_objects = $(SRCDIR)main.o \
	$(SRCDIR)tweakbukconv.o \
	$(SRCDIR)Database.o \
	$(SRCDIR)GlobalBase.o \
	$(SRCDIR)Groups.o \
	$(SRCDIR)Group.o \
	$(SRCDIR)Users.o \
	$(SRCDIR)User.o \
	$(SRCDIR)ConfigReader.o
admin_objects = $(MODULEDIR)Admin.o
tweakconvert_objects = $(MODULEDIR)ModuleBase.o $(MODULEDIR)TweakZoneConvert.o $(MODULEDIR)Zone.o
test_objects = $(MODULEDIR)ModuleBase.o $(MODULEDIR)Test.o

default: tweakbukconv

tweakbukconv: $(main_objects)
	$(CC) -rdynamic -o $(EXECUTABLE) $(main_objects) $(MYSQLFLAGS) $(LIBS) $(CXXFLAGS)
Admin.so: $(admin_objects)
	$(CC) -shared -o $(LIBDIR)$(@) $(admin_objects) $(CXXFLAGS)
TweakZoneConvert.so: $(tweakconvert_objects)
	$(CC) -shared -o $(LIBDIR)$(@) $(tweakconvert_objects) $(CXXFLAGS)

all: $(allfunctions)
Debug: all
Release: all
cleanDebug: clean
cleanRelease: clean
clean:
	rm -f $(LIBDIR)*.so $(SRCDIR)*.o $(MODULEDIR)*.o $(EXECUTABLE)

cleanAdmin:
	rm -f $(LIBDIR)Admin.so $(admin_objects)

cleanTweakConvert:
	rm -f $(LIBDIR)TweakZoneConvert.so $(tweakconvert_objects)

radmin: cleanAdmin Admin.so

rtweakconv: cleanTweakConvert TweakZoneConvert.so
