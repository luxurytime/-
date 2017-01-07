#include "cocos2d.h"

USING_NS_CC;

class Demo :public Layer
{
public:
	Demo();
	~Demo();
	CREATE_FUNC(Demo);
	void onRightPressed(Ref* sender);
	void onLeftPressed(Ref* sender);
	void onUpPressed(Ref* sender);
	void onDownPressed(Ref* sender);
	void initTouchEvent();
	virtual bool init();
	void testTMX();
	static cocos2d::Scene* createScene();
private:
	Size visibleSize;
	TMXTiledMap* tmx;
	Vector<Sprite*> wallcontainer;
	Vector<Sprite*> boxcontainer;
	Vector<Sprite*> goalcontainer;
	//TMXLayer* walllayer;
	Sprite* player;
	Sprite* goal;
	Sprite* wall;
	Sprite* box;
	int px, py;
	int step;
	int goalfinish = 0;
	int value;
};
