#
# Automatic Generated Makefile by Maketool
#

LIBDIR = 
INCDIR =  -I./ -I../
TARGET = util
OBJS   = scanner.o scanconfig.o
DEFINES = -DsCONFIG_GUID=\{0xB405548B,\{0xF306,0x45C9,0x856B\},\{0x76,0x7B,0xB3,0xF6,0xB6,0xE0\}\}  -DsCONFIG_BUILD_DEBUG -DsCONFIG_RENDER_BLANK -DsCONFIG_OPTION_SHELL -DsCONFIG_SYSTEM_LINUX
LIBS    =
 
#
# System settings
#

CFLAGS      = -O2 -Wall -Werror -I$(INCDIR)  -fno-strict-aliasing -fshort-wchar
CXXFLAGS    = -O2 -Wall $(DEFINES) $(INCDIR) -fno-exceptions -fno-strict-aliasing -fno-rtti -fshort-wchar

LDFLAGS     = -Wl -mno-crt0 -L$(LIBDIR) -lm -lrt

#
# Rules
#

.SUFFIXES: .c .s .cc .dsm


all: spacer lib$(TARGET).a 

spacer:
	@echo -e "\n\n\n B E G I N\n";

#$(TARGET).elf: $(OBJS)
#	g++ -o $@  $(OBJS) $(LDFLAGS) $(LIBS) 

lib$(TARGET).a: $(OBJS)
	ar cr lib$(TARGET).a $(OBJS)

.c.o:
	gcc $(CFLAGS) -c $< -o $*.o

.cc.o:
	gcc $(CXXFLAGS) -c $< -o $*.o

.cpp.o:
	gcc $(CXXFLAGS) -c $< -o $*.o

#
# Fake Targets
#


clean:
	/bin/rm -f *.o *.map *.lst core *.dis *.elf 

#
# end
#
