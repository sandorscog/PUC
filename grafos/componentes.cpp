#include <iostream>
#include <vector>

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

  enum class Cor {
    branco,
    cinza,
    preto
  };

  std::vector<std::vector<int>> getMatrix(){
    return matrix;
  }

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
        std::cout << "\n";
      }
    }//for
    return count;
  }

  std::vector<Cor> busca(int i, std::vector<Cor> cores){
    cores.at(i) = Cor::cinza;
    char letra = 'a';
    std::cout << static_cast<char>(letra + i) << ",";
    for(int j = 0; j < tam; j++){
      if(matrix.at(i).at(j) == 1){
        if(cores.at(j) == Cor::branco)
          cores = busca(j, cores);
      }
    }//for
    cores.at(i) = Cor::preto;
    return cores;
  }//func

};

int main() {
  int n, v, e;
  std::cin >> n;

  for(int i = 0; i < n; i++){ //numero de casos testados
    std::cin >> v;
    std::cin >> e;
    std::cout << "Case #" << i+1 << ":\n";

    Grafo graph(v);

    for(int j = 0; j < e; j++){
      char a, b;
      std::cin >> a >> b;
      int ver1 = a - 'a',
          ver2 = b - 'a';
      graph.criarAresta(ver1, ver2);
    }

    std::cout << graph.busca() << " connected components"  << "\n\n";
  }// for do num de casos

  return 0;
}
