
template<typename T>
class Lista {
private:
	T* dados;
	int ultimo;
	int tamanho;

public:
	Lista();
	explicit Lista(int tam);
	void adiciona(T dado);
	void adicionaNoInicio(T dado);
	void adicionaNaPosicao(T dado, int posicao);
	void adicionaEmOrdem(T dado);
	T retira();
	T retiraDoInicio();
	T retiraDaPosicao(int posicao);
	T retiraEspecifico(T dado);
	int posicao(T dado);
	bool contem(T dado);
	bool igual(T dado1, T dado2);
	bool maior(T dado1, T dado2);
	bool menor(T dado1, T dado2);
	bool listaCheia();
	bool listaVazia();
	void destroiLista();
	void print();
};

