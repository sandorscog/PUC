#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <utility>
#include<iomanip>

class Grafo{
private:
  int tam;
  std::vector<std::pair<double, double>> pos;
  std::vector<std::vector<double>> matrix;
public:
  Grafo(int v){
    tam = v;
    pos.resize(tam);
    matrix.resize(tam);
    for(int i = 0; i < tam; i++){
      matrix.at(i).resize(tam);
    }
  }

  std::vector<std::vector<double>> getMatrix(){
    return matrix;
  }

  void adiconaPosicao(int n, double x, double y){
    pos.at(n).first = x;
    pos.at(n).second = y;
  }

  void criaArestas(){
    for(int i = 0; i < tam; i++){
      for(int j = 0; j < tam; j++){
        double peso = sqrt(pow(pos.at(i).first - pos.at(j).first, 2) + pow(pos.at(i).second - pos.at(j).second, 2));
        matrix.at(i).at(j) = peso;
        matrix.at(j).at(i) = peso;
      }
    }

  }//end func

  double agm(){
    double resp = 0;
    auto compare = [](std::pair<int, double> a, std::pair<int, double> b){return a.second > b.second;};
    std::vector<std::pair<int, double>> heap;

    for(int i = 1; i < tam; i++)
      heap.push_back({i, std::numeric_limits<double>::infinity()});

    heap.push_back({0, 0});
    std::make_heap(heap.begin(), heap.end(), compare);

    while(!heap.empty()){

      std::pair<int, double> topo = heap.front();
      //std::cout << topo.second << "*\n";
      heap.at(0) = heap.back();
      heap.pop_back();
      std::make_heap(heap.begin(), heap.end(), compare);

      resp += topo.second;

      for(int i = 0; i < heap.size(); i++){
        double dist = matrix.at(topo.first).at(heap.at(i). first);
        if(dist < heap.at(i).second && dist != 0){
          heap.at(i).second = dist;
          std::make_heap(heap.begin(), heap.end(), compare);
        }
      }

    }
    return resp;
  }
};

int main() {
  int n, c, e;
  std::cin >> c;

  for(int i = 0; i < c; i++){ //numero de casos testados
    std::cin >> n; //num de pessoas

    Grafo graph(n);

    for(int j = 0; j < n; j++){
      double a, b;
      std::cin >> a >> b;
      graph.adiconaPosicao(j, a, b);
    }

    graph.criaArestas();

    std::cout << std::fixed << std::setprecision(2) << graph.agm()/100.0 << "\n\n";
  }// for do num de casos

  return 0;
}
