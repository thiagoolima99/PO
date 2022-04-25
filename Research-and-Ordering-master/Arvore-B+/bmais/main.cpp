#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <sstream>
#include <vector>

#define tsdefault getCurrentPath() + "/ts_default"

#define CONTROLEINICIO '('
#define CONTROLEFINAL ')'
#define DEBUG 1
#define DEBUGARG 0
#define DEBUGARQ 0
#define DEBUGVAL 0
#define NODOINICIO '['
#define NODODIVISOR '|'
#define NODOFIM ']'
#define NULO -99999999

using namespace std;

//Estruturas
class Folha{
private:
    int valEsq,valDir,valExtra;
    Folha *ant,*prox;
public:
    Folha(){
        this->valEsq = NULO;
        this->valDir = NULO;
        this->valExtra = NULO;
        this->ant = NULL;
        this->prox = NULL;
    }
    void setValEsq(int newValEsq){
        this->valEsq = newValEsq;
    }
    int getValEsq(){
        return this->valEsq;
    }
    void setValDir(int newValDir){
        this->valDir = newValDir;
    }
    int getValDir(){
        return this->valDir;
    }
    void setValExtra(int newValExtra){
        this->valExtra = newValExtra;
    }
    int getValExtra(){
        return this->valExtra;
    }
    void setAnt(Folha *newAnt){
        this->ant = newAnt;
    }
    Folha* getAnt(){
        return this->ant;
    }
    void setProx(Folha *newProx){
        this->prox = newProx;
    }
    Folha* getProx(){
        return this->prox;
    }
};
class Nodo{
private:
    int val1,val2,val3;
    Folha *fEsq,*fMeio,*fDir;
    Nodo  *nEsq,*nMeio,*nDir;
public:
    Nodo(){
        this->val1 = this->val2 = this->val3 = -1;
        this->fEsq = this->fMeio = this->fDir = NULL;
        this->nEsq = this->nMeio = this->nDir = NULL;
    }
    void setValor1(int newValor){
        this->val1 = newValor;
    }
    int getValor1(){
        return this->val1;
    }
    void setValor2(int newValor){
        this->val2 = newValor;
    }
    int getValor2(){
        return this->val2;
    }
    void setValor3(int newValor){
        this->val3 = newValor;
    }
    int getValor3(){
        return this->val3;
    }
    void setFolhaEsquerda(Folha *newFolha){
        this->fEsq = newFolha;
    }
    Folha* getFolhaEsquerda(){
        return this->fEsq;
    }
    void setFolhaDireita(Folha *newFolha){
        this->fDir = newFolha;
    }
    Folha* getFolhaDireita(){
        return this->fDir;
    }
    void setFolhaMeio(Folha *newFolha){
        this->fMeio = newFolha;
    }
    Folha* getFolhaMeio(){
        return this->fMeio;
    }
    void setNodoEsquerda(Nodo *newNodo){
        this->nEsq = newNodo;
    }
    Nodo* getNodoEsquerda(){
        return this->nEsq;
    }
    void setNodoDireita(Nodo *newNodo){
        this->nDir = newNodo;
    }
    Nodo* getNodoDireita(){
        return this->nDir;
    }
    void setNodoMeio(Nodo *newNodo){
        this->nMeio = newNodo;
    }
    Nodo* getNodoMeio(){
        return this->nMeio;
    }
};
class Raiz{
private:
    int qntElem;
    Folha *inicio;
public:
    Raiz(){
        this->qntElem = 0;
        this->inicio = NULL;
    }
    void setQntElem(int newQnt){
        this->qntElem = newQnt;
    }
    void atualizaQntElem(){
        this->qntElem = this->qntElem + 1;
    }
    void removeElem(){
        if(this->qntElem > 0)
			this->qntElem = this->qntElem - 1;
    }
    int getQntElem(){
        return this->qntElem;
    }
    void setInicio(Folha *newInicio){
        this->inicio = newInicio;
    }
    Folha* getInicio(){
        return this->inicio;
    }
};
class Topo{
private:
    Nodo *inicio;
public:
    Topo(){
        this->inicio = NULL;
    }
    void setInicio(Nodo *newInicio){
        this->inicio = newInicio;
    }
    Nodo* getInicio(){
        return this->inicio;
    }
};

