#!/usr/bin/python3
# -*- coding: utf-8 -*-
import random
import sys
from collections import deque
from grafo import Grafo
import biblioteca
import json

def listar_operaciones():
    for cmd in dicc_comandos.keys():
        if cmd == 'listar_operaciones': continue
        print(cmd)
        #print(dicc_comandos.keys())

#Complejidad: O(P+L), P: Cant de paginas, L cantidad de links
def camino(grafo, origen, destino):
    padres, orden = biblioteca.camino_minimo_bfs(grafo, origen, destino)
    #print(orden[destino])
    if destino not in orden:
        print("no hay camino posible")
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
    x = ' '
    print("Costo:"+x+str(orden[destino]))
    #return camino, orden[destino]

def mas_importantes():
    print("mas importantes")

#Complejidad: O(P+L)

def diametro(grafo):
    costo, distancias, padres, aux_origen = biblioteca.diametro(grafo)
    with open("text.text",'w') as fp:
        print(distancias, file = fp)
    fp.close()
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
    #'->'.join(map(str,camino))
    print(*camino, sep=' -> ')
    #pila = deque()
    #print(distancias)
    x = ' '
    print("Costo:"+x+str(costo))

def ciclo_n(grafo, origen, n):
    if not grafo.vertice_pertenece(origen):
        print("no existe el vertice")
        return None
    sol_parcial = []
    visitados = set()
    sol_parcial.append(origen)
    visitados.add(origen)
    ciclo = biblioteca.dfs_ciclo(grafo, origen, origen, visitados, sol_parcial, n)
    if ciclo == None:
        print("No se encontro el recorrido")
    else:
        print(ciclo)


def rango(grafo, origen, n):
    padres, orden = biblioteca.bfs_rango(grafo, origen, n)
    cont = 0
    for v in orden:
        if orden[v] == n:
            cont += 1
    return cont

def navegacion(grafo, origen):
    if grafo.vertice_pertenece(origen) == False:
        return "No existe el origen en NetStats"
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


def netstats_crear(ruta_archivo,grafo):
    datos = []
    with open(ruta_archivo) as wiki:
        for linea in wiki:
            linea = linea.strip()
            datos = linea.split('\t')
            i = 0
            for i in range(len(datos)):
                #print(datos[i])
                grafo.agregar_vertice(datos[i]) 
            for w  in range(1,len(datos)):
                grafo.agregar_arista(datos[0],datos[w])

    wiki.close()

def grados_salida_dirigido(grafo):
    grados = {}
    for v in grafo.obtener_todos_vertices():
        grados[v] = len(grafo.adyacentes(v))

    return grados

def conectados(grafo, origen):
    return biblioteca.cfc_tarjan(grafo)
    #print(todas_cfc)

def main():
    if len(sys.argv) != 2:
        print("Cantidad de parametros inválidos")
    sys.setrecursionlimit(5000)
    grafo = Grafo(True)
    netstats_crear(sys.argv[1],grafo)
    #diametro(grafo)
    #aux = list(grafo.adyacentes("Brasil"))
    #print(aux[0])
    navegacion(grafo, "Argentina")
    navegacion(grafo, "Alemania")
    navegacion(grafo, "queso")
    navegacion(grafo, "Bolivia")
    navegacion(grafo, "Brasil")



    #print(rango(grafo, "Perón", 4))
    #cfcs = conectados(grafo,"Boca Juniors")
    #with open("text.txt",'w') as f:
    #    print(cfcs, file=f)
    #f.close()
    #print(cfcs)
    #print("Roma" in grafo.adyacentes("Japón"))
    #print(grafo.adyacentes("Japón"))
    #diametro(grafo)
    #ciclo_n(grafo,"Rock de Argentina",2)
    #print(grafo.adyacentes("Arte"))
    """cam, costo = camino(grafo, "Boca Juniors", "Australia")
    print(cam)˙

    #conectados(grafo, "Boca Juniors")
    #biblioteca.bfs(grafo,"A")"""
    """print(grafo.vertices_cantidad())
    print(grafo.vertice_aleatorio())
    print(grafo.adyacentes("A"))
    print(grafo.adyacentes("B"))
    print(grafo.adyacentes("C"))
    print(grafo.adyacentes("T"))"""

    #print(grafo.estan_conectados("Miniatura","Luis XIV"))
    """
    
    print(grafo.adyacentes('A'))
    print(grafo.adyacentes('C'))
    grafo.borrar_arista('A','T')
    print(grafo.adyacentes('A'))
    print(grafo.adyacentes('B'))
    print(grafo.vertice_aleatorio())
    #print(grafo.estan_conectados("Ottawa","Toronto"))
    """
    

#if __name__ == "__main__":

dicc_comandos = {
    'listar_operaciones': listar_operaciones,
    'camino': camino,
    'mas_importantes': mas_importantes,
    'conectados': conectados,
    'diametro': diametro,
    'ciclo': ciclo_n,
    'rango': rango,
    'navegación': navegacion
}

main()

"""
    if sys.argv[1] in dicc_comandos:
        dicc_comandos[sys.argv[1]]()
    else:
        print("no esta en comandos")
    #listar_operaciones()
"""