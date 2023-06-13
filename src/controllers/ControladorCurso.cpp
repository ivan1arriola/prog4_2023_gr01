#include "../../include/controllers/ControladorCurso.h"
#include "../../include/datatypes/DTDataCurso.h"

#include "../../include/classes/Curso/Curso.h"

#include "../../include/handlers/HandlerCurso.h"
#include "../../include/handlers/HandlerUsuario.h"
#include "../../include/handlers/HandlerIdioma.h"

#include "../../include/classes/Curso/Completar.h"
#include "../../include/classes/Curso/Curso.h"
#include "../../include/classes/Curso/Ejercicio.h"
#include "../../include/classes/Curso/Leccion.h"
#include "../../include/classes/Curso/Traducir.h"

#include <string>

using namespace std;

ControladorCurso* ControladorCurso::instancia = NULL;

HandlerCurso* ControladorCurso::coleccionCursos = NULL;
HandlerUsuario* ControladorCurso::coleccionUsuarios = NULL;
HandlerIdioma* ControladorCurso::coleccionIdiomas = NULL;



ControladorCurso::ControladorCurso() {
    ControladorCurso::coleccionCursos = HandlerCurso::getInstancia();
    ControladorCurso::coleccionUsuarios = HandlerUsuario::getInstancia();
    ControladorCurso::coleccionIdiomas = HandlerIdioma::getInstancia();
}

ControladorCurso::~ControladorCurso() {

    if (ControladorCurso::coleccionCursos != NULL) {
        ControladorCurso::coleccionCursos->deleteInstancia();
        ControladorCurso::coleccionCursos = NULL;
    }
    
}

IControladorCurso* ControladorCurso::getInstancia() {
    if (instancia == NULL)
        instancia = new ControladorCurso();
    return instancia;
}


set<string> ControladorCurso::listarCursosHabilitados() {
    
    HandlerCurso *h = HandlerCurso::getInstancia();
    map<string, Curso*> mapCursos = h->obtenerCursos();
    set<string> cursos;
    string insertar;

    for(auto it = mapCursos.begin(); it != mapCursos.end(); ++it){
        insertar = it->second->getNombre();
        if(it->second->getDisponible())
            cursos.insert(insertar);
    }

    return cursos;
}

void ControladorCurso::seleccionarIdioma(string nombreIdioma) {
    if (coleccionIdiomas->existeIdioma(nombreIdioma))
        this->idiomaCursoActual = coleccionIdiomas->obtenerIdioma(nombreIdioma);
    else
        throw invalid_argument("No existe el idioma");
}


void ControladorCurso::altaCurso(bool disponible) {
    if(coleccionCursos->existeCurso(this->nombreCurso)){
        this->nombreCursoActual = "";
        this->descripcionCursoActual = "";
        this->idiomaCursoActual = NULL;
        this->nicknameProfesorActual = "";
        this->usuarioActual = NULL;
        this->leccionesCursoActual.clear();
        //this->cursosPreviosCursoActual.clear();

        this->ejercicioActual = NULL;
        for (auto it = this->ejerciciosLeccionActual->begin(); it != this->ejerciciosLeccionActual->end(); ++it)
            delete *it;
        this->ejerciciosLeccionActual->clear();
        delete this->ejerciciosLeccionActual;

        throw invalid_argument("Ya existe un curso con ese nombre");
    }else {

        Profesor* profesor = dynamic_cast<Profesor*>(this->usuarioActual);

        //Curso(string nombre, string descripcion, Nivel nivel, bool disponible, Idioma* idioma, Profesor* profesor, vector<Leccion*> lecciones)
        Curso* cursoNuevo = new Curso(this->nombreCursoActual, this->descripcionCursoActual, this->dificultadlCursoActual,
                                        disponible, this->idiomaCursoActual, profesor,
                                        this->leccionesCursoActual);
        coleccionCursos->agregarCurso(cursoNuevo);
    }
}

set<string> ControladorCurso::obtenerCursos() {
    set<string> cursos;
    // Implementación de la función obtenerCursos
    // Código para obtener la lista de cursos disponibles
    return cursos;
}

string ControladorCurso::getNombreCurso() {
    return nombreCurso;
}

set<string> ControladorCurso::getDataCurso() {
    set<string> dataCurso;
    // Implementación de la función getDataCurso
    // Código para obtener los datos del curso seleccionado
    return dataCurso;
}

string ControladorCurso::getNickProfesor() {
    // Implementación de la función getNickProfesor
    string nickProfesor;
    // Código para obtener el nick del profesor del curso seleccionado
    return nickProfesor;
}

set<string> ControladorCurso::getNombresCursosPrevios() {
    set<string> cursosPrevios;
    // Implementación de la función getNombresCursosPrevios
    // Código para obtener los nombres de los cursos previos del curso seleccionado
    return cursosPrevios;
}

set<DTDataLeccion> ControladorCurso::getLecciones() {
    set<DTDataLeccion> lecciones;
    // Implementación de la función getLecciones
    // Código para obtener las lecciones del curso seleccionado
    return lecciones;
}

void ControladorCurso::eliminarCurso(string nombre) {
    // Implementación de la función eliminarCurso
    // Código para eliminar el curso con el nombre proporcionado
}

void ControladorCurso::agregarLeccion(string tema, string objetivo) {
    Leccion* leccion = new Leccion(tema, objetivo, * this->ejerciciosLeccionActual);
    this->leccionesCursoActual.push_back(leccion);
}

