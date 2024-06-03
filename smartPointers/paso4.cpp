#include <iostream>
#include <memory>
using namespace std;
int main()
{
    shared_ptr<int> a = shared_ptr<int>(new int(5));
    cout << a.use_count() << endl;
    shared_ptr<int> b = a;
    weak_ptr<int> VARIABLE = a;
    // cout << a.use_count() << endl;
    cout << "VARIABLE.use_count(): " << VARIABLE.use_count() << endl;
    weak_ptr<int> VARIABLE1 = a;
    cout << "VARIABLE1.use_count(): " << VARIABLE1.use_count() << endl;
    shared_ptr<int> c = shared_ptr<int>(b);
    cout << a.use_count() << endl;
    {
        // contexto anidado
        shared_ptr<int> d = shared_ptr<int>(a);
        cout << a.use_count() << endl;

        shared_ptr<int> temp = VARIABLE.lock();
        cout << a.use_count() << endl;
    }
    cout << a.use_count() << endl;
    return 0;
}
/*
¿Qué valores se imprimen?
1
2
3
4
3

Ahora, agregue algunos weak_ptr , usando weak_ptr<int> VARIABLE = a . ¿La cuenta del
programa cambia?
1
2
3
4
3
No

Modifique el programa para que también imprima el contador de referencias de los
weak_ptr (usando use_count ).

1
VARIABLE.use_count(): 2
VARIABLE1.use_count(): 2
3
4
3

¿Se incrementó el conteo? ¿Porqué?

1
VARIABLE.use_count(): 2
VARIABLE1.use_count(): 2
3
4
5
3
La razón por la cual shared_ptr<int> temp = VARIABLE.lock(); 
incrementa el contador de referencias es que el método lock() 
de weak_ptr intenta obtener un shared_ptr que comparte la propiedad
 del objeto gestionado. Si el objeto aún existe (es decir, no ha sido
  destruido), lock() devuelve un shared_ptr que incrementa el contador de referencias.

*/