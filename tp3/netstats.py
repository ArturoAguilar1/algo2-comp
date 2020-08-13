#!/usr/bin/python3

import random
import sys
from collections import deque
from grafo import Grafo
import biblioteca


def listar_operaciones(grafo,args):
    for cmd in dicc_comandos.keys():
        if cmd == 'listar_operaciones': continue
        print(cmd)

def _camino(grafo, origen, destino):
    if not grafo.vertice_pertenece(origen):
        print ("No existe el origen indicado")
        return None
    if not grafo.vertice_pertenece(destino):
        print ("No existe el destino indicado")
        return None
    padres, orden = biblioteca.camino_minimo_bfs(grafo, origen, destino)
    if destino not in padres:
        print("No se encontro recorrido")
        return None
    pila = deque()
    aux = destino
    while aux != origen:
        pila.append(aux)
        aux = padres[aux]

    pila.append(origen)
    camino = []
    while pila:
        camino.append(pila.pop())
    print(*camino, sep=' -> ')
    x = ' '
    print("Costo:"+x+str(orden[destino]))

def camino(grafo, args):
    """print(args[0])
    print(args[1])
    print(len(args))
    return None
    for p in args:
        aux = p.split(",")"""
    if len(args) != 2:
        print("Cantidad de parametros incorrectos en 'camino'.")
        return None
    return _camino(grafo,args[0],args[1])




def diametro(grafo,args):
    costo, distancias, padres, aux_origen = biblioteca.diametro(grafo)
    aux_final = list(distancias.keys())[list(distancias.values()).index(costo)]
    pila = deque()
    aux = aux_final
    while aux != aux_origen:
        pila.append(aux)
        aux = padres[aux]
    pila.append(aux_origen)
    camino = []
    while pila:
        camino.append(pila.pop())
    print(*camino, sep=' -> ')
    x = ' '
    print("Costo:"+x+str(costo))

def _ciclo_n(grafo, origen, n):
    if not grafo.vertice_pertenece(origen):
        print("No se encontro el recorrido")
        return None
    if len(grafo.adyacentes(origen)) == 0:
        print("No se encontro el recorrido")
        return None
    sol_parcial = []
    visitados = set()
    sol_parcial.append(origen)
    visitados.add(origen)
    ciclo = biblioteca.dfs_ciclo_largo_n(grafo,origen,origen,visitados,sol_parcial,n)
    if ciclo == None:
        print("No se encontro el recorrido")
    else:
        ciclo.append(origen)
        print(*ciclo, sep=' -> ')

def ciclo_n(grafo, args):
    if len(args) != 2:
        print("Cantidad de parametros incorrectos en 'ciclo'")
        return None
    try:
        n = int(args[1])
    except ValueError:
        print("Error al indicar el numero n")
        return None
    if n > 0:
        return _ciclo_n(grafo,args[0],n)
    else:
        print("Error, ingrese un numero positivo válidio")

def _rango(grafo, origen, n):
    if not grafo.vertice_pertenece(origen):
        print("No existe la página indicada")
        return None
    padres, orden = biblioteca.bfs_rango(grafo, origen, n)
    cont = 0
    for v in orden:
        if orden[v] == n:
            cont += 1
    print(cont)

def rango(grafo,args):
    if len(args) != 2:
        print("Cantidad de parametros incorrectos en 'rango'")
        return None
    
    try:
        n = int(args[1])
    except ValueError:
        print("Error al indicar el numero n")
        return None
    if n > 0:
        return _rango(grafo,args[0],n)
    else:
        print("Error, ingrese un numero postivio")

def navegacion(grafo, args):
    if len(args) != 1:
        print("Error al invocar el comando 'navegacion'")
        return None
    origen = args[0]
    if not grafo.vertice_pertenece(origen):
        print("No existe el origen en NetStats")
        return None
    recorrido = []
    recorrido.append(origen)
    aux = list(grafo.adyacentes(origen))
    n = 0
    #aux is not None and
    while n < 20:
        try:
            recorrido.append(aux[0])
            aux = list(grafo.adyacentes(aux[0]))
        except IndexError:
            aux = 'null'
            break
        n += 1
    print(*recorrido, sep=' -> ')


