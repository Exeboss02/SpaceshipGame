#include "../headers/resourceStorage.h"

TextureStorage::~TextureStorage()
{
    for (int i = 0; i < this->textures.size(); i++)
    {
        if(this->textures[i]) delete this->textures[i];
    }
    
}