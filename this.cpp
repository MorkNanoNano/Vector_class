#include <iostream>


// Creo una semplice classe per potere vedere la keyword this
class Entity{
public:
    Entity(); // Costruttore di classe
    void print_value(); //funzione che stampa a terminale il valore di x
    void print_using_this(); // funzione che stampa x, y usando this

public:
    double x, y; // datamembri che per semplicità sono stati dichiarati public
};


// Semplice dicharazione della firma della funzione print(),
void print(Entity* ptr);
// altrimenti C++ mi picchia durissimo


// Implementazione delle funzioni membro della classe Entity
Entity::Entity() 
    : x(100), y(50) { }

void Entity::print_value() {
    std::cout << "The x value is: " << x << std::endl;
}

void Entity::print_using_this(){
    print(this);
}

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// Quanto scritto sopra funziona ed è sintatticamente corretto,
// ma adesso vediamo come traduce la funzione il compilatore
// una volta compilato il file:

/*

void print_value(Entity* this) {
    std::cout << this->x << std::endl;
}

*/

// Di fatto il puntatore passato sarà un pò piu complesso
// in quanto sara Entity* const this, 
// ma non ci serve sapere questa finezza che resta only for curious kids xD

// Il compilatore non "conosce il concetto di classe" ma "aggira"
// il problema dichiarando la funzione come se non fosse parte
// della classe, e passandoci un putatore
// all'oggetto della classe, chiamato appunto this.
// il this quindi è un paramtro "nascosto" in ogni funzione
// di una classe e punta appunto all'istanza(oggetto)
// Quindi il this è essenzialmente un puntatore 
// all'oggetto sul quale applichiamo il metodo.
// Ricordantoci la sintassi dei puntatori sappiamo che
// this->x sinonimo di (*this).x ci darà accesso
// alla componente x salvata nella cella di memoria puntata da this.
// in questo modo riusciamo ad accedere a ogni singolo 
// "mattoncino" che compone l'oggetto.
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 

//funzione che prende un puntatore ad un oggeto Entity e ne stampa le componenti
void print(Entity* ptr){ 
    std::cout << "This x = " << ptr->x << "\n" 
              << "This y = " <<  ptr->y << std::endl;
}
// chiamata dentro la funzione di classe print_using_this 
// che passa il puntatore this alla funzione

int main(){

    Entity entity; // creo un oggetto di tipo Entity

    entity.print_value(); // chiamo il metodo print_value, 
                          // in questo caso il this sarà un puntatore 
                          // che punta ad entity., l'oggetto su cui applico il metodo.

    entity.print_using_this(); // userà la keyword this per passare 
                               // il parametro alla funzione print()

    return 0;
}
