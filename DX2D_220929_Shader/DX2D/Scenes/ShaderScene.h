#pragma once

class ShaderScene : public Scene
{
public:
	ShaderScene();
	~ShaderScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	Quad* quad;
	Dog* dog;
	IntValueBuffer* valueBuffer;
	FloatValueBuffer* sizeBuffer;

};