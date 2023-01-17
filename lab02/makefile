CC := g++
CFLAGS := -Wall -Werror -pedantic
OBJS := enigma.o reflector.o rotor.o
RM := rm

CHECK_OBJS := check_crypt.o

test_path := func_tests/
tests := $(wildcard $(test_path)test_*_args.txt)
tests := $(tests:_args.txt=)

vpath %.cpp ./src ./unit
vpath %.hpp ./inc
vpath %.o ./out

#Main
app.exe: main.o $(OBJS)
	$(CC) -Iout $^ -o $@
	@mv $^ ./out

main.o: main.cpp
	$(CC) $(CFLAGS) -Iinc -c $<

%.o: %.cpp %.hpp
	$(CC) $(CFLAGS) -Iinc -c $<

#Unit tests
unit_tests.exe: check_main.o $(CHECK_OBJS) $(OBJS)
	$(CC) -Iout $^ -lcheck -o $@
	-mv *.o ./out

check_main.o: check_main.cpp
	$(CC) $(CFLAGS) -Iinc -c $<

check_%.o: check_%.cpp %.o %.hpp
	$(CC) $(CFLAGS) -Iinc -c $<

#Other
.PHONY: clean unit func
clean:
	-$(RM) *.exe
	-$(RM) ./out/*.o

unit: unit_tests.exe
	-./$<

func: app.exe test_header $(tests)
	-rm $(txt_path)*_out.txt

$(test_path)test_%:
	-$(shell cat ./$@_args.txt)
	@-cd $(test_path); FC $(subst $(test_path),,$@)_out.txt $(subst $(test_path),,$@)_res.txt 

test_header:
	@echo +-------------------+
	@echo +------ Tests ------+
	@echo +-------------------+
