#include <iostream>
#include <conio.h>
using namespace std;

class Nodo
{
public:
    int valor;
    Nodo* izquierda;
    Nodo* derecha;
    int altura;
};

int getAltura(Nodo* _nodo)
{
    if (_nodo == NULL)
        return 0;
    return _nodo->altura;
}

Nodo* nodoNuevo(int valor)
{
    Nodo* _nodo = new Nodo();
    _nodo->valor = valor;
    _nodo->izquierda = NULL;
    _nodo->derecha = NULL;
    _nodo->altura = 1;
    return(_nodo);
}

int max(int valorA, int valorB)
{
    return (valorA > valorB) ? valorA : valorB;
}

Nodo* rotacionDerecha(Nodo* nodo2)
{
    Nodo* nodo1 = nodo2->izquierda;
    Nodo* nodo3 = nodo1->derecha;

    // rotar
    nodo1->derecha = nodo2;
    nodo2->izquierda = nodo3;

    // actualizar altura
    nodo2->altura = max(getAltura(nodo2->izquierda), getAltura(nodo2->derecha)) + 1;
    nodo1->altura = max(getAltura(nodo1->izquierda), getAltura(nodo1->derecha)) + 1;

    // retornar nueva raiz
    return nodo1;
}

Nodo* rotacionIzquierda(Nodo* _nodo1)
{
    Nodo* _nodo2 = _nodo1->derecha;
    Nodo* _nodo3 = _nodo2->izquierda;

    // rotar
    _nodo2->izquierda = _nodo1;
    _nodo1->derecha = _nodo3;

    // actualizar altura
    _nodo1->altura = max(getAltura(_nodo1->izquierda), getAltura(_nodo1->derecha)) + 1;
    _nodo2->altura = max(getAltura(_nodo2->izquierda), getAltura(_nodo2->derecha)) + 1;

    // retornar nueva raiz
    return _nodo2;
}

int getBalance(Nodo* _nodo)
{
    if (_nodo == NULL)
        return 0;
    return getAltura(_nodo->izquierda) - getAltura(_nodo->derecha);
}

Nodo* insertarNodo(Nodo* _nodo, int valor)
{
    if (_nodo == NULL)
        return(nodoNuevo(valor));

    if (valor < _nodo->valor)
        _nodo->izquierda = insertarNodo(_nodo->izquierda, valor);
    else if (valor > _nodo->valor)
        _nodo->derecha = insertarNodo(_nodo->derecha, valor);
    else
        return _nodo;

    _nodo->altura = 1 + max(getAltura(_nodo->izquierda), getAltura(_nodo->derecha));

    int balance = getBalance(_nodo);

    if (balance > 1 && valor < _nodo->izquierda->valor)
        return rotacionDerecha(_nodo);

    if (balance < -1 && valor > _nodo->derecha->valor)
        return rotacionIzquierda(_nodo);

    if (balance > 1 && valor > _nodo->izquierda->valor)
    {
        _nodo->izquierda = rotacionIzquierda(_nodo->izquierda);
        return rotacionDerecha(_nodo);
    }

    if (balance < -1 && valor < _nodo->derecha->valor)
    {
        _nodo->derecha = rotacionDerecha(_nodo->derecha);
        return rotacionIzquierda(_nodo);
    }

    return _nodo;
}

void imprimirPreOrden(Nodo* raiz)
{
    if (raiz != NULL)
    {
        cout << raiz->valor << " ";
        imprimirPreOrden(raiz->izquierda);
        imprimirPreOrden(raiz->derecha);
    }
}

void imprimirInOrden(Nodo* raiz)
{
    if (raiz != NULL)
    {
        imprimirInOrden(raiz->izquierda);
        cout << raiz->valor << " ";
        imprimirInOrden(raiz->derecha);
    }
}

void imprimirPostOrden(Nodo* raiz)
{
    if (raiz != NULL)
    {
        imprimirPostOrden(raiz->izquierda);
        imprimirPostOrden(raiz->derecha);
        cout << raiz->valor << " ";

    }
}

Nodo* nodoMenorValor(Nodo* _nodo)
{
    //menor del subarbol derecho
    Nodo* actual = _nodo;

    while (actual->izquierda != NULL)
        actual = actual->izquierda;

    return actual;
}

