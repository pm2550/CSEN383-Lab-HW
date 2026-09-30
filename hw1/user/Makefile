U = user
ULIB = $(U)/ulib.o $(U)/usys.o $(U)/printf.o $(U)/umalloc.o
$U/_%: hw1/user/%.o $(ULIB)
	$(LD) $(LDFLAGS) -T $U/user.ld -o $@ $^
	$(OBJDUMP) -S $@ > $U/$*.asm
	$(OBJDUMP) -t $@ | sed '1,/SYMBOL TABLE/d; s/ .* / /; /^$$/d' > $U/$*.sym
$U/_hw1_test: hw1/user/hw1_test.o hw1/user/usysinfo.o hw1/user/uprocinfo.o $(ULIB)
	$(LD) $(LDFLAGS) -T $U/user.ld -o $@ $^
	$(OBJDUMP) -S $@ > $U/hw1_test.asm
	$(OBJDUMP) -t $@ | sed '1,/SYMBOL TABLE/d; s/ .* / /; /^$$/d' > $U/hw1_test.sym