typedef struct{
	Nodo arvore[50][50];
}Arvore;

//Manipulação de Arquivos
void imprimeNodo(Nodo *nodo){
	if(nodo != NULL){
		cout <<nodo->getValor1();
		if(nodo->getValor2() != NULO)
			cout <<" | "<<nodo->getValor2();
		cout <<endl;
	}else
		cout <<"Nodo nulo"<<endl;
}

int analisaNodo(Nodo *nodo){
	int contador=0;
	if(nodo->getValor1() != NULO)
		contador = 2;
	
	if(nodo->getValor2() != NULO)
		contador = 3;
	
	return contador;
}

//Converte inteiro para string
string intToString(int numero){
	std::stringstream ss;
	ss << numero;
	string str = ss.str();
	return str;
}

vector<string> explodeStr(const string& str, const char& ch) {
    string next;
    vector<string> result;
    
    // For each character in the string
    for (string::const_iterator it = str.begin(); it != str.end(); it++) {
        // If we've hit the terminal character
        if (*it == ch) {
            // If we have some characters accumulated
            if (!next.empty()) {
                // Add them to the result vector
                result.push_back(next);
                next.clear();
            }
        } else {
            // Accumulate the next character into the sequence
            next += *it;
        }
    }
    if (!next.empty())
        result.push_back(next);
    return result;
}

//Decodifica a estrutura da folha a partir de uma string e atualiza os ponteiros das folhas e da raiz
void decodificaFolha(string structFolha,Raiz *raiz){
	Folha *novaFolha = (Folha*)malloc(sizeof(Folha));
	string valorEsquerda,valorDireita;
	if(structFolha.find(NODODIVISOR)!=-1){
        //Separa a string da Estrutura Folha no valor da direita e da esquerda
        valorEsquerda = structFolha.substr(0,structFolha.find(NODODIVISOR));
        valorDireita = structFolha.substr(structFolha.find(NODODIVISOR)+1);
        novaFolha->setValEsq(atoi(valorEsquerda.c_str()));//Seta o valor da esquerda da nova folha
        novaFolha->setValDir(atoi(valorDireita.c_str()));//Seta o valor da direita da nova folha
        novaFolha->setValExtra(NULO);//Seta o valor extra da nova folha para NULO
        novaFolha->setProx(raiz->getInicio());//Faz a nova folha apontar para o inicio atual como seu sucessor
        if(raiz->getInicio()!=NULL)//Se o inicio da raiz não for NULL
            raiz->getInicio()->setAnt(novaFolha);//Faz o inicio atual apontar para a nova folha como sua precedente
        raiz->setInicio(novaFolha);//Faz o inicio atual apontar para a nova folha
    }else{
        novaFolha->setValEsq(atoi(structFolha.c_str()));//Seta o valor da esquerda da nova folha
        novaFolha->setValDir(NULO);//Seta o valor da direita da nova folha para NULO
        novaFolha->setValExtra(NULO);//Seta o valor extra da nova folha para NULO
        novaFolha->setProx(raiz->getInicio());//Faz a nova folha apontar para o inicio atual
        if(raiz->getInicio()!=NULL)
            raiz->getInicio()->setAnt(novaFolha);//Faz o inicio atual apontar para a nova folha como sua precedente
        raiz->setInicio(novaFolha);//Faz o inicio atual apontar para a nova folha
    }
}

void imprimeOrdem(Raiz *raiz){
	
	Folha *atual;
	int cont = 0;
	atual = raiz->getInicio();
	cout <<"| ";
	while (atual != NULL){
        cont++;
        cout << atual->getValEsq() << " | ";
        if(atual->getValDir() != NULO){
            cout <<atual->getValDir()<<" | ";
		}
		atual = atual->getProx();
	}
	cout <<endl;
}

bool checkFile(char *texto){//Verifica se o arquivo existe
	ifstream fr(texto);
	if(fr.good()){
		fr.close();
		return true;
	}else{
		fr.close();
    	return false;
	}
}



