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

def bfs_rango(grafo, origen, n):
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
                q.append(w)
    return padres, orden


def caminos_minimos(grafo, origen):
    q = deque()
    visitados = set()
    distancia = {}
    padres = {}
    padres[origen] = None
    distancia[origen] = 0
    visitados.add(origen)
    q.append(origen)

    while q:
        v = q.popleft()
        for w in grafo.adyacentes(v):
            if w not in visitados:
                distancia[w] = distancia[v] + 1
                q.append(w)
                visitados.add(w)
                padres[w] = v
    return distancia, padres

def diametro(grafo):
    max_min_dist = 0
    aux_distancias = {}
    aux_padres = {}
    for v in grafo:
        distancias, padres = caminos_minimos(grafo, v)
        for w in distancias:
            if distancias[w] > max_min_dist:
                max_min_dist = distancias[w]
                aux_distancias = distancias
                aux_padres = padres
                aux_origen = v
    return max_min_dist, aux_distancias, aux_padres, aux_origen



def cfcs_conectividad(grafo, v, apilados,mb, visitados, todas_cfc, orden):
    pila = deque()
    visitados.add(v)
    mb[v] = orden[v]
    pila.appendleft(v)
    apilados.add(v)
    
    for w in grafo.adyacentes[v]:
        if w not in visitados:
        #print(f'{w} no esta visitado, lo visito')
            orden[w] = orden[v] + 1
            cfcs_conectividad(grafo, w, apilados, mb, visitados, todas_cfc, orden)

    if w in apilados:
      if mb[v] > mb[w]:
        #print(f'wii {v} bajo su mb de {mb[v]} a {mb[w]} gracias a la coneccion con {w}')
        mb[v] = min(mb[v], mb[w])
    
  
    if orden[v] == mb[v] and len(pila) > 0:
        nueva_cfc = []
        while True:
            w = pila.popleft()
            apilados.remove(w)
            nueva_cfc.append(w)
            if w == v:
                break
    
    #print('NUEVA CFC!: ', nueva_cfc)
    todas_cfc.append(nueva_cfc)
  #print(f"Termine de trabajar con {v}")


def reconstruir_ciclo(sol_parcial, inicio):
    camino = []
    camino = sol_parcial[:]
    camino.append(inicio)
    return camino

def dfs_ciclo(grafo, v, buscado, visitados, sol_parcial, n):
    for w in grafo.adyacentes(v):
        if len(sol_parcial) > n:
            return None
        if w in visitados:
            if w == buscado and len(sol_parcial) == n:
                return reconstruir_ciclo(sol_parcial, buscado)
        else:
            visitados.add(w)
            sol_parcial.append(w)
            ciclo = dfs_ciclo(grafo, w, buscado, visitados, sol_parcial, n)
            visitados.remove(sol_parcial.pop())
            if ciclo is not None:
                return ciclo
    return None
