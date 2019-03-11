#ifndef ALEA_H
#define ALEA_H
class alea
{
public:
    alea();
    alea(int a,int b);
    alea(int a);
    int val_alea()const;

    bool tirageAleatoire(int p);
private:
    int d_val;
};
#endif
