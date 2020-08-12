from collections import deque
import random
from grafo import Grafo
from collections import defaultdict
from heapq import *


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

def orden_topologico(grafo):
    grados = {}
    for v in grafo:
        grados[v] = 0
    for v in grafo:
        for w in grafo.adyacentes(v):
            grados[w] += 1
    q = deque()
    for v in grafo:
        if grados[v] == 0:
            q.append(v)
    resul = []
    while q:
        v = q.popleft()
        resul.append(v)
        for w in grafo.adyacentes(v):
            grados[w] -= 1
            if grados[w] == 0:
                q.append(w)
    if len(resul) == len(grafo.obtener_todos_vertices()):
        return resul
    else:
        return None # El grafo tiene algun ciclo

def orden_topologico_rec(grafo, v, visitados, pila,visitados_ahora):
    visitados.add(v)
    visitados_ahora.add(v)
    for w in grafo.adyacentes(v):
        if w not in visitados:
            orden_topologico_rec(grafo, v, visitados, pila,visitados_ahora)
        elif w in visitados_ahora:
            return None # El grafo tiene algun ciclo
    pila.append(v)

#Hay un problmea con la recursividad
def orden_topologico_dfs(grafo):
    visitados = set()
    pila = deque() 
    for v in grafo:
        if v not in visitados:
            orden_topologico_rec(grafo, v, visitados, pila, set())
    return pila_a_lista(grafo)

def pila_a_lista(pila):
    resul = []
    while pila:
        resul.append(pila.pop())
    return resul

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

def dfs_ciclo_largo_n(grafo, v, origen, n, visitados, camino_actual):
    visitados.add(v)
    if len(camino_actual) == n:
        if origen in grafo.adyacentes(v):
            return camino_actual
        else:
            visitados.remove(v)
            return None

    for w in grafo.adyacentes(v):
        if w in visitados: continue
        solucion = dfs_ciclo_largo_n(grafo, w, origen, n, visitados, camino_actual + [w])
        if solucion is not None:
            return solucion
    visitados.remove(v)
    return None
    
#or grafo.estan_conectados(vk,vj):
def clustering_vertice(grafo, origen):
    aristas_entre_ady = 0
    for vj in grafo.adyacentes(origen):
        for vk in grafo.adyacentes(origen):
            if grafo.estan_conectados(vj,vk):
                aristas_entre_ady += 1
    try:
        k = len(grafo.adyacentes(origen))
        aux = k * (k-1)
        return aristas_entre_ady / float(aux)
    except ZeroDivisionError:
        return 0

def clustering_red(grafo):
    sum_coef = 0
    fails = 0
    for v in grafo:
        c = clustering_vertice(grafo,v)
        if c == 0:
            fails += 1
        else:
            sum_coef += c
    return sum_coef / (grafo.vertices_cantidad() - fails)

def grados_entrada_dirigido(grafo):
    grados = {}
    for v in grafo:
        grados[v] = 0
    for v in grafo:
        for w in grafo.adyacentes(v):
            grados[w] += 1
    return grados

def grados_salida_dirigido(grafo):
    grados = {}
    for v in grafo.obtener_todos_vertices():
        grados[v] = len(grafo.adyacentes(v))
    return grados

def aristas_de_entrada(grafo):
    entradas = defaultdict(list)
    for v in grafo:
        for w in grafo.adyacentes(v):
            entradas[w].append(v)
    return entradas

def primeros_k(heap,k):
    resultado = []
    aux = {}
    for i in range(k):
        aux[i] = heappop(heap)
        print(aux[i])
        #print(aux)
        resultado.append(aux[1])
    #for i in aux:
    #    heappush(heap,(aux.keys(),aux[i]))
    print(aux)
    #heappush(heap,aux)
    return list(resultado)


def pagerank(grafo,ranks,limite_iteraciones = 10, d = 0.85):
    aristas_entrada = aristas_de_entrada(grafo)
    grados_salida = grados_salida_dirigido(grafo)
    N = grafo.vertices_cantidad()
    for v in grafo:
        ranks[v] = 0
    for _ in range(limite_iteraciones):
        for v in grafo:
            try:
                ranks[v] = (1 - d)/N +  d *sum([ranks[x] / grados_salida[x] for x in aristas_entrada[v]])
            except ZeroDivisionError:
                continue

def crear_heap_desde_dicc(dicc,k):
    heap = [(-valor,clave) for clave,valor in dicc.items()]
    heapify(heap)
    return heap

heap_esta_vacio = True
heap = []
ranks = {}
def _mas_importantes(grafo,k):
    global heap_esta_vacio
    global heap
    global ranks
    if heap_esta_vacio == True:
        heap_esta_vacio = False
        pagerank(grafo,ranks)
        heap = crear_heap_desde_dicc(ranks,k)
        result  = nsmallest(k,heap)
        return result
    else:
        res = nsmallest(k,heap)
        return res

