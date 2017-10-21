/** @file */

#include <iostream>
#include "ProtecaoCivil.h"
#include "generic-functions.h"


/**
 * @brief Main Function
 * @return 0 on successfull run
 */
int main(){


	///////////////////////////////////////////////////////////////////////
	// Criar Proteção Civil e verificar se não houve erros na sua abertura

	ProtecaoCivil protecaoCivil("postos","TODO","locais");
	try{	// Ler info dos ficheiros e verificar que nao ha erros na sua abertura
		protecaoCivil.openFiles();
	}
	catch(Erro &e){
		std::cerr << e.getInfo();
		return 1;
	}


	int opt;

	// Perguntar ao utilizador o que quer fazer até este indicar que deseja sair
	while(true){
		printMainMenu();

		// Pedir opcao ao utilizador e verificar se nao houve erro de input
		try{
			opt = getOption(1,5);
		}
		catch(Erro &e){
			std::cout << "\n" << e.getInfo();
			continue;	// Ir para o proximo loop , pedir nova opcao
		}

		if (opt == 1)
			declararOcorrencia(protecaoCivil);
		else if (opt == 2)
			terminarOcorrencia(protecaoCivil);
		else if (opt == 3)
			infoOcorrencia(protecaoCivil);
		else if (opt == 4)
			pesquisarPostos(protecaoCivil);
		else
			break;	// opt = 5, o utilizador quer sair
	}

	return 0;
}


int getOption(int min, int max){
	int opt;

	// Get the option
	std::cout << ">>> ";
	std::cin >> opt;

	// Check if not a number was entered
	if(std::cin.fail()){
		// Clear the cin error flags and the stream content, throw the error
		std::cin.clear();
		std::cin.ignore(1000,'\n');
		throw (Erro("Input Invalido!"));
	}

	// Clear the cin stream even if no error occured, to ensure the stream always stays clean
	std::cin.ignore(1000,'\n');

	// Check if the option is valid
	if(opt>=min && opt<=max)
		return opt;
	else
		throw (Erro("Opcao Invalida!"));
}

void declararOcorrencia(ProtecaoCivil &protecaoCivil){
	std::string localidade, data, tipoCasa, tipoEstrada;
	int tipoAcidente;
	bool existenciaFeridos;
	unsigned int numFeridos, numVeiculos, numBombeirosNecess, numAutotanquesNecess, areaChamas;

	try{
		localidade = obterLocalidade(protecaoCivil);
		data = lerData();
		tipoAcidente = obterTipoAcidente();

		switch(tipoAcidente){
		case 1:		// Assaltos
			tipoCasa = assaltoObterTipoCasa();
			existenciaFeridos = assaltoObterExistenciaFeridos();
			break;
		case 2:		// Acidentes de Viacao
			tipoEstrada = viacaoObterTipoEstrada();
			numFeridos = viacaoObterNumFeridos();
			numVeiculos = viacaoObterNumVeiculos();
			break;
		case 3:		// Incendios Florestais
			numBombeirosNecess = incendioObterNumBombeiros();
			numAutotanquesNecess = incendioObterNumAutotanques();
			areaChamas = incendioObterAreaChamas();
			break;	// Incendios Domesticos
		case 4:
			numBombeirosNecess = incendioObterNumBombeiros();
			numAutotanquesNecess = incendioObterNumAutotanques();
			tipoCasa = incendioObterTipoCasa();
			break;
		}
	}
	catch(Erro &e){
		std::cout << '\n' << e.getInfo() << std::endl << std::endl;
		pause();
		return;
	}

	std::cout << "\n*******************************";
	std::cout << "\n**********  SUCESSO  **********";
	std::cout << "\n*******************************\n\n";
	pause();
}

void terminarOcorrencia(ProtecaoCivil &protecaoCivil){

	std::cout << "\n\nThis is a STUB!!" << std::endl;
	std::cout << "We are Inside terminarOcorrencia()";

	///////////////////////////////////
	// TODO: IMPLEMENT THIS FUNCTION //
	///////////////////////////////////


}

