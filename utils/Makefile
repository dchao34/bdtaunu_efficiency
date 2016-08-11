BINARIES = 
OBJECTS = PsqlReader.o CsvWriter.o gauss_legendre.o ff_reweight_utils.o \
					custom_program_option_utils.o visualization_utils.o

LIBNAME = libefficiency_utils.so

BOOST_ROOT = /usr/local/boost_1_59_0
BOOST_LIBS = $(BOOST_ROOT)/stage/lib

CLHEP_ROOT = /usr/local/CLHEP_2.3.3.1
CLHEP_INCS = $(CLHEP_ROOT)/include
CLHEP_LIBS = $(CLHEP_ROOT)/lib

LIBPQ_ROOT = /usr/pgsql-9.4
LIBPQ_INCS = $(LIBPQ_ROOT)/include
LIBPQ_LIBS = $(LIBPQ_ROOT)/lib

INCFLAGS = -I$(BOOST_ROOT) -I$(CLHEP_INCS) -I$(LIBPQ_INCS)
LDFLAGS = -L$(BOOST_LIBS) -L$(CLHEP_LIBS) -L$(LIBPQ_LIBS) \
					-Wl,-rpath,$(BOOST_LIBS) -lboost_program_options \
					-Wl,-rpath,$(CLHEP_LIBS) -lCLHEP \
					-Wl,-rpath,$(BOOST_LIBS) -lpq

CXX := g++
CXXFLAGS = -Wall -fPIC -pthread -std=c++11 -O2 #-Wno-unused-local-typedef -Wno-redeclared-class-member

SRCS = $(wildcard *.cc)
BUILDDIR = build

DEPDIR = .d
$(shell mkdir -p $(DEPDIR) > /dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
POSTCOMPILE = @mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

all : lib $(BINARIES)

lib : $(LIBNAME)

test% : $(addprefix $(BUILDDIR)/, test%.o $(OBJECTS))
	  $(CXX) $(LDFLAGS) $^ -o $@

$(LIBNAME) : $(addprefix $(BUILDDIR)/, $(OBJECTS))
	if [ "$(shell uname)" = "Darwin" ]; then \
    SHARED_LIB_FLAG="-dynamiclib -Wl,-install_name,@rpath/$(LIBNAME)"; \
  else \
    SHARED_LIB_FLAG="-shared -Wl,-soname,$(LIBNAME)"; \
  fi; \
	$(CXX) $${SHARED_LIB_FLAG} $(LDFLAGS) $^ -o $(LIBNAME)


$(BUILDDIR)/%.o : %.cc
$(BUILDDIR)/%.o : %.cc $(DEPDIR)/%.d
	$(CXX) $(DEPFLAGS) $(CXXFLAGS) $(INCFLAGS) -c $< -o $@
	$(POSTCOMPILE)

$(DEPDIR)/%.d: ;

.PRECIOUS: $(DEPDIR)/%.d

-include $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS)))

clean : 
	@rm -f *~ $(BUILDDIR)/* $(LIBNAME) $(BINARIES)

cleanall : clean
	@rm -f $(DEPDIR)/*
