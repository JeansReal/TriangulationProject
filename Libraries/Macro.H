/* Libreria que Contiene Macros para el Modo Grafico */

/* Definicion de Constantes y Macros */
#define NONE	-1
/* Dirrecionales */
#define UP      72
#define DOWN    80
#define RIGHT   77
#define LEFT	75
/* Teclas De Control */
#define ENTER   13

#define CURSORMOTION 5

/* Macro Para Pintar Pixel en XOR */
#define PixelXor(x, y)	putpixel(x, y, 40 ^ getpixel(x, y))

/* Macro Para Determinar Columnas de Arreglos Unidimensionales Dinamicos */
#define ArraySize(Array) (sizeof(Array) / sizeof(Array[0]))

/* Macros Para Funciones De Estilo */
#define FillStyle(Trama, Color)            setfillstyle(Trama, Color)
#define LineStyle(Style, Thickness, Color)    setcolor(Color), setlinestyle(Style, 0, Thickness)

/* Verifica si Puede Moverse a los extremos del Area de Trabajo */
#define CanMoveLeft(x)  (x >   0) ? CURSORMOTION : False ;
#define CanMoveRight(x) (x < 640) ? CURSORMOTION : False ;
#define CanMoveUp(y)    (y >   0) ? CURSORMOTION : False ;
#define CanMoveDown(y)  (y < 480) ? CURSORMOTION : False ;

/* Verifica si Esta Fuera del Marco de Trabajo */
#define IsOutsideWorkArea(x, y) (((x > 55) && (x < 895) && (y > 41) && (y < 707)) ? False : True)