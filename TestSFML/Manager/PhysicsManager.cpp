#include "stdafx.h"
#include "PhysicsManager.h"
#include "../Components/Collision_Components/RectCollisionCP.h"

void positionalCorrection(Manifold& man)
{
    const float percent = 0.2f;
    const float slop = 0.01f;

    sf::Vector2f correction = std::max(man.penetration - slop, 0.0f) / (man.body1->getInvMass() + man.body2->getInvMass()) * percent * man.normal;

    man.body1->setPosNotifyTransf(man.body1->getPos() + man.body1->getInvMass() * correction);
    man.body2->setPosNotifyTransf(man.body2->getPos() + man.body2->getInvMass() * correction);
}

bool aabbVsAabb(const sf::FloatRect& a, const sf::FloatRect& b, sf::Vector2f& normal, float& penetration)
{
    auto getCenter = [](const sf::FloatRect& rect) -> sf::Vector2f
        { return sf::Vector2f(rect.left, rect.top) + 0.5F * sf::Vector2f(rect.width, rect.height); };

    // TODO: implement SAT for axis aligned bounding box (AABB) collision
    // TODO determine separation normal for collision resolution, i.e., the axis
    // showing the smallest penetration.
    // TODO determine the corresponding penetration depth for the positional correction step.

    const sf::Vector2f n = getCenter(b) - getCenter(a); // Vector from A to B
    const float    aExtentX = a.width * 0.5F;              // Calculate half extents along x axis
    const float    bExtentX = b.width * 0.5F;
    const float    xOverlap = aExtentX + bExtentX - abs(n.x); // Calculate overlap on x axis

    // SAT test on x axis
    if (xOverlap > 0)
    {
        const float aExtentY = a.height * 0.5F; // Calculate half extents along y axis
        const float bExtentY = b.height * 0.5F;
        const float yOverlap = aExtentY + bExtentY - abs(n.y); // Calculate overlap on y axis

        // SAT test on y axis
        if (yOverlap > 0)
        {
            // Find out which axis is axis of least penetration
            if (xOverlap < yOverlap)
            {
                // Point towards B knowing that n points from A to B
                if (n.x < 0)
                {
                    normal = sf::Vector2f(1.0F, 0.0F);
                }
                else
                {
                    normal = sf::Vector2f(-1.0F, 0.0F);
                }
                penetration = xOverlap;
                return true;
            }
            // Point towards B knowing that n points from A to B
            if (n.y < 0)
            {
                normal = sf::Vector2f(0, 1);
            }
            else
            {
                normal = sf::Vector2f(0, -1);
            }
            penetration = yOverlap;
            return true;
        }
    }
    return false;
}

void PhysicsManager::collisionCheck(std::vector<std::shared_ptr<GameObject>>& gameObjects)
{
    for (auto itA = gameObjects.begin(); itA != gameObjects.end(); ++itA)
    {
        auto& body1 = *itA;
        if (body1->getComponentsOfType<RigidBodyCP>().size() == 0)
        {
            continue;
        }

        std::shared_ptr<RigidBodyCP> r1 = body1->getComponentsOfType<RigidBodyCP>().at(0);

        for (auto itB = itA; itB != gameObjects.end(); ++itB)
        {
            if (itA == itB)
            {
                continue;
            }

            auto& body2 = *itB;

            if (body2->getComponentsOfType<RigidBodyCP>().size() == 0)
            {
                continue;
            }

            std::shared_ptr<RigidBodyCP> r2 = body2->getComponentsOfType<RigidBodyCP>().at(0);

            if (r1->getMass() == 0 && r2->getMass() == 0)
            {
                continue;
            }

            sf::Vector2f normal;
            float penetration = NAN;

            std::shared_ptr<RectCollisionCP> c1 = body1->getComponentsOfType<RectCollisionCP>().at(0);
            std::shared_ptr<RectCollisionCP> c2 = body2->getComponentsOfType<RectCollisionCP>().at(0);

            if (aabbVsAabb(
                c1->getCollisionRect(),
                c2->getCollisionRect(),
                normal,
                penetration))
            {
                std::shared_ptr<Manifold> manifold = std::make_shared<Manifold>();

                manifold->body1 = r1;
                manifold->body2 = r2;
                manifold->normal = normal;
                manifold->penetration = penetration;

                manifolds.push_back(manifold);
            }
        }
    }
}

void PhysicsManager::collisionResolve()
{
    for (auto& man : manifolds)
    {
        std::cout << "Collision Detected" << std::endl;

        const sf::Vector2f rv = man->body1->getVel() - man->body2->getVel();

        const float velAlongNormal = rv.x * man->normal.x + rv.y * man->normal.y;

        if (velAlongNormal >= 0)
        {
            return;
        }

        if (bool restitutionOn = true)
        {
            sf::Vector2f impulse = velAlongNormal * man->normal;

            man->body1->setVelNotifyTransf(man->body1->getVel() - 0.5f * impulse);
            man->body2->setVelNotifyTransf(man->body2->getVel() + 0.5f * impulse);
        }

        if (bool posCorrection = false)
        {
            positionalCorrection(*man);
        }
    }
}

void PhysicsManager::update(std::vector<std::shared_ptr<GameObject>> gameObjects)
{
    manifolds.clear();

    collisionCheck(gameObjects);
    collisionResolve();
}
