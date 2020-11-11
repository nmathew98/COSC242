/* graph-skel.c */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"
#include "mylib.h"
#include "queue.h"

typedef struct vertexrec vertex;

typedef enum state {UNVISITED, VISITED_SELF, VISITED_DESCENDANTS} state_t;

struct vertexrec {
	int distance;
	int finish;
	int predecessor;
	state_t state;
};

struct graphrec {
	int size;
	int **edges;
	vertex *vertices;
};

static int step = 0;

graph graph_new(int vertices) {
	int i;
	int j;
	graph g = emalloc(sizeof *g);
	g->edges = emalloc(sizeof(int *) * vertices);
	for (i = 0; i < vertices; i++) {
		g->edges[i] = emalloc(sizeof(int) * vertices);
		for (j = 0; j < vertices; j++) {
			g->edges[i][j] = 0;
		}
	}
	g->size = vertices;
	g->vertices = emalloc(sizeof (vertex) * vertices);
	return g;
}

void graph_add_edge(graph g, int u, int v) {
	g->edges[u][v] = 1;
}

void graph_add_2edges(graph g, int u, int v) {
	g->edges[u][v] = g->edges[v][u] = 1;
}

graph graph_free(graph g) {
	int i;
	free(g->vertices);
	for (i = 0; i < g->size; i++) {
		free(g->edges[i]);
	}
	free(g->edges);
	free(g);

	return g;
}

void graph_print_list(graph g) {
	int flag;
	int i;
	int j;
	printf("Adjacency List:\n");
	for (i = 0; i < g->size; i++) {
		printf("%d | ", i);
		flag = 0;
		for (j = 0; j < g->size; j++) {
			if (g->edges[i][j]) {
				if (flag) printf(", ");
				printf("%d", j);
			}
			if (g->edges[i][j]) flag = 1;
		}
		printf("\n");
	}
	printf("\n");
	printf("Vertex\tDistance\tPredecessor\tFinish\n");
	for (i = 0; i < g->size; i++) {
		printf("%5d\t%5d\t%5d\t%5d\n", i, g->vertices[i].distance,
             g->vertices[i].predecessor, g->vertices[i].finish);
	}
}

void graph_print_state(graph g) { 
	int i;
	for (i = 0; i < g->size; i++) {
		if(g->vertices[i].state == UNVISITED) printf("UNVISITED\n");
		if(g->vertices[i].state == VISITED_SELF) printf("VISITED_SELF\n");
		if(g->vertices[i].state == VISITED_DESCENDANTS) printf("VISITED_DESCENDANTS\n");
	}
}

/* Either Breadth-first Search (e) */
void graph_bfs(graph g, int source) { /* source = vertex we find distances from */
	int_queue q = int_queue_new();
	vertex u;
	int i;

	for (i = 0; i < g->size; i++) {
		g->vertices[i].state = UNVISITED;
		g->vertices[i].distance = -1;
		g->vertices[i].predecessor = -1;
	}

	g->vertices[source].state = VISITED_SELF;
	g->vertices[source].distance = 0;
	int_enqueue(q, source);
	while (int_queue_size(q)) {
		source = int_dequeue(q);
		u = g->vertices[source];
		for (i = 0; i < g->size; i++) {
			if (g->edges[source][i]) {
				if (g->vertices[i].state == UNVISITED) {
					g->vertices[i].state = VISITED_SELF;
					g->vertices[i].distance = u.distance + 1;
					g->vertices[i].predecessor = source;
					int_enqueue(q, i);
				}
			}
		}
		u.state = VISITED_DESCENDANTS;
	}
	int_queue_free(q);
}

/* Or Depth-first search (f) */
void graph_dfs(graph g) {
	int i;
	for (i = 0; i < g->size; i++) {
		g->vertices[i].state = UNVISITED;
		g->vertices[i].predecessor = -1;
	}
	step = 0;
	for (i = 0; i < g->size; i++) {
		if (g->vertices[i].state == UNVISITED) {
			visit(g, 1);
		}
	}
}

void visit(graph g, int source) {
	int i;

	g->vertices[source].state = VISITED_SELF;
	step++;
	g->vertices[source].distance = step;

	for (i = 0; i < g->size; i++) {
		if (g->edges[source][i]) {
			if (g->vertices[i].state == UNVISITED) {
				g->vertices[i].predecessor = source;
				visit(g, i);
			}
		}
	}

	step++;

	g->vertices[source].state = VISITED_DESCENDANTS;
	g->vertices[source].finish = step;
}
