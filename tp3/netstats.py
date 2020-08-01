#!/usr/bin/python3
# -*- coding: utf-8 -*-
import random
import sys
from collections import deque
from grafo import Grafo
import biblioteca

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
    return camino, orden[destino]

def mas_importantes():
    print("mas importantes")

def conectados():
    print("conectados")



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

def main():
    if len(sys.argv) != 2:
        print("Cantidad de parametros inválidos")
    
    grafo = Grafo(True)
    netstats_crear(sys.argv[1],grafo)
    cam, costo = camino(grafo, "Boca Juniors", "Australia")
    print(cam)
    x = ' '
    print("Costo:"+x+str(costo))
    #biblioteca.bfs(grafo,"A")
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
    'conectados': conectados
}

main()

"""
    if sys.argv[1] in dicc_comandos:
        dicc_comandos[sys.argv[1]]()
    else:
        print("no esta en comandos")
    #listar_operaciones()
"""