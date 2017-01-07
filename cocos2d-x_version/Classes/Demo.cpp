#include "Demo.h"
#include <map>
#include <sqlite3/include/sqlite3.h>
#include <iostream>
using namespace std;

const float SIZE_WSAD = 100.0;
const int FONT_SIZE = 100;


#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
using namespace  rapidjson;

//#pragma comment(lib,"C:/Users/CBUU/Desktop/project/richgame/cocos2d/external/sqlite3/libraries/win32/sqlite3.lib")

Demo::Demo()
{

}

Demo::~Demo()
{

}
Scene* Demo::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Demo::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
bool Demo::init()
{
	if (!Layer::init())
	{
		return false;
	}
 	testTMX();
	
	visibleSize = Director::getInstance()->getVisibleSize();
	goalfinish = 0;
	step = 0;
	initTouchEvent();

 //	testUserDefault();
    value = UserDefault::getInstance()->getIntegerForKey("value");
//	log("the value is %d ", value);
	char str[100] = { '0' };
	sprintf(str, "%d", value);
	
	Label* steps = Label::create("0", "Arial", 20);
	steps->setString(str);
	steps->setPosition(visibleSize.width / 2+100, visibleSize.height / 2 + 340);
	this->addChild(steps);
	Label* steps2 = Label::create("Last steps is :", "Arial", 20);
	steps2->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 340);
	this->addChild(steps2);
	
	return true;
}



void Demo::testTMX()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//����tiledmap����
	 tmx = TMXTiledMap::create("map.tmx");
	tmx->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	tmx->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(tmx);
	//��tmx�л�ȡ����� 
	TMXObjectGroup* objects = tmx->getObjectGroup("_wall");
	//�Ӷ�����л�ȡ�������� 
	ValueVector container = objects->getObjects();
	//�������� 
	for(auto obj:container){ 
		ValueMap values = obj.asValueMap(); 
	//��ȡ�ݺ������꣨cocos2dx���꣩ 
		int x = values.at("x").asInt()+32;
	    int y = values.at("y").asInt()+96;
			wall = Sprite::create("wall.png");
			wall->setPosition(x, y);
			wallcontainer.pushBack(wall);
			tmx->addChild(wall,0);
	}
	TMXObjectGroup* objects2 = tmx->getObjectGroup("_box");
	//�Ӷ�����л�ȡ�������� 
	ValueVector container2 = objects2->getObjects();
	//�������� 
	for (auto obj : container2){
		ValueMap values = obj.asValueMap();
		//��ȡ�ݺ������꣨cocos2dx���꣩ 
		int x = values.at("x").asInt() + 32;
		int y = values.at("y").asInt() + 96;
		box = Sprite::create("box.png");
		box->setPosition(x, y);
		boxcontainer.pushBack(box);
		tmx->addChild(box,2);
	}
	TMXObjectGroup* objects3 = tmx->getObjectGroup("_goal");
	//�Ӷ�����л�ȡ�������� 
	ValueVector container3 = objects3->getObjects();
	//�������� 
	for (auto obj : container3){
		ValueMap values = obj.asValueMap();
		//��ȡ�ݺ������꣨cocos2dx���꣩ 
		int x = values.at("x").asInt() + 32;
		int y = values.at("y").asInt() + 96;
		goal = Sprite::create("goal.png");
		goal->setPosition(x, y);
		goalcontainer.pushBack(goal);
		tmx->addChild(goal,1);
	}
	//��tmx�л�ȡ����� 
	TMXObjectGroup* objects4 = tmx->getObjectGroup("_player");
	//�Ӷ�����л�ȡ�������� 
	ValueVector container4 = objects4->getObjects();
	//�������� 
	for (auto obj : container4){
		ValueMap values = obj.asValueMap();
		//��ȡ�ݺ������꣨cocos2dx���꣩ 
	     px = values.at("x").asInt() + 32;
		 py = values.at("y").asInt() + 96;
		player = Sprite::create("player.png");
		player->setPosition(Vec2(px, py));
		tmx->addChild(player,2);
	}
}



