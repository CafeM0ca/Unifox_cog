/*
  ==============================================================================

    Casino.cpp
    Created: 24 Mar 2018 11:20:14pm
    Author:  moca

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Casino.h"

//==============================================================================
Casino::Casino()
{
	// 장부 확인
	// 없으면 만들고 있으면 불러옴
	SetBase();
}

Casino::~Casino()
{
}

void Casino::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.setFont (Font (76.0f));
    g.setColour (Colours::orange);
    g.drawText ("Unifox", getLocalBounds(), Justification::centredTop, true);

}

void Casino::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
	//capital_label.setBounds(0,150,70,200);
	//cap_text_label.setBounds(70,150,100,170);	
	//coin_label.setBounds(0,200,70,250);

}

void Casino::SetBase()
{
	//init capital and number of coin
	capital_label = new Label;
	cap_text_label = new Label;
	addAndMakeVisible(capital_label);
	capital_label->setFont(Font(15.0f,Font::bold));
	capital_label->setText("start capital: ",dontSendNotification);
	capital_label->attachToComponent(cap_text_label,true);
	capital_label->setColour(Label::textColourId,Colours::orange);
	capital_label->setJustificationType(Justification::centred);
	capital_label->setBounds(100,80,50,20);

	addAndMakeVisible(cap_text_label); 
	cap_text_label->setEditable(true);
	cap_text_label->setColour (Label::backgroundColourId,Colours::orange);
	cap_text_label->addListener(this);
	cap_text_label->setBounds(100,80,50,20);	
	
	coin_label = new Label;
	coin_text_label = new Label;
	addAndMakeVisible(coin_label);
	coin_label->setFont(Font(15.0f,Font::bold));
	coin_label->setText("All of chip: ",dontSendNotification);
	coin_label->attachToComponent(coin_text_label,true);
	coin_label->setColour(Label::textColourId,Colours::orange);
	coin_label->setJustificationType(Justification::centredLeft);
	coin_label->setBounds(100,110,50,20);

	addAndMakeVisible(coin_text_label);
	coin_text_label->setEditable(true);
	coin_text_label->setColour (Label::backgroundColourId,Colours::orange);
	coin_text_label->addListener(this);
	coin_text_label->setBounds(100,110,50,20);	

	check_init = new TextButton;
	addAndMakeVisible(check_init);
	check_init->setButtonText("set up");
	check_init->setBounds(0,135,50,50);
	check_init->addListener(this);
}
