/*
  ==============================================================================

    Casino.cpp
    Created: 24 Mar 2018 11:20:14pm Author:  moca 
  ============================================================================== */
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
	sales_label(nullptr),
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
	sales(0),
	revenue(0),
	capital(0),
	init_check(false),
	listener_check(false)
{
	// 장부 확인
	// 없으면 만들고 있으면 불러옴
	/*
	if(AutoSave())
	{
	}
	*/

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
	if(sales_label != nullptr) delete sales_label;
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
    g.setFont (Font (40.0f,Font::bold));
    g.setColour (Colours::orange);
    g.drawText ("Unifox Festival Cog Program", getLocalBounds(), Justification::centredTop, true);
	g.setFont (Font (16.0f));
	g.setColour(Colours::pink);
	g.drawText ("This Is Programmed By M0ca(Unifox 9th)",getWidth()-300,getHeight()-30,300,30,Justification::bottomRight,true);
	if(init_check == true)
	{
		g.setColour (Colours::white);
		g.setFont(Font(16.0f,Font::bold));
		g.drawSingleLineText(static_cast<String>(capital),80,175);
		g.drawSingleLineText(static_cast<String>(coin),120,115);
		g.drawSingleLineText(static_cast<String>(revenue),90,205);
		g.drawSingleLineText(static_cast<String>(sold_coin),100,145);
		g.drawSingleLineText(static_cast<String>(sales),60,235);
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
	capital_label->setFont(Font(40.0f));
	capital_label->setText("Set Capital: ",dontSendNotification);
	capital_label->setColour(Label::textColourId,Colours::pink);
	capital_label->setJustificationType(Justification::centred);
	capital_label->attachToComponent(cap_text_label,true);

	addAndMakeVisible(cap_text_label); 
	cap_text_label->setFont(Font(20.0f));
	cap_text_label->setEditable(true);
	cap_text_label->setColour (Label::backgroundColourId,Colours::orange);
	cap_text_label->addListener(this);
	cap_text_label->setBounds(300,140,100,30);	
	
	coin_label = new Label;
	coin_text_label = new Label;
	addAndMakeVisible(coin_label);
	coin_label->setFont(Font(40.0f));
	coin_label->setText("Set Coin: ",dontSendNotification);
	coin_label->setColour(Label::textColourId,Colours::pink);
	coin_label->setJustificationType(Justification::centred);
	coin_label->attachToComponent(coin_text_label,true);

	addAndMakeVisible(coin_text_label);
	coin_text_label->setFont(Font(20.0f));
	coin_text_label->setEditable(true);
	coin_text_label->setColour (Label::backgroundColourId,Colours::orange);
	coin_text_label->addListener(this);
	coin_text_label->setBounds(300,180,100,30);	

	check_init = new TextButton("Complete Setting!");
	addAndMakeVisible(check_init);
	check_init->setToggleState(true,dontSendNotification);
	check_init->setColour(TextButton::buttonColourId,Colours::white);
	check_init->setColour(TextButton::buttonOnColourId,Colours::pink);
	check_init->setColour(TextButton::textColourOnId,Colours::black);
	check_init->setBounds(225,240,150,50);
	check_init->addListener(this);
}

void Casino::Menu()
{
	price_label = new Label;	
	addAndMakeVisible(price_label);
	price_label->setFont(Font(24.0f,Font::bold));
	price_label->setText("Buy Price : 5 coin per 1000won!\n5 coin : 1000won\n10 coin : 2000won\n15 coin : 3000won\n25 coin : 5000won\n\nSell Price : 6 coin per 1000won!\n6 coin : 1000won\n12 coin : 2000won\n18 coin : 3000won\n30 coin : 5000won",dontSendNotification);
	price_label->setColour(Label::textColourId,Colours::pink);
	price_label->setJustificationType(Justification::topRight);
	price_label->setBounds(getWidth()/3,70,getWidth()-getWidth()/3,getHeight()-70);
				
	cur_coin_label = new Label; addAndMakeVisible(cur_coin_label);
	cur_coin_label->setFont(Font(20.0f,Font::bold));
	cur_coin_label->setText("Current coin: ",dontSendNotification);
	cur_coin_label->setColour(Label::textColourId,Colours::orange);
	cur_coin_label->setJustificationType(Justification::left);
	cur_coin_label->setBounds(0,100,120,20);

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

	sales_label = new Label;
	addAndMakeVisible(sales_label);
	sales_label->setFont(Font(20.0f,Font::bold));
	sales_label->setText("sales:",dontSendNotification);
	sales_label->setColour(Label::textColourId,Colours::orange);
	sales_label->setJustificationType(Justification::left);
	sales_label->setBounds(0,220,120,20);
	

	//Buy coin!
	buy_txtbtn = new TextButton;
	addAndMakeVisible(buy_txtbtn);
	buy_txtbtn->setColour(TextButton::buttonColourId,Colours::red);
	buy_txtbtn->setButtonText("Buy Coin");
	buy_txtbtn->setBounds(0,getHeight()-30,70,30);
	buy_txtbtn->addListener(this);

	sell_txtbtn = new TextButton;
	addAndMakeVisible(sell_txtbtn);
	sell_txtbtn->setColour(TextButton::buttonColourId,Colours::green);
	sell_txtbtn->setButtonText("Sell Coin");
	sell_txtbtn->setBounds(70,getHeight()-30,70,30);
	sell_txtbtn->addListener(this);

	collect_txtbtn = new TextButton;
	addAndMakeVisible(collect_txtbtn);
	collect_txtbtn->setColour(TextButton::buttonColourId,Colours::blue);
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
	coin_menu->addItem("12 coin / 2000won",7);
	coin_menu->addItem("18 coin / 3000won",8);
	coin_menu->addItem("30 coin / 5000won",9);
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
			sales += 1000;	
			revenue += 1000;
			break;
		case 3: 
			coin -= 10;	
			sold_coin += 10;
			sales += 2000;	
			revenue += 2000;
			break;
		case 4:
			coin -= 15;
			sold_coin += 15;
			sales += 3000;
			revenue += 3000;
			break;
		case 5:
			coin -= 25;
			sold_coin += 25;
			sales += 5000;
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
		//자본 += 매출 - 수익
		//수익 += 매출 - 원가
		case 6: 
			coin += 6;	
			sold_coin -= 6;
			revenue -= 1000;
			capital += sales - revenue;
			break;
		case 7: 
			coin += 12;	
			sold_coin -= 12;
			revenue -= 2000;
			capital += sales - revenue;
			break;
		case 8:
			coin += 18;
			sold_coin -= 18;
			revenue -= 3000;
			capital += sales - revenue;
			break;
		case 9:
			coin += 30;
			sold_coin -= 30;
			revenue -= 5000;
			capital += sales - revenue;
			break;
		}
	coin_menu->setSelectedId(1);
	repaint();
}

void Casino::CollectCoin()
{
	if(sold_coin >= coin_collector->getSelectedId()-1)
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
			if(sold_coin >= 30)
				coin_menu->setItemEnabled(9,true);
			else
				coin_menu->setItemEnabled(9,false);
			if(sold_coin >= 18)
				coin_menu->setItemEnabled(8,true);
			else 
				coin_menu->setItemEnabled(8,false);
			if(sold_coin >= 12)
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

int Casino::AutoSave()
{
	/*
	ifstream in = ("cog.txt"); //파일 읽기
	if(in.open())
	{
		DBG("파일이 있다.");	
		return 1;
	}
	else
	{
		DBG("파일이 없다.");
		return 0;
	}
	*/
}

