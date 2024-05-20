class Node
{
public:
    int value;
    Node *next;

    // Constructor
    Node(int valor)
    {
        value = valor;
        next = nullptr;
    }
};

class List
{
public:
    Node node;
    Node head;

    // Constructor
    /* Nodo actual = cabeza;
            while (actual.siguiente != null) {
                actual = actual.siguiente;
            }
            actual.siguiente = nodoNuevo;*/

    /*Haga una funcion que recibe 2 listas ordenadas que las une y ordena.
    Input: 1-3-7
    Input: 1-2-3
    Output: 1-1-2-3-7
    */
    List mergedList(List list1, List list2)
    {
        Node actual1 = list1.head;
        Node actual2 = list2.head;
        if (actual1 == nullptr)
        {
            actual1 = actual2;
        }
        while (actual1.next != nullptr)
        {
            actual1 = actual1.next;
        }
        actual1.next = nodeNew;
        return listNew;
    }
};

int main()
{
    return 0;
}
