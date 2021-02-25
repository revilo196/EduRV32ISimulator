export PATH:=${PATH}:/opt/riscv/bin

test_c_source_files := $(shell find test/ -name "*.c")
test_c_out_files := $(patsubst test/%.c, build/test/%.out, $(test_c_source_files))

test_c_driver_source_files := $(shell find driver/ -name "*.c")
test_c_obj_diver_files := $(patsubst driver/%.c, build/driver/%.o, $(test_c_driver_source_files))

$(test_c_obj_diver_files) : build/driver/%.o : driver/%.c
	mkdir -p build/driver && \
	riscv32-unknown-elf-gcc -g  -c -Idriver -ffreestanding -O0 $(patsubst build/driver/%.o, driver/%.c, $@) -o $@

$(test_c_out_files) : build/test/%.out : test/%.c
	mkdir -p build/test && \
	riscv32-unknown-elf-gcc -g -Idriver -ffreestanding -O0 -Wl,--gc-sections -nostartfiles -Wl,-T,riscv-emu.ld crt0.s $(patsubst build/test/%.out, test/%.c, $@) $(test_c_obj_diver_files)  -o $@

all :  $(test_c_obj_diver_files)  $(test_c_out_files)

.PHONY: clean
clean: 
	$(RM) $(test_c_obj_diver_files) $(test_c_out_files)
