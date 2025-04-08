/*parcurgerge  graf cu DFS/BFS*/

// Imi cer scuze in avans

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
struct Node {
    int vertex_id;
    Node *next;
};

typedef struct {
    //  G = (V, E)
    // A graph G is a pair of sets V and E, where V is the set of vertices
    // and E is the set of edges.
    int vertices;  // number of vertices in set V of graph G
    bool *visited; // (v[i] == true) means node i has been visited by the DFS
    Node **adj;    // adj[u] is a pointer to the first Node in vertex u's
                   // adjacency list
} Graph;

/// utils
Node *create_Node(int v) {
    Node *new_Node = malloc(sizeof(Node));
    new_Node->vertex_id = v;
    new_Node->next = NULL;

    return new_Node;
}

Graph *create_graph(int vertices) {
    Graph *graph = malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->adj = malloc((vertices + 1) * sizeof(Node *));
    graph->visited = malloc((vertices + 1) * sizeof(int));

    for (int i = 1; i <= graph->vertices; i += 1) {
        graph->adj[i] = NULL;
        graph->visited[i] = false;
    }

    return graph;
}

void add_edge(Graph *graph, int src, int dest) {
    Node *new_Node = create_Node(dest);
    new_Node->next = graph->adj[src];
    graph->adj[src] = new_Node;

    new_Node = create_Node(src);
    new_Node->next = graph->adj[dest];
    graph->adj[dest] = new_Node;
}

void insert_edges(Graph *graph, int edges) {
    printf("adauga %d muchii (de la 1 la %d)\n", edges, graph->vertices);
    for (int i = 0; i < edges; i++) {
        int src, dest;
        scanf("%d%d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

/// bfs utils
int is_empty(Node *queue) {
    return queue == NULL;
}

void enqueue(Node **queue, int data) {
    Node *new_Node = create_Node(data);

    if (is_empty(*queue)) {
        *queue = new_Node;
    } else {
        Node *temp;
        for (temp = *queue; temp->next != NULL; temp = temp->next) {}
        temp->next = new_Node;
    }
}

int dequeue(Node **queue) {
    int vertex_id = (*queue)->vertex_id;
    Node *temp = *queue;
    *queue = (*queue)->next;

    return vertex_id;
}

void print_graph(Graph *graph) {
    for (int i = 1; i <= graph->vertices; i += 1) {
        for (Node *temp = graph->adj[i]; temp != NULL;
             temp = temp->next) {
            printf("%d ", temp->vertex_id);
        }
        printf("\n");
    }
}

void print_queue(Node *queue) {
    for (; queue != NULL; queue = queue->next) {
        printf("%d ", queue->vertex_id);
    }
}

void wipe_visited_list(Graph *graph) {
    for (int i = 1; i <= graph->vertices; i += 1) {
        graph->visited[i] = false;
    }
}

// parcurgeri
void dfs(Graph *graph, int vertex_nr) {
    graph->visited[vertex_nr] = true;
    printf("%d->", vertex_nr);

    for (Node *curr = graph->adj[vertex_nr]; curr != NULL;
         curr = curr->next) {
        if (!graph->visited[curr->vertex_id]) dfs(graph, curr->vertex_id);
    }
}

void bfs(Graph *graph, int start) {
    Node *queue = NULL;

    graph->visited[start] = 1;
    enqueue(&queue, start);

    while (!is_empty(queue)) {
        int current = dequeue(&queue);
        printf("%d ", current);

        for (Node *temp = graph->adj[current]; temp != NULL;
             temp = temp->next) {
            int adj_vertex = temp->vertex_id;
            if (graph->visited[adj_vertex] == 0) {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
        }
    }
}

int main() {

    int vertices;
    int edges;
    int src, dest;

    int starting_vertex;
    printf("Cîte noduri are graful? ");
    scanf("%d", &vertices);
    printf("Cîte muchii are graful? ");
    scanf("%d", &edges);
    Graph *graph = create_graph(vertices);
    insert_edges(graph, edges);
    printf("de unde plecam in DFS? ");
    scanf("%d", &starting_vertex); // =)))
    printf("parcurgere cu DFS: ");
    dfs(graph, starting_vertex);
    wipe_visited_list(graph);
    printf("\n");
    printf("de unde plecam in BFS? ");
    scanf("%d", &starting_vertex);
    printf("parcurgere cu BFS: ");
    bfs(graph, starting_vertex);

    return 0;
}
