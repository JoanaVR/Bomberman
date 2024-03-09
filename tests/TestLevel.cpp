#include <gtest/gtest.h>
#include <iostream>
#include "game/Level.h"
#include "game/Board.h"
#include "game/Blocks.h"
#include "game/Player.h"
#include <string>

TEST(LevelTest, test_serialiserEmptyBoard)
{
    Board b(2,2);
    Level l;
    std::string str = l.serialize(b);
    std::cout << str;
    Board b2(0,0);
    /*
    EXPECT_TRUE(l.deserialize(str, b2));
    EXPECT_EQ(b.getRows(), b2.getRows());
    EXPECT_EQ(b.getColumns(), b2.getColumns());
    for (int i = 0; i < b.getBoardSize(); i++)
    {
        EXPECT_EQ(b.getObject(i)->getType(), b2.getObject(i)->getType());
    }
    */

}
TEST(LevelTest, test_serialiser)
{
    Board b(2,2);
    Block block1(true, 0,1, PowerUp::NO_POWERUP, &b);
    b.addObject(&block1);
    Block block2(false, 1, 1, PowerUp::NO_POWERUP, &b);
    b.addObject(&block2);
    Player p(1,0);
    b.addObject(&p);
    Level l;
    std::string str = l.serialize(b);
    std::cout << str;
    Board b2(0,0);
    std::vector<Player*> players;
    EXPECT_TRUE(l.deserialize(str, b2, players));
    EXPECT_EQ(b.getRows(), b2.getRows());
    EXPECT_EQ(b.getColumns(), b2.getColumns());
    for (int i = 0; i < b.getGameObjectsSize(); i++)
    {
        EXPECT_EQ(b.getObject(i)->getType(), b2.getObject(i)->getType());
    }

}