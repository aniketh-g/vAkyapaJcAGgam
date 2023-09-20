.PHONY: clean
clean:
	@rm -r *.gch *.o
.PHONY: spa_tester
spa_tester:
	@gcc spa_tester.c spa.c -lm -o spa.o
	@./spa.o
.PHONY: generate_table
generate_table:
	@gcc spa_table_generator.c spa.c -lm -o spa_table_generator.o
	@./spa_table_generator.o