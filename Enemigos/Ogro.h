//
//  Creamos al enemigo Ogro
//

#ifndef OGRO_H
#define OGRO_H
#include "Enemigo.h"



class Ogro: public Enemigo {
public:
    Ogro();
    Enemigo* clone() const override;

};
#endif //OGRO_H