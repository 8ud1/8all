#include "Scene.h"


void Scene::Update(float deltaTime)
{
	physicsSystem.Update(deltaTime);

	for (auto& obj : gameObjects)
	{
		obj->Update(deltaTime);
	}
}

void Scene::Render(Renderer& renderer)
{
	for (auto& obj : gameObjects)
	{
		obj->Render(renderer);
	}
}
