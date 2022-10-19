#pragma once

class InstancingScene : public Scene
{
private:
	const UINT SIZE = 1000;

	struct InstanceData
	{
		// vertex shader의 input 순서대로 맞춰야함
		Matrix transform; 
		Vector2 maxFrame;
		Vector2 curFrame;
	};

public:
	InstancingScene();
	~InstancingScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;


private:
	//vector<Quad*> quads;
	Quad* quad;

	vector<InstanceData> instances;
	VertexBuffer* instanceBuffer;
};