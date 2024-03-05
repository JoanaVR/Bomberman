#include <gtest/gtest.h>
#include "game/Blocks.h"
#include "game/Player.h"
#include "game/Board.h"
#include "game/Level.h"

TEST(Board, test_findCollisions)
{
    Board b(2, 2);
    Block block1(true, 0, 0);
    b.addObject(&block1);
    Block block2(false, 0, 1);
    b.addObject(&block2);
    Player p(1, 0);
    b.addObject(&p);
    EXPECT_TRUE(b.findCollisions().empty());
}

TEST(Board, test_move)
{
    /*
    auto boardXML = R"(
    <board Rows="3" Columns="3">
    <object cell_type="block" rows="0" columns="1"/>
    <object cell_type="unbreakable_block" rows="1" columns="1"/>
    </board>
    )";
    */
    Level l;
    Board b(3, 3);
    Block block1(true, 0, 0);
    b.addObject(&block1);
    Block block2(false, 0, 1);
    b.addObject(&block2);
    Player p(2, 0);
    p.setSpeed(20);
    p.setDirection(GameObject::LEFT);
    b.addObject(&p);
    b.move();
    // EXPECT_EQ(b.getObject(2)->getRow(), 0);
    // EXPECT_EQ(b.getObject(2)->getColumn(), 1);
}

TEST(Board, test_eraseBlock)
{
    Level l;
    Board b(3, 3);
    Block *block1 = new Block(true, 0, 0);
    b.addObject(block1);
    Block *block2 = new Block(false, 0, 1);
    b.addObject(block2);
    EXPECT_EQ(b.getGameObjectsSize(), 2);
    b.removeObject(0, 0);
    EXPECT_EQ(b.getGameObjectsSize(), 1);
}

TEST(Board, test_explodeBombHorizontally)
{
    Level l;
    Board b(5, 5);
    Block *block1 = new Block(true, 2, 0);
    b.addObject(block1);
    Block *block2 = new Block(false, 2, 3);
    b.addObject(block2);
    Block *block3 = new Block(true, 2, 4);
    b.addObject(block3);
    EXPECT_EQ(b.getGameObjectsSize(), 3);
    Bomb* bomb = new Bomb(2,2,&b,3);
    b.addObject(bomb);
    for(int i = 0; i < 1000; i++)
        b.move();
    EXPECT_EQ(b.getGameObjectsSize(), 2);
}

TEST(Board, test_explodeBombVertically)
{
    Level l;
    Board b(5, 5);
    Block *block1 = new Block(true, 0, 3);
    b.addObject(block1);
    Block *block2 = new Block(true, 3, 3);
    b.addObject(block2);
    EXPECT_EQ(b.getGameObjectsSize(), 2);
    Bomb* bomb = new Bomb(2,3,&b,2);
    b.addObject(bomb);
    for(int i = 0; i < 1000; i++)
        b.move();
    EXPECT_EQ(b.getGameObjectsSize(), 0);
}

TEST(Board, test_placeBomb)
{
    Level l;
    Board b(5, 5);
    Block *block1 = new Block(true, 0, 3);
    b.addObject(block1);
    Block *block2 = new Block(true, 3, 3);
    b.addObject(block2);
    EXPECT_EQ(b.getGameObjectsSize(), 2);
    Player p(2, 3);
    Bomb* bomb = new Bomb(2,3,&b,3);
    b.addObject(bomb);
    for(int i = 0; i < 1000; i++)
        b.move();
    EXPECT_EQ(b.getGameObjectsSize(), 0);
}

