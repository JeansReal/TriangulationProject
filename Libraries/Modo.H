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
    {   0,   0, 1024, 768 } , {  55,  43, 895, 703 }
};

/* Variables Globales */

/*Iniciando Modo Grafico 1024*768 A>> 256 Colores*/
int huge HighLevelXGA(void)
{
    return 4;
}

void InitGraph(void)
{
    Graph driver=DETECT, mode=0, error=0;
    /*detectgraph(&driver, &mode);*/

    /* Instalar Driver Para el Modo Grafico de Alto Nivel */
    installuserdriver("SVGA256", HighLevelXGA);
    initgraph(&driver, &mode, "");

    /* Validamos Si el Modo Grafico Inicio Sin Problemas */
    if ((error = graphresult()) != grOk)
    {
        printf("Error Al Iniciar El Modo Grafico\nError #%d >> %s\n\n", error, grapherrormsg(error));
        system("Pause") , abort() ;
    } else {
        cleardevice();
        graphdefaults();
        setviewport(0, 0, getmaxx() + 1, getmaxy() + 1, 1);
        mlimit(1, 0, 0, getmaxx(), getmaxy());
    }
}

/* Verifica si Esta Fuera del Marco de Trabajo */
Boolean IsOutsideWorkArea(ControlEje x, ControlEje y)
{
    if (x > 55 && x < 895 && y > 41 && y < 707)
        return False;
    else
        return True;
}

/* Verifica si Puede Moverse a los extremos del Area de Trabajo */
Boolean CanMoveLeft(ControlEje x)
{
    if (x > Limit[_activeLimit].x1)
        return True;
    else
        return False;
}

Boolean CanMoveRight(ControlEje x)
{
    if (x < Limit[_activeLimit].x2)
        return True;
    else
        return False;
}

Boolean CanMoveUp(ControlEje y)
{
    if (y > Limit[_activeLimit].y1)
        return True;
    else
        return False;
}

Boolean CanMoveDown(ControlEje y)
{
    if (y < Limit[_activeLimit].y2)
        return True;
    else
        return False;
}