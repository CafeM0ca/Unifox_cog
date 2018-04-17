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
class Casino  : public Component ,
				private Button::Listener,
				private Label::Listener
{
public:
    Casino();
    ~Casino();

    void paint (Graphics&) override;
    void resized() override;
	void labelTextChanged(Label *label) override;
	void buttonClicked (Button *button) override;
private:
	//SetBase
	Label *capital_label; //자본
	Label *coin_label;    //코인
	Label *cap_text_label;
	Label *coin_text_label;
	TextButton *check_init; 
	//Menu
	Label *price_label;
	Label *revenue_label; //수익
	Label *sales_label;    //부채
	Label *cur_coin_label;
	Label *sold_coin_label; 		
	ComboBox *coin_menu;
	ComboBox *coin_collector;
	//BuyCoin
	TextButton *buy_txtbtn;
	TextButton *sell_txtbtn;
	TextButton *collect_txtbtn;	
	String coin_string; //레이블에서 입력받은값 Int로 바꾸기위해
	String cap_string; //레이블에서 입력받은값 Int로 바꾸기위해
	int coin;
	int sold_coin;
	int sales;
	int revenue;
	int capital;
	bool init_check;
	bool listener_check;
	void Menu();	
	void SetBase();
	void BuyCoin();
	void SellCoin();
	void CollectCoin();
	void CheckStatus();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Casino)
};
