#include "stdafx.h"
#include "RigidBodyCP.h"
#include "../Transformation_Components/TransformationCP.h"

void RigidBodyCP::setPosNotifyTransf(sf::Vector2f pos)
{
    this->position = pos;
    if (!gameObject.expired())
    {
        std::shared_ptr<GameObject> go = gameObject.lock();
        std::shared_ptr<TransformationCP> transCP = go->getComponentsOfType<TransformationCP>().at(0);
        transCP->setPosition(position);
    }
}

// RigidBody Vel => transform.direction * transform.velocity => vel = RigidBodyVel / x or y (what is not 0)
void RigidBodyCP::setVelNotifyTransf(sf::Vector2f vel)
{
    this->velocity = vel;

    if (!gameObject.expired())
    {
        std::shared_ptr<GameObject> go = gameObject.lock();
        std::shared_ptr<TransformationCP> transCP = go->getComponentsOfType<TransformationCP>().at(0);
        if (vel.x == 0)
        {
            transCP->setVelocity(vel.y);
            transCP->setDirection(vel / vel.y);
        }
        else
        {
            transCP->setVelocity(vel.x);
            transCP->setDirection(vel / vel.x);
        }
    }
}
