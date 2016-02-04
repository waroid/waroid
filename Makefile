DEPEND_FILE = depend_file
BINDIR = /usr/local/bin
DATADIR = /usr/local/share/waroid

CC = gcc
CXX = g++
CFLAGS = 
CXXFLAGS = 

INCPATH = 
LINK = g++
LIBS = -lwiringPi -lm -lpthread -lasound -lsndfile

# FILE
CSOURCES = 

CPPSOURCES = main.cpp \
	core/Logger.cpp \
	core/WavPlayer.cpp \
	module/AdafruitAudioFxSoundBoard.cpp \
	module/AduinoBoard.cpp \
	module/BatteryChecker.cpp \
	module/PicoBorgReverse.cpp \
	module/PololuQik.cpp \
	module/TestModule.cpp \
	robot/Robot.cpp \
	robot/Crabbot.cpp \
	robot/Harpybot.cpp \
	robot/Hydrabot.cpp \
	robot/Scorpiobot.cpp \
	robot/Spiderbot.cpp \
	robot/Taurusbot.cpp \
	robot/Testbot.cpp \
	robot/Thorbot.cpp \
	robot/Toadbot.cpp \
	robot/Turtlebot.cpp \
	robot/Warthogbot.cpp \
	weapon/Weapon.cpp \
	weapon/Cannon.cpp \
	weapon/Gatling.cpp \
	weapon/Rocket.cpp \
	Global.cpp \
	MainManager.cpp

OBJECTS = $(CSOURCES:%.c=%.o)
OBJECTS += $(CPPSOURCES:%.cpp=%.o)

SOUNDS = sound/boot_sentrymode_active.wav \
	sound/cannon.wav \
	sound/gatling.wav \
	sound/rocket.wav \
	sound/5.56mm_XM214_Microgun.wav \
	sound/12.7mm_GAU-19B_HMG.wav \
	sound/20mm_M61_Vulcan.wav \
	sound/20mm_M134D_Minigun.wav \
	sound/test.wav

TARGET = WaroidServer

# Implict rules
.SUFFIXES : .cpp .c

.cpp.o: $(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<
.c.o: $(CC) -c $(CFLAGS) $(INCPATH) -o $@ $<

.PHONY: all clean depend install uninstall kill

all : $(TARGET)

$(TARGET): $(OBJECTS)
	$(LINK) -o $@ $(OBJECTS) $(LIBS)

clean:
	rm -f $(OBJECTS) $(TARGET) $(DEPEND_FILE)

depend:
	#$(CC) -MM $(CSOURCES) > $(DEPEND_FILE)
	$(CXX) -MM $(CPPSOURCES) > $(DEPEND_FILE)

rebuild: clean depend all

install:
	mkdir -p $(DATADIR)
	cp -f $(TARGET) $(BINDIR)
	cp -f $(SOUNDS) $(DATADIR)

uninstall:
	- killall $(TARGET)
	rm -fr $(DATADIR)
	rm -f $(BINDIR)/$(TARGET)

kill:
	- killall $(TARGET)

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
