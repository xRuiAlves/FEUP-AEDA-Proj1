#ifndef BOMBEIROS_H_
#define BOMBEIROS_H_
#include "Posto.h"

class Bombeiros : public Posto {
private:
	unsigned int numAutotanques;
	unsigned int numAmbulancias;
public:
	Bombeiros(const Local* local, unsigned int numSocorristas, unsigned int numAutotanques, unsigned int numAmbulancias);
	~Bombeiros();
	void addAutotanques(unsigned int num);
	void addAmbulancias(unsigned int num);
	bool rmAutotanques(unsigned int num);
	bool rmAmbulancias(unsigned int num);
	unsigned int getNumAutotanques() const;
	unsigned int getNumAmbulancias() const;
	std::string getTipoPosto() const;
};

#endif /* BOMBEIROS_H_ */
