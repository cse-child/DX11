#pragma once

class VertexShader : public Shader
{
public:
	VertexShader(wstring file);
	~VertexShader();

	virtual void Set() override;

private:
	void CreateInputLayout();

private:
	ID3D11VertexShader* vertexShader;
	ID3D11InputLayout* inputLayout;

	// Reflection: 반사하다?반영하다?
	// input layout을 쓰는 이유는 CPU에 있는 정점 정보를 GPU(Vertex Shader)에 알려주는 역할인데
	// reflection는 Vertex Shader에 있는 정보를 훔쳐와서 자동으로 정보를 맞출 수 있도록 도움
	ID3D11ShaderReflection* reflection;
};