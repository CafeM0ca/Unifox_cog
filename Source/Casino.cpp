/*
  ==============================================================================

    Casino.cpp
    Created: 24 Mar 2018 11:20:14pm Author:  moca

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Casino.h"

//==============================================================================
Casino::Casino() :capital_label(nullptr),coin_label(nullptr),cap_text_label(nullptr),coin_text_label(nullptr),check_init(nullptr),price_label(nullptr),revenue_label(nullptr),debt_label(nullptr),cur_coin_label(nullptr),sold_coin_label(nullptr) 
{
	// 장부 확인
	// 없으면 만들고 있으면 불러옴
	SetBase();
}

Casino::~Casino()
{
	if(check_init != nullptr) delete check_init;
	if(capital_label != nullptr) delete capital_label;
	if(cap_text_label != nullptr) delete cap_text_label;
	if(coin_label != nullptr) delete coin_label;
	if(coin_text_label != nullptr) delete coin_text_label;
	if(price_label != nullptr) delete price_label;
	if(revenue_label != nullptr) delete revenue_label;
	if(debt_label != nullptr) delete debt_label;
	if(cur_coin_label != nullptr) delete cur_coin_label;
	if(sold_coin_label != nullptr) delete sold_coin_label;


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

	g.setColour (Colours::white);
	g.setFont(Font(16.0f,Font::bold));
	g.drawText(cap_string,100,160,20,30,false);
	g.drawText(cap_string,100,160,20,30,false);

	//g.drawText()
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
	capital_label->setFont(Font(20.0f,Font::bold));
	capital_label->setText("init capital: ",dontSendNotification);
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
	coin_label->setFont(Font(20.0f,Font::bold));
	coin_label->setText("init coin: ",dontSendNotification);
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
	check_init->setBounds(0,135,100,50);
	check_init->addListener(this);
}

void Casino::Menu()
{
	price_label = new Label;	
	addAndMakeVisible(price_label);
	price_label->setFont(Font(24.0f,Font::bold));
	price_label->setText("Buy Price\n5 coin per 1000won\n10 coin per 2000won\n15 coin per 3000won\n25 coin per 5000won \n\nSell Price\n6 coin per 1000won\n12 coin per 2000won\n18 coin per 3000won\n29 coin per 5000won",dontSendNotification);
	price_label->setColour(Label::textColourId,Colours::white);
	price_label->setJustificationType(Justification::centredRight);
	price_label->setBounds(0,50,getWidth(),getHeight()-50);
				
	cur_coin_label = new Label;
	addAndMakeVisible(cur_coin_label);
	cur_coin_label->setFont(Font(20.0f,Font::bold));
	cur_coin_label->setText("Current coin: ",dontSendNotification);
	cur_coin_label->setColour(Label::textColourId,Colours::orange);
	cur_coin_label->setJustificationType(Justification::topLeft);
	cur_coin_label->setBounds(0,100,120,30);
		
//	coin_text_label->setFont(Font(20.0f,Font::bold));
//	coin_text_label->setColour(Label::textColourId,Colours::white);
//	coin_text_label->setJustificationType(Justification::centredRight);
//	coin_text_label->setBounds(120,100,30,30);

	sold_coin_label = new Label;
	addAndMakeVisible(sold_coin_label);
	sold_coin_label->setFont(Font(20.0f,Font::bold));
	sold_coin_label->setText("Sold coin:",dontSendNotification);
	sold_coin_label->setColour(Label::textColourId,Colours::orange);
	sold_coin_label->setJustificationType(Justification::topLeft);
	sold_coin_label->setBounds(0,130,120,30);
	
		
	
	capital_label = new Label;
	addAndMakeVisible(capital_label);
	capital_label->setFont(Font(20.0f,Font::bold));
	capital_label->setText("capital:",dontSendNotification);
	capital_label->setColour(Label::textColourId,Colours::orange);
	capital_label->setJustificationType(Justification::topLeft);
	capital_label->setBounds(0,160,120,30);
	

	revenue_label = new Label;
	addAndMakeVisible(revenue_label);
	revenue_label->setFont(Font(20.0f,Font::bold));
	revenue_label->setText("revenue:",dontSendNotification);
	revenue_label->setColour(Label::textColourId,Colours::orange);
	revenue_label->setJustificationType(Justification::topLeft);
	revenue_label->setBounds(0,190,120,30);

	debt_label = new Label;
	addAndMakeVisible(debt_label);
	debt_label->setFont(Font(20.0f,Font::bold));
	debt_label->setText("debt:",dontSendNotification);
	debt_label->setColour(Label::textColourId,Colours::orange);
	debt_label->setJustificationType(Justification::topLeft);
	debt_label->setBounds(0,220,120,30);
}

int Casino::ConvertToInt(String &s) const
{
	int k=1;
	int result=0;
	for(int i=0;s[i]!='\0';i++)
	{
		
		result += ((s[i]-48)*k);	
		k*=10;
	}
	
	return result;
}