bool createFile(char *texto){//Cria o arquivo
	if(checkFile(texto)){
		if(DEBUG){
			cout<<"Arquivo ja existe, nao e possivel criar."<<endl;
		}
        return false;
	}else{
        ofstream f(texto,ios::app);
        f.close();
        return true;
	}
}

Nodo createNodo(string structNodo){
	Nodo *novoNodo = (Nodo*)malloc(sizeof(Nodo));
	string valorEsquerda,valorDireita;
	if(structNodo.find(NODODIVISOR)!=-1){
        //Separa a string da Estrutura nodo no valor da direita e da esquerda
        valorEsquerda = structNodo.substr(0,structNodo.find(NODODIVISOR));
        valorDireita = structNodo.substr(structNodo.find(NODODIVISOR)+1);
        novoNodo->setValor1(atoi(valorEsquerda.c_str()));//Seta o valor da esquerda da nova folha
        novoNodo->setValor2(atoi(valorDireita.c_str()));//Seta o valor da direita da nova folha
        novoNodo->setValor3(NULO);//Seta o valor extra da nova folha para NULO
        novoNodo->setFolhaDireita(NULL);
        novoNodo->setFolhaEsquerda(NULL);
        novoNodo->setFolhaMeio(NULL);
        novoNodo->setNodoEsquerda(NULL);
        novoNodo->setNodoDireita(NULL);
        novoNodo->setNodoMeio(NULL);
        return *novoNodo;
    }else{
        novoNodo->setValor1(atoi(structNodo.c_str()));//Seta o valor da esquerda da nova folha
        novoNodo->setValor2(NULO);//Seta o valor da direita da nova folha para NULO
        novoNodo->setValor3(NULO);//Seta o valor extra da nova folha para NULO
        novoNodo->setFolhaDireita(NULL);
        novoNodo->setFolhaEsquerda(NULL);
        novoNodo->setFolhaMeio(NULL);
        novoNodo->setNodoEsquerda(NULL);
        novoNodo->setNodoDireita(NULL);
        novoNodo->setNodoMeio(NULL);
        return *novoNodo;
    }
}

vector<Nodo> decodificaNodos(Topo *topo, string line){
    string estruturaNodo;
    Nodo nodoCriado;
    vector<Nodo> nodosCriados;
    
    while(line != "\0"){
        //Separa o ultimo nodo recebido na string do resto
        estruturaNodo = line.substr(line.rfind(NODOINICIO)+1, line.rfind(NODOFIM)-line.rfind(NODOINICIO)-1);
        //Cria o novo nodo
        nodoCriado = createNodo(estruturaNodo);
        //Coloca no vector
        nodosCriados.push_back(nodoCriado);
        //Retira a parte usada recentemente
        line = line.substr(0,line.rfind(NODOINICIO));
    }
    return nodosCriados;
}

void decodificaRaiz(string line,Raiz *raiz,bool controle){//Decodifica a primeira linha do arquivo, da raiz
	if(controle){
		//Procura os delimitadores de controle e converte para int
		string quantidadeElementos = line.substr(line.rfind(CONTROLEINICIO)+1,line.rfind(CONTROLEFINAL)-1);
		//Coloca na raiz, o valor encontrado é o numero de elementos na árvore
		raiz->setQntElem(atoi(quantidadeElementos.c_str()));
		//Atualiza a string line somente com os valores dos nodos, sem o controle
		line = strrchr(line.c_str(),CONTROLEFINAL)+1;
		decodificaRaiz(line,raiz,false);//Chama a função novamente para decodificar o resto
	}else{
		string estruturaFolha;
		//Separa o primeiro nodo recebido do resto
		estruturaFolha = line.substr(line.rfind(NODOINICIO)+1, line.rfind(NODOFIM)-line.rfind(NODOINICIO)-1);
		//Separa a estrutura da folha baseada na constante NODODIVISOR, verificando se ela existe ( 2 valores ) ou não ( 1 valor )
		decodificaFolha(estruturaFolha,raiz);
		//Atualiza a string, retirando o nodo usado recentemente
		line = line.substr(0,line.rfind(NODOINICIO));
		if(line != "\0")//Se a linha não for em branco, continua decodificando
            decodificaRaiz(line,raiz,false);
	}
    
}

