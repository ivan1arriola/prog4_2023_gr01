#ifndef LECCION
#define LECCION

#include <string>
#include <set>

#include "Ejercicio.h"

using namespace std;

class Leccion {
    private:
        string tema;
        string objetivo;
        set<Ejercicio*> ejercicios;
    public:
        Leccion();
        Leccion(string descripcion);
        Leccion(string tema, string objetivo);
        Leccion(string tema,string objetivo,set<Ejercicio*>);

        // Getters
        string getTema();
        string getObjetivo();

        // Setters
        void setTema(string tema);
        void setObjetivo(string objetivo);

        // Operaciones
        void crearEjercicioYAgregarlo(string desc);
        set<Ejercicio*> getEjercicios(); // Aun no esta linkeado con Ejercicio
        int getCantEj();

        ~Leccion();

};

#endif