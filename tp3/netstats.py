#!/usr/bin/python3

import random
import sys

import biblioteca


graph = {
    'A' : {'B' : '', 'C': ''},
    'B' : {'A' : '4', 'D': '8'},
    'C' : {'D': '0'},
    'D' : {'B': '2'}
}


def main():
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

#if __name__ == "__main__":
main()