/* Libreria que Contiene Funciones y Enumeraciones y Estructuras para el Modo Grafico */

/* Declaracion de Nuevos Tipos de Datos */
typedef int Graph;
typedef unsigned short Iteracion, ControlEje, Boolean, Cantidad, Direccional;
typedef char* String;

/* Enumeraciones Para Control de Funciones y Validaciones */
enum Boolean { False, True };

enum Limits { Default, WorkArea } _activeLimit = Default ;
enum Button {
    btnInputVector,     /* Botones Superiores(Comandos) */
    btnCloseVector,
    btnMonotone,
    btnTrapezoidal,

    btnRestore, btnExit /* Botones Laterales */
} _hoverButton = NONE;

enum UserMovementControl {
    Keyboard, Mouse
} _activeMovementControl = NONE;

/* Enumeracion Para el Macro Linea>> Que Representa Funcion setlinestyle(Estilo,Trama,Grosor) */
enum Estilos_De_Linea { Continua, Punteada, Centrada, Guiones };
enum Grosor_De_Linea { Fina, Gruesa = 3 };

/* Enumeracion Para el Macro Relleno>> Que Representa Funcion setfillstyle(Trama,Color)*/
enum Tramas_De_Relleno {
    Vacio, Solido,
    Ln_Hor,
    Ln_Dia, Ln_Dia_G,
    Ln_Dia_I_G, Ln_Dia_I,
    Cuadricula, X_Cuadricula,
    Intervalo,
    Punteado, Punteado_C
};

/* Estructura que Simula una Clase con Atributos Predeterminados para en Control de Estilo de los Botones */
struct ButtonsStyle {
    Graph bkColor, lineColor, lblColor;
} btnCommandsStyle[2] = {
    { 75, 0, 0 } , { 127, 42, 93 }
}, btnRestoreStyle[2] = {
    { 36, 0, 0 } , { 15, 40, 47 }
}, btnExitStyle[2] = {
    { 20, 0, 40 } , { 41, 15, 47 }
};

/* Estructura que Contiene Los Limites de Movimiento del Cursor cuando mueve una Figura*/
struct CursorLimitMovement {
    ControlEje x1, y1, x2, y2;
} Limit[4] = {
    {   0,   0, 640, 480 } , {  55,  43, 895, 703 }
};

/* Variables Globales */

void InitGraph(void)
{
    Graph driver = VGA, mode = VGAHI, error = 0;

    initgraph(&driver, &mode, "");

    /* Validamos Si el Modo Grafico Inicio Sin Problemas */
    if ((error = graphresult()) != grOk)
    {
        printf("Error Al Iniciar El Modo Grafico\nError #%d >> %s\n\n", error, grapherrormsg(error));
        system("Pause") , abort() ;
    }
    
}