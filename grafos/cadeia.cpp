#include <iostream>
#include <vector>
#include <queue>

class Grafo{
private:
  int tam;
  std::vector<std::vector<int>> matrix;
public:
  Grafo(int v){
    tam = v;

    matrix.resize(tam);
    for(int i = 0; i < tam; i++){
      matrix.at(i).resize(tam);
    }
  }

  void criarAresta(int x, int y){
    matrix.at(x).at(y) = 1;
  }

  enum class Cor {
    branco,
    cinza,
    preto
  };

  std::vector<std::vector<int>> getMatrix(){
    return matrix;
  }

  int buscaEmLargura(int id){
    int resp = 0;
    std::vector<Cor> color;
    color.resize(tam);
    for(int i = 0; i < tam; ++i) color.at(i) = Cor::branco;

    std::queue<int> q;
    q.push(id);

    int fifo;
    while(!q.empty()){
      fifo = q.front();
      q.pop();

      for(int i = 0; i < tam; i++){

        if(matrix.at(fifo).at(i) == 1){
          if(color.at(i) == Cor::branco){
            color.at(i) = Cor::cinza;
            q.push(i);
            resp++;
          }
        }//if fora

      }//for
      color.at(fifo) = Cor::preto;
    }//while
    return resp;
  }//end func

  bool bolada(){

    int maior = 0, nova;
    for(int i = 0; i < tam; i++){
      nova = (buscaEmLargura(i) + 1);
      if(nova > maior) maior = nova;
    }
    return (maior == tam) ? 1 : 0;
  }
};

int main(){
  int v, a, x, y;
  std::cin >> v >> a;

  Grafo graph(v);

  for(int i = 0; i < a; ++i){
    std::cin >> x >> y;
    graph.criarAresta(x-1, y-1);
  }

  if(graph.bolada())
    std::cout << "Bolada";
  else
    std::cout << "Nao Bolada";

  return 0;
}