void infoOcorrencia(ProtecaoCivil &protecaoCivil){

	int opt;

	// Perguntar ao utilizador o que quer fazer até estes querer voltar ao menu anterior
	while(true){
		printInfoOcorrenciasMenu();

		// Pedir opcao ao utilizador e verificar se nao houve erro de input
		try{
			opt = getOption(1,9);
		}
		catch(Erro &e){
			std::cout << "\n" << e.getInfo();
			continue;	// Ir para o proximo loop , pedir nova opcao
		}

		std::cout << std::endl;

		if (opt == 1){
			// Ordenenar os Acidentes por local e imprimi-los a todos
			protecaoCivil.ordernarAcidentes(compararAcidentesLocal);
			protecaoCivil.printTodosAcidentes();
			pause();
			break;
		}
		else if (opt == 2){
			// Pedir ao utilizador que introduzar uma Localidade
			std::string localidade;
			std::cout << "Insira a localidade que deseja: ";
			getline(std::cin,localidade);

			// Ordenar os acidentes por localidade
			protecaoCivil.ordernarAcidentes(compararAcidentesLocal);

			std::cout << std::endl;

			// Imprimir todos os acidentes que existem nesse local ; caso não haja nenhum, informar o utilizador
			protecaoCivil.printAcidentesLocal(localidade);

			std::cout << std::endl << std::endl;

			pause();
			break;
		}
		else if (opt == 3){
			// Ordenenar os Acidentes por data e imprimi-los a todos
			protecaoCivil.ordernarAcidentes(compararAcidentesData);
			protecaoCivil.printTodosAcidentes();
			pause();
			break;
		}
		else if (opt == 4){
			// Pedir ao utilizador que introduzar uma Data
			std::string data;
			std::cout << "Insira a data que deseja (DD-MM-AAAA) : ";
			try{
				data = lerData();
			}
			catch(Erro &e){
				std::cout << "\n" << e.getInfo();
				break;
			}

			// Ordenar os acidentes por data
			protecaoCivil.ordernarAcidentes(compararAcidentesData);

			std::cout << std::endl;

			// Imprimir todos os acidentes que existem nessa data ; caso não haja nenhum, informar o utilizador
			protecaoCivil.printAcidentesData(data);

			std::cout << std::endl << std::endl;

			pause();
			break;
		}
		else if (opt == 5){
			// Ordenenar os Acidentes por tipo e imprimi-los a todos
			protecaoCivil.ordernarAcidentes(compararAcidentesTipo);
			protecaoCivil.printTodosAcidentes();
			pause();
			break;
		}
		else if (opt == 6){
			// Ordenar os acidentes por tipo e imprimir os Assaltos
			protecaoCivil.ordernarAcidentes(compararAcidentesTipo);
			protecaoCivil.printAcidentesTipo("Assalto");
			pause();
			break;
		}
		else if (opt == 7){
			// Ordenar os acidentes por tipo e imprimir os Acidentes de Viacao
			protecaoCivil.ordernarAcidentes(compararAcidentesTipo);
			protecaoCivil.printAcidentesTipo("Acidente de Viacao");
			pause();
			break;
		}
		else if (opt == 8){
			// Ordenar os acidentes por tipo e imprimir os Incendios (quer Domesticos, quer Florestais)
			protecaoCivil.ordernarAcidentes(compararAcidentesTipo);
			protecaoCivil.printAcidentesTipo("Incendio Domestico");
			protecaoCivil.printAcidentesTipo("Incendio Florestal");
			pause();
			break;
		}
		else
			break;	// opt = 6, o utilizador quer voltar
	}



}

