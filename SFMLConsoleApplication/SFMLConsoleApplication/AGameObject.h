#ifndef INCLUDED_MOVABLE_H
#define INCLUDED_MOVABLE_H

class AGameObject
{
public:	
	virtual void update(float deltaTime) = 0;
protected:
	virtual ~AGameObject() {};
};

#endif