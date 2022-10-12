#pragma once

class RenderTargetScene : public Scene
{
public:
	RenderTargetScene();
	~RenderTargetScene();

	virtual void Update() override;
	
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
	
private:
	Quad* bg;
	Dog* dog;

	RenderTarget* renderTarget;

	vector<Quad*> renderTextures;

	IntValueBuffer* indexBuffer;
};