DEPEND_FILE = depend_file
BINDIR = /usr/local/bin
DATADIR = /usr/local/share/waroid

CC = gcc
CXX = g++
CFLAGS = 
CXXFLAGS = 

INCPATH = 
LINK = g++
LIBS = -lwiringPi -lm -lpthread

# FILE
CSOURCES = 

CPPSOURCES = main.cpp \
	core/Logger.cpp \
	module/PicoBorgReverse.cpp \
	module/PololuQik.cpp \
	module/ServoMotor.cpp \
	module/RelayMotor.cpp \
	module/BatteryChecker.cpp \
	Global.cpp \
	Robot.cpp \
	Crab.cpp \
	Hydra.cpp \
	Turtle.cpp \
	Toad.cpp \
	Scorpio.cpp \
	MainManager.cpp

OBJECTS = $(CSOURCES:%.c=%.o)
OBJECTS += $(CPPSOURCES:%.cpp=%.o)

SOUNDS = boot_sentrymode_active.wav

TARGET = WaroidServer

# Implict rules
.SUFFIXES : .cpp .c

.cpp.o: $(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<
.c.o: $(CC) -c $(CFLAGS) $(INCPATH) -o $@ $<

.PHONY: all clean depend install uninstall

all : $(TARGET)

$(TARGET): $(OBJECTS)
	$(LINK) -o $@ $(OBJECTS) $(LIBS)

clean :
	rm -f $(OBJECTS) $(TARGET) $(DEPEND_FILE)

depend:
	#$(CC) -MM $(CSOURCES) > $(DEPEND_FILE)
	$(CXX) -MM $(CPPSOURCES) > $(DEPEND_FILE)

rebuild: clean depend all

install :
	mkdir -p $(DATADIR)
	cp -f $(TARGET) $(BINDIR)
	cp -f sound/$(SOUNDS) $(DATADIR)

uninstall :
	- killall $(TARGET)
	rm -fr $(DATADIR)
	rm -f $(BINDIR)/$(TARGET)

ifneq ($(MAKECMDGOALS), clean)
ifneq ($(MAKECMDGOALS), depend)
ifneq ($(MAKECMDGOALS), install)
ifneq ($(MAKECMDGOALS), uninstall)
ifneq ($(CSOURCES), )
ifneq ($(CPPSOURCE), )
-include $(DEPEND_FILE)
endif
endif
endif
endif
endif
endif
