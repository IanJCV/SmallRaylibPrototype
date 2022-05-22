#include "scene.h"
#include "gamephysics.h"
#include "gamecore.h"

int Scene::addObject(std::shared_ptr<GameObject> g)
{
    m_Objects.push_back(g);
    if (m_PhysicsSystem != nullptr)
        m_PhysicsSystem->addObject(m_Objects.size() - 1);
    return (m_Objects.end() - 1) - m_Objects.begin();
}

std::shared_ptr<GameObject> Scene::getObject(int index)
{
    return m_Objects[index];
}

int Scene::getObjectCount()
{
    return m_Objects.size();
}

// Removes a GameObject by reference. Not implemented.
bool Scene::removeObject(std::shared_ptr<GameObject> g)
{
    for (uint16_t i = 0; i < m_Objects.size(); i++)
    {
        if (m_Objects[i] == g)
        {
            m_Objects.erase(m_Objects.begin() + i);
            return true;
        }
    }

    return false;
}

// Removes a GameObject at a certain position.
// Use " m_Objects.begin() + int " to get the iterator at an index.
bool Scene::removeObjectAtPosition(std::vector<std::shared_ptr<GameObject>>::iterator i)
{
    if (m_Objects.size() < 1)
        return false;
    if (*i == nullptr)
        throw "No object at iterator i location!";
    m_Objects.erase(i);
    m_Objects.shrink_to_fit();
    
    return true;
}

bool Scene::removeObjectAtPosition(int i)
{
    if (m_Objects.size() < 1)
        return false;

    m_Objects.erase(m_Objects.begin() + i);
    m_Objects.shrink_to_fit();
    return true;
}

void Scene::setName(std::string newName)
{
    m_Name = newName;
}

std::string Scene::name()
{
    return m_Name;
}

Scene::Scene()
{
    setName("Unnamed Scene");
    m_PhysicsSystem = nullptr;
}

Scene::Scene(std::string name)
{
    setName(name);
    m_PhysicsSystem = nullptr;
}

Scene::~Scene()
{
}

void Scene::load()
{
    m_Camera = Camera3D();
    m_Camera.fovy = 45;
    m_Camera.position = Vector3{ 0, 5, -10 };
    m_Camera.projection = CAMERA_PERSPECTIVE;
    m_Camera.up = Vector3{ 0, 1, 0 };
    m_Camera.target = Vector3{ 0,0,0 };

    SetCameraMode(m_Camera, CAMERA_CUSTOM);

    m_PhysicsSystem = new PhysicsSystem();
    m_PhysicsSystem->initPhysics(this);
    loaded = true;

}

void Scene::unload()
{
    printf("GAME SYSTEMS: Scene unloaded.\n");
    loaded = false;
    m_Objects.clear();
    m_Objects.shrink_to_fit();

    delete m_PhysicsSystem;
    m_PhysicsSystem = nullptr;
}

void Scene::update()
{
    for (uint16_t i = 0; i < m_Objects.size(); i++)
    {
        std::shared_ptr<GameObject> o = m_Objects[i];

        if (o->active == false)
        {
            removeObjectAtPosition(m_Objects.begin() + i);
            continue;
        }

        o->update();
    }

    m_PhysicsTimer += GetFrameTime();

    if (m_PhysicsTimer > 1 / PHYSICS_TIME)
    {
        m_PhysicsSystem->simulatePhysics();
    }
}


void Scene::draw()
{
    BeginMode3D(m_Camera);

    DrawGrid(50, 1);

    drawObjects();

    EndMode3D();

    drawObjects2d(m_Camera);

    DrawText(getSceneInfo().c_str(), 5, 60, 20, BLACK);
}

void Scene::drawObjects()
{
    for (uint16_t i = 0; i < m_Objects.size(); i++)
    {
        if (m_Objects[i]->active)
			m_Objects[i]->draw();
    }
}

void Scene::drawObjects2d(Camera3D camera)
{
    for (uint16_t i = 0; i < m_Objects.size(); i++)
    {
        if (m_Objects[i]->active)
			m_Objects[i]->draw2d(camera);
    }
}

std::string Scene::getSceneInfo()
{
    std::string result = "Scene name: " + m_Name + "\n" 
        + "Object amount: " + std::to_string(m_Objects.size()) + " " + std::to_string(m_Objects.capacity()) + "\n";
    return result;
}