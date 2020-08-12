
import random
from heapq import *
from grafo import Grafo


class Pagerank:
    def __init__(self):
        self.heap = []
        self.ranks = {}
        self.heap_esta_vacio = True


    def _pagerank(grafo,limite_iteraciones = 10, d = 0.85):
        

        Hola, como están? Tengo un par de consultar de las pruebas de algunos comandos del tp3. No se si debería publicar por cada comando por separado, si es así, háganmelo saber por favor.
-)Comando ciclo n: Si la pagina que me pasan por parámetro no existe en mi grafo, qué debería devolver?  Prueba 4-Error: Se esperaba que no se encuentre camino
        Comandos de la prueba:
                ciclo complejidad computacional,4
Actualmente si no pertenece el vértice devuelvo que no se encontró el recorrido, debería devolver directamente None?
-) Comando lectura:Acá me pasa algo similar, no todas las paginas que me pasan por parámetro pertenecen a mi grafo. Probé con las paginas de prueba que prueba el corrector y hay algunas que no pertenecen, a modo de probar, puse que si alguna página no pertenece al grafo que siga normal y esa pagina que no pertenece la pone en la solución total no tiene ningún orden de lectura. Como debería validar?      Prueba 1 - Error: La cantidad de artículos de la lectura no coincide con las que se quieren leer -Comandos de la prueba:
  lectura Eduardo VI de Inglaterra,siglo XV,Inglaterra,Polonia,París,Milán,España
Aca, por ejemplo. 'Eduardo VI de Inglaterra' no pertenece a mi grafo. La prueba 3 de lectura la pasa sin problema. Una cosa más, probando los ejemplos de la explicación del tp, noté que la prueba de las muchas paginas, no me devuelve el mismo orden como está ahi en el tp, no sé si esto tendrá que ver. Pero supongo que puede existir un orden distinto en la devolución de este comando. Ejemplo:lectura Hockey sobre hielo ,Roma,Japón,árbol,Guerra,Dios,universo,Himalaya,otoño obtengo: Hockey sobre hielo -> árbol -> universo -> Himalaya -> otoño -> Guerra -> Dios -> Japón -> Roma
-)Comando Clustering:
Acá hay algo que me llama mucho la atención, tengo algunas pruebas que las pasa y otras no, las que me generan error, el resultado me difiere muy poco de lo que debería. No sé bien por qué sería. Según la descripción del tp en la explicación del calculo para clustering:"Lo cual quiere decir: por cada par de adyacentes al vértice en cuestión, si existe la arista yendo de uno al otro (si además está la recíproca, lo contamos otra vez" yo entiendo que como bien dice, si existe la reciproca sumo en un contador uno más. Si lo hago de esa manera, no me coinciden los resultados con los de la página, pero, si saco la reciproca, es decir, no cuento en el contador si está la reciproca, si me coinciden con los de la pagina y ademas tengo los siguientes resultados de las pruebas, y por último, no entiendo que problema surje en la ultima prueba, la prueba 7 con The Beatles que aparece lo ultimo. Prueba 1 OK Prueba 2 OK Prueba 3 OK
        Prueba 4
        Error: Coeficiente erroneo. Esperado 0.153 obtenido 0.161
        Comandos de la prueba:
                clustering Luna
        Prueba 5 OK
        Prueba 6
        Error: Coeficiente erroneo. Esperado 0.068 obtenido 0.073
        Comandos de la prueba:
                clustering The Beatles
        Prueba 7
Traceback (most recent call last):
  File "pruebas.py", line 400, in <module>
    pruebas()
  File "pruebas.py", line 390, in pruebas
    if pruebas_comando():
  File "pruebas.py", line 297, in pruebas_clustering
    if not ejecutar_y_validar("pruebas/clustering/0" + str(prueba + 1) + "_in", SET_PEQ, validar_coeficiente):
  File "pruebas.py", line 45, in ejecutar_y_validar
    expected = validacion(l.strip())
  File "pruebas.py", line 292, in validar_coeficiente
    obtenido = float(salida)
ValueError: could not convert string to float: 'No existe la pagina indicada en NetStats'
make: *** [Makefile:13: run] Error 1
make: Target 'all' not remade because of errors

Desde ya muchas gracias. Disculpen por la extensión del mail.
Saludos.