struct Folha *atribuiFolhas(struct Nodo *n,struct Nodo *p, struct Folha *f){
    struct Folha *ultimaFolha = f;
    cout << "passando pelo nodo" << endl;
    if (n->getValor1()) {
        cout << "v1: " << n->getValor1();
    }
    if (n->getValor2()) {
        cout << " v2: " << n->getValor2();
    }
    if (n->getValor3()) {
        cout << " v3: " << n->getValor3() << endl;
    }
    
    if(!n->getNodoEsquerda()&&!n->getNodoMeio()&&!n->getNodoDireita()){
        cout << "quase folha: " << endl;
        if ( f->getValEsq() <= n->getValor1() && f->getValDir() <= n->getValor1() && n->getValor1()!=NULO) {
            if (!n->getFolhaEsquerda()) {
                n->setFolhaEsquerda(f);
                f = f->getProx();
                ultimaFolha = f;
                
            }else if (n->getFolhaEsquerda() && !n->getFolhaMeio()){
                n->setFolhaMeio(f);
                f = f->getProx();
                ultimaFolha = f;
            }else if (n->getFolhaEsquerda() && n->getFolhaMeio() && !n->getFolhaDireita()){
                n->setFolhaDireita(f);
                f = f->getProx();
                ultimaFolha = f;
            }
        }
        if ( (f->getValEsq() >= n->getValor1() && f->getValDir() >= n->getValor1() && n->getValor1()!=NULO) || (f->getValEsq() >= n->getValor2() && f->getValDir() >= n->getValor2()) || f->getValEsq()==n->getValor1()) {
            if (!n->getFolhaEsquerda()) {
                n->setFolhaEsquerda(f);
                f = f->getProx();
                ultimaFolha = f;
            }else if (n->getFolhaEsquerda() && !n->getFolhaMeio()){
                n->setFolhaMeio(f);
                f = f->getProx();
                ultimaFolha = f;
            }else if (n->getFolhaEsquerda() && n->getFolhaMeio() && !n->getFolhaDireita()){
                n->setFolhaDireita(f);
                f = f->getProx();
                ultimaFolha = f;
            }
        }
        if ( f->getValEsq() == n-> getValor1() && f->getValDir() == n->getValor2() && n->getValor1()!=NULO && n->getValor2()!=NULO) {
            n->setFolhaMeio(f);
            f = f->getProx();
            ultimaFolha = f;
            
        }
        
        return ultimaFolha;
    }else{
        if (n->getNodoEsquerda()) {
            ultimaFolha = atribuiFolhas(n->getNodoEsquerda(),n, ultimaFolha);
        }
        if (n->getNodoMeio()) {
            ultimaFolha = atribuiFolhas(n->getNodoMeio(),n, ultimaFolha);
            
        }
        if (n->getNodoDireita()) {
            ultimaFolha = atribuiFolhas(n->getNodoDireita(),n, ultimaFolha);
        }
        if (p) { //estamos na raiz?
            if (f->getValEsq() >= p->getValor1() || f->getValEsq() >= p->getValor2() || f->getValDir() >= p->getValor1() || f->getValDir() >= p->getValor2()) {
                return ultimaFolha;
            }
/*            if (n->getNodoMeio()) {
                salto += atribuiFolhas(n->getNodoMeio(),n, f);
                while (salto!=0) {
                    f=f->getProx();
                    salto--;
                }
            }*/
            if (f->getValEsq() >= p->getValor1() || f->getValEsq() >= p->getValor2() || f->getValDir() >= p->getValor1() || f->getValDir() >= p->getValor2()) {
                return ultimaFolha;
            }
            /*if (n->getNodoDireita()) {
                salto += atribuiFolhas(n->getNodoDireita(),n, f);
                while (salto!=0) {
                    f=f->getProx();
                    salto--;
                }
            }*/
            if (f->getValEsq() >= p->getValor1() || f->getValEsq() >= p->getValor2() || f->getValDir() >= p->getValor1() || f->getValDir() >= p->getValor2()) {
                return ultimaFolha;
            }
        }else{
            
            return ultimaFolha;
        }
    }
    
    return ultimaFolha;
}

