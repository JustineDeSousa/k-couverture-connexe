
#pragma once

#ifndef Target_h
#define Target_h

#include <vector>

#include "sfLine.h"
#include "Header.hpp"

#define radius 6.0f // rayon des cibles

namespace state
{
	enum
	{
		normal = 0,
		hovered = 1,
		cible = 2,
		isCapted = 3
	};
};


class TargetManager;

class Target : public sf::Drawable
{
public:
	//Constucteur
	Target();
	Target(TargetManager* TargetManager);
	void set(vec2f position, float Rcom, float Rcapt, float spacing);

	//Destructeur
	~Target();

	bool gesEvent(sf::Event& e, sf::RenderWindow& window);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setState(uint s);
	bool isHovered() const { return state == state::hovered; };

private:

	TargetManager* manager;
	uint state;

	float r, rcom, rcapt;
	sf::CircleShape target;
	sf::CircleShape captor;
	sf::CircleShape com;
};

class Link : public sf::Drawable
{
public:
	//Constucteur
	Link();
	Link(TargetManager* TargetManager);
	void set(vec2f a, std::vector<vec2f> b);

	//Destructeur
	~Link();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:

	TargetManager* manager;

	vector<sfLine> points;
};

class TargetManager : public sf::Drawable
{
public:
	//Constucteur
	TargetManager();
	//void init();
	//Destructeur
	~TargetManager();

	Target* createTarget();
	Link* createLink();
	float createTargets(const Instance* instance, const Solution* solution);

	void gesEvent(sf::Event& e, sf::RenderWindow& window);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool getClicked();

private:
	std::vector<Target*> Targets;
	bool switchGraph;
	std::vector<Link*> Linkscom;

	bool clicked;

	//sf::Clock clock;

	//SpriteManager* spriteManager;
	//uint nbrPhoto, maxDim;
	//uint w, h;


	//Config config;
};

#endif