void Demo::initTouchEvent(){
	auto menu = Menu::create();
	menu->setPosition(visibleSize.width, 0);
	menu->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	this->addChild(menu, 10);

	auto label_W = Label::createWithTTF("W", "fonts/Marker Felt.ttf", FONT_SIZE);
	auto label_S = Label::createWithTTF("S", "fonts/Marker Felt.ttf", FONT_SIZE);
	auto label_A = Label::createWithTTF("A", "fonts/Marker Felt.ttf", FONT_SIZE);
	auto label_D = Label::createWithTTF("D", "fonts/Marker Felt.ttf", FONT_SIZE);

	auto button_up = MenuItemLabel::create(label_W, CC_CALLBACK_1(Demo::onUpPressed, this));
	auto button_down = MenuItemLabel::create(label_S, CC_CALLBACK_1(Demo::onDownPressed, this));
	auto button_left = MenuItemLabel::create(label_A, CC_CALLBACK_1(Demo::onLeftPressed, this));
	auto button_right = MenuItemLabel::create(label_D, CC_CALLBACK_1(Demo::onRightPressed, this));

	button_up->setPosition(SIZE_WSAD * -1, SIZE_WSAD * 2);
	button_down->setPosition(SIZE_WSAD * -1, SIZE_WSAD * 0);
	button_left->setPosition(SIZE_WSAD * -2, SIZE_WSAD * 1);
	button_right->setPosition(SIZE_WSAD * 0, SIZE_WSAD * 1);

	button_up->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	button_down->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	button_left->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	button_right->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);

	menu->addChild(button_up);
	menu->addChild(button_down);
	menu->addChild(button_left);
	menu->addChild(button_right);
}
//
//void Demo::setTiledMap(TMXTiledMap* map) {
//	this->m_map = map;
//	this->walllayer = m_map->getLayer("wall");
//
//}





void Demo::onRightPressed(Ref* sender)
{
	//���õ���������Vector�ı���
	Vector<Sprite*>::iterator wallit = wallcontainer.begin();
	int wallflag = 0;
	int wallflag2 = 0;
	for (; wallit != wallcontainer.end();)
	{
		//����ɾ����ǩΪ1�ľ���
		if ((*wallit)->getPosition() == Vec2(px + 64, py))
		{
			wallflag = 1;
			break;
		}
		if ((*wallit)->getPosition() == Vec2(px + 128, py))
		{
			wallflag2 = 2;
			break;
		}
		
		wallit++;

	}
	Vector<Sprite*>::iterator boxit = boxcontainer.begin();
	int boxflag = 0;
	for (; boxit != boxcontainer.end();)
	{
		//����ɾ����ǩΪ1�ľ���
		if ((*boxit)->getPosition() == Vec2(px + 64, py))
		{
			boxflag = 1;

			break;
		}
		boxit++;

	}
	if (wallflag == 0 && boxflag == 0) {
		px += 64;
		step++;
	}
	else if (wallflag == 0 && boxflag == 1 && wallflag2 == 2) {
	
	}
	else if (wallflag == 0 && boxflag == 1 && wallflag2 != 2)
	{
		px += 64;
		step++;
		(*boxit)->setPosition(px + 64, py);
	//	is_win();
		Vector<Sprite*>::iterator goalit = goalcontainer.begin();

		for (; goalit != goalcontainer.end();)
		{
			//����ɾ����ǩΪ1�ľ���
			if ((*goalit)->getPosition() == Vec2(px + 64, py))
			{
				goalfinish++;

			}
			if (goalfinish == goalcontainer.size()){
				Label* labelwin = Label::create("You win,guy!", "Arial", 50);
				labelwin->setPosition(visibleSize.width / 2, visibleSize.height / 2);
				this->addChild(labelwin);
				UserDefault::getInstance()->setIntegerForKey("value", step);
			}
			goalit++;
		}

	} else {}
	player->setPosition(px, py);
	//is_win();
}




void Demo::onLeftPressed(Ref* sender)
{
	Vector<Sprite*>::iterator wallit = wallcontainer.begin();
	int wallflag = 0;
	int wallflag2 = 0;
	for (; wallit != wallcontainer.end();)
	{
		//����ɾ����ǩΪ1�ľ���
		if ((*wallit)->getPosition() == Vec2(px - 64, py))
		{
			wallflag = 1;
			break;
		}
		if ((*wallit)->getPosition() == Vec2(px - 128, py))
		{
			wallflag2 = 2;
			break;
		}
		wallit++;
	}
	Vector<Sprite*>::iterator boxit = boxcontainer.begin();
	int boxflag = 0;
	for (; boxit != boxcontainer.end();)
	{

		if ((*boxit)->getPosition() == Vec2(px - 64, py))
		{
			boxflag = 1;
			break;
		}
		boxit++;
	}
	if (wallflag == 0 && boxflag == 0) {
		px -= 64;
		step++;
	}
	else if (wallflag == 0 && boxflag == 1 && wallflag2 == 2) {

	}
	else if (wallflag == 0 && boxflag == 1 && wallflag2 != 2)
	{
		px -= 64;
		step++;
		(*boxit)->setPosition(px - 64, py);
	//	is_win();
		Vector<Sprite*>::iterator goalit = goalcontainer.begin();

		for (; goalit != goalcontainer.end();)
		{
			//����ɾ����ǩΪ1�ľ���
			if ((*goalit)->getPosition() == Vec2(px - 64, py))
			{
				goalfinish++;
			}
			if (goalfinish == goalcontainer.size()){
				Label* labelwin = Label::create("You win,guy!", "Arial", 50);
				labelwin->setPosition(visibleSize.width / 2, visibleSize.height / 2);
				this->addChild(labelwin);
				UserDefault::getInstance()->setIntegerForKey("value", step);
			}
			goalit++;
		}
	}
	else {}
	player->setPosition(px, py);
	//is_win();

}




