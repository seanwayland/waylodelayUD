/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class WaylodelayUdAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    WaylodelayUdAudioProcessorEditor (WaylodelayUdAudioProcessor&);
    ~WaylodelayUdAudioProcessorEditor() override;
    
    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void setSliders();
    void getPreset();

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    juce::TextButton updateSlidersButton;
    
    juce::ComboBox delaySettings;
    
    
    
    juce::Slider mDelayTimeSlider;
    juce::Label timeLabel;
    juce::Slider mDryGainSlider;
    juce::Label dryGainLabel;
    juce::Slider mDelayOneGainSlider;
    juce::Label delayGainLabel;
    juce::Slider mDelayOneModDepthSlider;
    juce::Label depthLabel;
    juce::Slider mDelayOneModRateSlider;
    juce::Label RateLabel;
    juce::Slider mDelayOneFeedbackSlider;
    juce::Label FeedbackLabel;
    juce::Label TitleLabel;
    
    juce::Slider mDelayTwoTimeSlider;
    juce::Slider mDelayTwoGainSlider;
    juce::Slider mDelayTwoModDepthSlider;
    juce::Slider mDelayTwoModRateSlider;
    juce::Slider mDelayTwoFeedbackSlider;
    
    juce::Slider mDelayThreeTimeSlider;
    juce::Slider mDelayThreeGainSlider;
    juce::Slider mDelayThreeModDepthSlider;
    juce::Slider mDelayThreeModRateSlider;
    juce::Slider mDelayThreeFeedbackSlider;
    
    
    
    juce::Slider mDelayFourTimeSlider;
    juce::Slider mDelayFourGainSlider;
    juce::Slider mDelayFourModDepthSlider;
    juce::Slider mDelayFourModRateSlider;
    juce::Slider mDelayFourFeedbackSlider;
    
    
    
    juce::Slider mDelayFiveTimeSlider;
    juce::Slider mDelayFiveGainSlider;
    juce::Slider mDelayFiveModDepthSlider;
    juce::Slider mDelayFiveModRateSlider;
    juce::Slider mDelayFiveFeedbackSlider;
    
    
    
    juce::Slider mDelaySixTimeSlider;
    juce::Slider mDelaySixGainSlider;
    juce::Slider mDelaySixModDepthSlider;
    juce::Slider mDelaySixModRateSlider;
    juce::Slider mDelaySixFeedbackSlider;
    
    
    
    juce::Slider mDelaySevenTimeSlider;
    juce::Slider mDelaySevenGainSlider;
    juce::Slider mDelaySevenModDepthSlider;
    juce::Slider mDelaySevenModRateSlider;
    juce::Slider mDelaySevenFeedbackSlider;
    
    juce::Slider mDelayEightTimeSlider;
    juce::Slider mDelayEightGainSlider;
    juce::Slider mDelayEightModDepthSlider;
    juce::Slider mDelayEightModRateSlider;
    juce::Slider mDelayEightFeedbackSlider;
    WaylodelayUdAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaylodelayUdAudioProcessorEditor)
    
    int x[3][4] = {{0,1,2,3}, {4,5,6,7}, {8,9,10,11}};
    
    float settingsArray [26][41] = {
        
                                {   },
        
        
                                {0.5, 0.0236, 0.030, 0.0361, 0.0476, 0.3, 0.4, 0.341, 0.45, // dry gain plus delay times
                               0.8,0.8, 0.8, 0.8, 0.5, 0.5, 0.5, 0.5, // delay gains
                                0.1 , 0.1 , 0.1 , 0.1 , 0.1 , 0.1 ,0.1 ,0.1, // mod depths
                                0.35, 0.4, 0.42 , 0.37, 0.35, 0.38, 0.47, 0.33, // mod rates
                                0.0, 0.0, 0.0, 0.0, 0.45, 0.35, 0.43 , 0.34 // feedback levels
                                },
        
        
        /***
         ON IN NOR 1->1 OFF SIN 25.1 OFF OFF 0 100 3 2.5 L10 10
         2 ON IN NOR 2->2 OFF SIN 33.4 OFF OFF 0 100 4 2.5 R10 10
         3 ON IN NOR 3->3 OFF SIN 43.1 OFF OFF 0 100 3.4 2.5 R10 10
         4 ON IN NOR 4->4 OFF SIN 50 OFF OFF 0 100 4.2 2.5 L10 10
         5 ON IN NOR 5->5 OFF SIN 300 OFF OFF 4.5 100 3.5 2.5 L10 6
         6 ON IN NOR 6->6 OFF SIN 400 OFF OFF 3.5 100 3.8 2.5 R10 6
         7 ON IN NOR 7->7 OFF SIN 341 OFF OFF 4.3 100 4.7 2.5 L10 6
         8 ON IN NOR 8->8 OFF SIN 450 OFF OFF 3.4 100 3.3 2.5 R10 6
         ***/
                                { 0.65, 0.0231, 0.0334,0.0431, 0.050, 0.3, 0.4 , 0.341, 0.45,
                                    1.0, 1.0, 1.0 ,1.0, 1.0, 0.65, 0.65, 0.65,
                                    0.1 , 0.1 , 0.1 , 0.1 , 0.1 , 0.1 ,0.1 ,0.1,
                                    0.3, 0.4, 0.34, 0.42, 0.35, 0.38,0.47, 0.33,
                                    0.0, 0.0, 0.0, 0.0, 0.45, 0.35, 0.43, 0.34
                                },
        /***
        1 ON IN NOR 1->1 OFF SIN 25.1 OFF OFF 0 100 3 2.5 L10 10
        2 ON IN NOR 2->2 OFF SIN 33.4 OFF OFF 0 100 4.5 2.5 R10 10
        3 ON IN NOR 3->3 OFF SIN 95.6 OFF OFF 0 100 3.4 2.5 R7.0 7
        4 ON IN NOR 4->4 OFF SIN 120 OFF OFF 0 100 4.2 2.5 L7.0 5.7
        5 ON IN NOR 5->5 OFF SIN 300 OFF OFF 4.5 100 3.5 2.5 L10 4.5
        6 ON IN NOR 6->6 OFF SIN 400 OFF OFF 3.5 100 3.8 2.5 R10 4.5
        7 ON IN NOR 7->7 OFF SIN 341 OFF OFF 4.3 100 4.7 2.5 L10 4.5
        8 ON IN NOR 8->8 OFF SIN 450 OFF OFF 3.4 100 3.3 2.5 R10 4.5
         ***/
                                {0.65, 0.0251, 0.0334, 0.0956, 0.120, 0.3, 0.4, .341 , 0.45 ,   //first value is direct level then 8 delay times / 1000
                                1.0, 1.0,0.7,0.57,0.45,0.45,0.45,0.45, // delay gains is "level" multiplied by effect level / 10
                                0.1 , 0.1 , 0.1 , 0.1 , 0.1 ,0.1 ,0.1 , 0.1 , // depth divided by 25
                                0.3, 0.45, 0.34 , 0.42 , 0.35, 0.38, 0.47, 0.33, // speed // 10
                                0.0, 0.0 , 0.0 , 0.0 , 0.45, 0.35, 0.43, 0.34 // feedback divided by 10
                                },
                                    
        
                                {   },
                                {   },
                                {   },
                                {   },
        {   }
    };
    
    
    
    
};
