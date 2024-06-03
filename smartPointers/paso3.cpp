// g++ -o paso3 paso3.cpp
// ./paso3
// valgrind --leak-check=full --show-leak-kinds=all ./paso3

#include <iostream>
#include <memory>

using namespace std;

int main()
{
    unique_ptr<int> num = unique_ptr<int>(new int(5));
    //*num = 7;
    // int* num2 = num;
    //unique_ptr<int> num2 = num;
 // Imprimir la dirección a la que apunta num antes de mover la memoria
    cout << "Direccion de num antes de mover: " << num.get() << endl;

    // Declarar num2 y mover la memoria de num a num2
    unique_ptr<int> num2 = move(num);

    // Imprimir las direcciones después de mover la memoria
    cout << "Direccion de num despues de mover: " << num.get() << endl;
    cout << "Direccion de num2 despues de mover: " << num2.get() << endl;

    //unique_ptr<int> num2 = move(num);
    //cout << num << endl;
 

    return 0;
}

/*
Agregue una variable num2 de tipo int* justo debajo de num y copie num a dicha
variable. ¿Es posible compilar? ¿Qué errores da?
No se puede compilar
error: cannot convert ‘std::unique_ptr<int>’ to ‘int*’ in initialization

Cambie el tipo de num2 para que sea unique_ptr. Intente asignar num a num2 .
¿Compila o qué errores da?
No
error: use of deleted function ‘std::unique_ptr<_Tp, _Dp>::
unique_ptr(const std::unique_ptr<_Tp, _Dp>&) [with _Tp = int; _Dp = std::default_delete<int>]’

Ahora, "mueva" la memoria apuntada por num a num2 . Use move(num) a la derecha del
igual para mover la memoria. Compile y corra el programa con Valgrind. ¿Qué resultados
da? ¿Porqué hay un segmentation fault?
Segmentation fault
Porque intenta acceder a un lugar que no puede

Elimine la asignación *num = 7 . También elimine la desreferencia en la instrucción de
impresión, para que imprima num en lugar de *num . Vuelva a correr el programa. ¿Se
solucionaron los errores?
NO
error: no match for ‘operator<<’ (operand types are ‘std::ostream’ {aka ‘std::basic_ostream<char>’} and ‘std::unique_ptr<int>’)
   17 |     cout << num << endl;

Modifique el programa para que imprima los punteros a num y num2 antes de mover la
memoria y después de moverla. ¿Qué imprimen?
Direccion de num antes de mover: 0x5597a1a6feb0
Direccion de num despues de mover: 0
Direccion de num2 despues de mover: 0x5597a1a6feb0

*/
