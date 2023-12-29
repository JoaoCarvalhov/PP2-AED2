#include <iostream>
#include <vector>
#include <list>
#include <limits>

const float inf = std::numeric_limits<float>::infinity();

using namespace std;

class Vertex {
public:
    
    int index;
    char col;
    int row;

    int cor; //0 branco 1 cinza 2 preto
    float d;
    Vertex* pi;

    Vertex(int idx, char c, int r, int cor, float d, Vertex* pi) : index(idx), col(c), row(r), cor(cor), d(d), pi(pi) {}
    Vertex(int index) :  index(index){}
};

class Graph {
public:
    vector<list<Vertex>> adjacencyList;

    Graph(int size) : adjacencyList(size) {}

    void addEdge(const Vertex& u, const Vertex& v) {
        adjacencyList[u.index].push_back(v);
    }
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
    bool isEmpty(){ return list.empty(); }
};

void createKnightGraph(Graph& graph) {

    int lista1[]= {-2, -2, -1, -1, 1, 1, 2, 2};
    int lista2[]= {-1, 1, -2, 2,-2, 2, -1 , 1};

    for (int row = 1; row <= 8; ++row) {
        for (int col = 1; col <= 8; ++col) {
            int uIndex = (row - 1) * 8 + col;

            Vertex u(uIndex, 'A' + col - 1, row, 0, inf,nullptr);
            
            for (int i = 0; i < 8 ; i+=1) {
                int newRow = row + lista1[i];
                int newCol = col + lista2[i];

                if (newRow >= 1 && newRow <= 8 && newCol >= 1 && newCol <= 8) {
                    int vIndex = (newRow - 1) * 8 + newCol;
                    Vertex v(vIndex, 'A' + newCol - 1, newRow,0,inf,nullptr);
                    graph.addEdge(u, v);
                }
            }
        }
    }
}

float BFS(Graph& graph, Vertex s, Vertex rei){
        for (auto& lista : graph.adjacencyList) {
            //cout << "a";
            for (auto& vertice : lista) {
                vertice.cor = 0;
                vertice.d = inf;
                vertice.pi = nullptr;
            }
        }
    s.cor = 1;
    s.d = 0;
    s.pi = nullptr;
    for (const Vertex& adjVertex : graph.adjacencyList[rei.index]) {
        if (s.index == adjVertex.index) {
            return s.d;
        }
    }
    Queue<Vertex> queue;
    queue.enqueue(s);
    while (!queue.isEmpty()) {
        Vertex u = queue.dequeue();
        for (Vertex& v : graph.adjacencyList[u.index]) {
            if (v.cor == 0) {
                v.cor = 1;
                v.d = u.d + 1;
                v.pi = &u;
                queue.enqueue(v);
                for (const Vertex& adjVertex : graph.adjacencyList[rei.index]) {
                    if (v.index == adjVertex.index) {
                        return v.d;
                    }
                }
            }
        }
        u.cor = 2;
    }
    return 0;
}

int getindex(const Graph& graph, const char Letra,const char Numero) {

    char col = Letra;
    col &= ~' ';
    
    int row = Numero - '0';
    
    int index = (row - 1) * 8 + (col - 'A') + 1;
    return index;
}

int main() {
    Graph knightGraph(65);  

    createKnightGraph(knightGraph);

    int vezes;
    cin >> vezes;


    for (int i = 0; i < vezes; i++) {
        int cont = 1;
        int menor_caminho = 64;
        char entrada[20];
        for (int i = 0; i < 10; i++) {
            cin >> entrada[i];
        }
    
        for (int i = 0; i < 8; i += 2) { 
            int Cavalo = getindex(knightGraph, entrada[i], entrada[i + 1]);
            int Rei = getindex(knightGraph, entrada[8], entrada[9]);
            
            Vertex cavalo(Cavalo);
            Vertex rei(Rei);
            float movimentos = BFS(knightGraph, cavalo, rei);
            if(movimentos < menor_caminho ){
                menor_caminho = movimentos;
                cont = 1;
            }
            if(movimentos == menor_caminho)
                cont += 1;
            
        }
        for (int i = 1; i < cont; i += 1) {
            cout << menor_caminho<< " ";
        }
        cout << endl;
    }

    return 0;
}

