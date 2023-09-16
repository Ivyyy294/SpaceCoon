#pragma once
#include "Dialog.h"

using namespace LarasEngine;

class IntroDialog :
    public Dialog
{
public:
    IntroDialog();
    virtual void Update () override;
};

