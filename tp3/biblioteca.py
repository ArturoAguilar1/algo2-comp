#Aca hay que poner todos los algoritmos vistos en clase

def grado_entrada(grafo):
    grados = {}
    for v in grafo:
        grafo[v] = 0
    for v in grafo:
        for w in grafo.adyacentes(v):
            grados[w] += 1
    return grados