#include <iostream>
#include <vector>

class Grafo{
private:
  int tam;
  std::vector<std::vector<int>> matrix;
  std::vector<int> color;
public:
  Grafo(int v){
    tam = v;
    color.resize(tam);
    matrix.resize(tam);
    for(int i = 0; i < tam; i++){
      matrix.at(i).resize(tam);
    }
  }

  std::vector<std::vector<int>> getMatrix(){
    return matrix;
  }

  std::vector<int> &getColor(){
    return color;
  }

  enum class Cor{
    branco,
    cinza,
    preto
  };

  void criarAresta(int x, int y){
    matrix.at(x).at(y) = 1;
    matrix.at(y).at(x) = 1;
  }

  int busca(){
    std::vector<Cor> cores(tam, Cor::branco);//cria vetor de cores sendo elas brancas

    int count = 0;
    for(int i = 0; i < tam; i++){
      if(cores.at(i) == Cor::branco){
        count++;
        cores = busca(i, cores);
        //std::cout << "aqui ";
      }
    }//for
    return count;
  }

  std::vector<Cor> busca(int i, std::vector<Cor> cores){
    cores.at(i) = Cor::cinza;
    for(int j = 0; j < tam; j++){
      if(matrix.at(i).at(j) == 1){
        if(cores.at(j) == Cor::branco)
          cores = busca(j, cores);
      }
    }//for
    cores.at(i) = Cor::preto;
    return cores;
  }//func

  int novasArestas(int max){
    int resp = 0;
    for(int i = 0; i < tam; i++){
      for(int j = i+1; j < tam; j++){
        if(matrix.at(i).at(j) == 0 && color.at(i) != color.at(j)){
          matrix.at(i).at(j) = 1;
          matrix.at(j).at(i) = 1;
          resp++;
          if(resp == max) i = j = tam;
        }
      }
    }
    return resp;
  }//end func

};

int main() {
  int t, a, p, v, c;

  std::cin >> t;
  for(int i = 0; i < t; i++){ //vertices, arestas, incluir, cores
    std::cin >> v >> a >> p >> c;

    Grafo graph(v);

    for(int j = 0; j < v; j++)
      std::cin >> graph.getColor().at(j);

    for(int j = 0; j < a; j++){
      int x, y;
      std::cin >> x >> y;
      graph.criarAresta(x-1, y-1);
    }

    if(graph.busca() == 1)
      std::cout << "Y\n\n";
    else
      std::cout << "N\n\n";
  }
  return 0;
}
