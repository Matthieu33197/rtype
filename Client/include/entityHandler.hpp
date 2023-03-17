/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** entityHandler
*/

#ifndef ENTITYHANDLER_HPP_
#define ENTITYHANDLER_HPP_

#include <iostream>
#include <raylib.h>
#include "soundManager.hpp"
#include "../../Lib/GameEngine/include/Entity/EntityManager.hpp"
#include "../../Lib/GameEngine/include/Components/Position.hpp"
#include "../../Lib/GameEngine/include/Components/Health.hpp"
#include "../../Lib/GameEngine/include/Components/Style.hpp"
#include "../../include/NetworkAlias.hpp"

class EntityHandler
{
    public:
        EntityHandler();
        ~EntityHandler();
        //! getEntities function
        /*!
         The function is a getter for the avaible entities
       	*/
        std::unique_ptr<GameEngine::EntityManager> &getEntities() { return _entityManager; };
        //! updateEntity function
        /*!
         The function updates the entity
       	*/
        int updateEntity(CombOwnedMsg &owner);
        //! removeEntity function
        /*!
         The function removes a given entity
       	*/
        int removeEntity(CombOwnedMsg &owner);
        //! removeEntityId function
        /*!
         The function removes a given entity
       	*/
		void removeEntityId(const uint32_t &id);
        //! moveEntity function
        /*!
         The function moves a given entity to a given position
       	*/
        int moveEntity(CombOwnedMsg &owner);
        //! preLoadTextures function
        /*!
         The function is used to load the textures before the displaying starts
       	*/
        void preLoadTextures(const std::string &playerSkin, const std::string &enemySkin);
    private:
	      std::unique_ptr<GameEngine::EntityManager> _entityManager;
        GameEngine::Style _style;
        Texture2D _playerSkin;
        Texture2D _enemySkin;
        Texture2D _rocketSkin;
        Texture2D _wall;
        Texture2D _powerup;
        SoundManager _soundManager;
};


#endif /* !ENTITYHANDLER_HPP_ */
