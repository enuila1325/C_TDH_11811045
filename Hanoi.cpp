#include <iostream>
#include <string>
#include <iomanip>

void hanoi(int, int, int, int);

int main()
{
    int discos;
    std::cout << "Numero de discos: ";
    std::cin >> discos;
    std::cout << "Aguja -> Aguja" << std::endl;
    hanoi(discos, 1, 2, 3);
}

void hanoi(int n, int origen, int auxiliar, int destino)
{
    if (n == 1)
    {
        std::cout << std::setw(5) << std::to_string(origen) << " -> " << std::to_string(destino) << std::endl;
    }
    else
    {
        hanoi(n - 1, origen, destino, auxiliar);
        std::cout << std::setw(5) << std::to_string(origen) << " -> " << std::to_string(destino) << std::endl;
        hanoi(n - 1, auxiliar, origen, destino);
    }
}