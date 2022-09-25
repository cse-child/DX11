#pragma once

class Scene
{
public:
	// 업캐스팅 됐을때 자식의 소멸자로 호출하기 위해 가상함수 사용
	virtual ~Scene() {} 

	virtual void Update() = 0;

	virtual void Render() = 0;
	virtual void PostRender() = 0;
};