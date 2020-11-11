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
    int i, j;
    graph g = emalloc(sizeof *g);
    g->size = vertices;
    g->edges = emalloc(g->size * sizeof g->edges[0]);
    g->vertices = emalloc(g->size * sizeof g->vertices[0]);

    for (i = 0; i < g->size; i++) {
        g->edges[i] = emalloc(g->size * sizeof g->edges[i][0]);
        g->vertices[i].state = UNVISITED;

        for (j = 0; j < g->size; j++) {
            g->edges[i][j] = 0;
        }
    }
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
    int node, neighbour, count;

    printf("adjacency list:\n");
    for (node = 0; node < g->size; node++) {
        count = 0;
        printf("%d | ", node);

        for (neighbour = 0; neighbour < g->size; neighbour++) {
            if (g->edges[node][neighbour] == 1) {
                if (count > 0) {
                    printf(", %d", neighbour);
                    count++;
                } else {
                    printf("%d", neighbour);
                    count++;
                }
            }
        }
        printf("\n");
    }

    printf("vertex distance pred\n");
    for (node = 0; node < g->size; node++) {
        printf("%5d %6d %6d\n", node, g->vertices[node].distance, g->vertices[node].predecessor);
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
    int i, u, v;
    queue q = queue_new(g->size);

    for (i = 0; i < g->size; i++) {
        g->vertices[i].state = UNVISITED;
        g->vertices[i].distance = -1;
        g->vertices[i].predecessor = -1;
    }

    g->vertices[source].state = VISITED_SELF;
    g->vertices[source].distance = 0;
    enqueue(q, source);

    while(queue_size(q) != 0) {
        u = dequeue(q);

        for (v = 0; v < g->size; v++) {
            if ((g->edges[u][v] == 1) && (g->vertices[v].state == UNVISITED)) {
                g->vertices[v].state = VISITED_SELF;
                g->vertices[v].distance = 1 + g->vertices[u].distance;
                g->vertices[v].predecessor = u;

                enqueue(q, v);
            }
        }
        g->vertices[u].state = VISITED_DESCENDANTS;
    }
    queue_free(q);
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