void ControladorCurso::agregarEjercicio(string nombreEjercicio, string tipoEjercicio, string descEjercicio) {
    if (this->ejerciciosLeccionActual == NULL)
        this->ejerciciosLeccionActual = new set<Ejercicio*>();

    if (tipoEjercicio == "Traducir" ) {
        this->ejercicioActual = new Traducir(nombreEjercicio, descEjercicio);
        this->ejerciciosLeccionActual->insert(this->ejercicioActual);
        return;
    }
    if (tipoEjercicio == "Completar" ) {
        this->ejercicioActual = new Completar(nombreEjercicio, descEjercicio);
        this->ejerciciosLeccionActual->insert(this->ejercicioActual);
        return;
    }

    throw invalid_argument("Tipo de ejercicio no válido");
}

void ControladorCurso::ingresarNicknameEstudiante(string nomEstudiante) {
    // Implementación de la función ingresarNicknameEstudiante
    // Código para ingresar el nickname del estudiante para realizar ejercicios
}

void ControladorCurso::ingresarDatosCurso(string nombre, string desc, Nivel dificultad) {
    this->nombreCursoActual = nombre;
    this->descripcionCursoActual = desc;
    this->dificultadlCursoActual = dificultad;

    this->nicknameProfesorActual = this->usuarioActual->getNickname();
    
}

set<string> ControladorCurso::listarCursosInscrip() {
    set<string> cursosInscrip;
    // Implementación de la función listarCursosInscrip
    // Código para obtener la lista de cursos disponibles para inscripción
    return cursosInscrip;
}

set<string> ControladorCurso::mostrarCursosNoAprobados() {
    set<string> cursosNoAprobados;
    // Implementación de la función mostrarCursosNoAprobados
    // Código para obtener la lista de cursos no aprobados del estudiante
    return cursosNoAprobados;
}

set<string> ControladorCurso::mostrarEjerciciosNoAprobados() {
    set<string> ejerciciosNoAprobados;
    // Implementación de la función mostrarEjerciciosNoAprobados
    // Código para obtener la lista de ejercicios no aprobados del estudiante
    return ejerciciosNoAprobados;
}

DTEjercicio ControladorCurso::seleccionarEjercicio(string nombreEjercicio) {
    // Implementación de la función seleccionarEjercicio
    // Código para obtener los datos del ejercicio seleccionado por su nombre
    return DTEjercicio();
}

void ControladorCurso::ingresarSolucionCompletar(set<string> solC) {
    // Implementación de la función ingresarSolucionCompletar
    // Código para ingresar la solución del ejercicio de completar en el Controlador de Ejercicio
}

void ControladorCurso::ingresarSolucionTraducir(string solT) {
    // Implementación de la función ingresarSolucionTraducir
    // Código para ingresar la solución del ejercicio de traducción en el Controlador de Ejercicio
}

void ControladorCurso::marcarEjercicioAprobado() {
    // Implementación de la función marcarEjercicioAprobado
    // Código para marcar el ejercicio actual como aprobado en el Controlador de Ejercicio
}

void ControladorCurso::marcarEjercicioNoAprobado() {
    // Implementación de la función marcarEjercicioNoAprobado
    // Código para marcar el ejercicio actual como no aprobado en el Controlador de Ejercicio
}

//Operaciones para Consulta Curso


set<string> ControladorCurso::listarNombreCursos() {
    map<string, Curso*> cursos = ControladorCurso::coleccionCursos->obtenerCursos();
    set<string> nombresCursos;
    for (map<string, Curso*>::iterator it = cursos.begin(); it != cursos.end(); ++it) {
        nombresCursos.insert(it->first);
    }
    return nombresCursos;
}

void ControladorCurso::seleccionarCurso(string nombreCurso) {
    this->nombreCurso = nombreCurso;
}

DTDataCurso* ControladorCurso::mostrarDatosCurso() {
    string nombreCurso = this->nombreCurso;
    Curso * curso = coleccionCursos->obtenerCurso(nombreCurso);
    return curso->getDT();
}

void ControladorCurso::seleccionarProfesor(string nickname) {
    //Averigua si existe el profesor, lo busca en la coleccion de usuarios y lo asigna a usuarioActual
    if (coleccionUsuarios->existeUsuario(nickname)) {
        this->usuarioActual = coleccionUsuarios->obtenerUsuario(nickname);
    } else {
        throw invalid_argument("No existe el profesor");
    }
}

set<string> ControladorCurso::listarCursosNoHabilitados(){
    HandlerCurso* h= HandlerCurso::getInstancia();
    map<string,Curso*> o= h->obtenerCursos();
    set<string> resultado;

    for(map<string,Curso*>::iterator it=o.begin();it!=o.end();++it){
        if(it->second->getDisponible()==false){
            resultado.insert(it->second->getNombre());
        }
    }
    return resultado;
}


void ControladorCurso::agregarFraseTraducir(string fraseATraducir, string fraseTraducida){
    if (this->ejercicioActual == NULL)
        throw invalid_argument("No hay ejercicio seleccionado");

    Traducir* traducir = dynamic_cast<Traducir*>(this->ejercicioActual);
    if (traducir == NULL)
        throw invalid_argument("El ejercicio seleccionado no es de tipo Traducir");

    traducir->setFraseATraducir(fraseATraducir);
    traducir->setFraseCorrecta(fraseTraducida);
}

void ControladorCurso::agregarFraseCompletar(string fraseACompletar, vector<string> palabras){
    if (this->ejercicioActual == NULL)
        throw invalid_argument("No hay ejercicio seleccionado");

    Completar* completar = dynamic_cast<Completar*>(this->ejercicioActual);
    if (completar == NULL)
        throw invalid_argument("El ejercicio seleccionado no es de tipo Completar");
    completar->setFraseACompletar(fraseACompletar);
    completar->setPalabrasFaltantes(palabras);
}
