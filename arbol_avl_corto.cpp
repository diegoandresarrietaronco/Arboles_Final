#include <algorithm>
#include <iostream>
using namespace std;

struct Nodo {
    int valor, altura = 1;
    Nodo *izq = nullptr, *der = nullptr;
    Nodo(int v) : valor(v) {}
};

class ArbolAVL {
    Nodo* raiz = nullptr;

    int alt(Nodo* n) { return n ? n->altura : 0; }
    void actualizar(Nodo* n) { n->altura = 1 + max(alt(n->izq), alt(n->der)); }
    int balance(Nodo* n) { return alt(n->izq) - alt(n->der); }

    Nodo* rotarDer(Nodo* y) {
        Nodo* x = y->izq;
        y->izq = x->der;
        x->der = y;
        actualizar(y); actualizar(x);
        return x;
    }

    Nodo* rotarIzq(Nodo* x) {
        Nodo* y = x->der;
        x->der = y->izq;
        y->izq = x;
        actualizar(x); actualizar(y);
        return y;
    }

    Nodo* insertar(Nodo* n, int v) {
        if (!n) return new Nodo(v);
        if (v < n->valor) n->izq = insertar(n->izq, v);
        else if (v > n->valor) n->der = insertar(n->der, v);
        else return n;

        actualizar(n);
        int b = balance(n);
        if (b > 1) {                                        // pesa a la izquierda
            if (balance(n->izq) < 0) n->izq = rotarIzq(n->izq);
            return rotarDer(n);
        }
        if (b < -1) {                                       // pesa a la derecha
            if (balance(n->der) > 0) n->der = rotarDer(n->der);
            return rotarIzq(n);
        }
        return n;
    }

    void preorden(Nodo* n) {   // raíz, izquierda, derecha
        if (!n) return;
        cout << n->valor << " ";
        preorden(n->izq);
        preorden(n->der);
    }

    void inorden(Nodo* n) {    // izquierda, raíz, derecha
        if (!n) return;
        inorden(n->izq);
        cout << n->valor << " ";
        inorden(n->der);
    }

    void postorden(Nodo* n) {  // izquierda, derecha, raíz
        if (!n) return;
        postorden(n->izq);
        postorden(n->der);
        cout << n->valor << " ";
    }

    void borrar(Nodo* n) {
        if (!n) return;
        borrar(n->izq);
        borrar(n->der);
        delete n;
    }

public:
    ~ArbolAVL() { borrar(raiz); }
    void insertar(int v) { raiz = insertar(raiz, v); }
    void mostrarPreorden()  { cout << "Preorden:  "; preorden(raiz);  cout << endl; }
    void mostrarInorden()   { cout << "Inorden:   "; inorden(raiz);   cout << endl; }
    void mostrarPostorden() { cout << "Postorden: "; postorden(raiz); cout << endl; }
};

int main() {
    ArbolAVL arbol;
    for (int v : {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45}) arbol.insertar(v);

    arbol.mostrarPreorden();
    arbol.mostrarInorden();
    arbol.mostrarPostorden();
    return 0;
}
