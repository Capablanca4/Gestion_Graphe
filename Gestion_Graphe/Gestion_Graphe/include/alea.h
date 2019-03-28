#ifndef ALEA_H
#define ALEA_H
class alea
{
public:
	alea();
	alea(int a);
	alea(int a, int b);
	int val_alea()const;

	bool tirageAleatoire(int p);
private:
	int d_val;
};
#endif