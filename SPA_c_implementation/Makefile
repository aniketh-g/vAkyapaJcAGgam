OUTPUTDIR = "./outputs"

.PHONY: clean
clean:
	@rm -rf $(OUTPUTDIR)
	@rm -rf ./__pycache__
	@mkdir $(OUTPUTDIR)
.PHONY: test_spa
test_spa:
	@gcc spa.c spa_tester.c -lm -o $(OUTPUTDIR)/test_spa.o
	@$(OUTPUTDIR)/spa.o
.PHONY: compute_longitudes
compute_longitudes:
	@gcc spa_table_generator.c spa.c -lm -o $(OUTPUTDIR)/spa_table_generator.o
	@$(OUTPUTDIR)/spa_table_generator.o
.PHONY: plot
plot:
	@python date_list_generator.py
	@make compute_longitudes
	# @python plotter.py