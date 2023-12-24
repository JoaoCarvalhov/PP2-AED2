#include <iostream>
#include <vector>
#include <list>
#include <limits>

using namespace std;

const float inf = std::numeric_limits<float>::infinity();

class ItemVertex
{
public:
    char name;
    int d;
    unsigned int color;
    ItemVertex *predecessor;

    // Construtor padrão
    ItemVertex() : name('\0'), d(inf), color(0), predecessor(nullptr) {}

    // Construtor com parâmetros
    ItemVertex(char _name, int _d, unsigned int _color, ItemVertex* _predecessor)
        : name(_name), d(_d), color(_color), predecessor(_predecessor) {}
};

template <typename T>
class Queue {
private:
    std::list<T> list;

public:
    Queue() {}
    void enqueue(T item) { list.push_back(item); }
    T dequeue()
    {
        if (!list.empty())
        {
            T front = list.front();
            list.pop_front();
            return front;
        }
    }
};

template <typename T>
class GraphAL
{
private:
    unsigned int num_vertices;
    unsigned int num_edges;
    list<T> *adj;
    std::list<ItemVertex> allVertices;  // Lista de todos os ItemVertex adicionados

public:
    GraphAL(unsigned int);
    ~GraphAL();
    void add_edge(char u, char v);
    void remove_edge(char u, char v);
    bool vertex_already_exists(char u, char v);
    list<T> get_adj(char v) { return adj[v - 96]; }
    unsigned int get_num_vertices() { return num_vertices; }
    unsigned int get_num_edges() { return num_edges; }
    std::list<ItemVertex> get_all_vertices() { return allVertices; }
};

template <typename T>
GraphAL<T>::GraphAL(unsigned int num_vertices) : num_vertices(num_vertices)
{
    adj = new list<T>[num_vertices];
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
    allVertices.clear();  // Limpar a lista de todos os ItemVertex
}

template <typename T>
void GraphAL<T>::add_edge(char u, char v)
{
    ItemVertex item_Vertex_v{v,  inf, 0, nullptr};
    ItemVertex item_Vertex_u{u,  inf, 0, nullptr};
    if (vertex_already_exists(u, v) == false)
    {
        adj[u - 96].push_back(item_Vertex_v); //u - 96 pq u vai ser a letra
        allVertices.push_back(item_Vertex_v);  // Adicionar a v à lista de todos os ItemVertex
    }
    if (vertex_already_exists(v, u) == false)
    {
        adj[v - 48].push_back(item_Vertex_u);//u - 48 pq u vai ser o numero
        allVertices.push_back(item_Vertex_u);  // Adicionar a u à lista de todos os ItemVertex
    }
    num_edges++;
}

template <typename T>
void GraphAL<T>::remove_edge(char u, char v)
{
    list<ItemVertex> &lista_u = adj[u - 96];
    for (auto itr = lista_u.begin(); itr != lista_u.end(); ++itr)
    {
        if (itr->name == v)
        {
            itr = lista_u.erase(itr);
            break;
        }
    }

    list<ItemVertex> &lista_v = adj[v - 48];
    for (auto itr2 = lista_v.begin(); itr2 != lista_v.end(); ++itr2)
    {
        if (itr2->name == u)
        {
            itr2 = lista_v.erase(itr2);
            break;
        }
    }

    // Remover da lista de todos os ItemVertex ==================ver isso aqui dps pq tem algo dando errado
    /*auto itrAll = std::find_if(allVertices.begin(), allVertices.end(),
                               [&](const ItemVertex &item) { return item.name == u || item.name == v; });
    if (itrAll != allVertices.end())
    {
        allVertices.erase(itrAll);
    }

    num_edges--;*/
}

template <typename T>
bool GraphAL<T>::vertex_already_exists(char u, char v)
{
    list<ItemVertex> &lista_u = adj[u - 96];
    for (auto itr = lista_u.begin(); itr != lista_u.end(); ++itr)
    {
        if (itr->name == v)
        {
            return true;
        }
    }
    return false;
}

template <typename T>
void input_GraphAL(GraphAL<T> &g, unsigned int num_edges)
{
    char u, v;
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
        cout << " (" << item_Vertex.name << ", " << item_Vertex.d << ", " << item_Vertex.color << ") ";
    }
    cout << endl;
}

template <typename T>
void display_GraphAL(GraphAL<T> &g)
{
    list<ItemVertex> allVertices = g.get_all_vertices();
    for (auto vertex : allVertices){
        cout << vertex.name << ": ";
        list<T> lst = g.get_adj(vertex.name);
        display_list(lst);
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

    display_GraphAL(g);
    return 0;
}
