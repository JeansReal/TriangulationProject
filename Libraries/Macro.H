/* Library that Contains Macros for the Graphic Mode */

/* Defining Constants */
#define NONE	-1
/* Directionals */
#define UP      72
#define DOWN    80
#define RIGHT   77
#define LEFT	75
/* Control Keys for Events */
#define CLICK   1
#define ENTER   13
/* Cursor Speed Motion Movement */
#define CURSORMOTION 5

/* Macro to Paint Pixel in XOR Mode */
#define PixelXor(x, y)	putpixel(x, y, 40 ^ getpixel(x, y))

/* Macro to Determine Columns of Dynamical Dimensional Arrays */
#define ArraySize(Array) (sizeof(Array) / sizeof(Array[0]))

/* Macro to Draw Figures Contained in Arrays of Coordinates */
#define Draw(Array)		drawpoly(ArraySize(Array) / 2, Array)

/* Macros For Style Mode */
#define FillStyle(Trama, Color)               setfillstyle(Trama, Color)
#define LineStyle(Style, Thickness, Color)    setcolor(Color), setlinestyle(Style, 0, Thickness)

/* Check if the Cursor Can Move to One Direction */
#define CanMoveLeft(x)  (x >   0) ? CURSORMOTION : false ;
#define CanMoveRight(x) (x < 639) ? CURSORMOTION : false ;
#define CanMoveUp(y)    (y >   0) ? CURSORMOTION : false ;
#define CanMoveDown(y)  (y < 479) ? CURSORMOTION : false ;

/* Check if the User its Outside the WorsSpace */
#define IsOutsideWorkSpace(x, y) (((x < 50) || (x > 590) || (y < 50) || (y > 430)) || ((y > 360) && (x > 520)))

/* Check if the cursor|Mouse is inside a button: Check If the Actual Pixel Color is not the Background Color */
#define IsInsideButton(x, y)     ((getpixel(x - 1, y - 1) != 7) && (getpixel(x - 1, y - 1) != 8))

/* Macros for Check if its posible a Monotone Triangulation */
#define Xor(x, y)                            (!x^!y)
#define Left(A, B, C)                        (Area2(A, B, C) > 0)
#define LeftOn(A, B, C)                      (Area2(A, B, C) >= 0)
#define Collinear(A, B, C)                   (!Area2(A, B, C))
#define Diagonal(i, j, nPoints, PolyPoints)  (InCone(i, j, nPoints, PolyPoints) && Diagonalie(i, j, nPoints, PolyPoints))