#include "DTSMap.h"
#include <iostream>

DTS::Background::Background()
{

}

bool DTS::Background::loadFromFile(const std::string& filepath)
{
    if (background.loadFromFile(filepath))
    {
        // Chargement réussi !
        std::cout << "Background chargé directement! Taille: "
            << background.getSize().x << "x"
            << background.getSize().y << std::endl;
    }
    else
    {
        // Le chargement a échoué (probablement image trop grande)
        std::cout << "Chargement direct échoué, tentative de redimensionnement..." << std::endl;
    }

	return false;
}

