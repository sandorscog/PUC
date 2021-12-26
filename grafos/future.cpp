#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <utility>

class Grafo{
private:
  int tam;
  std::vector<std::pair<int, int>> pos;
  std::vector<std::vector<int>> matrix;
public:
  Grafo(int v){
    tam = v;

    matrix.resize(tam);
    for(int i = 0; i < tam; i++){
      matrix.at(i).resize(tam);
    }
  }

  std::vector<std::vector<int>> getMatrix(){
    return matrix;
  }

  void adicionaAresta(int x, int y, int p){
    matrix.at(x).at(y) = p;
    matrix.at(y).at(x) = p;
  }

  static bool compara(std::pair<int, int> a, std::pair<int, int> b){
    return a.second > b.second;
  }

  int dijkstra(){
    int resp = 0;
    std::vector<std::pair<int, int>> heap;
    std::vector<int> caminho;

    for(int i = 1; i < tam; i++)
      heap.push_back({i, std::numeric_limits<int>::max()});

    heap.push_back({0, 0});
    std::make_heap(heap.begin(), heap.end(), compara);

    while(!heap.empty()){
      //std::cout << '\n';
      std::pair<int, int> topo = heap.front();
      //std::cout << topo.first << " - " << topo.second << "\n";

      heap.at(0) = heap.back();
      heap.pop_back();
      std::make_heap(heap.begin(), heap.end(), compara);

      resp += topo.second;
      caminho.push_back(topo.first);

      for(int i = 0; i < heap.size(); i++){
        int dist = matrix.at(topo.first).at(heap.at(i). first);

        if(topo.second + dist < heap.at(i).second && dist != 0){
          if(heap.at(i).first == (tam-1)){
            caminho.push_back(tam-1);

            for(int k = 1; k < caminho.size(); k++){
              //std::cout << "k = " << k << "- k-1 = " << k-1 << '\n';
              int u = caminho.at(k-1);
              int v = caminho.at(k);
              matrix.at(v).at(u) = 0;
              matrix.at(u).at(v) = 0;
            }
            return resp + dist;
          }

          heap.at(i).second = dist + topo.second;
          //std::cout << heap.at(i).second << " pou" << '\n';
          std::make_heap(heap.begin(), heap.end(), compara);
        }
      }
    }//while

    return -1;
  }//end func

};

int main() {
  int n, m, a, b, c, d, k;

  for(int i = 0; i < 3; i++){ //numero de casos testados
    std::cout << "Instancia " << i+1 << "\n\n";

    std::cin >> n >> m; //num de pessoas

    Grafo graph(n);

    for(int j = 0; j < m; j++){
      std::cin >> a >> b >> c;
      graph.adicionaAresta((a-1), (b-1), c);
    }

    std::cin >> d >> k;

    int custo = 0;
    int taxa = d/(std::ceil(static_cast<double>(d)/k));
    for(int r = 0; r < std::ceil(static_cast<double>(d)/k); r++){
      custo += graph.dijkstra();
    }

    if(custo*taxa > 0)
      std::cout << custo*taxa << "\n\n\n\n";
    else
      std::cout << "impossivel\n\n";
  }// for do num de casos

  return 0;
}


//debug
/*std::cout << "\n";
for (int k = 0; k < n; k++) {
  for (int h = 0; h < n; h++) {
    std::cout << graph.getMatrix().at(k).at(h) << " ";
  }
  std::cout << "\n";
}*/