TEST(Board, test_playerMoveRightAndDown)
{ // GTEST_SKIP();
    GameObject::setCellSize(10);
    GameObject::setDefaulfSpeed(7);
    Level l;
    Board b(4, 4);
    Player *player = new Player(0, 0);
    b.addObject(player);
    player->setDirection(GameObject::RIGHT);
    b.move();
    EXPECT_EQ(player->getmX(), 7);
    EXPECT_EQ(player->getmY(), 0);
    player->setDirection(GameObject::DOWN);
    b.move();
    EXPECT_EQ(player->getmX(), 10);
    EXPECT_EQ(player->getmY(), 0);
    b.move();
    EXPECT_EQ(player->getmX(), 10);
    EXPECT_EQ(player->getmY(), 7);
    b.move();
    EXPECT_EQ(player->getmX(), 10);
    EXPECT_EQ(player->getmY(), 14);
    b.move();
    EXPECT_EQ(player->getmX(), 10);
    EXPECT_EQ(player->getmY(), 21);
    b.move();
    EXPECT_EQ(player->getmX(), 10);
    EXPECT_EQ(player->getmY(), 28);
    b.move();
    EXPECT_EQ(player->getmX(), 10);
    EXPECT_EQ(player->getmY(), 30);
    b.move();
    EXPECT_EQ(player->getmX(), 10);
    EXPECT_EQ(player->getmY(), 30);
}
TEST(Board, test_playerTurning)
{
    GameObject::setCellSize(10);
    GameObject::setDefaulfSpeed(7);
    Level l;
    Board b(4, 4);
    Player *player = new Player(0, 0);
    b.addObject(player);
    player->setDirection(GameObject::RIGHT);
    b.move();
    EXPECT_EQ(player->getmX(), 7);
    EXPECT_EQ(player->getmY(), 0);
    b.move();
    EXPECT_EQ(player->getmX(), 14);
    EXPECT_EQ(player->getmY(), 0);
    player->setDirection(GameObject::DOWN);
    b.move();
    EXPECT_EQ(player->getmX(), 20);
    EXPECT_EQ(player->getmY(), 0);
    b.move();
    EXPECT_EQ(player->getmX(), 20);
    EXPECT_EQ(player->getmY(), 7);
}

TEST(Board, test_alignPlayerToNearestCellHorizontal)
{
    GameObject::setCellSize(10);
    GameObject::setDefaulfSpeed(7);
    Level l;
    Board b(4, 4);
    Player *player = new Player(0, 0);
    b.addObject(player);
    player->setDirection(GameObject::RIGHT);
    b.move();
    EXPECT_EQ(player->getmX(), 7);
    EXPECT_EQ(player->getmY(), 0);
    player->alignObjectToNearestCell();
    EXPECT_EQ(player->getmX(), 10);
    EXPECT_EQ(player->getmY(), 0);
    b.move();
    b.move();
    EXPECT_EQ(player->getmX(), 24);
    EXPECT_EQ(player->getmY(), 0);
    player->alignObjectToNearestCell();
    EXPECT_EQ(player->getmX(), 20);
    EXPECT_EQ(player->getmY(), 0);
}

TEST(Board, test_alignPlayerToNearestCellVertical)
{
    GameObject::setCellSize(10);
    GameObject::setDefaulfSpeed(7);
    Level l;
    Board b(4, 4);
    Player *player = new Player(0, 0);
    b.addObject(player);
    player->setDirection(GameObject::DOWN);
    b.move();
    EXPECT_EQ(player->getmX(), 0);
    EXPECT_EQ(player->getmY(), 7);
    player->alignObjectToNearestCell();
    EXPECT_EQ(player->getmX(), 0);
    EXPECT_EQ(player->getmY(), 10);
    b.move();
    b.move();
    EXPECT_EQ(player->getmX(), 0);
    EXPECT_EQ(player->getmY(), 24);
    player->alignObjectToNearestCell();
    EXPECT_EQ(player->getmX(), 0);
    EXPECT_EQ(player->getmY(), 20);
}

TEST(Board, test_playerCornerTurning)
{
    GameObject::setCellSize(10);
    GameObject::setDefaulfSpeed(7);
    Level l;
    Board b(5, 5);
    Player *player = new Player(4, 4);
    b.addObject(player);
    Block *block1 = new Block(true, 3, 2);
    b.addObject(block1);
    player->setDirection(GameObject::UP);
    b.move();
    EXPECT_EQ(player->getmX(), 40);
    EXPECT_EQ(player->getmY(), 33);
    b.move();
    EXPECT_EQ(player->getmX(), 40);
    EXPECT_EQ(player->getmY(), 26);
    b.move();
    EXPECT_EQ(player->getmX(), 40);
    EXPECT_EQ(player->getmY(), 19);
    player->setDirection(GameObject::LEFT);
    b.move();
    EXPECT_EQ(player->getmX(), 40);
    EXPECT_EQ(player->getmY(), 12);
    b.move();
    EXPECT_EQ(player->getmX(), 40);
    EXPECT_EQ(player->getmY(), 10);
    b.move();
    EXPECT_EQ(player->getmX(), 33);
    EXPECT_EQ(player->getmY(), 10);
}