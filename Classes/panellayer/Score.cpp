#include "Score.h"


Score::Score()
{

}


Score::~Score()
{

}
Score * Score::create()
{
	Node* _scorenode = CSLoader::createNode("panellayer/nodescore.csb");
	Score* _score = new Score();
	//_score->init();
	_score->_nodescore = DataOfGame::getInstance()->seekNodebyName(_scorenode, "node_score");
	_score->_spritebg = static_cast<Sprite*>(DataOfGame::getInstance()->seekNodebyName(_scorenode, "sprite_scorepanel"));
	_score->scoreLabel = static_cast<ui::Text*>(DataOfGame::getInstance()->seekNodebyName(_scorenode,"text_score"));
	//_score->_startPos.x = _score->scoreLabel->getPosition().x - _score->scoreLabel->getContentSize().width / 2;
	_score->_scoreTitle = static_cast<ui::Text*>(DataOfGame::getInstance()->seekNodebyName(_scorenode, "text_title"));
	return _score;
}
void Score::addScoreLabelToScene(Node*scene)
{
	//Size winSize = Director::getInstance()->getWinSize();
	//Sprite* ScoreView = Sprite::create("panellayer/scoreview_1.png");
	//ScoreView->setAnchorPoint(Vec2(0.5f,0.5f));
	//float p_X = winSize.width * 0 + ScoreView->getContentSize().width / 2+30;
	//float p_Y=	winSize.height  - ScoreView->getContentSize().height/2-50;
	//ScoreView->setPosition(DataOfGame::getInstance()->getrealposition(Vec2(p_X,p_Y)));
	//scoreLabel = ui::Text::create("0", "font/fangzhengzongyijianti.ttf", 20);
	//scoreLabel->setAnchorPoint(Vec2(0.5f,0.5f));
	//scoreLabel->setPosition(Vec2(124.83, 28.14));
	//scoreLabel->setColor(Color3B::YELLOW);
	//ScoreView->addChild(scoreLabel);
	//scene->addChild(ScoreView,5);
}
void Score::addScoreOnScene(int score,Node*scene, Vec2 point)
{
	if (!scene)
	{
		DataOfGame::getInstance()->_scorenow+= score;
		log("scene == nullptr");
		return;
	}
	DataOfGame::getInstance()->_scorenow += score;
	//TODO：展示特效
	char s_score[10];
	sprintf(s_score,"+%d",score);
	Label* addScore = Label::createWithTTF(s_score,"font/fangzhengzongyijianti.ttf",36);
	addScore->setColor(Color3B::YELLOW);
	addScore->setPosition( point);
	auto moveBy = MoveBy::create(0.3f, Vec2(0, 80));
	auto scale = ScaleTo::create(0.3f, 1.5);
	auto moveFinish = CCCallFuncN::create(CC_CALLBACK_1(Score::scoreMovefinish, this));
	auto action = Sequence::create(Spawn::create(moveBy, scale, nullptr), moveFinish, nullptr);
	addScore->runAction(action);
	scene->addChild(addScore,3);
}
void Score::scoreMovefinish(Ref*sender)
{
	Label* addScore = static_cast<Label*>(sender);
	addScore->stopAllActions();
	addScore->removeFromParent();
}
void Score::SubScoreOnScene(int score)
{
	DataOfGame::getInstance()->_gameScore -= 0;
	//TODO:展示特效
}
void Score::updateScoreLabel(int _score)
{
	char s_score[10];
	sprintf(s_score, "%d", _score);
	if (scoreLabel == nullptr)
	{
		return;
	}
	scoreLabel->setString(s_score);
	//scoreLabel->setPositionX(_startPos.x+scoreLabel->getContentSize().width/2);
}