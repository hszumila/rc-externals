my_objs     = externals_2020.o f1f220.o
my_grid_obj = make_grid.o
my_rc_obj   = make_rc_dat.o

#CERNLIBS = /apps/cernlib/x86_64_rhel7/2005/lib -lmathlib 
#CERNLIBS = /u/site/cernlib/x86_64_rhel7/2005/lib -lmathlib
#CERNLIBS = /opt/cernlib/2005/lib -lmathlib
CERNLIBS = $(CERN_ROOT)/lib -lmathlib -lpacklib -lc -lm

FFLAGSA = -C -g -w -fno-automatic -fbounds-check -ffixed-line-length-132 -finit-local-zero 
INCLUDES = -I.
FFLAGS = $(INCLUDES) $(FFLAGSA)
FFLAG1 = $(FFLAGS) -c
OTHERLIBS = \
-L$(CERNLIBS) 
FC  := gfortran
CPP := g++

%.o: %.f
	$(FC) $(FFLAGS) -c $< -o $@

all: externals_2020 make_grid make_rc_dat

 externals_2020 :  Makefile $(my_objs)
	$(FC) -o $@ $(FFLAGS) $(my_objs)  $(OTHERLIBS)
 make_grid : Makefile $(my_grid_obj)
	$(CPP) -o $@ $(my_grid_obj)
 make_rc_dat : Makefile $(my_rc_obj)
	$(CPP) -o $@ $(my_rc_obj)
clean:
	rm -f *.o *.so externals_2020 make_grid make_rc_dat
