#ifndef ENTITY_OBJ_H
#define ENTITY_OBJ_H

#include "Entity.h"

#include <map>

#include <boost/variant.hpp>

#include "Vector2.h"

enum class Type {none = 0, test_attack = 1};
enum class Type_test_attack {destroyStuff = 0};

class Type_Field
{
public:
    std::map <int,  boost::variant<std::string, float, int, bool> > atrs;
};

class Entity_Obj : public Entity
{
public:
    Entity_Obj(unsigned int id, EntityManager& entityManager, ResourceManager& _resourceManager);
    virtual ~Entity_Obj() = 0;

    virtual void draw(sf::RenderWindow& window, const DrawLayer& drawLayer);

    utl::Vector2f coords;
    std::map <Type, Type_Field> atrs;

    std::string displayTag = "";
    bool showTag = false;

protected:
    ResourceManager& resourceManager;
};

#endif // ENTITY_OBJ_
