#include <graphics.h>
#include <conio.h>
#include <mouse.h>
#include <math.h>

#define radioX 		60
#define radioY 		40
#define Xcentro 	250
#define Ycentro 	200
#define ejemayor 	(2 * radioX)

void main(void)
{
	int driver = DETECT, mode = 0;
	float a, b, c, d;
	int x, y;
	int f1, f2, Distancia;

	initgraph(&driver,&mode,"");
	mver();

	ellipse(Xcentro, Ycentro, 0, 360, radioX, radioY);
	
	do {
		if (!mclick()) /* mclick devuelve 1 si das click, si no das click entonces te saltas el ciclo */
			continue;  /* tecnica para mejorar velocidad y no sobrecargar el programa: :Nesting: */

		x = mxpos(1);
		y = mypos(1);

		/* Calcular Rectangulo Manualmente, se puede mejorar!! */
		if ((x < Xcentro - radioX) || (x > Xcentro + radioX) || (y < Ycentro - radioY) || (y > Ycentro + radioY))
			continue;

		/* Si Pasa Esta Validacion significa que esta dentro de un recatangulo inmaginario que contiene el ellipse */

		a = (radioX * radioX) - (radioY * radioY);
		c = sqrt(a);

		f1 = Xcentro - c;
		f2 = Xcentro + c;

		b = ((x - f1) * (x - f1) + (y - Ycentro) * (y - Ycentro));
		d = ((x - f2) * (x - f2) + (y - Ycentro) * (y - Ycentro));

		Distancia = sqrt(d) + sqrt(b);

		if (Distancia < ejemayor)
			outtextxy(200, 200, "Dentro");
		else
			outtextxy(150, 150, "Fuera");
	
	} while(!kbhit());
}