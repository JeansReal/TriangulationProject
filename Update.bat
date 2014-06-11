@Echo Off

Title Proyecto Geometria Computacional - Actualizando...

Color F2

Echo Se Actualizara Las Librerias y El Codigo Remoto Automaticamente.
Echo.

TaskList | Find /I "notepad++.exe"
    If Not %ErrorLevel% == 1 (
        Echo.
        Echo Se Detecto Abierto el Programa Notepad++
        Echo Verifique si Guardo sus Cambios, de lo contrario no se Actualizara el Codigo!!.
        Pause
    )
Echo.

If Exist C:\TC20\INCLUDE\Apple (
    Echo Copiando Librerias
        Xcopy C:\TC20\INCLUDE\Apple C:\TC20\TriangulationProject\Libraries /S /D
) Else (
    Echo Error al leer las Librerias
    Goto Problema
)
Echo.

If Exist C:\TC20\xD.C (
    Echo Copiando Codigo Principal
        Xcopy C:\TC20\xD.C C:\TC20\TriangulationProject\ /D
) Else (
    Echo Error al Leer el Codigo Principal!
    Goto Problema
)
Echo.

If %ErrorLevel% == 1 (
    :Problema
    Echo Un Problema a Ocurrido, Ejecute como Administrador y Verifique sus Archivos!
) Else (
    Echo Todo Se Actualizo Correctamente, Proceda a Hacer el Push :}
)

Echo.
Pause
Exit