Nodo* eliminarNodo(Nodo* raiz, int valor)
{

    if (raiz == NULL)
        return raiz;

    // If the valor to be deleted is smaller
    // than the raiz's valor, then it lies
    // in izquierda subtree
    if (valor < raiz->valor)
        raiz->izquierda = eliminarNodo(raiz->izquierda, valor);

    // If the valor to be deleted is greater
    // than the raiz's valor, then it lies
    // in derecha subtree
    else if (valor > raiz->valor)
        raiz->derecha = eliminarNodo(raiz->derecha, valor);

    // if valor is same as raiz's valor, then
    // This is the node to be deleted
    else
    {
        // node with only one child or no child
        if ((raiz->izquierda == NULL) ||
            (raiz->derecha == NULL))
        {
            Nodo* temp = raiz->izquierda ?
                raiz->izquierda :
                raiz->derecha;

            // No child case
            if (temp == NULL)
            {
                temp = raiz;
                raiz = NULL;
            }
            else // One child case
                *raiz = *temp; // Copy the contents of
                               // the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the derecha subtree)
            Nodo* temp = nodoMenorValor(raiz->derecha);

            // Copy the inorder successor's
            // data to this node
            raiz->valor = temp->valor;

            // Delete the inorder successor
            raiz->derecha = eliminarNodo(raiz->derecha,
                temp->valor);
        }
    }

    // If the tree had only one node
    // then return
    if (raiz == NULL)
        return raiz;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    raiz->altura = 1 + max(getAltura(raiz->izquierda),
        getAltura(raiz->derecha));

    // STEP 3: GET THE BALANCE FACTOR OF
    // THIS NODE (to check whether this
    // node became unbalanced)
    int balance = getBalance(raiz);

    // If this node becomes unbalanced,
    // then there are 4 cases

    // izquierda izquierda Case
    if (balance > 1 &&
        getBalance(raiz->izquierda) >= 0)
        return rotacionDerecha(raiz);

    // izquierda derecha Case
    if (balance > 1 &&
        getBalance(raiz->izquierda) < 0)
    {
        raiz->izquierda = rotacionIzquierda(raiz->izquierda);
        return rotacionDerecha(raiz);
    }

    // derecha derecha Case
    if (balance < -1 &&
        getBalance(raiz->derecha) <= 0)
        return rotacionIzquierda(raiz);

    // derecha izquierda Case
    if (balance < -1 &&
        getBalance(raiz->derecha) > 0)
    {
        raiz->derecha = rotacionDerecha(raiz->derecha);
        return rotacionIzquierda(raiz);
    }

    return raiz;
}

int main()
{
    Nodo* test = NULL;
    test = insertarNodo(test, 2);
    test = insertarNodo(test, 7);
    test = insertarNodo(test, 8);
    test = insertarNodo(test, 1);
    test = insertarNodo(test, 6);
    test = insertarNodo(test, 9);
    test = insertarNodo(test, 11);
    test = insertarNodo(test, 15);
    test = insertarNodo(test, 3);
    test = insertarNodo(test, 5);

    cout << endl << "-----PREORDEN----------" << endl;
    imprimirPreOrden(test);
    cout << endl << "-----POSTORDEN----------" << endl;
    imprimirPostOrden(test);
    cout << endl << "-----INORDEN----------" << endl;
    imprimirInOrden(test);


    cout << endl << "----eliminar 7----------" << endl;
 
    test = eliminarNodo(test, 7);
    cout << endl << "-----PREORDEN----------" << endl;
    imprimirPreOrden(test);
    cout << endl << "-----POSTORDEN----------" << endl;
    imprimirPostOrden(test);
    cout << endl << "-----INORDEN----------" << endl;
    imprimirInOrden(test);

 
    cout << endl << "----eliminar 15----------" << endl;

    test = eliminarNodo(test, 15);
    cout << endl << "-----PREORDEN----------" << endl;
    imprimirPreOrden(test);
    cout << endl << "-----POSTORDEN----------" << endl;
    imprimirPostOrden(test);
    cout << endl << "-----INORDEN----------" << endl;
    imprimirInOrden(test);


    _getch();
}