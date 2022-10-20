#include <iostream>
#include <string>
using namespace std;
// 2 - Faça uma função que simule a leitura de um sensor lendo o 
// valor do teclado ao final a função retorna este valor

int main()
{
    std::cout << "digite um número: ";

    int vdigitado{ };
    std::cin >> vdigitado; //pega o número digitado e armazena na variável vdigitado

    std::cout << "O valor digitado foi... " << vdigitado << '\n';
    return 0;
}