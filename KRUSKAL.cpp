#include <iostream>
#include <vector>
#include <tuple>
#include <map>
#include <algorithm>
using namespace std;

struct DSU {
    map<char, char> parent;

    char find(char x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];}

    void unite(char x, char y) {
        parent[find(x)] = find(y);}

    void add(char x) {
        if (!parent.count(x)) parent[x] = x;}};

int main() {
    int numAristas;
    cout << "¿Cuántas aristas tiene el grafo? ";
    cin >> numAristas;

    vector<tuple<int, char, char>> aristas;
    DSU dsu;

    cout << "Ingresa las aristas en formato: A 5 L" << endl;
    for (int i = 0; i < numAristas; ++i) {
        char u, v;
        int w;
        cin >> u >> w >> v;
        aristas.push_back({w, u, v});
        dsu.add(u);
        dsu.add(v);}

    sort(aristas.begin(), aristas.end());

    cout << "\nÁrbol de Expansión Mínima (Kruskal):\n";
    for (auto [peso, u, v] : aristas) {
        if (dsu.find(u) != dsu.find(v)) {
            dsu.unite(u, v);
            cout << u << " " << peso << " " << v << endl;}}
    return 0;}
