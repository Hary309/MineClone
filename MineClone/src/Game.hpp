﻿#pragma once

#include <memory>

#include "Graphics/Camera.hpp"
#include "Graphics/ShaderProgram.hpp"
#include "Graphics/VertexBuffer.hpp"
#include "Graphics/ShaderProgram.hpp"

#include "World/World.hpp"
#include "World/Player.hpp"

class Texture;
struct GLFWwindow;

class Game
{
public:
	static constexpr unsigned ScreenWidth = 1024;
	static constexpr unsigned ScreenHeight = 768;

private:
	static Game* _inst;

	GLFWwindow* _window = nullptr;

	Camera _camera;
	Player _player;
	World _world;

	std::unique_ptr<ShaderProgram> _shaderProgram;

	glm::vec2 _lastCursorPos;

public:
	Game();
	~Game();

	bool init();
	void run();

	Camera& getCamera() { return _camera; }
	const Camera& getCamera() const { return _camera; }

	GLFWwindow* getWindow() { return _window; }
	const GLFWwindow* getWindow() const { return _window; }

	glm::vec2 getCursorOffset(const glm::vec2& pos) 
	{ 
		glm::vec2 result;
		result.x = pos.x - _lastCursorPos.x;
		result.y = _lastCursorPos.y - pos.y;
		_lastCursorPos = pos; 

		return result;
	}

	static Game* get()
	{
		return _inst;
	}

private:
	bool initRenderer();
	bool initGame();

	void update();
	void render();
};
