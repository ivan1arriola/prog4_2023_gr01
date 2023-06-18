#ifndef INSCRIPCION
#define INSCRIPCION

#include <iostream>
#include <string>
#include <map>

#include "../datatypes/DTDate.h"

#include "Usuario/Estudiante.h"

#include "Curso/Ejercicio.h"

class Curso;

using namespace std;

class Inscripcion {
private:
    DTDate* fechaInscripcion;
    bool aprobado;

    Estudiante* estudiante;
    Curso* curso;

    set<Ejercicio*> ejAprobados;
    set<Ejercicio*> ejNoAprobados;

public:

    // Constructores
    Inscripcion();
    Inscripcion(DTDate* fechaInscripcion, bool aprobado, Estudiante* estudiante, Curso* curso);
    Inscripcion(DTDate* fechaInscripcion, bool aprobado, Estudiante* estudiante, Curso* curso,set<Ejercicio*>);

    // Getters
    DTDate* getFechaInscripcion();
    bool getAprobado();
    set<Ejercicio*> getejAprobados();
    set<Ejercicio*> getejNoAprobados();

    // Setters
    void setFechaInscripcion(DTDate* date);
    void setAprobado(bool);
    void setejAprobado(Ejercicio*);
    void setejNoAprobado(Ejercicio*);

    // Metodos
    string obtenerNombreCurso();
    float calcPorcentajeAvance();
    float getCantEjsAprob(); 

    ~Inscripcion();   
    
};

#include "Curso/Curso.h"

#endif