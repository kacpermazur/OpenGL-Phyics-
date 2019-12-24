#include "Application.h"

Application::Application(const unsigned width, const unsigned height)
	: m_width(width), m_height(height), m_input(), m_state(ACTIVE)
{
}

Application::~Application()
{
}

void Application::Initialize()
{
}

void Application::InputHandler(float& delta)
{
}

void Application::Update(float& delta)
{
}

void Application::Render()
{
}
