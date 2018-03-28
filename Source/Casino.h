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
	
		}
		
		else if(label == coin_text_label)
		{
			coin_text_label->setText(coin_label->getText(),dontSendNotification);
		}
		
	}

	void buttonClicked (Button *button) override
	{
			delete check_init;
			delete capital_label;
			delete cap_text_label;
			delete coin_label;
			delete coin_text_label;
			Menu();	
	}
	void ShowDebt();
	void SetBase();
								

private:
	Label *capital_label; //자본
	Label *coin_label;    //코인
	Label *cap_text_label;
	Label *coin_text_label;
	TextButton *check_init;

	Label *menu1_label;
	Label *menu2_label;
	Label *menu3_label;
	Label revenue_label; //수익
	Label debt_label;    //부채
	
	
	void Menu();	
	void AutoSave();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Casino)
};