bool lerDecodificado(char *nomeArquivo,Raiz *raiz, Topo *topo){//Lê o arquivo decodificado
    
    ifstream fileReader(nomeArquivo);//Abre o arquivo recebido por argumento
    string line;
    if(fileReader.is_open())//Se o arquivo foi aberto com sucesso
        getline(fileReader,line);
    if(line == "\0")//Se a linha for nula, sai da função
        return false;
    //Decodifica a linha da raiz
    decodificaRaiz(line,raiz,true);
    vector<Nodo> nodosAnteriores;
    Nodo nAnteriores[50];
    vector<Nodo> nodosAtuais;
    Nodo *novoInicio,*nodoAux;
    novoInicio = (Nodo*) malloc(sizeof(Nodo));
    
    int contadorControle,proxIndice,cont;
    while(fileReader.good()){//Enquanto o arquivo puder ser lido
        getline(fileReader,line);
        if(line != "\0"){//Se a linha não for vazia
            
            nodosAnteriores = nodosAtuais;	//Atualiza os nodosAnteriores
            nodosAtuais = decodificaNodos(topo,line);//Atualiza os nodosAtuais
            proxIndice = nodosAnteriores.size() -1;//Seta o valor do próximo indice, serve pra controle dos ponteiramentos
            
            if(!nodosAnteriores.empty()){//Se os nodos Anteriores não forem nulos, então eu ja sai de perto da raiz
                for(int i = nodosAtuais.size()-1;i>-1;i--){//Percore os nodos atuais de trás pra frente (menor para maior)
                    cont = 0;
                    contadorControle = analisaNodo(&nodosAtuais[i]);//Atualiza o contador que controla quantos ponteiramentos devo fazer
                    if(contadorControle == 2){
                        //Alocando novo espaço na memória, copiando conteúdo do vector e fazendo aponteiramento
                        nodoAux = (Nodo*) malloc(sizeof(Nodo));
                        memcpy(nodoAux,&nodosAnteriores[proxIndice],sizeof(Nodo));
                        nodosAtuais[i].setNodoEsquerda(nodoAux);
                        proxIndice--;
                        
                        nodoAux = (Nodo*) malloc(sizeof(Nodo));
                        memcpy(nodoAux,&nodosAnteriores[proxIndice],sizeof(Nodo));
                        nodosAtuais[i].setNodoMeio(nodoAux);
                        proxIndice--;
                    }else if(contadorControle == 3){
                        nodoAux = (Nodo*) malloc(sizeof(Nodo));
                        memcpy(nodoAux,&nodosAnteriores[proxIndice],sizeof(Nodo));
                        nodosAtuais[i].setNodoEsquerda(nodoAux);
                        proxIndice--;
                        
                        nodoAux = (Nodo*) malloc(sizeof(Nodo));
                        memcpy(nodoAux,&nodosAnteriores[proxIndice],sizeof(Nodo));
                        nodosAtuais[i].setNodoMeio(nodoAux);
                        proxIndice--;
                        
                        nodoAux = (Nodo*) malloc(sizeof(Nodo));
                        memcpy(nodoAux,&nodosAnteriores[proxIndice],sizeof(Nodo));
                        nodosAtuais[i].setNodoDireita(nodoAux);
                        proxIndice--;
                    }
                }
            }else{//Se o NodosAnteriores estiver vazio, cai aqui, significa que estou trabalhando no nível próximo da raiz
                //Aqui se deve fazer o ponteiramento do nível mais próximo da raiz para as folhas da raiz
                //O segredo é que aqui, cada valor1 do nodo(exceto do primeiro nodo) vai existir em algum ValEsq das folhas
                //Então é só andar na raiz e descobrir onde está o valor que está no nodo e apontar
                //A raiz já se encontra em memória em pleno funcionamento
                cout << "else do aponteiramento das folhas" << endl;
                
            }
            memcpy(novoInicio,&nodosAtuais.at(nodosAtuais.size()-1),sizeof(Nodo));
            topo->setInicio(novoInicio);//Seta o novo início
        }
    }
    atribuiFolhas(topo->getInicio(),NULL, raiz->getInicio());
    fileReader.close();
    return true;
}