void pesquisarPostos(ProtecaoCivil &protecaoCivil){

	int opt;

	// Perguntar ao utilizador o que quer fazer até estes querer voltar ao menu anterior
	while(true){
		printPesquisarPostosMenu();

		// Pedir opcao ao utilizador e verificar se nao houve erro de input
		try{
			opt = getOption(1,7);
		}
		catch(Erro &e){
			std::cout << "\n" << e.getInfo();
			continue;	// Ir para o proximo loop , pedir nova opcao
		}

		std::cout << std::endl;

		if (opt == 1){
			// Ordenar os postos por local e imprimi-los a todos
			protecaoCivil.ordernarPostos(compararPostosLocal);
			protecaoCivil.printTodosPostos();
			pause();
			break;
		}
		else if (opt == 2){
			// Pedir ao utilizador que introduzar uma Localidade
			std::string localidade;
			std::cout << "Insira a localidade que deseja: ";
			getline(std::cin,localidade);

			// Ordenar os postos por localidade
			protecaoCivil.ordernarPostos(compararPostosLocal);

			std::cout << std::endl;

			// Imprimir todos os postos que existem nesse local ; caso não haja nenhum, informar o utilizador
			protecaoCivil.printPostosLocal(localidade);

			std::cout << std::endl << std::endl;

			pause();
			break;
		}
		else if (opt == 3){
			// Ordenar os postos por tipo e imprimi-los a todos
			protecaoCivil.ordernarPostos(compararPostosTipo);
			protecaoCivil.printTodosPostos();
			pause();
			break;
		}
		else if (opt == 4){
			// Ordenar os postos por tipo e imprimir os postos de Bombeiros
			protecaoCivil.ordernarPostos(compararPostosTipo);
			protecaoCivil.printPostosTipo("Bombeiros");
			pause();
			break;
		}
		else if (opt == 5){
			// Ordenar os postos por tipo e imprimir os postos de Policia
			protecaoCivil.ordernarPostos(compararPostosTipo);
			protecaoCivil.printPostosTipo("Policia");
			pause();
			break;
		}
		else if (opt == 6){
			// Ordenar os postos por tipo e imprimir os postos de Inem
			protecaoCivil.ordernarPostos(compararPostosTipo);
			protecaoCivil.printPostosTipo("Inem");
			pause();
			break;
		}
		else
			break;	// opt = 6, o utilizador quer voltar
	}

}

bool compararPostosLocal(Posto* p1, Posto* p2){
	return (p1->getLocal()->getNome() < p2->getLocal()->getNome());
}

bool compararPostosTipo(Posto* p1, Posto* p2){
	return (p1->getTipoPosto() < p2->getTipoPosto());
}

bool compararAcidentesLocal(Acidente* a1, Acidente* a2){
	return (a1->getLocal()->getNome() < a2->getLocal()->getNome());
}

bool compararAcidentesTipo(Acidente* a1, Acidente* a2){
	return (a1->getTipoAcidente() < a2->getTipoAcidente());
}

bool compararAcidentesData(Acidente* a1, Acidente* a2){
	return (a1->getData() < a2->getData());
}

void printMainMenu(){
	// Draw the header
	printHeader("Protecao Civil");

	// Draw the options
	std::cout << "1. Declarar Ocorrencia" << std::endl;
	std::cout << "2. Terminar Ocorrencia" << std::endl;
	std::cout << "3. Informacoes sobre Ocorrencias" << std::endl;
	std::cout << "4. Pesquisar Postos" << std::endl;
	std::cout << "5. Sair" << std::endl << std::endl;
}

void printPesquisarPostosMenu(){
	// Draw the header
	printHeader("Pesquisar Postos");

	// Draw the options
	std::cout << "1. Pesquisar por Localidade (totalidade)" << std::endl;
	std::cout << "2. Pesquisar por Localidade (especifico)" << std::endl;
	std::cout << "3. Pesquisar por Tipo de Posto" << std::endl;
	std::cout << "4. Pesquisar por Postos de Bombeiros" << std::endl;
	std::cout << "5. Pesquisar por Postos da Policia" << std::endl;
	std::cout << "6. Pesquisar por Postos do Inem" << std::endl;
	std::cout << "7. Voltar" << std::endl << std::endl;
}

void printInfoOcorrenciasMenu(){
	// Draw the header
	printHeader("Informacoes sobre Ocorrencias");

	// Draw the options
	std::cout << "1. Pesquisar por Localidade (totalidade)" << std::endl;
	std::cout << "2. Pesquisar por Localidade (especifico)" << std::endl;
	std::cout << "3. Pesquisar por Data (totalidade)" << std::endl;
	std::cout << "4. Pesquisar por Data (especifica)" << std::endl;
	std::cout << "5. Pesquisar por Tipo de Ocorrencia" << std::endl;
	std::cout << "6. Pesquisar por Assaltos" << std::endl;
	std::cout << "7. Pesquisar por Acidentes de Viacao" << std::endl;
	std::cout << "8. Pesquisar por Incendios" << std::endl;
	std::cout << "9. Voltar" << std::endl << std::endl;
}

