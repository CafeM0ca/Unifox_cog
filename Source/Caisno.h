/*
  ==============================================================================

    Caisno.h
    Created: 24 Mar 2018 11:20:14pm
    Author:  moca

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class Caisno    : public Component
{
public:
    Caisno();
    ~Caisno();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Caisno)
};