string raizToString(Raiz *raiz,char *nomeArquivo){
	Folha *atual;
	string linhaRaiz,linhaAtual,vEsq,vDir;//Cria as strings auxiliares
	atual = raiz->getInicio();//Faz a folha atual apontar para o inicio da raiz
	linhaRaiz = CONTROLEINICIO+intToString(raiz->getQntElem())+CONTROLEFINAL;//Atualiza a string da raiz com o numero de controle
	while (atual != NULL){
		vEsq = intToString(atual->getValEsq());//Transforma o valor da esquerda para string
		vDir = intToString(atual->getValDir());//Transforma o valor da direita para string
		if(atual->getValDir()!=NULO)//Se o valor da sireita existir
			linhaAtual = NODOINICIO+vEsq+NODODIVISOR+vDir+NODOFIM;
		else//Caso ele não exista
			linhaAtual = NODOINICIO+vEsq+NODOFIM;
		
		//Cria a string da raiz, concatenando com a string atual
		linhaRaiz = linhaRaiz + linhaAtual;
		atual = atual->getProx();//Faz o atual apontar para o seu próximo
	}
	return linhaRaiz;
}

void gravarDecodificado(char *nomeArquivo,Raiz *raiz,Topo *topo){
	vector<string> nodos;
	string linhaRaiz = raizToString(raiz,nomeArquivo);
	linhaRaiz= linhaRaiz + "\n";
	cout <<linhaRaiz;
	//ofstream file(nomeArquivo);
	ofstream file;
    file.open(nomeArquivo);
    cout<<"Aperte qualquer tecla para continuar e gravar no arquivo: "<<endl;
    getchar();
	file << linhaRaiz;
	file.close();
    
}


//Funções de manipulação da árvore
bool divideFolha(Folha *folha){
	Folha *novaFolha = (Folha *) malloc(sizeof(Folha));
	//Seta os valores da nova folha
	novaFolha->setValEsq(folha->getValDir());
	novaFolha->setValDir(folha->getValExtra());
	novaFolha->setValExtra(NULO);
	folha->setValDir(NULO);
	folha->setValExtra(NULO);
	if(folha->getProx() != NULL){
		folha->getProx()->setAnt(novaFolha);
		novaFolha->setProx(folha->getProx());
	}else{
		novaFolha->setProx(NULL);
	}
	folha->setProx(novaFolha);
	novaFolha->setAnt(folha);
	return true;
	
}

bool removeFolha(Folha *folha){
	if(folha->getAnt() != NULL){
		folha->getAnt()->setProx(folha->getProx());
		if(folha->getProx() != NULL)
			folha->getProx()->setAnt(folha->getAnt());
	}else{
		folha->getProx()->setAnt(NULL);
	}
	free(folha);
	return true;
}

bool verificaArvore(Raiz *raiz,Topo *topo){
	//Verifica se existe valor no valor extra da raiz ( inserção extra )
	Folha *atual = raiz->getInicio();
	while (atual->getValExtra()==NULO){
		if(atual->getProx() != NULL)
			atual = atual->getProx();
		else
			break;
	}
	if(atual->getValExtra() != NULO){
        divideFolha(atual);
	}
	//Verifica se existe algum valor da esquerda NULO ( remoção total )
	atual = raiz->getInicio();
	while (atual->getValEsq()!=NULO){
		if(atual->getProx() != NULL)
			atual = atual->getProx();
		else
			break;
	}
	if(atual->getValEsq() == NULO){
        removeFolha(atual);
	}
	return true;
}

