#include "game/Board.h"
#include "Level.h"
#include "Player.h"
#include "Blocks.h"
#include "Bomb.h"
#include <tinyxml2.h>
#include <sstream>

std::string Level::serialize(const Board &board)
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement *routElement = doc.NewElement("board");
    int bRow = board.getRows();
    routElement->SetAttribute("Rows", bRow);
    int bColumn = board.getColumns();
    routElement->SetAttribute("Columns", bColumn);

    for (auto i = 0; i < board.getGameObjectsSize(); i++)
    {
        tinyxml2::XMLElement *object = doc.NewElement("object");
        const GameObject *currentObject = board.getObject(i);

        switch (currentObject->getType())
        {
        case GameObject::ObjectType::PLAYER:
            object->SetAttribute("cell_type", "player");
            break;
        case GameObject::ObjectType::BLOCK:
            object->SetAttribute("cell_type", "block");
            break;
        case GameObject::ObjectType::UNBREAKABLE_BLOCK:
            object->SetAttribute("cell_type", "unbreakable_block");
            break;
        case GameObject::ObjectType::POWERUP:
            object->SetAttribute("cell_type", "powerup");
            break;
        case GameObject::ObjectType::EMPTY:
            object->SetAttribute("cell_type", "empty");
            break;
        case GameObject::ObjectType::BOMB:
            object->SetAttribute("cell_type", "bomb");
            break;
        }
        int objectRow = currentObject->getRow();
        object->SetAttribute("rows", objectRow);

        int objectColumn = currentObject->getColumn();
        object->SetAttribute("columns", objectColumn);

        routElement->InsertEndChild(object);
    }
    doc.InsertEndChild(routElement);

    tinyxml2::XMLPrinter myPrinter(0, false, 0); // Set compact to true
    doc.Print(&myPrinter);
    return std::string(myPrinter.CStr());
}

bool Level::deserialize(std::string &filename, Board &b)
{
    tinyxml2::XMLDocument doc;
    doc.Parse(filename.data(), filename.size());

    if (doc.Error())
    {
        return false;
    }
    const char *attribute = doc.RootElement()->Attribute("Rows");
    int row = 0;

    std::istringstream ss;
    if (attribute)
    {
        ss.str(attribute);
        ss >> std::dec >> row;
    }

    attribute = doc.RootElement()->Attribute("Columns");
    int column = 0;

    ss.clear();
    if (attribute)
    {
        ss.str(attribute);
        ss >> std::dec >> column;
    }

    Board resultBoard(row, column);
    for (tinyxml2::XMLElement *object = doc.RootElement()->FirstChildElement(); object; object = object->NextSiblingElement())
    {
        attribute = object->Attribute("cell_type");
        const char* objectRowChar =  object->Attribute("rows");
        const char* objectColumnChar = object->Attribute("columns");
        int objectRow =  std::stoi(objectRowChar);
        int objectColumn =  std::stoi(objectColumnChar);

        if (attribute)
        {
            /*if (std::strcmp(attribute, "empty") == 0)
            {
                resultBoard.addObject(GameObject::ObjectType::EMPTY);
            }*/
            if (std::strcmp(attribute, "player") == 0)
            {
                Player *p = new Player(objectRow, objectColumn);
                resultBoard.addObject(p);
            }
            else if (std::strcmp(attribute, "block") == 0)
            {
                Block *b = new Block(true, objectRow, objectColumn);
                resultBoard.addObject(b);
            }
            else if (std::strcmp(attribute, "unbreakable_block") == 0)
            {
                Block *b = new Block(false, objectRow, objectColumn);
                resultBoard.addObject(b);
            }
            else if (std::strcmp(attribute, "powerup") == 0)
            {
                // resultBoard.addObject(GameObject::ObjectType::POWERUP);
            }
            else if (std::strcmp(attribute, "bomb") == 0)
            {
                resultBoard.placeBomb(objectRow, objectColumn);
            }
        }
    }

    b = resultBoard;
    return true;
}