'''
TDA Grafo 
'''

class Grafo:
    def __init__(self, es_nodirigido = False):
        self.vertices = {}
        self.es_nodirigido = es_nodirigido
        self.cant_vertices = 0
    

    def agregar_vertice(self, vertice, dato = None):
        if vertice not in self.vertices:
            self.vertices[vertice] = {}
            self.cant_vertices += 1
        else: #Solo para probar el grafo, despues habria que borrar este else
             print("Vertice: '%s' ya existe" % str(vertice))
    
    def borrar_vertice(self, vertice):
        if vertice not in self.vertices:
            return False
        #del self.vertices[vertice]
        for w in self.vertices.values():
            if vertice in w:
                w.pop(vertice)
        del self.vertices[vertice]
        self.cant_vertices -= 1


    def agregar_arista(self, v1, v2, peso = None):
        if v1 not in self.vertices or v2 not in self.vertices:
            return False
        self.vertices[v1][v2] = peso
        if self.es_nodirigido:      #Si el grafo es no dirigido, se tiene que agregar la arista de "vuelta"
            self.vertices[v2][v1] = peso


    def borrar_arista(self, v1, v2):
        if v1 not in self.vertices or v2 not in self.vertices[v1]:
            return False
        self.vertices[v1].pop(v2)
        return True
        

    def adyacentes(self, vertice):
        if vertice in self.vertices:
            return self.vertices[vertice].keys()

    def obtener_vertice(self, vertice):
        if vertice in self.vertices:
            return self.vertices[vertice]
        else:
            return None
    
    def vertice_pertenece(self, vertice):
        return vertice in self.vertices

    def vertices_cantidad(self):
        #o se puede hacer con un len(self.vertices)
        return self.cant_vertices
    
    def estan_conectados(self,v1,v2):
        return v2 in self.vertices[v1]
    
    def obtener_todos_vertices(self):
        #Ver despues si habria que devolver una copia de los vertices, como enadyacentes
        return self.vertices.keys()

    def obtener_peso(self, v1, v2):
        if v1 not in self.vertices or v2 not in self.vertices:
            return False
        return self.vertices[v1][v2]

    def __iter__(self):
        return iter(self.vertices)

"""
    Dicc=set(["ArturoAguilar","Hola","Buenas","Dijkstra"])
    d = 0
    for d in Dicc:
        if "Buenas" in Dicc:
            print("El buenas esta en dicc")
            break
        else:
            print(d)
    
    #for clave in graph.items():
        #elemenetos = ",".join(valor.keys())
#    print(graph.keys())
 #   print(graph.values())
  #  print(graph.items())
    print(len(graph))
    if 'C' in graph:
        del graph['C']
    print(len(graph))
    print(graph.keys())
    graph['Z'] = {'A':' '}
    print(graph.keys())
    print(graph.items())
    for v in graph.values():
        if 'B' in v:
            v.pop('B')
    print(graph.keys())
    print(graph.items())

    graph = {
    'A' : {'B' : '', 'C': ''},
    'B' : {'A' : '4', 'D': '8'},
    'C' : {'D': '0'},
    'D' : {'B': '2'}
}

"""