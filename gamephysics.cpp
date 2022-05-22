#include "gameobject.h"
#include "gamephysics.h"


PhysicsSystem::PhysicsSystem()
{
    m_Scene = nullptr;
    m_PhysicsObjects.clear();
}

PhysicsSystem::~PhysicsSystem()
{
    m_PhysicsObjects.clear();
    printf("GAME SYSTEMS: Physics deinitialized.\n");
}

void PhysicsSystem::initPhysics(Scene* scene)
{
    m_Scene = scene;
    for (uint16_t i = 0; i < m_Scene->getObjectCount(); i++)
    {
        std::shared_ptr<GameObject> go(m_Scene->getObject(i));
        if (go->useGravity)
            m_PhysicsObjects.push_back(go);
    }
}

void PhysicsSystem::simulatePhysics()
{
    for (uint16_t i = 0; i < m_PhysicsObjects.size(); i++)
    {
        Vector3* vel = &m_PhysicsObjects[i]->velocity;

        if (vel->y < TERMINAL_VELOCITY)
        {
            vel->y += GRAVITY_CONSTANT / PHYSICS_TIME * GetFrameTime();
        }

        m_PhysicsObjects[i]->setPosition(Vector3Add(m_PhysicsObjects[i]->getPosition(), *vel));

        //Check collision
    }
}

void PhysicsSystem::addObject(int sceneIndex)
{
    std::shared_ptr<GameObject> obj(m_Scene->getObject(sceneIndex));

    if (obj->useGravity == true)
        m_PhysicsObjects.push_back(obj);
}

void PhysicsSystem::removeObject(std::shared_ptr<GameObject> obj)
{
    for (int i = m_PhysicsObjects.size() - 1; i > -1; i--)
    {
        if (m_PhysicsObjects[i] == obj)
            m_PhysicsObjects.erase((m_PhysicsObjects.end() - 1) - i);
    }
}