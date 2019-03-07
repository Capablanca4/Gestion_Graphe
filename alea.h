#ifndef ALEA_H
#define ALEA_H
class alea
{
public:
    alea(int a,int b);
    int val_alea(int a,int b)const;
    int ValeurBinaireAleatoire()const;
    bool tirageAleatoire(int p);
private:
    int d_a,d_b;
};
#endif
