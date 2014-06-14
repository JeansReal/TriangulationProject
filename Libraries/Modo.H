/* Libreria que Contiene Funciones y Enumeraciones y Estructuras para el Modo Grafico */

/* Declaracion de Nuevos Tipos de Datos */
typedef int Graph;
typedef unsigned short Iteration, Axis, Boolean, Quantity, EventHandler;

/* Enumeraciones Para Control de Funciones y Validaciones */
enum Boolean { false, true };

enum Limits { Default, WorkArea } _activeLimit = Default ;
enum Button {
    btnInputVector,     /* Botones Superiores(Comandos) */
    btnCloseVector,
    btnMonotone,
    btnTrapezoidal,

    btnRestore, btnExit /* Botones Laterales */
} static _hoverButton = NONE;

enum UserMovementControl {
    Keyboard, Mouse
} _activeMovementControl = NONE;

/* Enumeracion Para el Macro Linea>> Que Representa Funcion LineStyle(Style, Trama, Thickness) */
enum Line_Styles { Continua, Punteada, Centrada, Guiones };
enum Line_Thickness { Fina = NORM_WIDTH, Gruesa = THICK_WIDTH };

/* Enumeracion Para el Macro Relleno>> Que Representa Funcion setfillstyle(Trama, Color)*/
enum Fill_Styles {
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
    { 11, 0, 0 } , { 15, 10, 13 }
}, btnRestoreStyle[2] = {
    { 12, 5, 15 } , { 10, 6, 0 }
}, btnExitStyle[2] = {
    { 4, 9, 15 } , { 9, 4, 15 }
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