void printHeader(const std::string &header){
	unsigned int headerSize = 80;
	unsigned int headerLeftSpaces = (headerSize - header.size()) / 2;

	// Give some space from previous menu print
	std::cout << "\n\n";

	// Draw the Menu Header
	for(unsigned int i=0 ; i<headerSize ; i++) { std::cout << "-"; }
	std::cout << std::endl;
	for(unsigned int i=0 ; i<headerLeftSpaces ; i++) { std::cout << " "; }
	std::cout << header << std::endl;
	for(unsigned int i=0 ; i<headerSize ; i++) { std::cout << "-"; }
	std::cout << std::endl << std::endl;
}

std::string lerData(){
	std::string data;
	std::cout << "\nInsira a data em que ocorreu o acidente (Formato DD-MM-AAAA): ";
	getline(std::cin,data);

	// Verificar se está no formato válido (DD-MM-AAAA)
	if(data.size() != 10)											// Verificar se a data tem o tamanho correto
		throw (Erro("Data Invalida!"));
	else if ((data.at(2) != '-') || (data.at(5) != '-'))			// Verificar se dia, mes e ano estao separados por um traco
		throw (Erro("Data Invalida!"));
	else if ((data.at(0) < '0') || (data.at(0) > '9'))				// Verificar se Dx é um digito
		throw (Erro("Data Invalida!"));
	else if ((data.at(1) < '0') || (data.at(1) > '9'))				// Verificar se xD é um digito
		throw (Erro("Data Invalida!"));
	else if ((data.at(3) < '0') || (data.at(3) > '9'))				// Verificar se Mx é um digito
		throw (Erro("Data Invalida!"));
	else if ((data.at(4) < '0') || (data.at(4) > '9'))				// Verificar se xM é um digito
		throw (Erro("Data Invalida!"));
	else if ((data.at(6) < '0') || (data.at(6) > '9'))				// Verificar se Axxx é um dígito
		throw (Erro("Data Invalida!"));
	else if ((data.at(7) < '0') || (data.at(7) > '9'))				// Verificar se xAxx é um dígito
		throw (Erro("Data Invalida!"));
	else if ((data.at(8) < '0') || (data.at(8) > '9'))				// Verificar se xxAx é um dígito
		throw (Erro("Data Invalida!"));
	else if ((data.at(9) < '0') || (data.at(9) > '9'))				// Verificar se xxxA é um dígito
		throw (Erro("Data Invalida!"));
	else
		return data;		// Nao houve erro, retornar data
}

std::string obterLocalidade(ProtecaoCivil &protecaoCivil){
	std::string localidade;
	std::cout << "\nInsira a localidade em que a ocorrencia teve lugar: ";
	getline(std::cin,localidade);

	// Verificar se o local existe na base de dados da Protecao Civil
	if(protecaoCivil.findLocal(localidade) == -1)		// local não existe no vetor de locais
		throw (Erro("A localidade introduzida nao existe na base de dados da Protecao Civil"));
	else
		return localidade;
}

int obterTipoAcidente(){
	int opt;
	std::cout << "\nInsira o tipo de Acidente:" << std::endl;
	std::cout << "1. Assalto" << std::endl;
	std::cout << "2. Acidente de Viacao" << std::endl;
	std::cout << "3. Incendio Florestal" << std::endl;
	std::cout << "4. Incendio Domestico" << std::endl << std::endl;
	try{
		opt = getOption(1,4);
	}
	catch(Erro &e){
		throw e;
	}

	return opt;		// Sucesso na leitura
}
std::string assaltoObterTipoCasa(){
	std::string tipoCasa;
	std::cout << "\nIndique o tipo de casa em que o assalto teve lugar (Partiular ou Comercial): ";
	getline(std::cin, tipoCasa);

	// Aceitar "Particular" de várias formas diferentes
	if ((tipoCasa=="p") || (tipoCasa=="P") || (tipoCasa=="particular") || (tipoCasa=="Particular") || (tipoCasa=="1"))
		return "Particular";

	// Aceitar "Comercial" de várias formas diferentes
	else if ((tipoCasa=="c") || (tipoCasa=="C") || (tipoCasa=="comercial") || (tipoCasa=="Comercial") || (tipoCasa=="2"))
		return "Comercial";

	// Input Invalido
	else
		throw (Erro("Tipo de casa invalido!"));
}