bool inserir(Raiz *raiz,int novoValor,Topo *topo,char *nomeArquivo){
	bool end = false;
    if(raiz->getInicio()==NULL){//Se a árvore for nula entra para criar a primeira folha
        Folha *newFolha = (Folha*)malloc(sizeof(Folha));//Cria a nova folha e aloca memória
        *newFolha = Folha();//Constroi o objeto
        newFolha->setValEsq(novoValor);//Insere o valor
        raiz->setInicio(newFolha);//Faz a raiz apontar para a nova folha
        raiz->atualizaQntElem();//Atualiza a quantidade de elementos da arvore
        return true;
    }else{//Se a raiz não for nula, então entra nessa opção
        Folha *atual = raiz->getInicio();
        Folha *anterior = NULL;
        while(atual->getValEsq()<novoValor){//Enquanto o novo valor for maio que o primeiro valor da folha
            if (novoValor == atual->getValDir() || novoValor == atual->getValEsq() || novoValor == atual->getValExtra()) {
                cout << "valor " << novoValor << " já existente, não foi inserido." << endl;
                return false;
            }else{
                if(atual->getProx() == NULL){//Se o proximo nodo for NULL, chegou ao ultimo nodo
                    if((novoValor > atual->getValDir())&&(atual->getValDir()!=NULO)){
                        atual->setValExtra(novoValor);
                        //divideFolha(atual);
                        raiz->atualizaQntElem();
                    }else if((novoValor < atual->getValDir())&&(atual->getValDir()!=NULO)){
                        atual->setValExtra(atual->getValDir());
                        atual->setValDir(novoValor);
                        //divideFolha(atual);
                        raiz->atualizaQntElem();
                    }else if(atual->getValDir()==NULO){
                        atual->setValDir(novoValor);
                        raiz->atualizaQntElem();
                    }else{
                        return false;
                    }
                    end = true;
                    break;
                }
                anterior = atual;
                atual = atual->getProx();
            }
        }
        if(!end){//Não chegou ao fim da lista
            if(anterior == NULL){//Não entrou uma vez no laço
                atual->setValDir(atual->getValEsq());
                atual->setValEsq(novoValor);
                raiz->atualizaQntElem();
			}else if((novoValor > anterior->getValDir())&&(anterior->getValDir()!=NULO)){
                anterior->setValExtra(novoValor);
                //divideFolha(anterior);
                raiz->atualizaQntElem();
            }else if((novoValor < anterior->getValDir())&&(anterior->getValDir()!=NULO)){
                anterior->setValExtra(anterior->getValDir());
                anterior->setValDir(novoValor);
                //divideFolha(anterior);
                raiz->atualizaQntElem();
            }else if(anterior->getValDir()==NULO){
                anterior->setValDir(novoValor);
                raiz->atualizaQntElem();
            }else{
                return false;
            }
            
        }
        verificaArvore(raiz,topo);
        
        string linhaRaiz = raizToString(raiz,nomeArquivo);
        linhaRaiz= linhaRaiz + "\n";
        cout <<linhaRaiz;
        cout << "|<>|"<<endl;
        return true;
	}
	return false;
}

bool remover(Raiz *raiz,int valor,Topo *topo){
	Folha *atual = raiz->getInicio();
	if (atual == NULL)
		return false;
	
	if(atual->getProx() == NULL){//Se o próximo da raiz for nulo, esta é a única folha
		if(valor == atual->getValEsq()){//Se o valor for o da esquerda
			if(atual->getValDir() == NULO){//Se o valor da direita for NULO, a folha só tem um valor
				free(atual);//Libera a raiz
				raiz->setInicio(NULL);//Seta a raiz pra NULL
				raiz->removeElem();
				return true;
			}else{
				atual->setValEsq(atual->getValDir());
				atual->setValDir(NULO);
				raiz->removeElem();
				return true;
			}
		}else if(valor == atual->getValDir()){//Se o valor for o da direita
			atual->setValDir(NULO);
			raiz->removeElem();
			return true;
		}
		return false;
	}else{//Caso exista mais de uma folha
		bool found = false;
		bool ended = false;
		while (!ended){//enquanto não achar o valor
			if(atual->getValEsq() == valor){//O valor requisitado encontra-se na esquerda da folha
				if(atual->getValDir()==NULO){//Se o valor da direita for NULO
					atual->setValEsq(NULO);//Seta o valor da esquerda para NULO
					raiz->removeElem();
					found = true;
					ended = true;
				}else{//Se o valor da direita não for NULO
					atual->setValEsq(atual->getValDir());
					atual->setValDir(NULO);
					raiz->removeElem();
					found = true;
					ended = true;
				}
			}else if(atual->getValDir() == valor){//Se o valor encontrado for o da direita
				atual->setValDir(NULO);
				raiz->removeElem();
				found = true;
				ended = true;
			}
			if(atual->getProx()!=NULL)//Se o próximo não for nulo, continua
				atual = atual->getProx();
			else
				ended = true;
		}
		if(found){
			verificaArvore(raiz,topo);
			return true;
		}
	}
	return false;
}

