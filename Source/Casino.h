/*
 *
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
				public Button::Listener,
				private Label::Listener
{
public:
    Casino();
    ~Casino();

    void paint (Graphics&) override;
    void resized() override;
	void labelTextChanged(Label *label) override
	{
		
		if(label == cap_text_label)
		{
			cap_text_label->setText(cap_text_label->getText(),dontSendNotification);
			cap_text_label->removeListener(this);
			//Value v = cap_text_label->getTextValue();

	
		}
		else if(label == coin_text_label)
		{
			coin_text_label->setText(coin_text_label->getText(),dontSendNotification);
			coin_text_label->removeListener(this);
		}
		
	}

	void buttonClicked (Button *button) override
	{
			delete check_init;
			check_init = nullptr;
			delete coin_label;
			coin_label = nullptr;
			Menu();	
	}
	void ShowDebt();
	void SetBase();
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
	Label *debt_label;    //부채
	Label *cur_coin_label, *sold_coin_label; 		
	
	unsigned short coin;
	short debt;
	short revenue;

	void Menu();	
	void AutoSave();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Casino)
};
