#include "GRAFO.h"

GRAFO::GRAFO(char nombrefichero[]) {
	ElementoLista dummy, dummy1;
	unsigned i, h;
	ifstream textfile;
	textfile.open(nombrefichero);
	if (textfile.is_open()) {
		textfile >> (unsigned &) n >> (unsigned &) m >> (unsigned &) dirigido;
		LS.resize(n);
		LP.resize(n);
		for (unsigned k = 0; k < m; k++) {
			textfile >> (unsigned &) i >> (unsigned &) h;
			dummy.j = --h;
			dummy1.j = --i;
			LS[i].push_back(dummy);
			LP[h].push_back(dummy1);
			if (dirigido == 0) {
				dummy.j = i;
				dummy1.j = h;
				LS[h].push_back(dummy);
				LP[i].push_back(dummy1);
			}
		}
	}
	textfile.close();
}

void GRAFO::Mostrar_Grafo() {
	unsigned i, h;
	if (dirigido == 0) {
		cout << "El grafo no es dirigido." << endl;
	}
	else {
		cout << "El grafo es dirigido." << endl;
	}
	cout << "Dicho grafo tiene " << n << " nodos y " << m << " arcos." << endl;
	for (i = 0; i < n; i++) {
		cout << "Los sucesores del nodo " << (i+1) << " son: ";
		for (h = 0; h < LS[i].size(); h++) {
			cout << LS[i][h].j + 1 << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (i = 0; i < n; i++) {
		cout << "Los predecesores del nodo " << (i+1) << " son: ";
		for (h = 0; h < LP[i].size(); h++) {
			cout << LP[i][h].j + 1 << " ";
		}
		cout << endl;
	}
	
}

void GRAFO::ComponentesConexas() {
	unsigned i, compconexas = 0;
	vector<bool> visitado;
	visitado.resize(n,false);
	for (i = 0; i < n; i++) {
		if (visitado[i] == false) {
			compconexas++;
			cout << "La componente conexa (" << compconexas << ") tiene los nodos :"; dfs(i,visitado); 
			cout << endl;
		}
	}
	cout << endl;
}

void GRAFO::ComponentesFuertementeConexas() {
	unsigned i, compfconexas = 0, cont = n-1;
	vector<bool> visitado;
	vector<unsigned> order;
	visitado.resize(n,false);
	order.resize(n,UERROR);
	for(i = 0; i < n; i++) {
		if (visitado[i] == false) {
			dfsOrder(i,order,visitado,cont);
		}
	}
	
	for (i = 0; i < n; i++) {
		visitado[i] = false;
	}
	
	for (i = 0; i < n; i++) {
		if (visitado[order[i]] == false) {
			compfconexas++;
			cout << "La componente fuertemente conexa (" << compfconexas << ") esta formada por los nodos: " ;
			dfsInv(order[i],visitado);
			cout << endl;
		}
	}
}

void GRAFO::dfs(unsigned i, vector<bool> &visitado) {
	
	visitado[i] = true;
	cout << ++i << " ";
	i--;
	for (unsigned k = 0; k < LS[i].size(); k++) {
		if (visitado[LS[i][k].j] == false)
			dfs(LS[i][k].j,visitado);
	}
	
	if (dirigido == 1) {
		for (unsigned k = 0; k < LP[i].size(); k++) {
			if (visitado[LP[i][k].j] == false)
				dfs(LP[i][k].j,visitado);
		}
	}
}

void GRAFO::dfsOrder(unsigned i, vector<unsigned> &order, vector<bool> &visitado, unsigned &cont) {
	visitado[i] = true;
	for (unsigned k = 0; k < LS[i].size(); k++) {
		if (visitado[LS[i][k].j] == false) {
			dfsOrder(LS[i][k].j,order,visitado,cont);
		}
	}
	order[cont] = i;
	cont--;
}

void GRAFO::dfsInv(unsigned i, vector<bool> &visitado) {
	visitado[i] = true;
	cout << ++i << " ";
	--i;
	for (unsigned k = 0; k < LP[i].size(); k++) {
		if (visitado[LP[i][k].j] == false)
			dfsInv(LP[i][k].j,visitado);
	}
}

GRAFO::~GRAFO() {}

void menu() {
	cout << endl;
	cout << "1. Mostrar grafo" << endl;
	cout << "2. Componentes conexas" << endl;
	cout << "3. Componentes fuertemente conexas" << endl;
	cout << "4. Salir" << endl;
}

int main() {
	char nombrefichero[85];
	
	cout << "Escriba el nombre del fichero que desea cargar: ";
	cin >> nombrefichero;
	
	GRAFO grafo(nombrefichero);
	
	int opc = 0;
	
	while(opc != 4) {
		menu();
		cin >> opc;
		switch(opc) {
			case 1: 
				grafo.Mostrar_Grafo();
				break;
			case 2:
				grafo.ComponentesConexas();
				break;
			case 3:
				grafo.ComponentesFuertementeConexas();
				break;
		}
	}
	return 0;
}