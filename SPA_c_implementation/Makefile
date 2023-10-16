OUTPUTDIR = "./outputs"

.PHONY: clean
clean:
	@rm -rf $(OUTPUTDIR)
	@rm -rf ./__pycache__
	@mkdir $(OUTPUTDIR)
.PHONY: test_spa
test_spa:
	@gcc spa.c spa_tester.c -lm -o $(OUTPUTDIR)/test_spa.o
	@$(OUTPUTDIR)/test_spa.o
.PHONY: generate_longitude_tables_from_greg_date
generate_longitude_tables_from_greg_date:
	@python date_list_generator.py
	@gcc spa_table_generator_greg_date.c spa.c -lm -o $(OUTPUTDIR)/spa_table_generator_greg_date.o
	@$(OUTPUTDIR)/spa_table_generator_greg_date.o
.PHONY: plot
plot:
	@make generate_longitude_tables_from_greg_date
	@python plotter.py
.PHONY: generate_longitude_tables_from_jd
generate_longitude_tables_from_jd:
	@gcc spa_table_generator_from_jd.c spa.c -lm -o $(OUTPUTDIR)/spa_table_generator_from_jd.o
	@$(OUTPUTDIR)/spa_table_generator_from_jd.o
.PHONY: generate_yogyadi_vakyas
generate_yogyadi_vakyas:
	@gcc vakya_calculator.c spa.c -lm -o $(OUTPUTDIR)/vakya_calculator.o
	@$(OUTPUTDIR)/vakya_calculator.o