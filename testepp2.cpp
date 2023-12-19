#include <iostream>
#include <vector>
#include <list>
#include <limits>
using namespace std;
const float inf = std::numeric_limits<float>::infinity();

typedef char Vertex;

template <typename T>
class No {
public:
    T valor;
    No<T>* proximo;

    No(T v) : valor(v), proximo(nullptr) {}
};

template <typename T>
class Fila {
public:
    No<T>* inicio;
    No<T>* fim;
    Fila() : inicio(nullptr), fim(nullptr) {}
    void destruirFila();
    bool enfileirar(T novo_valor);
    No<T>* desenfileirar();
    void imprimeFila();
};

class ItemVertex
{
public:
    Vertex value;
    int d;
    unsigned int visita;
    ItemVertex *predecessor;
    ItemVertex() {}
    ItemVertex(char value) : value(value){};
};

template <typename T>
class GraphAL
{
private:
    unsigned int num_vertices;
    unsigned int num_edges;
    list<T> *adj;

public:
    GraphAL(unsigned int);
    ~GraphAL();
    void add_edge(Vertex, Vertex);
    void remove_edge(Vertex, Vertex);
    bool vertex_already_exists(Vertex u, Vertex v);
    list<T> get_adj(Vertex v) { return adj[v]; }
    unsigned int get_num_vertices() { return num_vertices; }
    unsigned int get_num_edges() { return num_edges; }
};

template <typename T>
void Fila<T>::destruirFila() {
        No<T>* apagar;
        No<T>* i = inicio;
        while (i != nullptr) {
            apagar = i;
            i = i->proximo;
            delete apagar;
        }
}

template <typename T>
bool Fila<T>::enfileirar(T novo_valor) {
        No<T>* i = new No<T>(novo_valor);
        if (i == nullptr) {
            return false;
        }
        i->valor = novo_valor;
        i->proximo = nullptr;
        if (inicio == nullptr) {
            inicio = i;
        } else {
            fim->proximo = i;
        }
        fim = i;
        return true;
    }

template <typename T>
No<T>* Fila<T>::desenfileirar() {
        if (inicio == nullptr) {
            return nullptr;
        }
        No<T>* i = inicio;
        inicio = inicio->proximo;
        return i;
    }

template <typename T>
void Fila<T>::imprimeFila() {
        No<T>* i = inicio;
        while (i != nullptr) {
            std::cout << " " << i->valor << " ";
            std::cout << std::endl;
            i = i->proximo;
        }
}

template <typename T>
GraphAL<T>::GraphAL(unsigned int num_vertices) : num_vertices(num_vertices)
{
    adj = new list<ItemVertex>[num_vertices];
}

template <typename T>
GraphAL<T>::~GraphAL()
{
    for (unsigned int u = 0; u < num_vertices; ++u)
    {
        adj[u].clear();
    }
    delete[] adj;
    adj = nullptr;
    num_edges = 0;
    num_vertices = 0;
}

template <typename T>
void GraphAL<T>::add_edge(Vertex u, Vertex v)
{
    ItemVertex item_Vertex_v{v};
    ItemVertex item_Vertex_u{u};
    if (vertex_already_exists(u, v) == false)
    {
        adj[u].push_back(item_Vertex_v);
    }
    if (vertex_already_exists(v, u) == false)
    {
        adj[v].push_back(item_Vertex_u);
    }
    num_edges++;
}

template <typename T>
void GraphAL<T>::remove_edge(Vertex u, Vertex v)
{
    ItemVertex item_Vertex_v{v};
    ItemVertex item_Vertex_u{u};
    list<ItemVertex> &lista_u = adj[u];
    for (auto itr = lista_u.begin(); itr != lista_u.end(); ++itr)
    {
        if (itr->value == item_Vertex_v.value)
        {
            itr = lista_u.erase(itr);
        }
    }
    list<ItemVertex> &lista_v = adj[v];
    for (auto itr2 = lista_v.begin(); itr2 != lista_v.end(); ++itr2)
    {
        if (itr2->value == item_Vertex_u.value)
        {
            itr2 = lista_v.erase(itr2);
        }
    }
    num_edges--;
}
template <typename T>
bool GraphAL<T>::vertex_already_exists(Vertex u, Vertex v)
{
    ItemVertex item_Vertex_u{u};
    ItemVertex item_Vertex_v{v};
    list<ItemVertex> &lista_u = adj[u];
    for (auto itr = lista_u.begin(); itr != lista_u.end(); ++itr)
    {
        if (itr->value == item_Vertex_v.value)
        {
            return true;
        }
    }
    return false;
}

template <typename T>
void input_GraphAL(GraphAL<T> &g, unsigned int num_edges)
{
    Vertex u = 0;
    Vertex v = 0;
    for (unsigned int i = 0; i < num_edges; ++i)
    {
        cin >> u >> v;
        g.add_edge(u, v);
    }
}

template <typename T>
void display_list(list<T> &lst)
{
    for (auto item_Vertex : lst)
    {
        cout << " (" << item_Vertex.value << ", "<< item_Vertex.d << ", "<< item_Vertex.visita << ") ";
    }
    cout << endl;
}

template <typename T>
void display_GraphAL(GraphAL<T> &g)
{
    for (unsigned int v = 0; v < g.get_num_vertices(); v++)
    {
        cout << v << ": ";
        list<T> lst = g.get_adj(v);
        display_list(lst);
    }
}

template <typename T>
void BFS(GraphAL<T> &g, Vertex s){
    //percorre cada vertice de g
    ItemVertex item_Vertex_s{s};
    for (unsigned int v = 0; v < g.get_num_vertices(); v++)
    {
        list<T> lst = g.get_adj(v);
        for (auto item_Vertex : lst)
        {
            if(item_Vertex.value != item_Vertex_s.value){
                item_Vertex.visita = 0;
                item_Vertex.d = inf;
                item_Vertex.predecessor = nullptr;
            }
        }
    }
    item_Vertex_s.visita = 1;
    item_Vertex_s.d = 0;
    item_Vertex_s.predecessor = nullptr;
    Fila<T> fila;
    fila.enfileirar(item_Vertex_s);
    ItemVertex item_Vertex_u{};
    while (fila.inicio != nullptr){
        No<T>* teste = fila.desenfileirar();
        item_Vertex_u = teste->valor; 
        delete teste;
        list<T> adju = g.get_adj(item_Vertex_u.value); //pq value é vertex
        for (auto v : adju)
        {
            if(v.visita == 0){
                v.visita = 1;
                v.d = item_Vertex_u.d + 1;
                v.predecessor = &item_Vertex_u;
                fila.enfileirar(v);
            }
        }
        item_Vertex_u.visita = 2;
    }
}

int main()
{
    unsigned int num_vertices = 0;
    unsigned int num_edges = 0;
    cin >> num_vertices >> num_edges;
    cout << "num_vertices: " << num_vertices << endl;
    cout << "num_edges: " << num_edges << endl;
    GraphAL<ItemVertex> g{num_vertices};
    input_GraphAL(g, num_edges);
    Vertex s;
    BFS(g, s);
    display_GraphAL(g);
    return 0;
}