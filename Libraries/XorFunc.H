/* Libreria que Contiene Funciones Graficas Modo XOR */

/* Cursor XOR */
void DrawCursor(ControlEje x, ControlEje y)
{
    PixelXor(x, y);      /* Centro */
    PixelXor(x, y - 10); /* Arriba */
    PixelXor(x + 10, y); /* Derecha */
    PixelXor(x, y + 10); /* Abajo */
    PixelXor(x - 10, y); /* Izquierda */
}