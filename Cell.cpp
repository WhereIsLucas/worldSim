#include <iostream>
#include "Cell.h"

Cell::Cell()
{
    
}

Cell::~Cell()
{
    
}

void Cell::initCell(int i_index)
{
    m_index = i_index;
    headOfList = -9;
    m_numberOfNeighbors = 0;
}

void Cell::setHeadOfList(int i_headOfList)
{
    headOfList = i_headOfList;
}

void Cell::addNeighbor(int i_neighborIndex)
{
    m_listOfNeighbors[m_numberOfNeighbors] = i_neighborIndex;
    m_numberOfNeighbors++;
}

int Cell::getHeadOfList()
{
    return headOfList;
}

int Cell::neighbor(int i_n)
{
    return m_listOfNeighbors[i_n];
}

int Cell::numberOfNeighbors()
{
    return m_numberOfNeighbors;
}