def comunidad(grado,pagina):
    return True

def clustering(grafo, args):
    if len(args) > 1:
        print("Error al invocar el comando 'clustering'")
        return None
    pagina = args[0]
    """
    if not grafo.vertice_pertenece(pagina):
        print("No existe la pagina indicada en NetStats")
        return None"""
    if pagina == "":
        aux = biblioteca.clustering_red(grafo)
        print("%.3f" % aux)
    else:
        aux = biblioteca.clustering_vertice(grafo,pagina)
        print("%.3f" % aux)

def validar_vertices(grafo,paginas):
    no_pertencen = []
    for v in paginas:
        if not grafo.vertice_pertenece(v):
            no_pertencen.append(v)
    return no_pertencen

def lectura(grafo,paginas):
    grafo_aux = Grafo(True)
    for v in paginas:               #O(n)
        grafo_aux.agregar_vertice(v)
    for v in grafo_aux:
        for w in grafo.adyacentes(v):
            if w in paginas:
                #print(f"{w}: está en los adyacentes de {v} y tmb esta en paginas")
                grafo_aux.agregar_arista(w,v)    

    orden = biblioteca.orden_topologico(grafo_aux)
    if orden:
        print(*orden, sep=', ')
    else:
        print("No existe forma de leer las paginas en orden")

def netstats_crear(ruta_archivo,grafo):
    datos = []
    with open(ruta_archivo) as wiki:
        for linea in wiki:
            linea = linea.strip()
            datos = linea.split('\t')
            i = 0
            for i in range(len(datos)):
                grafo.agregar_vertice(datos[i]) 
            for w  in range(1,len(datos)):
                grafo.agregar_arista(datos[0],datos[w])

    wiki.close()

def conectados(grafo, origen):
    pagina = origen[0]
    mb = {}
    orden = {}
    cfcs = []
    visit = []
    apilados = []
    orden[pagina] = 0
    todas_cfc =  biblioteca.cfcs_conectividad(grafo,pagina,apilados,mb,visit,cfcs,orden)
    new_list = [ seq[0] for seq in todas_cfc ]
    print(*new_list, sep=', ')


def mas_importantes(grafo,args):
    if len(args) > 1:
        print("Error al invocar los argumentos del comando 'mas importantes'")
        return None
    try:
        n = int(args[0])
    except ValueError:
        print("Error al indicar el numero n de paginas mas importantes")
        return None

    resultado = biblioteca._mas_importantes(grafo,n)
    new_list = [ seq[1] for seq in resultado ]
    print(*new_list, sep=', ')

def main():
    if len(sys.argv) != 2:
        print("Cantidad de parametros inválidos")
    sys.setrecursionlimit(10000)
    grafo = Grafo(True)
    netstats_crear(sys.argv[1],grafo)

    for cmd in sys.stdin:
        args = cmd.split(' ')
        comando = args[0].strip()
        argumentos = [x.strip() for x in ' '.join(args[1:]).split(',')]
        if comando in dicc_comandos:
            dicc_comandos[comando](grafo,argumentos)
        else:
            print("Ingrese un comando válido para NetStats")
            continue


#if __name__ == "__main__":

dicc_comandos = {
    "listar_operaciones": listar_operaciones,
    "camino": camino, #OK-CORRECTOR
    'mas_importantes': mas_importantes, #OK-CORRECTOR
    "diametro": diametro, #OK-CORRECTOR
    'ciclo': ciclo_n, #OK
    'rango': rango, #OK - CORRECTOR
    'navegacion': navegacion, #OK - CORRECTOR
    'lectura': lectura, #CREO OK
    #'comunidad' : comunidad,
    'clustering' : clustering, #CREO OK,
    'conectados': conectados
}

main()
