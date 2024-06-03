// g++ -o paso2 paso2.cpp
// ./paso2
// valgrind --leak-check=full --show-leak-kinds=all ./paso2

#include <iostream>

using namespace std;

int main()
{
    int *num = new int(5);
    *num = 7;
    cout << *num << endl;
    //delete num;
    return 0;
}

/*
borre el delete y vuelva a correr el programa con Valgrind. ¿Hay fugas
de memoria?
Si
*/