bool assaltoObterExistenciaFeridos(){
	std::string feridos;
	std::cout << "\nIndique se houve feridos no decorrer do assalto (Sim ou Nao): ";
	getline(std::cin, feridos);

	// Aceitar "Sim" de várias formas diferentes
	if ((feridos=="s") || (feridos=="S") || (feridos=="sim") || (feridos=="Sim") || (feridos=="SIM") || (feridos=="1"))
		return true;

	// Aceitar "Nao" de várias formas diferentes
	else if ((feridos=="n") || (feridos=="N") || (feridos=="nao") || (feridos=="Nao") || (feridos=="NAO") || (feridos=="2"))
		return false;

	// Input Invalido
	else
		throw (Erro("Resposta invalida!"));
}

std::string viacaoObterTipoEstrada(){
	std::string tipoEstrada;
	std::cout << "\nIndique o tipo de estrada em que ocorreu o acidente (Estrada Nacional ou Auto-Estrada): ";
	getline(std::cin, tipoEstrada);

	// Aceitar "Estrada Nacional" de várias formas diferentes
	if ((tipoEstrada=="Estrada Nacional") || (tipoEstrada=="estrada nacional") || (tipoEstrada=="en") || (tipoEstrada=="EN") || (tipoEstrada=="1"))
		return "Estrada Nacional";

	// Aceitar "Auto-Estrada" de várias formas diferentes
	else if ((tipoEstrada=="Auto-Estrada") || (tipoEstrada=="auto-estrada") || (tipoEstrada=="ae") || (tipoEstrada=="AE") || (tipoEstrada=="2"))
		return "Auto-Estrada";

	// Input Invalido
	else
		throw (Erro("Tipo de estrada invalido!"));
}

unsigned int viacaoObterNumFeridos(){
	int numFeridos;
	std::cout << "\nInsira o numero de feridos envolvidos no acidente: ";
	std::cin >> numFeridos;

	// Verificar se foi introduzido um numero
	if(std::cin.fail()){
		// Limpar as flags de erro e limpar a stream, lançar a exceção
		std::cin.clear();
		std::cin.ignore(1000,'\n');
		throw (Erro("Input Invalido!"));
	}

	// Limpar a stream mesmo que não tenha ocorrido qualquer erro, para garantir que está sempre limpa e vazia
	std::cin.ignore(1000,'\n');

	// Verificar se o numero de feridos introduzido nao foi absurdo
	if (numFeridos < 0)
		throw (Erro("Numero de feridos nao pode ser negativo!"));
	else if (numFeridos == 0)
		throw (Erro("umero de feridos nao pode ser nulo!"));
	else
		return ((unsigned int) numFeridos);
}

unsigned int viacaoObterNumVeiculos(){
	int numVeiculos;
	std::cout << "\nInsira o numero de veiculos envolvidos no acidente: ";
	std::cin >> numVeiculos;

	// Verificar se foi introduzido um numero
	if(std::cin.fail()){
		// Limpar as flags de erro e limpar a stream, lançar a exceção
		std::cin.clear();
		std::cin.ignore(1000,'\n');
		throw (Erro("Input Invalido!"));
	}

	// Limpar a stream mesmo que não tenha ocorrido qualquer erro, para garantir que está sempre limpa e vazia
	std::cin.ignore(1000,'\n');

	// Verificar se o numero de veiculos introduzido nao foi absurdo
	if (numVeiculos < 0)
		throw (Erro("Numero de veiculos nao pode ser negativo!"));
	else if (numVeiculos == 0)
		throw (Erro("Numero de veiculos nao pode ser nulo!"));
	else
		return ((unsigned int) numVeiculos);
}

