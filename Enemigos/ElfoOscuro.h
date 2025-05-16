//
//
//

#ifndef ELFOOSCURO_H
#define ELFOOSCURO_H
# include "Enemigo.h"


class ElfoOscuro : public Enemigo {
public:
    ElfoOscuro();
    Enemigo* clone() const override;
};



#endif //ELFOOSCURO_H