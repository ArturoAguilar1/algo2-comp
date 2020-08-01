#Aca hay que poner todos los algoritmos vistos en clase

from collections import deque
import random
from grafo import Grafo

def camino_minimo_bfs(grafo, origen, destino):
    visitados = set()
    padres = {}
    orden = {}
    q  = deque()
    padres[origen] = None
    orden[origen] = 0
    visitados.add(origen)
    q.append(origen)
    while q:
        v = q.popleft()
        #print(v)
        for w in grafo.adyacentes(v):
            if w not in visitados:
                visitados.add(w)
                padres[w] = v
                orden[w] = orden[v] + 1
                if w == destino:
                    return padres, orden
                q.append(w)
    return padres, orden

def grado_entrada(grafo):
    grados = {}
    for v in grafo:
        grafo[v] = 0
    for v in grafo:
        for w in grafo.adyacentes(v):
            grados[w] += 1
    return grados