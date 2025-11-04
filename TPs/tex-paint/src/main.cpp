#include <algorithm>
#include <stdexcept>
#include <vector>
#include <string>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Model.hpp"
#include "Window.hpp"
#include "Callbacks.hpp"
#include "Debug.hpp"
#include "Shaders.hpp"
#include <iostream>
#include <cmath>     // Necesario para la función round() y abs()
#include <GL/glut.h> // Necesario para usar GLUT (o FreeGLUT)

#define VERSION 20250901


// Dimensiones de la ventana (para la proyección ortogonal)
const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 400;

/**
 * @brief Implementa el Algoritmo DDA para trazar una línea entre dos puntos.
 *
 * El DDA (Digital Differential Analyzer) es un algoritmo de interpolación lineal
 * que utiliza incrementos fraccionales para determinar los píxeles a trazar.
 *
 * @param x1 Coordenada X del punto inicial.
 * @param y1 Coordenada Y del punto inicial.
 * @param x2 Coordenada X del punto final.
 * @param y2 Coordenada Y del punto final.
 */
void dda_line(float x1, float y1, float x2, float y2) {
    // 1. Cálculo de las diferencias (del total del segmento)
    float dx = x2 - x1;
    float dy = y2 - y1;

    // 2. Determinación del número de pasos (Steps)
    // El número de pasos es igual a la mayor de las diferencias absolutas.
    // Esto asegura que la coordenada con el cambio más grande se incremente
    // en pasos unitarios (o casi unitarios después de la división), evitando huecos.
    float steps = std::max(std::abs(dx), std::abs(dy));

    // 3. Cálculo de los incrementos por paso
    // Los incrementos son el cambio total dividido por el número de pasos.
    float x_increment = dx / steps;
    float y_increment = dy / steps;

    // Inicialización de las coordenadas actuales
    float x = x1;
    float y = y1;

    // 4. Bucle de trazado de píxeles
    glBegin(GL_POINTS);
    for (int k = 0; k <= steps; ++k) {
        // Redondear las coordenadas a enteros para seleccionar el píxel (rasterización)
        // DDA requiere aritmética de punto flotante y redondeo.
        glVertex2i(static_cast<int>(std::round(x)), static_cast<int>(std::round(y)));

        // Actualizar las coordenadas para el siguiente paso
        x += x_increment;
        y += y_increment;
    }
    glEnd();
}

/**
 * @brief Función de visualización (callback de GLUT).
 * Se llama cada vez que la ventana necesita ser redibujada.
 */
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Limpiar el búfer de color

    // Establecer el color de dibujo (rojo brillante)
    glColor3f(1.0f, 0.2f, 0.2f);

    // --- Prueba 1: Línea con pendiente baja (dx > dy) ---
    // Puntos: (50, 50) a (350, 150)
    // Pendiente m = 100/300 = 0.33
    dda_line(50.0f, 50.0f, 350.0f, 150.0f);

    // Establecer otro color (azul)
    glColor3f(0.2f, 0.2f, 1.0f);

    // --- Prueba 2: Línea con pendiente alta (dy > dx) ---
    // Puntos: (100, 300) a (200, 50)
    // Pendiente m = -250/100 = -2.5
    dda_line(100.0f, 300.0f, 200.0f, 50.0f);

    // Establecer otro color (verde)
    glColor3f(0.1f, 0.8f, 0.1f);

    // --- Prueba 3: Línea vertical ---
    // Puntos: (450, 100) a (450, 300)
    dda_line(450.0f, 100.0f, 450.0f, 300.0f);

    glFlush(); // Asegurar que los comandos de dibujo se ejecuten inmediatamente
}

/**
 * @brief Inicializa la proyección ortogonal.
 * Establece un sistema de coordenadas 2D donde cada píxel de la ventana
 * se mapea directamente a una unidad de coordenadas OpenGL.
 */
void init() {
    // Color de fondo
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Gris oscuro

    // Configurar el sistema de coordenadas 2D
    glMatrixMode(GL_PROJECTION); // Seleccionar matriz de Proyección
    glLoadIdentity();            // Resetear la matriz
    // Establecer un volumen de vista ortogonal
    // (izquierda, derecha, abajo, arriba, cerca, lejos)
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);

    // Asegurar que solo se dibujen los puntos
    glPointSize(2.0f); // Puntos más grandes para mejor visualización
}

/**
 * @brief Función principal: Configura e inicia GLUT.
 */
int main(int argc, char** argv) {
    // Inicializar la librería GLUT
    glutInit(&argc, argv);

    // Configuración inicial de la ventana
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("DDA Line Drawing Algorithm Tester");

    // Llama a nuestra función de inicialización de OpenGL
    init();

    // Registrar las funciones callback
    glutDisplayFunc(display); // Función para dibujar

    // Entrar en el bucle principal de procesamiento de eventos de GLUT
    glutMainLoop();

    return 0;
}
