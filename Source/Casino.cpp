/*
  ==============================================================================

    Casino.cpp
    Created: 24 Mar 2018 11:20:14pm Author:  moca

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Casino.h"

//==============================================================================
Casino::Casino() 
	:
	//SetBase
	capital_label(nullptr),
	coin_label(nullptr),
	cap_text_label(nullptr),
	coin_text_label(nullptr),
	check_init(nullptr),
	//Menu
	price_label(nullptr),
	revenue_label(nullptr),
	debt_label(nullptr),
	cur_coin_label(nullptr),
	sold_coin_label(nullptr),
	coin_menu(nullptr),
	coin_collector(nullptr),
	//BuyCoin
	buy_txtbtn(nullptr),
	sell_txtbtn(nullptr),
	collect_txtbtn(nullptr),
	coin(0),
	sold_coin(0),
	debt(0),
	revenue(0),
	capital(0),
	init_check(false),
	listener_check(false)
{
	// 장부 확인
	// 없으면 만들고 있으면 불러옴
	SetBase();

}

Casino::~Casino()
{
	if(listener_check == false)
	{
		cap_text_label->removeListener(this);
		coin_text_label->removeListener(this);
		check_init->removeListener(this);
	}
	else
	{
		buy_txtbtn->removeListener(this);
		sell_txtbtn->removeListener(this);
		collect_txtbtn->removeListener(this);
	}
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

	if(buy_txtbtn != nullptr) delete buy_txtbtn;
	if(sell_txtbtn != nullptr) delete sell_txtbtn;
	if(collect_txtbtn != nullptr) delete collect_txtbtn;
	if(coin_menu != nullptr) delete coin_menu;
	if(coin_collector != nullptr) delete coin_collector;
}

void Casino::paint (Graphics& g)
{
    g.setFont (Font (76.0f));
    g.setColour (Colours::orange);
    g.drawText ("Unifox", getLocalBounds(), Justification::centredTop, true);
	if(init_check == true)
	{
		g.setColour (Colours::white);
		g.setFont(Font(16.0f,Font::bold));
		g.drawSingleLineText(static_cast<String>(coin),120,115);
		g.drawSingleLineText(static_cast<String>(capital),80,175);
		g.drawSingleLineText(static_cast<String>(revenue),90,205);
		g.drawSingleLineText(static_cast<String>(sold_coin),100,145);
		g.drawSingleLineText(static_cast<String>(debt),60,235);
		CheckStatus();
	}
}

void Casino::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
	//capital_label.setBounds(0,150,70,200);
	//cap_text_label.setBounds(70,150,100,170);	
	//coin_label.setBounds(0,200,70,250);

}

void Casino::labelTextChanged(Label *label)
{
	if(label == cap_text_label)
	{
		cap_string = cap_text_label->getText();
		cap_text_label->setText(cap_text_label->getText(),dontSendNotification);
		cap_text_label->removeListener(this);
		capital = cap_string.getIntValue();

	}
	else if(label == coin_text_label)
	{
		coin_string = coin_text_label->getText();
		coin_text_label->setText(coin_text_label->getText(),dontSendNotification);
		coin_text_label->removeListener(this);
		coin = coin_string.getIntValue();
	}

}

void Casino::buttonClicked(Button *button)
{
	if(button == check_init )
	{
		delete check_init;
		check_init = nullptr;
		delete coin_label;
		coin_label = nullptr;
		delete coin_text_label;
		coin_text_label = nullptr;
		delete capital_label;
		capital_label = nullptr;
		delete cap_text_label;
		cap_text_label = nullptr;
		init_check = true;
		listener_check = true;
		Menu();	
	}	
	else if(button == buy_txtbtn) BuyCoin();
	else if(button == sell_txtbtn) SellCoin();
	else if(button == collect_txtbtn) CollectCoin();
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
				
	cur_coin_label = new Label; addAndMakeVisible(cur_coin_label);
	cur_coin_label->setFont(Font(20.0f,Font::bold));
	cur_coin_label->setText("Current coin: ",dontSendNotification);
	cur_coin_label->setColour(Label::textColourId,Colours::orange);
	cur_coin_label->setJustificationType(Justification::left);
	cur_coin_label->setBounds(0,100,120,20);
		
//	coin_text_label->setFont(Font(20.0f,Font::bold));
//	coin_text_label->setColour(Label::textColourId,Colours::white);
//	coin_text_label->setJustificationType(Justification::centredRight);
//	coin_text_label->setBounds(120,100,30,30);

	sold_coin_label = new Label;
	addAndMakeVisible(sold_coin_label);
	sold_coin_label->setFont(Font(20.0f,Font::bold));
	sold_coin_label->setText("Sold coin:",dontSendNotification);
	sold_coin_label->setColour(Label::textColourId,Colours::orange);
	sold_coin_label->setJustificationType(Justification::left);
	sold_coin_label->setBounds(0,130,120,20);
	
		
	
	capital_label = new Label;
	addAndMakeVisible(capital_label);
	capital_label->setFont(Font(20.0f,Font::bold));
	capital_label->setText("capital:",dontSendNotification);
	capital_label->setColour(Label::textColourId,Colours::orange);
	capital_label->setJustificationType(Justification::left);
	capital_label->setBounds(0,160,120,20);
	

	revenue_label = new Label;
	addAndMakeVisible(revenue_label);
	revenue_label->setFont(Font(20.0f,Font::bold));
	revenue_label->setText("revenue:",dontSendNotification);
	revenue_label->setColour(Label::textColourId,Colours::orange);
	revenue_label->setJustificationType(Justification::left);
	revenue_label->setBounds(0,190,120,20);

	debt_label = new Label;
	addAndMakeVisible(debt_label);
	debt_label->setFont(Font(20.0f,Font::bold));
	debt_label->setText("debt:",dontSendNotification);
	debt_label->setColour(Label::textColourId,Colours::orange);
	debt_label->setJustificationType(Justification::left);
	debt_label->setBounds(0,220,120,20);
	

	//Buy coin!
	buy_txtbtn = new TextButton;
	addAndMakeVisible(buy_txtbtn);
	//setColour(TextButton::buttonColourId,Colours::orange);
	buy_txtbtn->setButtonText("Buy Coin");
	buy_txtbtn->setBounds(0,getHeight()-30,70,30);
	buy_txtbtn->addListener(this);

	sell_txtbtn = new TextButton;
	addAndMakeVisible(sell_txtbtn);
	//setColour(TextButton::buttonColourId,Colours::orange);
	sell_txtbtn->setButtonText("Sell Coin");
	sell_txtbtn->setBounds(70,getHeight()-30,70,30);
	sell_txtbtn->addListener(this);

	collect_txtbtn = new TextButton;
	addAndMakeVisible(collect_txtbtn);
	collect_txtbtn->setButtonText("Collect Coin");
	collect_txtbtn->setBounds(140,getHeight()-30,70,30);
	collect_txtbtn->addListener(this);



	coin_menu = new ComboBox;
	addAndMakeVisible(coin_menu);
	coin_menu->setBounds(0,250,170,20);
	coin_menu->addItem("Buy/Sell coin",1);
	coin_menu->addSectionHeading("Buy");
	coin_menu->addItem("5 coin / 1000won",2);
	coin_menu->addItem("10 coin / 2000won",3);
	coin_menu->addItem("15 coin / 3000won",4);
	coin_menu->addItem("25 coin / 5000won",5);
	coin_menu->addSectionHeading("Sell");
	coin_menu->addItem("6 coin / 1000won",6);
	coin_menu->addItem("11 coin / 2000won",7);
	coin_menu->addItem("17 coin / 3000won",8);
	coin_menu->addItem("29 coin / 5000won",9);
	coin_menu->setSelectedId(1);

	coin_collector = new ComboBox("Leftover coin");
	addAndMakeVisible(coin_collector);
	coin_collector->setBounds(170,250,170,20);
	coin_collector->addSectionHeading("How Many Collect?");
	coin_collector->addItem("Leftover coin",1);
	coin_collector->addItem("1 coin",2);
	coin_collector->addItem("2 coin",3);
	coin_collector->addItem("3 coin",4);
	coin_collector->addItem("4 coin",5);
	coin_collector->addItem("5 coin",6);
	coin_collector->setSelectedId(1);

}

void Casino::BuyCoin()
{
	//already filtered out coins
	switch(coin_menu->getSelectedId()) // buy 2~5
	{
		case 2: 
			coin -= 5;	
			sold_coin += 5;
			revenue += 1000;	
			break;
		case 3: 
			coin -= 10;	
			sold_coin += 10;
			revenue += 2000;	
			break;
		case 4:
			coin -= 15;
			sold_coin += 15;
			revenue += 3000;
			break;
		case 5:
			coin -= 25;
			sold_coin += 25;
			revenue += 5000;
			break;
	}
	coin_menu->setSelectedId(1);
	repaint();
}

void Casino::SellCoin()
{
	//already filtered out coins
	switch(coin_menu->getSelectedId()) // sell 6~9 
	{
		case 6: 
			coin += 6;	
			sold_coin -= 6;
			revenue -= 1000;	
			break;
		case 7: 
			coin += 11;	
			sold_coin -= 11;
			revenue -= 2000;	
			break;
		case 8:
			coin += 17;
			sold_coin -= 17;
			revenue -= 3000;
			break;
		case 9:
			coin += 29;
			sold_coin -= 29;
			revenue -= 5000;
			break;
		}
	coin_menu->setSelectedId(1);
	repaint();
}

void Casino::CollectCoin()
{
	switch(coin_collector->getSelectedId())
	{
		case 2:
			coin += 1;
			sold_coin -= 1;
			break;
		case 3:
			coin += 2;
			sold_coin -= 2;
			break;
		case 4:
			coin += 3;
			sold_coin -= 3;	
			break;
		case 5:
			coin += 4;
			sold_coin -= 4;
			break;
		case 6:
			coin += 5;
			sold_coin -= 5;
			break;
	}
	coin_collector->setSelectedId(1);
	repaint();
}
void Casino::CheckStatus()
{
	//at least coin over 5
	if(coin_menu != nullptr)
	{
		if(coin >= 25)
		{
			coin_menu->setItemEnabled(2,true);
			coin_menu->setItemEnabled(3,true);
			coin_menu->setItemEnabled(4,true);
			coin_menu->setItemEnabled(5,true);
		}
		else
		{
			if(coin < 5)
			{
				coin_menu->setItemEnabled(2,false);
				coin_menu->setItemEnabled(3,false);
				coin_menu->setItemEnabled(4,false);
				coin_menu->setItemEnabled(5,false);
			}
			else if(coin < 10)
			{
				coin_menu->setItemEnabled(3,false);
				coin_menu->setItemEnabled(4,false);
				coin_menu->setItemEnabled(5,false);
			}
			else if(coin < 15)
			{
				coin_menu->setItemEnabled(4,false);
				coin_menu->setItemEnabled(5,false);
			}
			else if(coin < 25)
			{
				coin_menu->setItemEnabled(5,false);
			}
		}
		if(sold_coin <= 0)
		{
			coin_menu->setItemEnabled(6,false);
			coin_menu->setItemEnabled(7,false);
			coin_menu->setItemEnabled(8,false);
			coin_menu->setItemEnabled(9,false);
		}
		else
		{
			if(sold_coin >= 29)
				coin_menu->setItemEnabled(9,true);
			else
				coin_menu->setItemEnabled(9,false);
			if(sold_coin >= 17)
				coin_menu->setItemEnabled(8,true);
			else 
				coin_menu->setItemEnabled(8,false);
			if(sold_coin >= 11)
				coin_menu->setItemEnabled(7,true);
			else 
				coin_menu->setItemEnabled(7,false);
			if(sold_coin >= 6)
				coin_menu->setItemEnabled(6,true);
			else 
				coin_menu->setItemEnabled(6,false);
		}
	}
}
