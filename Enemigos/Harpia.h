//
//
//

#ifndef HARPIA_H
#define HARPIA_H
#pragma once
#include "Enemigo.h"

class Harpia :public Enemigo {
public:
    Harpia();
    Enemigo* clone() const override;

};



#endif //HARPIA_H