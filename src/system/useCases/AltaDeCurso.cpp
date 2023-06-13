#include <iostream>
#include <string>

#include "../../../include/system/Sistema.h"

#include "../../../include/system/operaciones.h"

using namespace std;

typedef unsigned long int nat;

/*Nombre Alta de curso
Actores Usuario
Sinopsis El caso de uso comienza cuando un usuario desea dar de alta un nuevo curso en el
sistema. Para ello, el Sistema lista los nicknames de los profesores registrados y el
Usuario selecciona al que dictará el curso. Luego, el Usuario ingresa el nombre del
curso, la descripción y la dificultad (Principiante, Medio, Avanzado). A continuación,
el Sistema lista los nombres de los idiomas en los que se especializa el profesor y el
Usuario selecciona el idioma en el que enseñará el curso. Adicionalmente, el Sistema
pregunta si para inscribirse al curso se requerirá la aprobación de cursos previos. En
caso afirmativo, el Sistema lista los nombres de todos los cursos habilitados y el
Usuario selecciona aquellos que serán requeridos como previos. A continuación, el
Sistema pregunta al Usuario si desea agregar lecciones. En caso de que así sea, el
Usuario ingresa las lecciones en el orden que deberán ser realizadas por un estudiante.
Por cada lección que se desea agregar, el Usuario ingresa el nombre del tema que
tratará la lección y su objetivo. Opcionalmente, para cada lección, el sistema permite
también que el Usuario agregue los ejercicios que la componen. Por cada ejercicio que
se desea agregar, el Usuario ingresa el tipo de ejercicio y la descripción. Para los
ejercicios de completar palabras, el Usuario ingresa la frase a completar, donde las
palabras faltantes se representan mediante 3 guiones, por ejemplo, “Mi --- es Juan y
tengo 21 ---”, y, por otro lado, el conjunto ordenado de palabras separados por una
coma que conforman la solución (en el caso anterior sería: “nombre”, “años”). Por otra
parte, para los ejercicios de traducción, el Usuario ingresa la frase a traducir, seguida de
la frase traducida, por ejemplo, “Soy Juan”, y su traducción, “I am Juan”. Estos pasos
se repiten cada vez que el Usuario desea agregar una nueva lección junto a sus
ejercicios. Notar que el sistema admite agregar lecciones sin que estas tengan
necesariamente ejercicios. Una vez que el Usuario termina, el Sistema da de alta el
nuevo curso con los datos ingresados y sus lecciones y ejercicios, en caso de existir,
dejándolo no disponible para los estudiantes hasta tanto no se ejecute el caso de uso
“Habilitar curso”.*/


static nat contarEspaciosACompletar (string frase) {
    nat contador = 0 ;
    // Si es menor a 5 no puede tener 3 guiones seguidos
    if (frase.size() < 5) {
        return 0 ;
    }
    // Cuenta cuantas secuencias de 3 guiones seguidos hay y que esten rodeados de espacios
    for (nat i = 0; i < frase.size() - 3; i++) {
        if (frase[i] == ' ' && frase[i+1] == '-' && frase[i+2] == '-' && frase[i+3] == '-') {
            contador++ ;
        }
    }
    return contador ;
}


static string ingresarFraseACompletar () {
    string frase = ingresarParametro("la frase a completar") ;
    // Controla que tenga al menos 3 guiones seguidos
    while (contarEspaciosACompletar(frase) == 0) {
        imprimirMensaje("La frase debe tener al menos una secuencia de 3 guiones seguidos") ;
        frase = ingresarParametro("la frase a completar") ;
    }
    return frase ;

}

static vector<string> ingresarConjuntoDePalabras (int cantEspacios) {
    vector<string> solucion ;
    for (int i = 0; i < cantEspacios; i++) {
        string palabra = ingresarParametro("la palabra que completa el espacio " + to_string(i+1) + ":") ;
        solucion.push_back(palabra) ;
    }
    return solucion ;
}


