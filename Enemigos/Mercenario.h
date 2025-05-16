//
// Created by Rachel on 22/04/2025.
//

#ifndef MERCENARIO_H
#define MERCENARIO_H
#pragma once
#include "Enemigo.h"

class Mercenario : public Enemigo {
public:
    Mercenario();
    Enemigo* clone() const override;

};



#endif //MERCENARIO_H