void Demo::onUpPressed(Ref* sender)
{
	Vector<Sprite*>::iterator wallit = wallcontainer.begin();
	int wallflag = 0;
	int wallflag2 = 0;
	for (; wallit != wallcontainer.end();)
	{
		//����ɾ����ǩΪ1�ľ���
		if ((*wallit)->getPosition() == Vec2(px, py + 64))
		{
			wallflag = 1;
			break;
		}
		if ((*wallit)->getPosition() == Vec2(px , py + 128))
		{
			wallflag2 = 2;
			break;
		}

		wallit++;

	}
	Vector<Sprite*>::iterator boxit = boxcontainer.begin();
	int boxflag = 0;
	for (; boxit != boxcontainer.end();)
	{
		//����ɾ����ǩΪ1�ľ���
		if ((*boxit)->getPosition() == Vec2(px , py + 64))
		{
			boxflag = 1;

			break;
		}
		boxit++;

	}
	if (wallflag == 0 && boxflag == 0) {
		py += 64;
		step++;
	}
	else if (wallflag == 0 && boxflag == 1 && wallflag2 == 2) {

	}
	else if (wallflag == 0 && boxflag == 1 && wallflag2 != 2)
	{
		py += 64;
		step++;
		(*boxit)->setPosition(px, py + 64);
		//is_win();
		Vector<Sprite*>::iterator goalit = goalcontainer.begin();

		for (; goalit != goalcontainer.end();)
		{
			//����ɾ����ǩΪ1�ľ���
			if ((*goalit)->getPosition() == Vec2(px, py + 64))
			{
				goalfinish++;

			}
			if (goalfinish == goalcontainer.size()){
				Label* labelwin = Label::create("You win,guy!", "Arial", 50);
				labelwin->setPosition(visibleSize.width / 2, visibleSize.height / 2);
				this->addChild(labelwin);
				UserDefault::getInstance()->setIntegerForKey("value", step);
			}
			goalit++;
		}
	}
	else {}
	player->setPosition(px, py);
	//is_win();
}




void Demo::onDownPressed(Ref* sender)
{
	Vector<Sprite*>::iterator wallit = wallcontainer.begin();
	int wallflag = 0;
	int wallflag2 = 0;
	for (; wallit != wallcontainer.end();)
	{
		//����ɾ����ǩΪ1�ľ���
		if ((*wallit)->getPosition() == Vec2(px, py - 64))
		{
			wallflag = 1;
			break;
		}
		if ((*wallit)->getPosition() == Vec2(px , py - 128))
		{
			wallflag2 = 2;
			break;
		}

		wallit++;

	}
	Vector<Sprite*>::iterator boxit = boxcontainer.begin();
	int boxflag = 0;
	for (; boxit != boxcontainer.end();)
	{
		//����ɾ����ǩΪ1�ľ���
		if ((*boxit)->getPosition() == Vec2(px , py - 64))
		{
			boxflag = 1;

			break;
		}
		boxit++;

	}
	if (wallflag == 0 && boxflag == 0) {
		py -= 64;
		step++;
	}
	else if (wallflag == 0 && boxflag == 1 && wallflag2 == 2) {

	}
	else if (wallflag == 0 && boxflag == 1 && wallflag2 != 2)
	{
		py -= 64;
		step++;
		(*boxit)->setPosition(px , py - 64);
	//	is_win();
		Vector<Sprite*>::iterator goalit = goalcontainer.begin();

		for (; goalit != goalcontainer.end();)
		{
			//����ɾ����ǩΪ1�ľ���
			if ((*goalit)->getPosition() == Vec2(px, py - 64))
			{
				goalfinish++;

			}
			if (goalfinish == goalcontainer.size()){
				Label* labelwin = Label::create("You win,guy!", "Arial", 50);
				labelwin->setPosition(visibleSize.width / 2, visibleSize.height / 2);
				this->addChild(labelwin);
				UserDefault::getInstance()->setIntegerForKey("value", step);
			}
			goalit++;
		}
	}
	else {}
	player->setPosition(px, py);
	//is_win();
}

