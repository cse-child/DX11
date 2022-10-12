#include "Framework.h"
#include "CollisionScene.h"

CollisionScene::CollisionScene()
{
	colliders.push_back(new CircleCollider(30));
	colliders.push_back(new RectCollider(Vector2(50, 100)));
	//colliders.push_back(new RectCollider(Vector2(100, 50)));
	
	colliders[0]->SetTag("Circle1");
	colliders[0]->Position() = { CENTER_X, CENTER_Y };
	//
	//colliders[1]->SetTag("Circle2");
	//colliders[1]->Position() = { CENTER_X, CENTER_Y };

	//colliders[0]->SetTag("Rect1");
	//colliders[0]->Position() = { CENTER_X, CENTER_Y };
	colliders[1]->SetTag("Rect2");
	colliders[1]->Position() = { CENTER_X, CENTER_Y };
}

CollisionScene::~CollisionScene()
{
	for (Collider* collider : colliders)
		delete collider;
	colliders.clear();
}

void CollisionScene::Update()
{
	//if (colliders[0]->IsPointCollision(mousePos))
	//{
	//	colliders[0]->SetColor(1, 0, 0);
	//}
	//else
	//{
	//	colliders[0]->SetColor(0, 1, 0);
	//}

	//Vector2 overlap;
	//
	//if (colliders[0]->IsRectCollision((RectCollider*)colliders[1], &overlap))
	if(colliders[0]->IsCollision(colliders[1]))
	{
		colliders[0]->SetColor(1, 0, 0);
		colliders[1]->SetColor(1, 0, 0);
	}
	else
	{
		colliders[0]->SetColor(0, 1, 0);
		colliders[1]->SetColor(0, 1, 0);
	}

	for (Collider* collider : colliders)
		collider->UpdateWorld();
}

void CollisionScene::Render()
{
	for (Collider* collider : colliders)
		collider->Render();
}

void CollisionScene::PostRender()
{
	for (Collider* collider : colliders)
		collider->RenderUI();
}
