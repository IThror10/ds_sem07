CC := g++
CFLAGS :=
RM := rm

vpath %.cpp ./src
vpath %.hpp ./inc
vpath %.o ./out

STLIB_NAME := libst_sum.dll

LIB_OBJS := sum_lib.o
LIB_HEADER := sum_lib.hpp
LIB_TYPE := st

main: app.exe installer.exe

# Build app with static lib
app.exe: app.o $(STLIB_NAME)
	$(CC) ./out/app.o -L . -lst_sum -o $@

installer.exe: installer.o
	$(CC) ./out/installer.o -o $@

#Статическая библиотека
static: $(STLIB_NAME)
	@echo "Static lib Created"

#Создание объектных файлов
%.o: %.cpp $(LIB_HEADER)
	$(CC) $(CFLAGS) -Iinc -c $<
	@mv $@ ./out/

#Создание библиотеки
$(STLIB_NAME): $(LIB_OBJS)
	cd ./out; $(CC) -shared $(LIB_OBJS) -o ../$(STLIB_NAME);
	@cd ./out;


#Other
.PHONY: clean unit func dynamic_header static_header clean_header unit
clean:
	-$(RM) *.exe ./out/*.o
	-$(RM) $(STLIB_NAME)

#Unit tests
unit: check_main.o $(CHECK_OBJS)
unit_static: static_header unit $(STLIB_NAME)
	$(CC) ./out/check_main.o ./out/check_work.o -L . -lst_array -lcheck -o unit_tests.exe
	-./unit_tests.exe
unit_dynamic: dynamic_header unit $(DNLIB_NAME)
	$(CC) ./out/check_main.o ./out/check_work.o -L . -ldn_array -lcheck -o unit_tests.exe
	-./unit_tests.exe

check_main.o: check_main.c
	$(CC) $(CFLAGS) -c $<
	@mv $@ ./out
check_%.o: check_%.c %.o work.h $(STHEADER)
	$(CC) $(CFLAGS) -Iinc -c $<
	@mv $@ ./out


#Func tests
txt_path := func_tests/
pos_tests := $(wildcard $(txt_path)pos_*_args.txt)
pos_tests := $(pos_tests:_args.txt=)
neg_tests := $(wildcard $(txt_path)neg_*_args.txt)
neg_tests := $(neg_tests:_args.txt=)

func: app.exe positive $(pos_tests) negative $(neg_tests)
	-rm $(txt_path)*_res.txt

$(txt_path)pos_%:
	-$(shell cat ./$@_args.txt)
	@-cd $(txt_path); FC $(subst $(txt_path),,$@)_out.txt $(subst $(txt_path),,$@)_res.txt 
$(txt_path)neg_%:
	-$(shell cat ./$@_args.txt)
	@echo

positive:
	@echo +------------------+
	@echo +- Pozitive Tests -+
	@echo +------------------+
negative:
	@echo +------------------+
	@echo +- Negative Tests -+
	@echo +------------------+
