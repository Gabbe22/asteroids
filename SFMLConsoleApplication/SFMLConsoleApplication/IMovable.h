#ifndef INCLUDED_MOVABLE_H
#define INCLUDED_MOVABLE_H

class IGameObject
{
public:	
	virtual void update(float deltaTime) = 0;
protected:
	virtual ~IGameObject() {};
};

#endif