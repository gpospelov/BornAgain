# 'make' to get executable
# 'make lib' to get shared library

SRCDIR        = ./src
OBJDIR        = ./obj
INCDIR        = ./inc
BINDIR        = ./
LIBDIR        = ./obj

#ROOTCFLAGS    = $(shell root-config --cflags)
#ROOTGLIBS     = $(shell root-config --glibs)
#ROOTLDFLAGS   = $(shell root-config --ldflags)

CC      = g++
CXX     = g++  -fpic -pthread -m64
LD      = g++  -rdynamic -m64
RM      = rm -f

UBIN = $(BINDIR)/Gisasfw
ULIB = $(LIBDIR)/Gisasfw.so

#USRC = $(sort TestLogosDict.cpp $(wildcard *.cpp))
USRCN = $(sort $(wildcard $(SRCDIR)/*.cpp))
USRC = $(notdir $(USRCN))
UOBJ = $(addprefix $(OBJDIR)/,$(addsuffix .o,$(basename $(USRC))))
UINC = $(wildcard $(INCDIR)/*.h)

# this is the list of object files which has to be excluded from the library
FILTEROUT = $(OBJDIR)/main.o

UDEPS = $(UOBJ) $(UINC)


INCLUDES = -I. -I${INCDIR}

.SUFFIXES: .cpp

$(UBIN): $(UDEPS)
	@echo "======================================================="
	@echo " => Linking $@ "
	$(LD) $(ROOTLDFLAGS) -o $@  $(UOBJ)  $(ROOTGLIBS)

lib: $(ULIB)
libs: $(ULIB)

$(ULIB): $(UDEPS)
	@echo "======================================================="
	@echo "TestLogos shared lib ..."
	mkdir -p $(LIBDIR)
	$(CC) $(ROOTLDFLAGS)  -o $@ -shared $(filter-out $(FILTEROUT),$(UOBJ)) $(ROOTGLIBS)

#TestLogosDict.cpp: TestLogos.h TestLogosLinkDef.h
#	@echo "======================================================="
#	@echo " - Making dictionary $<"
#	rootcint -f $@ -c $^

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@echo "======================================================="
	@echo " - C++ compiling $<"
	@echo "-------------------------------------------------------"
	mkdir -p $(OBJDIR)
	$(RM) $@
	$(CXX) $(INCLUDES) $(ROOTCFLAGS) -c  $< -o $@

clean:
	rm -f $(UBIN)
	rm -f $(UOBJ)
	rm -f *~
	rm -f *Dict*
	rm -f $(ULIB)







