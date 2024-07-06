CXX = g++  
CXXFLAGS = -fopenmp  
	
ARGS1 = 10 9 10_9.txt
ARGS2 = 10 30 10_30.txt
ARGS3 = 10 50 10_50.txt
ARGS4 = 10 70 10_70.txt
	
ARGS5 = 100 99 100_99.txt
ARGS6 = 100 300 100_300.txt
ARGS7 = 100 500 100_500.txt
ARGS8 = 100 700 100_700.txt
	
ARGS9 = 1000 999 1000_999.txt
ARGS10 = 1000 3000 1000_3000.txt
ARGS11 = 1000 5000 1000_5000.txt
ARGS12 = 1000 7000 1000_7000.txt
	
ARGS13 = 10000 9999 10000_9999.txt
ARGS14 = 10000 30000 10000_30000.txt
ARGS15 = 10000 50000 10000_50000.txt
ARGS16 = 10000 70000 10000_70000.txt
	
ARGS17 = 100000 99999 100000_99999.txt
ARGS18 = 100000 300000 100000_300000.txt
ARGS19 = 100000 500000 100000_500000.txt
ARGS20 = 100000 700000 100000_700000.txt
	
all: run1 run2 run3 run4 run5 run6 run7 run8 run9 run10 run11 run12 run13 run14 run15 run16 run17 run18 run19 run20 run
	
run:
	$(CXX) tarjan.cpp
	./a.out 10_9.txt > tarjan.txt
	./a.out 10_30.txt >> tarjan.txt
	./a.out 10_50.txt >> tarjan.txt
	./a.out 10_70.txt >> tarjan.txt
	./a.out 100_99.txt >> tarjan.txt
	./a.out 100_300.txt >> tarjan.txt
	./a.out 100_500.txt >> tarjan.txt
	./a.out 100_700.txt >> tarjan.txt
	./a.out 1000_999.txt >> tarjan.txt
	./a.out 1000_3000.txt >> tarjan.txt
	./a.out 1000_5000.txt >> tarjan.txt
	./a.out 1000_7000.txt >> tarjan.txt
	./a.out 10000_9999.txt >> tarjan.txt
	./a.out 10000_30000.txt >> tarjan.txt
	./a.out 10000_50000.txt >> tarjan.txt
	./a.out 10000_70000.txt >> tarjan.txt
	./a.out 100000_99999.txt >> tarjan.txt
	./a.out 100000_300000.txt >> tarjan.txt
	./a.out 100000_500000.txt >> tarjan.txt
	./a.out 100000_700000.txt >> tarjan.txt

	$(CXX) tv-nonparallel.cpp
	./a.out 10_9.txt > tvnp.txt
	./a.out 10_30.txt >> tvnp.txt
	./a.out 10_50.txt >> tvnp.txt
	./a.out 10_70.txt >> tvnp.txt
	./a.out 100_99.txt >> tvnp.txt
	./a.out 100_300.txt >> tvnp.txt
	./a.out 100_500.txt >> tvnp.txt
	./a.out 100_700.txt >> tvnp.txt
	./a.out 1000_999.txt >> tvnp.txt
	./a.out 1000_3000.txt >> tvnp.txt
	./a.out 1000_5000.txt >> tvnp.txt
	./a.out 1000_7000.txt >> tvnp.txt
	./a.out 10000_9999.txt >> tvnp.txt
	./a.out 10000_30000.txt >> tvnp.txt
	./a.out 10000_50000.txt >> tvnp.txt
	./a.out 10000_70000.txt >> tvnp.txt
	./a.out 100000_99999.txt >> tvnp.txt
	./a.out 100000_300000.txt >> tvnp.txt
	./a.out 100000_500000.txt >> tvnp.txt
	./a.out 100000_700000.txt >> tvnp.txt

	$(CXX) $(CXXFLAGS) tarjanvishkin.cpp
	./a.out 10_9.txt > tv.txt
	./a.out 10_30.txt >> tv.txt
	./a.out 10_50.txt >> tv.txt
	./a.out 10_70.txt >> tv.txt
	./a.out 100_99.txt >> tv.txt
	./a.out 100_300.txt >> tv.txt
	./a.out 100_500.txt >> tv.txt
	./a.out 100_700.txt >> tv.txt
	./a.out 1000_999.txt >> tv.txt
	./a.out 1000_3000.txt >> tv.txt
	./a.out 1000_5000.txt >> tv.txt
	./a.out 1000_7000.txt >> tv.txt
	./a.out 10000_9999.txt >> tv.txt
	./a.out 10000_30000.txt >> tv.txt
	./a.out 10000_50000.txt >> tv.txt
	./a.out 10000_70000.txt >> tv.txt
	./a.out 100000_99999.txt >> tv.txt
	./a.out 100000_300000.txt >> tv.txt
	./a.out 100000_500000.txt >> tv.txt
	./a.out 100000_700000.txt >> tv.txt

	$(CXX) $(CXXFLAGS) tvdsu.cpp
	./a.out 10_9.txt > tvdsu.txt
	./a.out 10_30.txt >> tvdsu.txt
	./a.out 10_50.txt >> tvdsu.txt
	./a.out 10_70.txt >> tvdsu.txt
	./a.out 100_99.txt >> tvdsu.txt
	./a.out 100_300.txt >> tvdsu.txt
	./a.out 100_500.txt >> tvdsu.txt
	./a.out 100_700.txt >> tvdsu.txt
	./a.out 1000_999.txt >> tvdsu.txt
	./a.out 1000_3000.txt >> tvdsu.txt
	./a.out 1000_5000.txt >> tvdsu.txt
	./a.out 1000_7000.txt >> tvdsu.txt
	./a.out 10000_9999.txt >> tvdsu.txt
	./a.out 10000_30000.txt >> tvdsu.txt
	./a.out 10000_50000.txt >> tvdsu.txt
	./a.out 10000_70000.txt >> tvdsu.txt
	./a.out 100000_99999.txt >> tvdsu.txt
	./a.out 100000_300000.txt >> tvdsu.txt
	./a.out 100000_500000.txt >> tvdsu.txt
	./a.out 100000_700000.txt >> tvdsu.txt
	
run1:
	python3 graph_generator.py $(ARGS1)
	
run2:
	python3 graph_generator.py $(ARGS2)
	
run3:
	python3 graph_generator.py $(ARGS3)
	
run4:
	python3 graph_generator.py $(ARGS4)
	
run5:
	python3 graph_generator.py $(ARGS5)
	
run6:
	python3 graph_generator.py $(ARGS6)
	
run7:
	python3 graph_generator.py $(ARGS7)
	
run8:
	python3 graph_generator.py $(ARGS8)
	
run9:
	python3 graph_generator.py $(ARGS9)
	
run10:
	python3 graph_generator.py $(ARGS10)
	
run11:
	python3 graph_generator.py $(ARGS11)
	
run12:
	python3 graph_generator.py $(ARGS12)
	
run13:
	python3 graph_generator.py $(ARGS13)
	
run14:
	python3 graph_generator.py $(ARGS14)
	
run15:
	python3 graph_generator.py $(ARGS15)
	
run16:
	python3 graph_generator.py $(ARGS16)
	
run17:
	python3 graph_generator.py $(ARGS17)
	
run18:
	python3 graph_generator.py $(ARGS18)
	
run19:
	python3 graph_generator.py $(ARGS19)
	
run20:
	python3 graph_generator.py $(ARGS20)
	
	
.PHONY: clean
	
clean:
		rm -f $(TARGET) $(OBJECTS)