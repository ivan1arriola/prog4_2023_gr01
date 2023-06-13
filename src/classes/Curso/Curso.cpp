#include "../../../include/classes/Curso/Curso.h"

Curso::Curso() {
    // Implementación del constructor por defecto
}

Curso::Curso(string nombre, string descripcion, Nivel nivel, bool disponible) {
    // Implementación del constructor con parámetros
}

Curso::Curso(string nombre, string descripcion, Nivel nivel, bool disponible, Idioma* idioma, Profesor* profesor, vector<Leccion*> lecciones) {
    this->nombre = nombre;
    this->descripcion = descripcion;
    this->nivel = nivel;
    this->disponible = disponible;
    this->lecciones = lecciones;
    this->idioma = idioma;
    this->profesor = profesor;
}

// Curso::Curso(string nombre, string descripcion, Nivel nivel, bool disponible, Idioma* idioma, Profesor* profesor, vector<Leccion*> lecciones, set<Curso*> cursosPrevios) {
//     this->nombre = nombre;
//     this->descripcion = descripcion;
//     this->nivel = nivel;
//     this->disponible = disponible;
//     this->lecciones = lecciones;
//     this->idioma = idioma;
//     this->profesor = profesor;
//     this->cursosPrevios = cursosPrevios;
// }

string Curso::getNombre() {
    return nombre;
}

string Curso::getDescripcion() {
    return descripcion;
}

Nivel Curso::getNivel() {
    return nivel;
}

bool Curso::getDisponible() {
    return disponible;
}
vector<Leccion *> Curso::getLecciones(){
    return lecciones;
}

set<Curso*> Curso::getCursosPrevios(){
    return cursosPrevios;
}

void Curso::setNombre(string nombre) {
    this->nombre = nombre;
}

void Curso::setDescripcion(string descripcion) {
    this->descripcion = descripcion;
}

void Curso::setNivel(Nivel nivel) {
    this->nivel = nivel;
}

void Curso::setDisponible(bool disponible) {
    this->disponible = disponible;
}

void Curso::setCursosPrevios(set<Curso*> cursosPrevios){
    this->cursosPrevios = cursosPrevios;
}

set<string> Curso::obtenerEjNoAprobados() {
    // Implementación de la función obtenerEjNoAprobados()
    return set<string>();
}

void Curso::agregarLeccion(Leccion* leccion) {
    this->lecciones.push_back(leccion);
}

// void Curso::agregarCursoPrevio(Curso* cursoPrevio){
//     this->cursosPrevios.insert(cursoPrevio);
// }

float Curso::getCantEjsTotal() {
    // Implementación de la función getCantEjsTotal()
    return 0;
}

float Curso::calcPromedioAvance() {
    // Implementación de la función calcPromedioAvance()
    return 0;
}

Curso::~Curso() {
    // Borrar todos las lecciones

    for (long unsigned int i = 0; i < lecciones.size(); i++) {
        delete lecciones[i];
    }
}
