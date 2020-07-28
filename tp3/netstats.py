#!/usr/bin/python3

import random
import sys
import grafo
import biblioteca



def main():
    Dicc=set(["ArturoAguilar","Hola","Buenas","Dijkstra"])
    d = 0
    for d in Dicc:
        if Dicc[d] == "Buenas":
            print("Encontre el Buenas")
        else:
            print(d)

#if __name__ == "__main__":
main()