void Sistema::altaDeCurso() {
    imprimirMensaje("Alta de Curso") ;

    //el caso de uso comienza listando los nickname de los profesores disponibles

    set<string> profesores = controladorUsuario->listarNIcknameProfesores() ;

    espacioSimple() ;

    if (profesores.size() == 0) {
        cancelarOperacion("No hay profesores registrados en el sistema", "Alta de Curso");
        return ;
    }

    string nicknameProfesor = seleccionarElemento(profesores, "profesor") ;

    espacioSimple() ;
    
    if (nicknameProfesor == "") {
        cancelarOperacion("A seleccionado cancelar la operación", "Alta de Curso") ;
        return ;
    }

    try {
        controladorCurso->seleccionarProfesor(nicknameProfesor) ;
        imprimirMensaje("Seleccionó el profesor con nickname: " + nicknameProfesor);
        espacioSimple() ;
    } catch (invalid_argument& e) {
        cancelarOperacion("No existe un profesor con el nickname " + nicknameProfesor, "Alta de Curso") ;
        return ;
    }

    string nombreCurso = ingresarParametro("el nombre del curso");
    espacioSimple() ;

    //controlar que no exista el nombre y que no sea vacío
    if(handlerCurso->existeCurso(nombreCurso)) {
        cancelarOperacion("Ya existe un curso con el nombre " + nombreCurso, "Alta de Curso") ;
        return ;
    }

    string descripcionCurso = ingresarParametro("la descripción del curso");

    espacioSimple() ;

    imprimirMensaje("Ingrese la dificultad del curso:") ;
    imprimirMensaje("1. Principiante") ;
    imprimirMensaje("2. Medio") ;
    imprimirMensaje("3. Avanzado") ;

    int opcion = ingresarOpcion(3) ;

    if (opcion == 0) {
        cancelarOperacion("A seleccionado cancelar la operación", "Alta de Curso") ;
        return ;
    }

    Nivel dificultad;

    if (opcion == 1 || opcion == 2 || opcion == 3) {
        dificultad = static_cast<Nivel>(opcion - 1);
    } else {
        cancelarOperacion("Opción inválida", "Alta de Curso");
        return;
    }


    controladorCurso->ingresarDatosCurso(nombreCurso, descripcionCurso, dificultad) ;

    set<string> idiomasDeProfesor = controladorUsuario->listarNombresIdiomasDeProfesor(nicknameProfesor) ;

    if (idiomasDeProfesor.size() == 0) {
        cancelarOperacion("El profesor no tiene idiomas registrados en el sistema", "Alta de Curso") ;
        return ;
    }


    string nombreIdioma = seleccionarElemento(idiomasDeProfesor, "idioma") ;

    if (nombreIdioma == "") {
        cancelarOperacion("A seleccionado cancelar la operación", "Alta de Curso") ;
        return ;
    }

    try {
        controladorCurso->seleccionarIdioma(nombreIdioma) ;
        imprimirMensaje("Seleccionó el idioma: " + nombreIdioma);
    } catch (invalid_argument& e) {
        cancelarOperacion("No existe un idioma con el nombre " + nombreIdioma, "Alta de Curso") ;
        return ;
    }

    //TODO: No esta contemplado las previas de un curso

    bool quiereAgregarLecciones = deseaContinuar("¿Desea agregar lecciones al curso?") ;

    if (!quiereAgregarLecciones) {
        cancelarOperacion("A seleccionado cancelar la operación", "Alta de Curso") ;
        return ;
    } else {
        do {

            

            string tema = ingresarParametro("el tema de la lección") ;

            string objetivo = ingresarParametro("el objetivo de la lección") ;

            

            bool quiereAgregarUnEjercicio = deseaContinuar("¿Desea agregar un Ejercicio a la Leccion?") ;

            while (quiereAgregarUnEjercicio) {

                string nombreEjercicio = ingresarParametro("el nombre del ejercicio") ;

                imprimirMensaje("Ingrese el tipo de ejercicio:") ;
                imprimirMensaje("1. Traducción") ;
                imprimirMensaje("2. Completar Frase") ;

                int tipoEjercicio = ingresarOpcion(2) ;

                if (opcion == 0) {
                    cancelarOperacion("A seleccionado cancelar la operación", "Alta de Curso") ;
                    return ;
                }

                string descripcion = ingresarParametro("la descripción del ejercicio") ;

                if (tipoEjercicio == 1) {

                    try {
                        controladorCurso->agregarEjercicio(nombreEjercicio, "Traducir", descripcion) ;
                    } catch (invalid_argument& e) {
                        cancelarOperacion( e.what(), "Alta de Curso") ;
                        return ;
                    }

                    string fraseATraducir = ingresarParametro("la frase a traducir");
                    string fraseTraducida = ingresarParametro("la frase traducida") ;

                    try {
                        controladorCurso->agregarFraseTraducir(fraseATraducir, fraseTraducida) ;
                    } catch (invalid_argument& e) {
                        cancelarOperacion( e.what(), "Alta de Curso") ;
                        return ;
                    }

                } else if (tipoEjercicio == 2) {

                    try {
                        controladorCurso->agregarEjercicio(nombreEjercicio, "Completar", descripcion) ;
                    } catch (invalid_argument& e) {
                        cancelarOperacion( e.what(), "Alta de Curso") ;
                        return ;
                    }

                    string fraseACompletar = ingresarFraseACompletar() ;
                    nat cantEspacios = contarEspaciosACompletar(fraseACompletar) ;
                    vector<string> conjuntoDePalabras = ingresarConjuntoDePalabras(cantEspacios) ;

                    try {
                        controladorCurso->agregarFraseCompletar(fraseACompletar, conjuntoDePalabras);
                    } catch (invalid_argument& e) {
                        cancelarOperacion( e.what(), "Alta de Curso") ;
                        return ;
                    }
                }

                quiereAgregarUnEjercicio = deseaContinuar("¿Desea agregar otro Ejercicio a la Leccion?") ;

                espacioSimple() ;
            }
            
            controladorCurso->agregarLeccion(tema, objetivo) ;

            quiereAgregarLecciones = deseaContinuar("¿Desea agregar otra lección al curso?") ;

            espacioSimple() ;

        } while (quiereAgregarLecciones) ;
    }






    //TODO: No esta contemplado los ejercicios de una leccion


    // Dar de alta el curso
    try {
        controladorCurso->altaCurso(false) ;
        imprimirMensaje("Se ha dado de alta el curso") ;
    } catch (invalid_argument& e) {
        imprimirMensaje( e.what() ) ;
        cancelarOperacion("No se pudo dar de alta el curso", "Alta de Curso") ;
        return ;
    }




}
