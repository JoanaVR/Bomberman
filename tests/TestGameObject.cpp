#include <gtest/gtest.h>
#include "game/Blocks.h"
#include "game/Player.h"

TEST(GameObject, test_alignMovingObjectToCellUp)
{
    GameObject::setCellSize(10);
    GameObject::setDefaulfSpeed(7);
    Player p(0, 0);
    p.move();
    p.alignMovingObjectToCell(GameObject::RIGHT);
    EXPECT_EQ(p.getRow(), 0);
    EXPECT_EQ(p.getColumn(), 1);
}