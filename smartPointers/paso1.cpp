// g++ -o paso1 paso1.cpp
// ./paso1
// valgrind --leak-check=full --show-leak-kinds=all ./paso1

#include <iostream>

using namespace std;

int main()
{
    int *num = new int(5);
    *num = 7;
    cout << *num << endl;
    delete num;
    return 0;
}

/*
Corra el programa anterior con valgrind. ¿Hay fugas de memoria?
No
*/