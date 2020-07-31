from grafo import *


def obtener_aristas(grafo):
    aristas = []
    visitados = set()
    for v in grafo:
        visitados.add(v)
        for w in grafo.adyacentes(v):
            #if w not in visitados:
                aristas.append((v, w))
    return aristas


def pruebas_grafo_dirigido():
    grafo = Grafo(True)

    for x in range(6):
        grafo.agregar_vertice(x,None)
    
    grafo.agregar_arista(1,2,None)
    grafo.agregar_arista(2,1,None)
    grafo.agregar_arista(1,0,None)
    grafo.agregar_arista(3,1,None)

    print(grafo.adyacentes(1))
    print("Ejemplo grafo paternidad de martin")
    paternidad = Grafo(False)
    paternidad.agregar_vertice("Boca")
    paternidad.agregar_vertice("Riber")
    paternidad.agregar_vertice("San Silencio")
    paternidad.agregar_vertice("Rasin gente")
    paternidad.agregar_vertice("Indemierda")

    paternidad.agregar_arista("Boca","Riber","Riber Gay")
    paternidad.agregar_arista("Boca","San Silencio")
    paternidad.agregar_arista("Boca","Rasin gente")
    paternidad.agregar_arista("Boca","Indemierda")

    paternidad.agregar_arista("Indemierda","Rasin gente")
    paternidad.agregar_arista("Indemierda","San Silencio")

    paternidad.agregar_arista("Rasin gente","Riber")

    paternidad.agregar_arista("Riber","San Silencio")

    #print(paternidad.adyacentes("Boca"))
    #print(paternidad.adyacentes("Indemierda"))

    print(obtener_aristas(paternidad))

def pruebas_dos():
    grafo = Grafo(True)

    grafo.agregar_vertice("A")
    grafo.agregar_vertice("B")
    grafo.agregar_vertice("C")
    grafo.agregar_vertice("E")

    grafo.agregar_arista("A","B")
    grafo.agregar_arista("A","E")
    grafo.agregar_arista("A","C")
    grafo.agregar_arista("B","E")
    grafo.agregar_arista("C","E")

    print("Adyacentes de A:",grafo.adyacentes("A"))
    print(grafo.adyacentes("B"))
    print(grafo.adyacentes("C"))
    print(grafo.adyacentes("E"))

    print("Borro arrista B-A")
    grafo.borrar_arista("B","A")

    print("Adyacentes de A",grafo.adyacentes("A"))
    print("Adyacentes de B",grafo.adyacentes("B"))
    print(grafo.adyacentes("C"))
    print(grafo.adyacentes("E"))
    print(grafo.estan_conectados("A","X"))
    print(grafo.vertice_pertenece("B"))
    print(grafo.obtener_todos_vertices())
    #print(obtener_aristas(grafo))

def pruebas_no_dirigido():
    grafo = Grafo(False)
    print("No dirigido")
    grafo.agregar_vertice("A")
    grafo.agregar_vertice("B")
    grafo.agregar_vertice("C")
    grafo.agregar_vertice("E")

    grafo.agregar_arista("A","B")
    grafo.agregar_arista("A","E")
    grafo.agregar_arista("A","C")
    grafo.agregar_arista("B","E")
    grafo.agregar_arista("C","E")

    print("Adyacentes de A:",grafo.adyacentes("A"))
    print(grafo.adyacentes("B"))
    print(grafo.adyacentes("C"))
    print(grafo.adyacentes("E"))
    print("Borro arrista B-A")
    grafo.borrar_arista("B","A")
    print("Adyacentes de A:",grafo.adyacentes("A"))
    print(grafo.adyacentes("B"))
    print(grafo.adyacentes("C"))
    print(grafo.adyacentes("E"))

def main():
    #pruebas_grafo_dirigido()
    pruebas_dos()
    #pruebas_no_dirigido()



main()