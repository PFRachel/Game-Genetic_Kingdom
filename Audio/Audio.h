//
// Created by Santiago on 27/5/2025.
//

#ifndef AUDIO_H
#define AUDIO_H
#include "raylib.h"

#endif //AUDIO_H

class Audio {
    public:
    Music MainTheme = LoadMusicStream(("../Audio/MainTheme.wav"));
    Sound GameOverSfx = LoadSound(("../Audio/GameOver.mp3"));
};
