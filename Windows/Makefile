#############################################################################
TARGET_NAME = Попингвини

####### Directories
SRC_DIR      = ./src
INC_DIR      = ./src
OBJ_DIR      = ./obj
RES_DIR      = ./Resources
EXE_DIR      = .

TARGET_DIR   = $(EXE_DIR)


####### Files
SOURCES = $(wildcard $(SRC_DIR)/*/*.cpp)
RESOURCES = $(wildcard $(RES_DIR)/Images/*/*.png) $(wildcard $(RES_DIR)/Images/*/*/*.png) $(wildcard $(RES_DIR)/Images/*/*/*/*.png) $(wildcard $(RES_DIR)/Images/*.png) $(wildcard $(RES_DIR)/Sound/*.ogg) $(wildcard $(RES_DIR)/Sound/*/*.ogg) $(wildcard $(RES_DIR)/Shrift/*.otf)

TARGET=$(EXE_DIR)/$(TARGET_NAME)

OBJ_FILES := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(SOURCES)))
OBJ_FILES += $(patsubst %, $(OBJ_DIR)/%.o, $(notdir $(RESOURCES)))

 
VPATH   = $(strip $(call uniq,$(dir $(SOURCES) $(RESOURCES))))
####### Compiler, tools and options
CC            = g++
CXX           = $(CC)

INCLUDES      = -I$(INC_DIR)

LDIRS         =   
LFILES        = -static -mwindows -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-system-s -lopengl32 -lwinmm -lopenal32 -lFLAC -lvorbisenc -lvorbisfile -lvorbis -logg

CFLAGS        = -g -Wall -W $(INCLUDES) $(DEFINES)
CXXFLAGS      = -g -Wall -W $(INCLUDES) $(DEFINES) -DSFML_STATIC
LINK          = $(CC)
LD            = ld
LFLAGS        = $(LDIRS)
LIBS          = $(LFILES) -static-libstdc++ -static-libgcc -lpthread -lm

DEL_FILE      = rm -f
DEL_DIR       = rm -rf
MKDIR         = mkdir -p


######################################################
define uniq =
  $(eval seen :=)
  $(foreach _,$1,$(if $(filter $_,${seen}),,$(eval seen += $_)))
  $(strip ${seen})
endef
######################################################
#.DELETE_ON_ERROR

first:  all 

####### Build rules

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	windres -i ./Resources/exe_icon.rc -o ./obj/exe_icon.o
	$(LINK) $(LFLAGS) -o $@ ./obj/exe_icon.o $(OBJ_FILES) $(LIBS)

$(OBJ_DIR)/%.o : %.cpp 
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	
$(OBJ_DIR)/%.o : %
	$(LD) -r -b binary $< -o $@ 
	



