/*
 *  GRAFO.h - definicion de la clase GRAFO
 *
 *  Autor : Antonio Sede§o Noda
 *  Fecha : 20-ENERO-2011
 */

#ifndef _GRAPH_H
#define _GRAPH_H


#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;


#define gotoxy(x,y)  printf("\33[%d;%dH",y,x)
#define clrscr()     gotoxy(1,1); printf("\33[2J")

const unsigned UERROR = 65000;


// definiciÛn de un elemento de la lista de adyacencia

typedef struct
{
	unsigned j; // nodo
	int      c; // peso, longitud, etc...
} ElementoLista;

// definiciÛn del tipo de una lista de adyacencia de un nodo

typedef vector<ElementoLista> LA_nodo;


class GRAFO
{
	unsigned            dirigido;  //0 si el grafo es no dirigido y 1 si es dirigido 
	unsigned            n;         /* n˙mero de NODOS */
	unsigned            m;         /* n˙mero de ARCOS */
	vector<LA_nodo>     LS;        /* Lista de adyacencia de los sucesores    es una matriz dode cada fila posiblemente es posiblemente de distinto tamaÒo*/
	vector<LA_nodo>     LP;        /* Lista de adyacencia de los Predecesores es una matriz dode cada fila posiblemente es posiblemente de distinto tamaÒo*/
public:
	GRAFO(char nombrefichero[]);
	void Mostrar_Grafo();
	void ListaPredecesores();
	void ComponentesConexas();
	void dfs(unsigned i, vector<bool> &visitado);
	void ComponentesFuertementeConexas();
	void dfsOrder(unsigned i, vector<unsigned> &order, vector<bool> &visitado, unsigned &cont);
	void dfsInv(unsigned i, vector<bool> &visitado);
	~GRAFO();
};


#endif
