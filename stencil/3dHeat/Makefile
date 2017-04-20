CC = gcc-6 
CFLAGS = -fopenmp -O3

debug : heat_debug 

heat: main.c util.c heat.c heat-blocked.c heat-time.c cycle.h common.h
	$(CC) $(CFLAGS) -DRANDOMVALUES -DHEAT main.c util.c heat.c heat-blocked.c heat-time.c -o heat
	$(CC) $(CFLAGS) -DRANDOMVALUES -DHEATBLOCK main.c util.c heat.c heat-blocked.c heat-time.c -o heat_block
	$(CC) $(CFLAGS) -DRANDOMVALUES -DHEATTIME main.c util.c heat.c heat-blocked.c heat-time.c -o heat_time

heat_debug: main.c util.c heat.c heat-blocked.c heat-time.c cycle.h common.h
	$(CC) $(CFLAGS) -DRANDOMVALUES -DDEBUG -DHEAT main.c util.c heat.c heat-blocked.c heat-time.c -o debug_heat
	$(CC) $(CFLAGS) -DRANDOMVALUES -DDEBUG -DHEATBLOCK main.c util.c heat.c heat-blocked.c heat-time.c -o debug_heat_block
	$(CC) $(CFLAGS) -DRANDOMVALUES -DDEBUG -DHEATTIME main.c util.c heat.c heat-blocked.c heat-time.c -o debug_heat_time

heat_base: main.c util.c heat.c heat-blocked.c heat-time.c cycle.h common.h
	$(CC) $(CFLAGS) -DHEAT main.c util.c heat.c heat-blocked.c heat-time.c -o base_heat
	$(CC) $(CFLAGS) -DHEATBLOCK main.c util.c heat.c heat-blocked.c heat-time.c -o base_heat_block
	$(CC) $(CFLAGS) -DHEATTIME main.c util.c heat.c heat-blocked.c heat-time.c -o base_heat_time