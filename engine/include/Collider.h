#pragma once
#include "Objects/Behaviour.h"

/*
class Bounds
{
	private:
	//center of collider relative to parent world space position
	sf::Vector2<float> center;

	//Always Half the size of the bounds
	sf::Vector2<float> extents;

public:

	void SetCenter(sf::Vector2<float> cent)
	{
		center = cent;
	}
	
	void ApplyExtents(sf::Vector2<float> extent)
	{
		extents = extent;
	}
};

class Collider : public Behaviour
{

	


};*/



class Collider: public Behaviour
{

};

class HitResult
{
public:
	HitResult();

	bool debugHit;

	///Hit Collider, will be null if nothing was hit.
	Collider* col;

	///Hit Position or estimated location
	sf::Vector2f hitPosition;

	/// overlap vector, can be used to move it back to a non colliding state
	sf::Vector2f delta;

	/// surface normal at contact point
	sf::Vector2f normal;

	///fraction between 0-1 for segment or sweep intersections
	float hitTime;
};

/*
export class Sweep {
public hit: Hit | null;
public pos: Point;
public time: number;

	constructor() {
		this.hit = null;
		this.pos = new Point();
		this.time = 1;
	}
};*/
class SweepResult
{
public:

	SweepResult();

	///Object that this sweep has hit, can be null if no result is found
	HitResult* hit;

	///Furthest point on a sweep path before hitting something
	sf::Vector2f pos;

	///Copy of sweep.hit.time offset by epsilon or 1 if no hit was made
	float time=1;

};