unsigned int incendioObterNumAutotanques(){
	int numAutotanques;
	std::cout << "\nInsira o numero de autotanques necessarios para este incendio: ";
	std::cin >> numAutotanques;

	// Verificar se foi introduzido um numero
	if(std::cin.fail()){
		// Limpar as flags de erro e limpar a stream, lançar a exceção
		std::cin.clear();
		std::cin.ignore(1000,'\n');
		throw (Erro("Input Invalido!"));
	}

	// Limpar a stream mesmo que não tenha ocorrido qualquer erro, para garantir que está sempre limpa e vazia
	std::cin.ignore(1000,'\n');

	// Verificar se o numero de autotanques introduzido nao foi absurdo
	if (numAutotanques < 0)
		throw (Erro("Numero de autotanques nao pode ser negativo!"));
	else if (numAutotanques == 0)
		throw (Erro("Numero de autotanques nao pode ser nulo!"));
	else
		return ((unsigned int) numAutotanques);
}

unsigned int incendioObterNumBombeiros(){
	int numBombeiros;
	std::cout << "\nInsira o numero de bombeiros necessarios para este incendio: ";
	std::cin >> numBombeiros;

	// Verificar se foi introduzido um numero
	if(std::cin.fail()){
		// Limpar as flags de erro e limpar a stream, lançar a exceção
		std::cin.clear();
		std::cin.ignore(1000,'\n');
		throw (Erro("Input Invalido!"));
	}

	// Limpar a stream mesmo que não tenha ocorrido qualquer erro, para garantir que está sempre limpa e vazia
	std::cin.ignore(1000,'\n');

	// Verificar se o numero de bombeiros introduzido nao foi absurdo
	if (numBombeiros < 0)
		throw (Erro("Numero de bombeiros nao pode ser negativo!"));
	else if (numBombeiros == 0)
		throw (Erro("Numero de bombeiros nao pode ser nulo!"));
	else
		return ((unsigned int) numBombeiros);
}

unsigned int incendioObterAreaChamas(){
	int areaChamas;
	std::cout << "\nInsira a area de chamas deste incendio (em Kilometros Quadrados): ";
	std::cin >> areaChamas;

	// Verificar se foi introduzido um numero
	if(std::cin.fail()){
		// Limpar as flags de erro e limpar a stream, lançar a exceção
		std::cin.clear();
		std::cin.ignore(1000,'\n');
		throw (Erro("Input Invalido!"));
	}

	// Limpar a stream mesmo que não tenha ocorrido qualquer erro, para garantir que está sempre limpa e vazia
	std::cin.ignore(1000,'\n');

	// Verificar se a area de chamas introduzida nao foi absurda
	if (areaChamas < 0)
		throw (Erro("Area de chamas nao pode ser negativa!"));
	else if (areaChamas == 0)
		throw (Erro("Area de chamas nao pode ser nula!"));
	else
		return ((unsigned int) areaChamas);
}

std::string incendioObterTipoCasa(){
	std::string tipoCasa;
	std::cout << "\nIndique o tipo de casa em que o incendio teve lugar (Apartamento ou Moradia): ";
	getline(std::cin, tipoCasa);

	// Aceitar "Apartamento" de várias formas diferentes
	if ((tipoCasa=="a") || (tipoCasa=="A") || (tipoCasa=="apartamento") || (tipoCasa=="Apartamento") || (tipoCasa=="1"))
		return "Apartamento";

	// Aceitar "Moradia" de várias formas diferentes
	else if ((tipoCasa=="m") || (tipoCasa=="M") || (tipoCasa=="moradia") || (tipoCasa=="Moradia") || (tipoCasa=="2"))
		return "Moradia";

	// Input Invalido
	else
		throw (Erro("Tipo de casa invalido!"));
}

void pause(){
	std::cout << "Prima <ENTER> para continuar ...";
	int c = getchar();	// Wait for user to press enter and check if only enter was pressed!

	if(c == 10)			// The user pressed only the enter key
		return;
	else 				// The user pressed keys other than enter, clear the stream from that input
		std::cin.ignore(1000,'\n');
}
