#pragma once

class Scene
{
public:
	// ��ĳ���� ������ �ڽ��� �Ҹ��ڷ� ȣ���ϱ� ���� �����Լ� ���
	virtual ~Scene() {} 

	virtual void Update() = 0;

	virtual void Render() = 0;
	virtual void PostRender() = 0;
};