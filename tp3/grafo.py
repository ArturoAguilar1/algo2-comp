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
             print("Vertice: '%s' ya existe" % str(clave_vertice))
    
    def borrar_vertice(self, vertice):
        if vertice not in self.vertices:
            return False
        #del self.vertices[vertice]
        for w in self.vertices.values():
            if vertice in w:
                w.pop(vertice)
        del self.vertices[vertice]
        self.cant_vertices -= 1


    def agregar_arista(self, v1, v2, peso):
        if v1 not in self.vertices or v2 not in self.vertices:
            return False
        self.vertices[v1][v2] = peso


    def borrar_arista(self, arista)

    def adyacentes(self, vertice):

    def vertice_en_grafo(self, vertice)

    def obtener_vertice(self, vertice):
        if vertice in self.vertices:
            return self.vertices[vertice]
        else:
            return None
    
    def vertice_pertenece(self, vertice):
        return vertice in self.vertices



    def __iter__(self):
        return iter(self.vertices)

'''
Primitivias: Lo saque de la lista, fue una respuesta de Martin
- Crear -> el init OK
- Destruir (si corresponde) -> En python creo que no hace falta destuir
- Agregar/Borrar un vértice -> agregar_vertice OK
- Agregar/Borrar una arista
- Ver si un vértice está en el grafo. -> vertice_pertenece OK 
- Si los vértices pudieran tener más información asociada, ver obtener dicha información (eso depende de la implementación, porque podría dejarse eso como algo externo). 
- Ver si dos vértices están conectados. 
- Obtener el peso de la unión de dos vértices (si fuera no pesado, podría ser 1). 
- Obtener todos los vértices
- Obtener un vértice aleatorio 
- Obtener los adyacentes a un vértice. 
- Obtener la cantidad de vértices.(len del grafo?)
- Tener alguna forma de iterarlo. -> con funcion iter de python
'''