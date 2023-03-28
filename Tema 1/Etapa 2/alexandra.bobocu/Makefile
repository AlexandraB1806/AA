build:
	gcc -Wall -Wextra floyd_warshall.c test_floyd_warshall.c -o floyd_warshall
	gcc -Wall -Wextra dijkstra.c test_dijkstra.c -o dijkstra
	gcc -Wall -Wextra johnson.c test_johnson.c -o johnson

run-p1:
	./floyd_warshall
run-p2:
	./dijkstra
run-p3:
	./johnson
run-best:
	./johnson

clean:
	rm -f floyd_warshall
	rm -f dijkstra
	rm -f johnson

.PHONY: clean