@Echo Off

Title Proyecto Geometria Computacional - Instalando...

Color F1

Echo Se Actualizara Las Librerias y El Codigo Local Automaticamente.
Echo.

TaskList | Find /I "notepad++.exe"
    If Not %ErrorLevel% == 1 (
        Echo.
        Echo Se Detecto Abierto el Programa Notepad++
        Echo Guarde sus Cambios y Cierre el Programa, de lo contrario Perdera sus Avanzes!!.
        Pause
        TaskKill /F /IM notepad++.exe
        If %ErrorLevel% == 1 Goto Problema
    )
Echo.

cd C:/

Echo Copiando Drivers
    robocopy C:\TC20\TriangulationProject\Driver C:\TC20\BIN SVGA256.BGI /MT:16 /NJH /NFL /NJS
Echo.

Echo Copiando Librerias
        If Not Exist C:\TC20\INCLUDE\Apple (
            Echo     Creando Directorio
                mkdir C:\TC20\INCLUDE\Apple

            If Not Exist C:\TC20\INCLUDE\Apple (
                Echo         Problema Al Crear el Directorio
                Goto Problema
            ) Else (
                Echo         Directorio Creado Exitosamente!
            )
        )

        If Exist C:\TC20\INCLUDE\Apple (
            robocopy C:\TC20\TriangulationProject\Libraries C:\TC20\INCLUDE\Apple /E /MT:16 /NJH /NFL /NJS
        )
Echo.

Echo Copiando Codigo Principal
    robocopy C:\TC20\TriangulationProject\ C:\TC20\ xD.C /MT:16 /NJH /NFL /NJS
Echo.

Start "" notepad++ C:\TC20\INCLUDE\Apple C:\TC20\xD.C

If %ErrorLevel% == 1 (
    :Problema
    Echo Un Problema a Ocurrido, Ejecute como Administrador y Verifique sus Archivos!
) Else (
    Echo Todo Se Ejecuto Correctamente :}
)

Echo.
Pause
Exit