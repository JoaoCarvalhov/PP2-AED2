#include <iostream>
#include <vector>
#include <list>
#include <limits>

// implementação do algoritmo BFS(busca em largura em grafos)
// problema: em um tabuleiro de xadrez com 4 cavalos e 1 rei
// encontrar a menor quantidade de movimentos de um cavalo
// até alcançar o rei.

const float inf = std::numeric_limits<float>::infinity();

using namespace std;

class Vertex
{
public:
    int index;
    char col;
    int row;
    int cor; // 0 branco 1 cinza 2 preto
    float d;
    Vertex *pi;

    Vertex(int idx, char c, int r, int cor, float d, Vertex *pi) : index(idx), col(c), row(r), cor(cor), d(d), pi(pi) {}
    Vertex(int index) : index(index) {}
};

template <typename T>
class Graph
{
public:
    vector<list<T>> adjacencyList;

    Graph(unsigned int size) : adjacencyList(size) {}

    void addEdge(const Vertex &u, const Vertex &v);
};

template <typename T>
class Queue
{
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
    bool isEmpty() { return list.empty(); }
};


template <typename T>
void Graph<T>::addEdge(const Vertex &u, const Vertex &v)
{
    adjacencyList[u.index].push_back(v);
}

template <typename T>
void createKnightGraph(Graph<T> &graph)
{

    int list1[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int list2[] = {-1, 1, -2, 2, -2, 2, -1, 1};

    for (int row = 1; row <= 8; ++row)
    {
        for (int col = 1; col <= 8; ++col)
        {
            int uIndex = (row - 1) * 8 + col;

            Vertex u(uIndex, 'A' + col - 1, row, 0, inf, nullptr);

            for (int i = 0; i < 8; i += 1)
            {
                int newRow = row + list1[i];
                int newCol = col + list2[i];

                if (newRow >= 1 && newRow <= 8 && newCol >= 1 && newCol <= 8)
                {
                    int vIndex = (newRow - 1) * 8 + newCol;
                    Vertex v(vIndex, 'A' + newCol - 1, newRow, 0, inf, nullptr);
                    graph.addEdge(u, v);
                }
            }
        }
    }
}

template <typename T>
float BFS(Graph<T> &graph, Vertex s, Vertex king)
{
    for (auto &lista : graph.adjacencyList)
    {
        for (auto &vertice : lista)
        {
            vertice.cor = 0;
            vertice.d = inf;
            vertice.pi = nullptr;
        }
    }
    s.cor = 1;
    s.d = 0;
    s.pi = nullptr;
    for (const Vertex &adjKing : graph.adjacencyList[king.index])
    {
        if (s.index == adjKing.index)
        {
            return s.d;
        }
    }
    Queue<Vertex> queue;
    queue.enqueue(s);
    while (!queue.isEmpty())
    {
        Vertex u = queue.dequeue();
        for (Vertex &v : graph.adjacencyList[u.index])
        {
            if (v.cor == 0)
            {
                v.cor = 1;
                v.d = u.d + 1;
                v.pi = &u;
                queue.enqueue(v);
                for (const Vertex &adjKing : graph.adjacencyList[king.index])
                {
                    if (v.index == adjKing.index)
                    {
                        return v.d;
                    }
                }
            }
        }
        u.cor = 2;
    }
    return 0;
}

int getindex(const char letter, const char number)
{
    int col = letter - 32;
    int row = number - '0';
    int index = (row - 1) * 8 + (col - 'A') + 1;
    return index;
}

int main()
{
    Graph<Vertex> Tabuleiro(65);

    createKnightGraph(Tabuleiro);

    int iteracoes;
    cin >> iteracoes;

    char entrada[20];
    float menores_caminhos[64];
    int cont_menores_caminhos = 0;

    for (int i = 0; i < iteracoes; i++)
    {
        int cont = 1;
        int menor_caminho = 64;
        for (int i = 0; i < 10; i++)
        {
            cin >> entrada[i];
        }
        for (int i = 0; i < 8; i += 2)
        {
            int Cavalo = getindex(entrada[i], entrada[i + 1]);
            int Rei = getindex(entrada[8], entrada[9]);

            Vertex cavalo(Cavalo);
            Vertex rei(Rei);
            float movimentos = BFS(Tabuleiro, cavalo, rei);
            if (movimentos < menor_caminho)
            {
                menor_caminho = movimentos;
                cont = 1;
            }
            if (movimentos == menor_caminho){
                cont += 1;
            }
        }
        for (int i = 1; i < cont; i += 1)
        {
            menores_caminhos[cont_menores_caminhos] = menor_caminho;
            cont_menores_caminhos++;
        }
    }
    for (int i = 0; i < cont_menores_caminhos; i++)
    {
        cout << menores_caminhos[i];
    }

    return 0;
}
