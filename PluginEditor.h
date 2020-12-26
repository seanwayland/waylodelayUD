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
class WaylodelayUdAudioProcessorEditor  : public juce::AudioProcessorEditor, private juce::Timer
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
    
    void timerCallback() override;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    //juce::TextButton updateSlidersButton;
    
    juce::ComboBox delaySettings;
    
    
    
    juce::Slider mDelayTimeSlider;
    juce::Label timeLabel;
    juce::Slider mDryGainSlider;
    juce::Label dryGainLabel;
    
    juce::Slider mWetGainSlider;
    juce::Label wetGainLabel;
    
    juce::Slider mRateSlider;
    juce::Label rateLabel;
    
    juce::Slider mDepthSlider;
    juce::Label depthLabel2;
    juce::Label depthLabel;
    
    juce::Slider mDelayOneGainSlider;
    juce::Label delayGainLabel;
    juce::Slider mDelayOneModDepthSlider;
    juce::Slider mDelayOneModRateSlider;
    juce::Label RateLabel;
    juce::Slider mDelayOneFeedbackSlider;
    juce::Label FeedbackLabel;
    juce::Label PanLabel;
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
    
    
    
    juce::Slider mDelayOnePanSlider;
    juce::Slider mDelayTwoPanSlider;
    juce::Slider mDelayThreePanSlider;
    juce::Slider mDelayFourPanSlider;
    juce::Slider mDelayFivePanSlider;
    juce::Slider mDelaySixPanSlider;
    juce::Slider mDelaySevenPanSlider;
    juce::Slider mDelayEightPanSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaylodelayUdAudioProcessorEditor)
    
    int x[3][4] = {{0,1,2,3}, {4,5,6,7}, {8,9,10,11}};
    
    float settingsArray [32][52] = {
        
                                {   },
        
        
                                {0.5, 0.0236, 0.030, 0.0361, 0.0476, 0.3, 0.4, 0.341, 0.45, // dry gain plus delay times
                               0.8,0.8, 0.8, 0.8, 0.5, 0.5, 0.5, 0.5, // delay gains
                                0.1 , 0.1 , 0.1 , 0.1 , 0.1 , 0.1 ,0.1 ,0.1, // mod depths
                                0.35, 0.4, 0.42 , 0.37, 0.35, 0.38, 0.47, 0.33, // mod rates
                                0.0, 0.0, 0.0, 0.0, 0.25, 0.2, 0.25 , 0.2, 0.5, 1.0, 1.0, // feedback levels
                                0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0 // pans
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
                                    0.0, 0.0, 0.0, 0.0, 0.25, 0.2, 0.25 , 0.2, 0.5,1.0, 1.0,
                                    0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0 // pans
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
                                0.1 , 0.1 , 0.1 , 0.1 , 0.1 , 0.1 ,0.1 ,0.1,  // depth divided by 25
                                0.3, 0.45, 0.34 , 0.42 , 0.35, 0.38, 0.47, 0.33, // speed // 10
                                0.0, 0.0 , 0.0 , 0.0 , 0.25, 0.2, 0.25 , 0.2, 0.5, 1.0, 1.0,// feedback divided by 10
                                    0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0 // pans
                                },
        
        
        
        //021
        {0.75, 0.0151,0.029,0.0411,0.037,0.3,0.4,0.355,0.463,
            0.8,0.8,0.8,0.8,0.32,0.32,0.32,0.32,
            0.1 , 0.1 , 0.1 , 0.1 , 0.1 , 0.1 ,0.1 ,0.1,
            0.38,0.43,0.5,0.56,0.35,0.38,0.47,0.33,
            0.0,0.0,0.0,0.0,0.4,0.3,0.4,0.3,0.5,1.0, 1.0,
            0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0 // pans
        },
        //022
        {0.8,0.0216,0.029,0.05,0.04,0.3,0.4,0.341,0.45,
            0.8,0.8,0.8,0.8,0.32,0.32,0.32,0.32,
            0.1 , 0.1 , 0.1 , 0.1 , 0.1 , 0.1 ,0.1 ,0.1,
            0.35,0.4,0.42,0.37,0.35,0.38,0.47,0.33,
            0.0,0.0,0.0,0.0,0.4,0.3,0.4,0.3,0.5,1.0, 1.0,
            0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0 // pans
        },
        //023
        {0.65,0.0216,0.029,0.0432,0.037,0.301,0.4,0.0,0.0,
            0.85,0.85,0.85,0.85,0.3825,0.3825,0.0,0.0,
           0.1 , 0.1 , 0.1 , 0.1 , 0.1 , 0.1 ,0.0 ,0.0,
            0.35,0.4,0.43,0.37,0.34,0.023,0.0,0.0,
            0.0,0.0,0.0,0.0,0.3,0.26,0.0,0.0,0.5,1.0, 1.0,
            0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0 // pans
            
        },
        //031
        {0.8,0.0315,0.0226,0.04,0.048,0.25,0.361,0.3,0.4,
            0.8,0.8,0.5,0.4,0.32,0.32,0.32,0.32,
            0.1 , 0.1 , 0.1 , 0.1 , 0.1 , 0.1 ,0.1 ,0.1,
            0.45,0.52,0.4,0.49,0.38,0.42,0.35,0.52,
            0.0,0.0,0.0,0.0,0.3,0.2,0.3,0.15,0.5,1.0, 1.0,
            0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0 // pans
        },
        //032
        {0.85,0.0316,0.0226,0.04,0.048,0.25,0.351,0.3,0.4,
            0.75,0.75,0.75,0.75,0.375,0.375,0.375,0.375,
            0.11,0.11,0.9,0.9,0.104,0.104,0.104,0.104,
            0.47,0.48,0.62,0.71,0.38,0.42,0.35,0.5,
            0.0,0.0,0.0,0.0,0.5,0.4, 0.5 ,0.3,0.5,1.0, 1.0,
            0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0 // pans
        },
        //033
        {0.82,0.0315,0.0226,0.04,0.048,0.25,0.341,0.3,0.4,
            0.75,0.75,0.75,0.75,0.3,0.3,0.3,0.3,
            0.2,0.2,0.2,0.2,0.14,0.114,0.12,0.12,
            0.45,0.52,0.4,0.49,0.38,0.42,0.35,0.5,
            0.0,0.0,0.0,0.0,0.3,0.2,0.3,0.15,0.5,1.0, 1.0,
            0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0 // pans
        },
        //111
        {0.6,0.0194,0.015,0.0,0.0,0.25,0.351,0.3,0.4,
            0.85,0.85,0.0,0.0,0.2975,0.2975,0.2975,0.2975,
            0.28,0.28,0.0,0.0,0.3,0.3,0.3,0.3,
            0.45,0.52,0.0,0.0,0.38,0.42,0.35,0.5,
            0.0,0.0,0.0,0.0,0.3,0.2,0.3,0.15,0.5,1.0, 1.0,
            0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0 // pans
        },
        //112
        {0.8,0.0236,0.03,0.0409,0.0482,0.0,0.0,0.0,0.0,
            0.8,0.8,0.8,0.8,0.0,0.0,0.0,0.0,
            0.2,0.2,0.22,0.22,0.0,0.0,0.0,0.0,
            0.39,0.52,0.4,0.49,0.0,0.0,0.0,0.0,
            0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.5,1.0, 1.0,
            0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0 // pans
        },
        //113
        {0.75,0.022,0.0271,0.03,0.04,0.0,0.0,0.3,0.4,
            0.75,0.75,0.75,0.75,0.0,0.0,0.45,0.45,
            0.1,0.1,0.07,0.07,0.0,0.0,0.114,0.114,
            0.47,0.58,0.68,0.72,0.0,0.0,0.35,0.558,
            0.0,0.0,0.0,0.0,0.0,0.0,0.3,0.2,0.5,1.0, 1.0,
            0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0 // pans
        },
        //121
        {0.85,0.0297,0.04,0.096,0.11,0.3,0.4,0.355,0.461,
            0.85,0.85,0.34,0.34,0.425,0.425,0.425,0.425,
            0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,0.0,0.0,0.0,0.3,0.2,0.18,0.2,0.5,1.0, 1.0,
            0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0 // pans
        },
        //122
        {0.85,0.025,0.0368,0.096,0.11,0.276,0.37,0.355,0.461,
            0.85,0.85,0.595,0.595,0.425,0.425,0.425,0.425,
            0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,0.0,0.0,0.0,0.3,0.2,0.18,0.2,0.5,1.0, 1.0,
            0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0 // pans
        },
        //123
        {0.85,0.0361,0.0454,0.092,0.112,0.3,0.4,0.355,0.455,
            0.81,0.81,0.6885,0.6885,0.324,0.324,0.324,0.324,
            0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,0.0,0.0,0.0,0.3,0.2,0.18,0.2,0.5,1.0, 1.0,
            0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0 // pans
        },
        //131
        {0.85,0.0361,0.045,0.134,0.0,0.3,0.4,0.355,0.455,
            0.85,0.85,0.425,0.0,0.34,0.34,0.34,0.34,
            0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,0.0,0.0,0.0,0.13,0.1,0.08,0.05,0.5,1.0, 1.0,
            0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0 // pans
        },
        //132
        {0.85,0.0205,0.0377,0.096,0.11,0.3,0.4,0.355,0.461,
            0.85,0.85,0.3825,0.3825,0.34,0.34,0.34,0.34,
            0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,0.0,0.0,0.0,0.3,0.2,0.18,0.2,0.5,1.0, 1.0,
            0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0 // pans
        },
        //133
        {0.85,0.0297,0.04,0.096,0.11,0.3,0.4,0.355,0.461,
            0.85,0.85,0.51,0.51,0.4675,0.4675,0.4675,0.4675,
            0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,0.0,0.0,0.0,0.3,0.2,0.18,0.2,0.5,1.0, 1.0,
            0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0 // pans
        },
        //211
        {0.85,0.0231,0.0331,0.11,0.0,0.3,0.4,0.0,0.0,
            0.85,0.85,0.6375,0.0,0.425,0.425,0.0,0.0,
            0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,0.0,0.0,0.0,0.3,0.2,0.0,0.0,0.5,1.0, 1.0,
            0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0 // pans
        },
        //212
        {0.85,0.0318,0.0421,0.095,0.0,0.0,0.0,0.333,0.445,
            0.85,0.85,0.51,0.0,0.0,0.0,0.3825,0.3825,
            0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,0.0,0.0,0.0,0.0,0.0,0.2,0.18,0.5,1.0, 1.0,
            0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0 // pans
        },
        //213
        {0.85,0.0212,0.0321,0.0,0.0,0.3,0.4,0.0,0.0,
            0.85,0.85,0.0,0.0,0.34,0.34,0.0,0.0,
            0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.5,1.0, 1.0,
            0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0 // pans
        },
        
        //221
        {0.5,0.0216,0.029,0.35,0.463,0.25,0.347,0.3,0.4,
            0.75,0.75,0.75,0.75,0.75,0.75,0.75,0.75,
            0.1 , 0.1 , 0.1 , 0.1 , 0.1 , 0.1 ,0.1 ,0.1,
            0.35,0.4,0.42,0.37,0.35,0.38,0.47,0.33,
            0.0,0.0,0.4,0.3,0.3,0.2,0.18,0.2,0.5,1.0, 1.0,
            0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0 // pans
        },
        //222
        {0.0,0.0231,0.0336,0.0433,0.0511,0.3,0.4,0.345,0.465,
            0.75,0.75,0.75,0.75,0.75,0.75,0.75,0.75,
            0.1 , 0.1 , 0.1 , 0.1 , 0.1 , 0.1 ,0.1 ,0.1,
            0.35,0.4,0.42,0.37,0.35,0.38,0.47,0.33,
            0.0,0.0,0.0,0.0,0.4,0.3,0.34,0.25,0.5,1.0, 1.0,
            0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0 // pans
        },
        //223
        {0.8,0.00525,0.0,0.00548,0.0,0.25,0.341,0.4,0.4,
            0.07,0.0,0.1,0.0,0.37,0.37,0.37,0.37,
            0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,0.0,0.0,0.0,0.4,0.35,0.4,0.35,0.5,1.0, 1.0,
            0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0 // pans
        },
        //231
        {0.85,0.0,0.0,0.0,0.0,0.321,0.429,0.36,0.0,
            0.0,0.0,0.0,0.0,0.4675,0.4675,0.425,0.0,
            0.0,0.0,0.0,0.0,0.046,0.046,0.046,0.0,
            0.0,0.0,0.0,0.0,0.37,0.41,0.46,0.0,
            0.0,0.0,0.0,0.0,0.24,0.2,0.25,0.0,0.5,1.0, 1.0,
            0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0 // pans
        },
        //232
        {0.85,0.0,0.0,0.0,0.0,0.3,0.4,0.355,0.461,
            0.0,0.0,0.0,0.0,0.4675,0.4675,0.4675,0.4675,
            0.0,0.0,0.0,0.0,0.08,0.07,0.08,0.08,
            0.0,0.0,0.0,0.0,0.45,0.54,0.39,0.34,
            0.0,0.0,0.0,0.0,0.45,0.25,0.2,0.18,0.5,1.0, 1.0,
            0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0 // pans
        },
        //233
        {0.85,0.0,0.0,0.0,0.0,0.25,0.33,0.3,0.401,
            0.0,0.0,0.0,0.0,0.425,0.425,0.425,0.425,
            0.0,0.0,0.0,0.0,0.08,0.08,0.08,0.08,
            0.0,0.0,0.0,0.0,0.35,0.41,0.31,0.45,
            0.0,0.0,0.0,0.0,0.3,0.2,0.19,0.15,0.5,1.0, 1.0,
            0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0 // pans
        },
        // WAYLOCHORUS
        {0.29 ,0.0236,0.03,0.036,0.028,0.00,0.00,0.00,0.00,
            0.9,0.9,0.9,0.9,0.0,0.0,0.0,0.0,
            0.9,0.9,0.9,0.9,0.4,0.4,0.4,0.4,
            0.65,0.57,0.48,0.44,0.0,0.0,0.0,0.0,
            0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.5,1.0, 1.0,
            0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0 // pans
        },
        // WAYLOLEAD
        {0.5 ,0.0236,0.03,0.036,0.0476,0.3,0.4,0.341,0.45,
            0.8,0.5,0.8,0.8,0.15,0.15,0.15,0.15,
            0.3,0.3,0.3,0.3,0.1,0.1,0.1,0.1,
            0.35,0.4,0.42,0.37,0.35,0.38,0.47,0.47,
            0.0,0.0,0.0,0.0,0.1,0.09,0.08,0.11,0.5,1.0, 1.0,
            0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0 // pans
        },
                                {   },
                                {   }
        
    };
    
    
    
    
};
