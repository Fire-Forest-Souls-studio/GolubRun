#############################################################################
TARGET_NAME = GolubRun

####### Directories
SRC_DIR      = ./src
INC_DIR      = ./src
OBJ_DIR      = ./obj
RES_DIR      = ./Resources
EXE_DIR      = .

TARGET_DIR   = $(EXE_DIR)


####### Files
SAVING_FILE = saving.blackfire-popingvini

SOURCES = $(wildcard $(SRC_DIR)/Code/src/*/*.cpp)
RESOURCES = $(wildcard $(RES_DIR)/Images/*/*.png) $(wildcard $(RES_DIR)/Images/*/*/*.png) $(wildcard $(RES_DIR)/Images/*/*/*/*.png) $(wildcard $(RES_DIR)/Images/*.png) \
	$(wildcard $(RES_DIR)/Sound/*.ogg) $(wildcard $(RES_DIR)/Sound/*/*.ogg) \
	$(wildcard $(RES_DIR)/Shrift/*.otf) \

TARGET=$(EXE_DIR)/$(TARGET_NAME)

OBJ_FILES := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(SOURCES)))
OBJ_FILES += $(patsubst %, $(OBJ_DIR)/%.o, $(notdir $(RESOURCES)))

 
VPATH   = $(strip $(call uniq,$(dir $(SOURCES) $(RESOURCES))))
####### Compiler, tools and options
CC            = gcc-13
CXX           = $(CC)

INCLUDES      = -I$(INC_DIR)

LDIRS         =   
LFILES        = -pg -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-system -z execstack

CFLAGS        = -g -Wall -W $(INCLUDES) $(DEFINES) -pg
CXXFLAGS      = -g -Wall -W $(INCLUDES) $(DEFINES) -pg
LINK          = $(CC)
LD            = ld
LFLAGS        = $(LDIRS)
LIBS          = $(LFILES) -lstdc++ -lm

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

info:
	@echo $(OBJ_FILES)


all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	@if [ ! -d $(EXE_DIR) ]; then mkdir -p $(EXE_DIR); fi
	$(LINK) $(LFLAGS) -o $@ $(OBJ_FILES) $(LIBS)


$(OBJ_DIR)/%.o : %.cpp 
	@if [ ! -d $(OBJ_DIR) ]; then mkdir -p $(OBJ_DIR); fi 	
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	
$(OBJ_DIR)/%.o : %
	@if [ ! -d $(OBJ_DIR) ]; then mkdir -p $(OBJ_DIR); fi 	
	$(LD) -r -b binary $< -o $@ 

########### Clean rules

clean:
	@rm -f $(OBJ_FILES); \
	rm -f $(TARGET); \
	rm -rf $(OBJ_DIR); \
	rm -rf $(SAVING_FILE); \
	rm -f *~ core *.core
	



