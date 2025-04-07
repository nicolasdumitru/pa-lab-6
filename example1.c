// Determinati daca exista sau nu drum direct intre doua
// restaurante dintr-o retea de tip graf

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node Node;
struct Node {
    int vertex_id;
    Node *next;
};
/// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
/// ex: 1 - restaurantul 1 si tot asa

typedef struct Graph Graph;
struct Graph {
    //  G = (V, E)
    // A graph G is a pair of sets V and E, where V is the set of vertices
    // and E is the set of edges.
    int vertices;  // number of vertices in set V of graph G
    bool *visited; // (v[i] == true) means node i has been visited by the DFS
    Node **adj;    // adj[u] is a pointer to the first Node in vertex u's
                   // adjacency list
};

Graph *create_g(const int vertices) { // pseudo-constructor
    Graph *g = malloc(sizeof(Graph));
    if (g == NULL) {
        fprintf(stderr, "eroare alocare\n");
        exit(1);
    }
    g->vertices = vertices;
    g->adj = malloc((vertices + 1) * sizeof(Node *));
    g->visited = malloc((vertices + 1) * sizeof(int));

    for (int i = 1; i <= vertices; i += 1) {
        g->visited[i] = false;
        g->adj[i] = NULL;
    }
    return g;
}

Node *create_node(const int vertex_id, Node *const next) {
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "eroare alocare\n");
        exit(1);
    }
    new_node->vertex_id = vertex_id;
    new_node->next = next;
    return new_node;
}

// This function creates the undirected edge (u, w) in graph G.
// Parameter g is a pointer to the stucture that represents graph G.
// Parameters id_u and id_w are the ids of nodes u and w respectively.
void add_edge(Graph *g, int id_u, int id_w) {
    g->adj[id_u] = create_node(id_w, g->adj[id_u]);
    g->adj[id_w] = create_node(id_u, g->adj[id_w]);
}

typedef struct {
    int height;
    int *data;
} Stack;

Stack *Stack_new(int capacity) { // pseudo-constructor
    Stack *s = malloc(sizeof(Stack));
    s->height = 0;
    s->data = malloc(capacity * sizeof(int));

    return s;
}

void Stack_push(Stack *s, int val) {
    s->data[s->height] = val;
    s->height = s->height + 1;
}

// Depth First Search
void dfs(Graph *const g, Stack *const s, const int vertex_id) {
    Stack_push(s, vertex_id);

    g->visited[vertex_id] = true;

    for (Node *curr = g->adj[vertex_id]; curr != NULL; curr = curr->next) {
        int id = curr->vertex_id;
        if (!g->visited[id]) dfs(g, s, id);
    }
}

void insert_edges(Graph *g, int edges) {
    printf("adauga %d muchii (de la 1 la %d)\n", edges, g->vertices);
    for (int i = 0; i < edges; i += 1) {
        int id_u, id_w;
        scanf("%d%d", &id_u, &id_w);
        add_edge(g, id_u, id_w);
    }
}

void wipe(Graph *g) {
    for (int i = 1; i <= g->vertices; i += 1) {
        g->visited[i] = false;
    }
}

void dfs_drumuri_directe(Graph *g, Stack *s1, Stack *s2) {
    int *ans = calloc(g->vertices, sizeof(int));
    if (ans == NULL) {
        fprintf(stderr, "eroare de alocare\n");
        exit(1);
    }
    for (int i = 1; i <= g->vertices; i += 1) {
        for (int j = 1; j <= g->vertices; j += 1) {
            s1->height = 0; // Era mai usor sa nu uitam sa facem asta pentru a
                            // evita erori de memorie daca incapsulam stiva si
                            // cod si mai clean.
            dfs(g, s1, i);

            wipe(g);

            s2->height = 0;
            dfs(g, s2, j);

            for (int j = 1; j <= g->vertices; j += 1) {
                for (int i = 1; i <= g->vertices; i += 1) {
                    if ((s1->data[i - 1] == j) && (s2->data[j - 1] == i)) {
                        ans[i] = true;
                    }
                }
            }
        }
    }
}

int main() {
    int vertices;
    int edges;
    bool ans;

    printf("Cîte noduri are graful? ");
    scanf("%d", &vertices);

    printf("Cîte muchii are graful? ");
    scanf("%d", &edges);

    Graph *g = create_g(vertices);
    Stack *s1 = Stack_new(2 * vertices);
    Stack *s2 = Stack_new(2 * vertices);

    insert_edges(g, edges);

    dfs_drumuri_directe(g, s1, s2);

    printf("Nu se știe ce e un \"drum direct\", dar parcurgerea DFS merge și "
           "avem clean code, așa cum s-a cerut.");

    return 0;
}
