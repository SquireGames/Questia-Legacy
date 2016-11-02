#ifndef ENTITY_OBJ_H
#define ENTITY_OBJ_H

#include "Entity.h"

#include <map>

#include <boost/variant.hpp>

#include "Vector2.h"

enum class Type {none = 0};
enum class Atr_Test {none = 0};

class Obj_Type
{
    std::map <int,  boost::variant<std::string, float, int> > atrs;
};

class Entity_Obj : public Entity
{
public:
    Entity_Obj(int id, EntityManager& entityManager, ResourceManager& _resourceManager);
    virtual ~Entity_Obj() = 0;

    virtual void draw(sf::RenderWindow& window, const DrawLayer& drawLayer);

    utl::Vector2f coords;
    std::map <Type, Obj_Type> atrs;

protected:
    ResourceManager& resourceManager;
};

#endif // ENTITY_OBJ_
