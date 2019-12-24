#pragma once

enum State
{
	MENU,
	ACTIVE,
	END
};

class Application
{
public:
	unsigned int m_width;
	unsigned int m_height;

	bool m_input[1024];
	
	State m_state;

	Application(const unsigned int width, const unsigned int height);
	~Application();

	void Initialize();
	void InputHandler(float& delta);
	void Update(float& delta);
	void Render();
};