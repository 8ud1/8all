#include "Scene.h"


void Scene::LogicUpdate(float deltaTime)
{
	for (auto& obj : gameObjects)
	{
		obj->Update(deltaTime);
	}
}

void Scene::PhysicsUpdate(float deltaTime)
{
	physicsSystem.Update(deltaTime);

	for (auto& obj : gameObjects)
	{
		obj->PhysicsUpdate(deltaTime);
	}
}

void Scene::Update(float deltaTime)
{
	int substeps = 4;
	float subDeltaTime = deltaTime / substeps;

	for (int i = 0; i < substeps; i++)
	{
		PhysicsUpdate(subDeltaTime);
	}

	LogicUpdate(deltaTime);
}

void Scene::Render(Renderer& renderer)
{
	for (auto& obj : gameObjects)
	{
		obj->Render(renderer);
	}
}
