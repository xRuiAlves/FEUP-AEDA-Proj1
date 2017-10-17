#ifndef PROTECAOCIVIL_H_
#define PROTECAOCIVIL_H_
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Posto.h"
#include "Policia.h"
#include "Inem.h"
#include "Bombeiros.h"
#include "Acidente.h"
#include "AcidenteViacao.h"
#include "Incendio.h"
#include "IncendioDomestico.h"
#include "IncendioFlorestal.h"
#include "Assalto.h"
#include "Local.h"
#include "Erro.h"


class ProtecaoCivil {
private:
	std::vector<Posto*> postos;
	std::vector<Acidente*> acidentes;
	std::vector<Local> locais;
	const std::string ficheiroPostos;
	const std::string ficheiroAcidentes;
	const std::string ficheiroLocais;
	void gravar() const;
	unsigned int findLocal(const std::string &nomeLocal) const;
	unsigned int findAcidenteMaiorNum() const;
public:
	ProtecaoCivil(const std::string &ficheiroPostos, const std::string &ficheiroAcidentes, const std::string &ficheiroLocais);
	~ProtecaoCivil();
	bool addAcidente(/*TODO parametros*/);
	bool rmAcidente(/*TODO parametros*/);
	void openFiles();
	void ordernarPostos(bool compareFunction(Posto* p1, Posto*p2));
	void printTodosPostos() const;
	void printPostosTipo(const std::string &tipo) const;		// ASSUMINDO POSTOS JA ORDENADOS POR TIPO!!!
	void printPostosLocal(const std::string &local) const;		// ASSUMINDO POSTOS JA ORDENADOS POR LOCAL!!!
	void ordernarAcidentes(bool compareFunction(Acidente* p1, Acidente*p2));
	void printTodosAcidentes() const;
	void printAcidentesTipo(const std::string &tipo) const;		// ASSUMINDO ACIDENTES JA ORDENADOS POR TIPO!!!
	void printAcidentesLocal(const std::string &local) const;	// ASSUMINDO ACIDENTES JA ORDENADOS POR LOCAL!!!
	void printAcidentesData(const std::string &data) const;		// ASSUMINDO ACIDENTES JA ORDENADOS POR DATA!!!
};

#endif /* PROTECAOCIVIL_H_ */
