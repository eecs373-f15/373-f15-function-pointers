CFLAGS += -O1 -Wall

check:	check_main check_reverse
	@printf "\nAll tests passed. Task complete.\n"

check_reverse: run_reverse golden_reverse.out
	@printf "\nChecking output of reverse\n"
	@diff -q golden_reverse.out reverse.out || diff -y golden_reverse.out reverse.out && echo "Test passed."

run_reverse:	reverse
	@printf "\nRunning reverse\n"
	@./reverse | tee reverse.out

check_main:	run_main golden_main.out
	@printf "\nChecking output of main\n"
	@diff -q golden_main.out main.out || diff -y golden_main.out main.out && echo "Test passed."
	@printf "\nChecking for qsort\n"
	@nm sort.o | egrep -q 'U _?qsort' || { echo "You must use the standard library's qsort as the third sort"; exit 1; } && echo "Test passed."

run_main:	main
	@printf "\nRunning main\n"
	@./main | tee main.out

main:	main.o sort.o

reverse:	main.o sort.o reverse_sort.o
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f *.o main reverse main.out reverse.out

.PHONY: clean run_main check_main run_reverse check_reverse check

