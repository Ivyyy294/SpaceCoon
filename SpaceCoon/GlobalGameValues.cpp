#include "stdafx.h"
#include "GlobalGameValues.h"

GlobalGameValues& GlobalGameValues::Me()
{
    static GlobalGameValues v;
    return v;
}