std::string exec(char* cmd) {
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "";
    while(!feof(pipe)) {
    	if(fgets(buffer, 128, pipe) != NULL)
    		result += buffer;
    }
    pclose(pipe);
    return result;
}

int main(int argc, char **argv){
    
	if(argc > 1){
		if(DEBUGARG){
			for (int i=1;i<argc;i++){
                cout<<argv[i]<<" | ";
			}
			cout <<endl;
		}
        
		if(strcmp(argv[1],"-c")==0){//Caso seja passado o argumento -c, será criado o arquivo da árvore
			createFile(argv[2]);
		}else{//Se o argumento -c não foi recebido, então é feita alguma operação com um arquivo recebido
			if(DEBUGARQ){
                cout << "Comecando impressao do arquivo "<<argv[1]<<":"<<endl;
                ifstream fileReader(argv[1]);//Abre o arquivo recebido por argumento
                string line;
                if(fileReader.is_open()){//Se o arquivo foi aberto com sucesso
                    while (getline(fileReader,line)){//Vai pegando as linhas do arquivo
                        cout <<line <<'\n';//Imprime cada linha
                    }
                }
                fileReader.close();
                cout <<endl;
            }
			Raiz raiz=Raiz();
			Topo topo=Topo();
		  	if(checkFile(argv[1])){//Checa se o arquivo recebido existe e se é valido
				
				lerDecodificado(argv[1],&raiz,&topo);
				if(strcmp(argv[2],"-i")==0){
					if(DEBUGVAL){
						cout<<"Selecionou inserir os valores: "<<endl;
						for(int i=3;i<argc;i++){
							cout<<argv[i] << " | " ;
						}
						cout<<endl;
					}
					
					for(int i=3;i<argc;i++){
                        cout <<"Inserindo "<<argv[i]<<endl;
                        inserir(&raiz,atoi(argv[i]),&topo,argv[1]);
                    }
					
					//cout <<raiz.getQntElem() <<" | "<<raiz.getInicio()->getValEsq()<<endl;
					
                    
				}else if(strcmp(argv[2],"-r")==0){
					if(DEBUGVAL){
						cout<<"Selecionou remover os valores: "<<endl;
						for(int i=3;i<argc;i++){
							cout<<argv[i] << " | " ;
						}
						cout<<endl;
					}				
                    
					for(int i=3;i<argc;i++){
                        cout <<"Removendo "<<argv[i]<<endl;
                        remover(&raiz,atoi(argv[i]),&topo);
                    }
					
				}else if(strcmp(argv[2],"-o")==0){
					cout<<endl<<"Imprimindo a árvore em ordem:"<<endl;
					imprimeOrdem(&raiz);
					cout <<endl;
				}else if(strcmp(argv[2],"-l")==0){
					cout <<"Imprimindo level "<<argv[3]<<":"<<endl;
					if(strcmp(argv[3],"0")==0){
						imprimeOrdem(&raiz);
					}else{
						
					}
                    
				}else if(strcmp(argv[2],"-s")==0){
					if(DEBUGVAL){
						cout<<"Selecionou procurar os valores: "<<endl;
						for(int i=3;i<argc;i++){
							cout<<argv[i] << " | " ;
						}
						cout<<endl;
					}
                    
				}else if(strcmp(argv[2],"-p")==0){
					cout<<"Entrando na opcao de imprimir toda a arvore"<<endl<<endl;
                  //  exec("open graph.dot");
				}
				gravarDecodificado(argv[1],&raiz,&topo);
				if(raiz.getInicio()!= NULL)
					free(raiz.getInicio());				
				
				if(topo.getInicio()!= NULL)	
					free(topo.getInicio());
				
                
			}else{
                cout <<"Arquivo invalido."<<endl;
			}
		}			
	}else{//Caso não receba argumentos
		cout << "Sem argumentos recebidos, finalizando programa..."<<endl;
	}
	
	return 0;
}
