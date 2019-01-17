#pragma once
#include "GameObject.h"
#include "Sprite.h"
class Renderable2D
	: public GameObject
{
private:
	//Variables:
	glm::ivec2* spriteDim;

	//Functions
	void scaleToSprite();

protected:
	float renderLayer = 1.f;
	glm::mat4* InstanceMatrix;

public:
	Renderable2D(const char* fileName, glm::vec2* _position, glm::ivec2* _spriteDim = new glm::ivec2(32, 32));
	~Renderable2D();

	//Public fields:
	float rotation = 0.f;
	glm::vec2* position;
	bool shouldRender = true;
	
	//Setters
	void setSprite(const char* fileName);
	void setLayer(float newLayer);

	//Accessors
	glm::vec2* getPosition();
	glm::mat4* getInstanceMatrix();
	float getRotation();
	float getLayer();
};