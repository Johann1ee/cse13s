#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <getopt.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define HELPMESSAGE                                                                                \
    "Usage: tsp [options]\n\n"                                                                     \
    "-i infile    Specify the input file path containing the cities and edges\n"                   \
    "             of a graph. If not specified, the default input should be\n"                     \
    "             set as stdin.\n\n"                                                               \
    "-o outfile   Specify the output file path to print to. If not specified,\n"                   \
    "	     the default output should be set as stdout.\n\n"                                        \
    "-d	     Specifies the graph to be directed.\n\n"                                              \
    "-h	     Prints out a help message describing the purpose of the\n"                            \
    "	     graph and the command-line options it accepts, exiting the\n"                           \
    "	     program afterwards.\n"

void dfs(Graph *g, Path *p, Path *f, uint32_t vertex, uint32_t starter, uint32_t *min_dist) {
    graph_visit_vertex(g, vertex);
    path_add(p, vertex, g);
    if (path_vertices(p) == graph_vertices(g)) {
        if (graph_get_weight(g, vertex, starter) != 0) {
            path_add(p, starter, g);
            uint32_t curr_dist = path_distance(p);

            if (curr_dist < *min_dist) {
                *min_dist = curr_dist;
                path_copy(f, p);
            }
        }
    } else {
        for (uint32_t i = 0; i < graph_vertices(g); i++) {
            if (graph_get_weight(g, vertex, i) != 0 && !graph_visited(g, i)) {
                dfs(g, p, f, i, starter, min_dist);
            }
        }
    }
    path_remove(p, g);
    graph_unvisit_vertex(g, vertex);
}

int main(int argc, char *argv[]) {
    int opt;
    bool directed = false;
    FILE *infile = stdin;
    FILE *outfile = stdout;
    Graph *theGraph;

    while ((opt = getopt(argc, argv, "dhi:o:")) != -1) {
        switch (opt) {
        case 'h': printf(HELPMESSAGE); return 0;
        case 'd': directed = true; break;
        case 'i':
            infile = fopen(optarg, "r");
            if (infile == NULL) {
                fprintf(stderr, "tsp:  error reading input file %s\n", optarg);
                printf(HELPMESSAGE);
                exit(1);
            }

            uint32_t vertex, edge;
            fscanf(infile, "%u\n", &vertex);
            theGraph = graph_create(vertex, directed);

            for (uint32_t i = 0; i < vertex; i++) {
                char name[PATH_MAX];

                if (fgets(name, sizeof(name), infile) == NULL) {
                    break;
                }

                size_t length = strlen(name);
                if (length > 0 && name[length - 1] == '\n') {
                    name[length - 1] = '\0';
                }

                graph_add_vertex(theGraph, name, i);
            }

            fscanf(infile, "%u", &edge);
            for (uint32_t i = 0; i < edge; i++) {
                uint32_t start, end, weight;
                fscanf(infile, "%u %u %u", &start, &end, &weight);
                graph_add_edge(theGraph, start, end, weight);
            }

            if (infile != stdin)
                fclose(infile);

            break;
        case 'o':
            outfile = fopen(optarg, "w");
            if (outfile == NULL) {
                fprintf(stderr, "tsp:  error reading input file %s\n", optarg);
                printf(HELPMESSAGE);
                exit(1);
            }
            break;
        }
    }
    Path *tempPath = path_create(graph_vertices(theGraph));
    Path *finalPath = path_create(graph_vertices(theGraph));

    uint32_t min_dist = UINT32_MAX;
    dfs(theGraph, tempPath, finalPath, START_VERTEX, START_VERTEX, &min_dist);

    if (path_distance(finalPath) != 0) {
        fprintf(outfile, "Alissa starts at:\n");
        path_print(finalPath, outfile, theGraph);
        fprintf(outfile, "%s\nTotal Distance: %u\n", graph_get_vertex_name(theGraph, START_VERTEX),
            path_distance(finalPath));
    } else {
        fprintf(outfile, "No path found! Alissa is lost!\n");
    }
    if (outfile != stdout)
        fclose(outfile);

    path_free(&tempPath);
    path_free(&finalPath);
    graph_free(&theGraph);

    return 0;
}
