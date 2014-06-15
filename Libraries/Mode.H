/* Library that contains Functions, Enumerations and Structures for Graphic Mode */

/* Declaration of New Data Types */
typedef int Graph;
typedef unsigned short Iteration, Axis, Boolean, Quantity, EventHandler;

/* Enumeration to Control Validations */
enum Boolean { false, true };

/* Enumerations to Control User Activities */
enum Button {
    btnInputPoints,     /* Top Buttons(Comandos) */
    btnClosePolygon,
    btnMonotone,
    btnTrapezoidal,

    btnRestore, btnExit /* Lateral Buttons */
} _hoverButton = NONE;

enum UserMovementControl {
    Keyboard, Mouse
} _activeMovementControl = NONE;

/* Enumerations for Graphic Styles >> LineStyle(Style, Trama, Thickness), FillStyle(Trama, Color) */
enum LineStyles { Continua, Punteada, Centrada, Guiones };
enum LineThickness { Fina = NORM_WIDTH, Gruesa = THICK_WIDTH };
enum Fill_Styles {
    Vacio, Solido,
    Ln_Hor,
    Ln_Dia, Ln_Dia_G,
    Ln_Dia_I_G, Ln_Dia_I,
    Cuadricula, X_Cuadricula,
    Intervalo,
    Punteado, Punteado_C
};

/* Structure that Contains Style Attributes for Buttons */
struct ButtonsStyle {
    Graph bkColor, lineColor, lblColor;
} btnCommandsStyle[2] = {
    { 11, 0, 0 } , { 15, 10, 13 }
}, btnRestoreStyle[2] = {
    { 12, 5, 15 } , { 10, 6, 0 }
}, btnExitStyle[2] = {
    { 4, 9, 15 } , { 9, 4, 15 }
};

/* Global Variables */
/*  */

/* Function that Initiates the Graphical Mode */
void InitGraphicMode(void)
{
    Graph driver = VGA, mode = VGAHI, error;

    initgraph(&driver, &mode, "");

    /* If the Graph Mode has problems with Start */
    if ((error = graphresult()) != grOk)
    {
        printf("Error Al Iniciar El Modo Grafico\nError #%d >> %s\n\n", error, grapherrormsg(error));
        system("Pause") , abort() ;
    }
}