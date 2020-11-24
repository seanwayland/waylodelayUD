/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WaylodelayUdAudioProcessorEditor::WaylodelayUdAudioProcessorEditor (WaylodelayUdAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1800,1000);
    auto& params = processor.getParameters();
    
    
    
    addAndMakeVisible (updateSlidersButton);
    updateSlidersButton.setButtonText ("Update Slider Positions after preset load");
    updateSlidersButton.onClick = [this] { setSliders(); };
    updateSlidersButton.setBounds(1300, 50 , 200, 50);
    
    
    addAndMakeVisible (delaySettings);
    delaySettings.setBounds(1000,50, 200,50);
    delaySettings.addItem ("Waylo Chorus 1",  1);
    delaySettings.addItem ("Waylo Chorus 2",   2);
    delaySettings.addItem ("Legend Chorus 1", 3);
    delaySettings.setSelectedId (1);
    
    
    
    
    
    
    
    
    
    
    
    juce::AudioParameterFloat* delayTimeParameter = (juce::AudioParameterFloat*)params.getUnchecked(0);
    mDelayTimeSlider.setBounds(200, 100 , 200, 200);
    timeLabel.setBounds(75,100,200,200);
    timeLabel.setText("Delay Time", juce::dontSendNotification);
    addAndMakeVisible (timeLabel);
    addAndMakeVisible(timeLabel);
    
    
    
    
    mDelayTimeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayTimeSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelayTimeSlider.setRange(delayTimeParameter->range.start, delayTimeParameter->range.end);
    mDelayTimeSlider.setValue(*delayTimeParameter);
    addAndMakeVisible(mDelayTimeSlider);
    mDelayTimeSlider.onValueChange = [this, delayTimeParameter] { *delayTimeParameter = mDelayTimeSlider.getValue(); };
    mDelayTimeSlider.onDragStart = [delayTimeParameter] {delayTimeParameter->beginChangeGesture(); };
    mDelayTimeSlider.onDragEnd = [delayTimeParameter] {delayTimeParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* dryGainParameter = (juce::AudioParameterFloat*)params.getUnchecked(1);
    mDryGainSlider.setBounds(500, 0, 200, 200);
    dryGainLabel.setBounds(425,0,200,200);
    dryGainLabel.setText("Dry Gain", juce::dontSendNotification);
    addAndMakeVisible(dryGainLabel);
    TitleLabel.setBounds(800,0,200,200);
    TitleLabel.setText("WAYLOMOD 2020", juce::dontSendNotification);
    addAndMakeVisible(TitleLabel);
    mDryGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDryGainSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDryGainSlider.setRange(dryGainParameter->range.start, dryGainParameter->range.end);
    mDryGainSlider.setValue(*dryGainParameter);
    addAndMakeVisible(mDryGainSlider);
    //mDryGainSlider.onValueChange = [this, dryGainParameter] { *dryGainParameter = mDryGainSlider.getValue(); };
    mDryGainSlider.onValueChange = [this, dryGainParameter] { *dryGainParameter = mDryGainSlider.getValue(); };
    mDryGainSlider.onDragStart = [dryGainParameter] {dryGainParameter->beginChangeGesture(); };
    mDryGainSlider.onDragEnd = [dryGainParameter] {dryGainParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delayOneGainParameter = (juce::AudioParameterFloat*)params.getUnchecked(2);
    mDelayOneGainSlider.setBounds(200, 200 , 200, 200);
    delayGainLabel.setBounds(75,200,200,200);
    delayGainLabel.setText("Delay Gain", juce::dontSendNotification);
    addAndMakeVisible(delayGainLabel);
    mDelayOneGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayOneGainSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelayOneGainSlider.setRange(delayOneGainParameter->range.start, delayOneGainParameter->range.end);
    mDelayOneGainSlider.setValue(*delayOneGainParameter);
    addAndMakeVisible(mDelayOneGainSlider);
    mDelayOneGainSlider.onValueChange = [this, delayOneGainParameter] { *delayOneGainParameter = mDelayOneGainSlider.getValue(); };
    mDelayOneGainSlider.onDragStart = [delayOneGainParameter] {delayOneGainParameter->beginChangeGesture(); };
    mDelayOneGainSlider.onDragEnd = [delayOneGainParameter] {delayOneGainParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delayOneModDpethParameter = (juce::AudioParameterFloat*)params.getUnchecked(3);
    mDelayOneModDepthSlider.setBounds(200, 300 , 200, 200);
    
    depthLabel.setBounds(75,300,200,200);
    depthLabel.setText("Mod Depth", juce::dontSendNotification);
    addAndMakeVisible(depthLabel);
    
    
    mDelayOneModDepthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayOneModDepthSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelayOneModDepthSlider.setRange(delayOneModDpethParameter->range.start, delayOneModDpethParameter->range.end);
    mDelayOneModDepthSlider.setValue(*delayOneModDpethParameter);
    addAndMakeVisible(mDelayOneModDepthSlider);
    mDelayOneModDepthSlider.onValueChange = [this, delayOneModDpethParameter] { *delayOneModDpethParameter = mDelayOneModDepthSlider.getValue(); };
    mDelayOneModDepthSlider.onDragStart = [delayOneModDpethParameter] {delayOneModDpethParameter->beginChangeGesture(); };
    mDelayOneModDepthSlider.onDragEnd = [delayOneModDpethParameter] {delayOneModDpethParameter->endChangeGesture(); };
    
    
    
    juce::AudioParameterFloat* delayOneModRateParameter = (juce::AudioParameterFloat*)params.getUnchecked(4);
    mDelayOneModRateSlider.setBounds(200, 400 , 200, 200);
    RateLabel.setBounds(75,400,200,200);
    RateLabel.setText("Mod Rate", juce::dontSendNotification);
    addAndMakeVisible(RateLabel);
    mDelayOneModRateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayOneModRateSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelayOneModRateSlider.setRange(delayOneModRateParameter->range.start, delayOneModRateParameter->range.end);
    mDelayOneModRateSlider.setValue(*delayOneModRateParameter);
    addAndMakeVisible(mDelayOneModRateSlider);
    mDelayOneModRateSlider.onValueChange = [this, delayOneModRateParameter] { *delayOneModRateParameter = mDelayOneModRateSlider.getValue(); };
    mDelayOneModRateSlider.onDragStart = [delayOneModRateParameter] {delayOneModRateParameter->beginChangeGesture(); };
    mDelayOneModRateSlider.onDragEnd = [delayOneModRateParameter] {delayOneModRateParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delayOneFeedbackParameter = (juce::AudioParameterFloat*)params.getUnchecked(5);
    mDelayOneFeedbackSlider.setBounds(200, 500 , 200, 200);
    FeedbackLabel.setBounds(75,500,200,200);
    FeedbackLabel.setText("Feedback", juce::dontSendNotification);
    addAndMakeVisible(FeedbackLabel);
    mDelayOneFeedbackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayOneFeedbackSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelayOneFeedbackSlider.setRange(delayOneFeedbackParameter->range.start, delayOneFeedbackParameter->range.end);
    mDelayOneFeedbackSlider.setValue(*delayOneFeedbackParameter);
    addAndMakeVisible(mDelayOneFeedbackSlider);
    mDelayOneFeedbackSlider.onValueChange = [this, delayOneFeedbackParameter] { *delayOneFeedbackParameter = mDelayOneFeedbackSlider.getValue(); };
    mDelayOneFeedbackSlider.onDragStart = [delayOneFeedbackParameter] {delayOneFeedbackParameter->beginChangeGesture(); };
    mDelayOneFeedbackSlider.onDragEnd = [delayOneFeedbackParameter] {delayOneFeedbackParameter->endChangeGesture(); };
    
    
    
    
    juce::AudioParameterFloat* delayTwoTimeParameter = (juce::AudioParameterFloat*)params.getUnchecked(6);
    mDelayTwoTimeSlider.setBounds(400, 100 , 200, 200);
    mDelayTwoTimeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayTwoTimeSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelayTwoTimeSlider.setRange(delayTwoTimeParameter->range.start, delayTwoTimeParameter->range.end);
    mDelayTwoTimeSlider.setValue(*delayTwoTimeParameter);
    addAndMakeVisible(mDelayTwoTimeSlider);
    mDelayTwoTimeSlider.onValueChange = [this, delayTwoTimeParameter] { *delayTwoTimeParameter = mDelayTwoTimeSlider.getValue(); };
    mDelayTwoTimeSlider.onDragStart = [delayTwoTimeParameter] {delayTwoTimeParameter->beginChangeGesture(); };
    mDelayTwoTimeSlider.onDragEnd = [delayTwoTimeParameter] {delayTwoTimeParameter->endChangeGesture(); };
    
    
    
    juce::AudioParameterFloat* delayTwoGainParameter = (juce::AudioParameterFloat*)params.getUnchecked(7);
    mDelayTwoGainSlider.setBounds(400, 200 , 200, 200);
    mDelayTwoGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayTwoGainSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelayTwoGainSlider.setRange(delayTwoGainParameter->range.start, delayTwoGainParameter->range.end);
    mDelayTwoGainSlider.setValue(*delayTwoGainParameter);
    addAndMakeVisible(mDelayTwoGainSlider);
    mDelayTwoGainSlider.onValueChange = [this, delayTwoGainParameter] { *delayTwoGainParameter = mDelayTwoGainSlider.getValue(); };
    mDelayTwoGainSlider.onDragStart = [delayTwoGainParameter] {delayTwoGainParameter->beginChangeGesture(); };
    mDelayTwoGainSlider.onDragEnd = [delayTwoGainParameter] {delayTwoGainParameter->endChangeGesture(); };
    
    
    
    juce::AudioParameterFloat* delayTwoModDpethParameter = (juce::AudioParameterFloat*)params.getUnchecked(8);
    mDelayTwoModDepthSlider.setBounds(400, 300 , 200, 200);
    mDelayTwoModDepthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayTwoModDepthSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelayTwoModDepthSlider.setRange(delayTwoModDpethParameter->range.start, delayTwoModDpethParameter->range.end);
    mDelayTwoModDepthSlider.setValue(*delayTwoModDpethParameter);
    addAndMakeVisible(mDelayTwoModDepthSlider);
    mDelayTwoModDepthSlider.onValueChange = [this, delayTwoModDpethParameter] { *delayTwoModDpethParameter = mDelayTwoModDepthSlider.getValue(); };
    mDelayTwoModDepthSlider.onDragStart = [delayTwoModDpethParameter] {delayTwoModDpethParameter->beginChangeGesture(); };
    mDelayTwoModDepthSlider.onDragEnd = [delayTwoModDpethParameter] {delayTwoModDpethParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delayTwoModRateParameter = (juce::AudioParameterFloat*)params.getUnchecked(9);
    mDelayTwoModRateSlider.setBounds(400, 400 , 200, 200);
    mDelayTwoModRateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayTwoModRateSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelayTwoModRateSlider.setRange(delayTwoModRateParameter->range.start, delayTwoModRateParameter->range.end);
    mDelayTwoModRateSlider.setValue(*delayTwoModRateParameter);
    addAndMakeVisible(mDelayTwoModRateSlider);
    mDelayTwoModRateSlider.onValueChange = [this, delayTwoModRateParameter] { *delayTwoModRateParameter = mDelayTwoModRateSlider.getValue(); };
    mDelayTwoModRateSlider.onDragStart = [delayTwoModRateParameter] {delayTwoModRateParameter->beginChangeGesture(); };
    mDelayTwoModRateSlider.onDragEnd = [delayTwoModRateParameter] {delayTwoModRateParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delayTwoFeedbackParameter = (juce::AudioParameterFloat*)params.getUnchecked(10);
    mDelayTwoFeedbackSlider.setBounds(400, 500 , 200, 200);
    mDelayTwoFeedbackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayTwoFeedbackSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelayTwoFeedbackSlider.setRange(delayTwoFeedbackParameter->range.start, delayTwoFeedbackParameter->range.end);
    mDelayTwoFeedbackSlider.setValue(*delayTwoFeedbackParameter);
    addAndMakeVisible(mDelayTwoFeedbackSlider);
    mDelayTwoFeedbackSlider.onValueChange = [this, delayTwoFeedbackParameter] { *delayTwoFeedbackParameter = mDelayTwoFeedbackSlider.getValue(); };
    mDelayTwoFeedbackSlider.onDragStart = [delayTwoFeedbackParameter] {delayTwoFeedbackParameter->beginChangeGesture(); };
    mDelayTwoFeedbackSlider.onDragEnd = [delayTwoFeedbackParameter] {delayTwoFeedbackParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delayThreeTimeParameter = (juce::AudioParameterFloat*)params.getUnchecked(11);
    mDelayThreeTimeSlider.setBounds(600, 100 , 200, 200);
    mDelayThreeTimeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayThreeTimeSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelayThreeTimeSlider.setRange(delayThreeTimeParameter->range.start, delayThreeTimeParameter->range.end);
    mDelayThreeTimeSlider.setValue(*delayThreeTimeParameter);
    addAndMakeVisible(mDelayThreeTimeSlider);
    mDelayThreeTimeSlider.onValueChange = [this, delayThreeTimeParameter] { *delayThreeTimeParameter = mDelayThreeTimeSlider.getValue(); };
    mDelayThreeTimeSlider.onDragStart = [delayThreeTimeParameter] {delayThreeTimeParameter->beginChangeGesture(); };
    mDelayThreeTimeSlider.onDragEnd = [delayThreeTimeParameter] {delayThreeTimeParameter->endChangeGesture(); };
    
    
    
    juce::AudioParameterFloat* delayThreeGainParameter = (juce::AudioParameterFloat*)params.getUnchecked(12);
    mDelayThreeGainSlider.setBounds(600, 200 , 200, 200);
    mDelayThreeGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayThreeGainSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelayThreeGainSlider.setRange(delayThreeGainParameter->range.start, delayThreeGainParameter->range.end);
    mDelayThreeGainSlider.setValue(*delayThreeGainParameter);
    addAndMakeVisible(mDelayThreeGainSlider);
    mDelayThreeGainSlider.onValueChange = [this, delayThreeGainParameter] { *delayThreeGainParameter = mDelayThreeGainSlider.getValue(); };
    mDelayThreeGainSlider.onDragStart = [delayThreeGainParameter] {delayThreeGainParameter->beginChangeGesture(); };
    mDelayThreeGainSlider.onDragEnd = [delayThreeGainParameter] {delayThreeGainParameter->endChangeGesture(); };
    
    
    
    juce::AudioParameterFloat* delayThreeModDpethParameter = (juce::AudioParameterFloat*)params.getUnchecked(13);
    mDelayThreeModDepthSlider.setBounds(600, 300 , 200, 200);
    mDelayThreeModDepthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayThreeModDepthSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelayThreeModDepthSlider.setRange(delayThreeModDpethParameter->range.start, delayThreeModDpethParameter->range.end);
    mDelayThreeModDepthSlider.setValue(*delayThreeModDpethParameter);
    addAndMakeVisible(mDelayThreeModDepthSlider);
    mDelayThreeModDepthSlider.onValueChange = [this, delayThreeModDpethParameter] { *delayThreeModDpethParameter = mDelayThreeModDepthSlider.getValue(); };
    mDelayThreeModDepthSlider.onDragStart = [delayThreeModDpethParameter] {delayThreeModDpethParameter->beginChangeGesture(); };
    mDelayThreeModDepthSlider.onDragEnd = [delayThreeModDpethParameter] {delayThreeModDpethParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delayThreeModRateParameter = (juce::AudioParameterFloat*)params.getUnchecked(14);
    mDelayThreeModRateSlider.setBounds(600, 400 , 200, 200);
    mDelayThreeModRateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayThreeModRateSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelayThreeModRateSlider.setRange(delayThreeModRateParameter->range.start, delayThreeModRateParameter->range.end);
    mDelayThreeModRateSlider.setValue(*delayThreeModRateParameter);
    addAndMakeVisible(mDelayThreeModRateSlider);
    mDelayThreeModRateSlider.onValueChange = [this, delayThreeModRateParameter] { *delayThreeModRateParameter = mDelayThreeModRateSlider.getValue(); };
    mDelayThreeModRateSlider.onDragStart = [delayThreeModRateParameter] {delayThreeModRateParameter->beginChangeGesture(); };
    mDelayThreeModRateSlider.onDragEnd = [delayThreeModRateParameter] {delayThreeModRateParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delayThreeFeedbackParameter = (juce::AudioParameterFloat*)params.getUnchecked(15);
    mDelayThreeFeedbackSlider.setBounds(600, 500 , 200, 200);
    mDelayThreeFeedbackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayThreeFeedbackSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelayThreeFeedbackSlider.setRange(delayThreeFeedbackParameter->range.start, delayThreeFeedbackParameter->range.end);
    mDelayThreeFeedbackSlider.setValue(*delayThreeFeedbackParameter);
    addAndMakeVisible(mDelayThreeFeedbackSlider);
    mDelayThreeFeedbackSlider.onValueChange = [this, delayThreeFeedbackParameter] { *delayThreeFeedbackParameter = mDelayThreeFeedbackSlider.getValue(); };
    mDelayThreeFeedbackSlider.onDragStart = [delayThreeFeedbackParameter] {delayThreeFeedbackParameter->beginChangeGesture(); };
    mDelayThreeFeedbackSlider.onDragEnd = [delayThreeFeedbackParameter] {delayThreeFeedbackParameter->endChangeGesture(); };
    
    
    
    
    
    juce::AudioParameterFloat* delayFourTimeParameter = (juce::AudioParameterFloat*)params.getUnchecked(16);
    mDelayFourTimeSlider.setBounds(800, 100 , 200, 200);
    mDelayFourTimeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayFourTimeSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelayFourTimeSlider.setRange(delayFourTimeParameter->range.start, delayFourTimeParameter->range.end);
    mDelayFourTimeSlider.setValue(*delayFourTimeParameter);
    addAndMakeVisible(mDelayFourTimeSlider);
    mDelayFourTimeSlider.onValueChange = [this, delayFourTimeParameter] { *delayFourTimeParameter = mDelayFourTimeSlider.getValue(); };
    mDelayFourTimeSlider.onDragStart = [delayFourTimeParameter] {delayFourTimeParameter->beginChangeGesture(); };
    mDelayFourTimeSlider.onDragEnd = [delayFourTimeParameter] {delayFourTimeParameter->endChangeGesture(); };
    
    
    
    juce::AudioParameterFloat* delayFourGainParameter = (juce::AudioParameterFloat*)params.getUnchecked(17);
    mDelayFourGainSlider.setBounds(800, 200 , 200, 200);
    mDelayFourGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayFourGainSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelayFourGainSlider.setRange(delayFourGainParameter->range.start, delayFourGainParameter->range.end);
    mDelayFourGainSlider.setValue(*delayFourGainParameter);
    addAndMakeVisible(mDelayFourGainSlider);
    mDelayFourGainSlider.onValueChange = [this, delayFourGainParameter] { *delayFourGainParameter = mDelayFourGainSlider.getValue(); };
    mDelayFourGainSlider.onDragStart = [delayFourGainParameter] {delayFourGainParameter->beginChangeGesture(); };
    mDelayFourGainSlider.onDragEnd = [delayFourGainParameter] {delayFourGainParameter->endChangeGesture(); };
    
    
    
    juce::AudioParameterFloat* delayFourModDpethParameter = (juce::AudioParameterFloat*)params.getUnchecked(18);
    mDelayFourModDepthSlider.setBounds(800, 300 , 200, 200);
    mDelayFourModDepthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayFourModDepthSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelayFourModDepthSlider.setRange(delayFourModDpethParameter->range.start, delayFourModDpethParameter->range.end);
    mDelayFourModDepthSlider.setValue(*delayFourModDpethParameter);
    addAndMakeVisible(mDelayFourModDepthSlider);
    mDelayFourModDepthSlider.onValueChange = [this, delayFourModDpethParameter] { *delayFourModDpethParameter = mDelayFourModDepthSlider.getValue(); };
    mDelayFourModDepthSlider.onDragStart = [delayFourModDpethParameter] {delayFourModDpethParameter->beginChangeGesture(); };
    mDelayFourModDepthSlider.onDragEnd = [delayFourModDpethParameter] {delayFourModDpethParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delayFourModRateParameter = (juce::AudioParameterFloat*)params.getUnchecked(19);
    mDelayFourModRateSlider.setBounds(800, 400 , 200, 200);
    mDelayFourModRateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayFourModRateSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelayFourModRateSlider.setRange(delayFourModRateParameter->range.start, delayFourModRateParameter->range.end);
    mDelayFourModRateSlider.setValue(*delayFourModRateParameter);
    addAndMakeVisible(mDelayFourModRateSlider);
    mDelayFourModRateSlider.onValueChange = [this, delayFourModRateParameter] { *delayFourModRateParameter = mDelayFourModRateSlider.getValue(); };
    mDelayFourModRateSlider.onDragStart = [delayFourModRateParameter] {delayFourModRateParameter->beginChangeGesture(); };
    mDelayFourModRateSlider.onDragEnd = [delayFourModRateParameter] {delayFourModRateParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delayFourFeedbackParameter = (juce::AudioParameterFloat*)params.getUnchecked(20);
    mDelayFourFeedbackSlider.setBounds(800, 500 , 200, 200);
    mDelayFourFeedbackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayFourFeedbackSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelayFourFeedbackSlider.setRange(delayFourFeedbackParameter->range.start, delayFourFeedbackParameter->range.end);
    mDelayFourFeedbackSlider.setValue(*delayFourFeedbackParameter);
    addAndMakeVisible(mDelayFourFeedbackSlider);
    mDelayFourFeedbackSlider.onValueChange = [this, delayFourFeedbackParameter] { *delayFourFeedbackParameter = mDelayFourFeedbackSlider.getValue(); };
    mDelayFourFeedbackSlider.onDragStart = [delayFourFeedbackParameter] {delayFourFeedbackParameter->beginChangeGesture(); };
    mDelayFourFeedbackSlider.onDragEnd = [delayFourFeedbackParameter] {delayFourFeedbackParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delayFiveTimeParameter = (juce::AudioParameterFloat*)params.getUnchecked(21);
    mDelayFiveTimeSlider.setBounds(1000, 100 , 200, 200);
    mDelayFiveTimeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayFiveTimeSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelayFiveTimeSlider.setRange(delayFiveTimeParameter->range.start, delayFiveTimeParameter->range.end);
    mDelayFiveTimeSlider.setValue(*delayFiveTimeParameter);
    addAndMakeVisible(mDelayFiveTimeSlider);
    mDelayFiveTimeSlider.onValueChange = [this, delayFiveTimeParameter] { *delayFiveTimeParameter = mDelayFiveTimeSlider.getValue(); };
    mDelayFiveTimeSlider.onDragStart = [delayFiveTimeParameter] {delayFiveTimeParameter->beginChangeGesture(); };
    mDelayFiveTimeSlider.onDragEnd = [delayFiveTimeParameter] {delayFiveTimeParameter->endChangeGesture(); };
    
    
    
    juce::AudioParameterFloat* delayFiveGainParameter = (juce::AudioParameterFloat*)params.getUnchecked(22);
    mDelayFiveGainSlider.setBounds(1000, 200 , 200, 200);
    mDelayFiveGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayFiveGainSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelayFiveGainSlider.setRange(delayFiveGainParameter->range.start, delayFiveGainParameter->range.end);
    mDelayFiveGainSlider.setValue(*delayFiveGainParameter);
    addAndMakeVisible(mDelayFiveGainSlider);
    mDelayFiveGainSlider.onValueChange = [this, delayFiveGainParameter] { *delayFiveGainParameter = mDelayFiveGainSlider.getValue(); };
    mDelayFiveGainSlider.onDragStart = [delayFiveGainParameter] {delayFiveGainParameter->beginChangeGesture(); };
    mDelayFiveGainSlider.onDragEnd = [delayFiveGainParameter] {delayFiveGainParameter->endChangeGesture(); };
    
    
    
    juce::AudioParameterFloat* delayFiveModDpethParameter = (juce::AudioParameterFloat*)params.getUnchecked(23);
    mDelayFiveModDepthSlider.setBounds(1000, 300 , 200, 200);
    mDelayFiveModDepthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayFiveModDepthSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelayFiveModDepthSlider.setRange(delayFiveModDpethParameter->range.start, delayFiveModDpethParameter->range.end);
    mDelayFiveModDepthSlider.setValue(*delayFiveModDpethParameter);
    addAndMakeVisible(mDelayFiveModDepthSlider);
    mDelayFiveModDepthSlider.onValueChange = [this, delayFiveModDpethParameter] { *delayFiveModDpethParameter = mDelayFiveModDepthSlider.getValue(); };
    mDelayFiveModDepthSlider.onDragStart = [delayFiveModDpethParameter] {delayFiveModDpethParameter->beginChangeGesture(); };
    mDelayFiveModDepthSlider.onDragEnd = [delayFiveModDpethParameter] {delayFiveModDpethParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delayFiveModRateParameter = (juce::AudioParameterFloat*)params.getUnchecked(24);
    mDelayFiveModRateSlider.setBounds(1000, 400 , 200, 200);
    mDelayFiveModRateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayFiveModRateSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelayFiveModRateSlider.setRange(delayFiveModRateParameter->range.start, delayFiveModRateParameter->range.end);
    mDelayFiveModRateSlider.setValue(*delayFiveModRateParameter);
    addAndMakeVisible(mDelayFiveModRateSlider);
    mDelayFiveModRateSlider.onValueChange = [this, delayFiveModRateParameter] { *delayFiveModRateParameter = mDelayFiveModRateSlider.getValue(); };
    mDelayFiveModRateSlider.onDragStart = [delayFiveModRateParameter] {delayFiveModRateParameter->beginChangeGesture(); };
    mDelayFiveModRateSlider.onDragEnd = [delayFiveModRateParameter] {delayFiveModRateParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delayFiveFeedbackParameter = (juce::AudioParameterFloat*)params.getUnchecked(25);
    mDelayFiveFeedbackSlider.setBounds(1000, 500 , 200, 200);
    mDelayFiveFeedbackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayFiveFeedbackSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelayFiveFeedbackSlider.setRange(delayFiveFeedbackParameter->range.start, delayFiveFeedbackParameter->range.end);
    mDelayFiveFeedbackSlider.setValue(*delayFiveFeedbackParameter);
    addAndMakeVisible(mDelayFiveFeedbackSlider);
    mDelayFiveFeedbackSlider.onValueChange = [this, delayFiveFeedbackParameter] { *delayFiveFeedbackParameter = mDelayFiveFeedbackSlider.getValue(); };
    mDelayFiveFeedbackSlider.onDragStart = [delayFiveFeedbackParameter] {delayFiveFeedbackParameter->beginChangeGesture(); };
    mDelayFiveFeedbackSlider.onDragEnd = [delayFiveFeedbackParameter] {delayFiveFeedbackParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delaySixTimeParameter = (juce::AudioParameterFloat*)params.getUnchecked(26);
    mDelaySixTimeSlider.setBounds(1200, 100 , 200, 200);
    mDelaySixTimeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelaySixTimeSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelaySixTimeSlider.setRange(delaySixTimeParameter->range.start, delaySixTimeParameter->range.end);
    mDelaySixTimeSlider.setValue(*delaySixTimeParameter);
    addAndMakeVisible(mDelaySixTimeSlider);
    mDelaySixTimeSlider.onValueChange = [this, delaySixTimeParameter] { *delaySixTimeParameter = mDelaySixTimeSlider.getValue(); };
    mDelaySixTimeSlider.onDragStart = [delaySixTimeParameter] {delaySixTimeParameter->beginChangeGesture(); };
    mDelaySixTimeSlider.onDragEnd = [delaySixTimeParameter] {delaySixTimeParameter->endChangeGesture(); };
    
    
    
    juce::AudioParameterFloat* delaySixGainParameter = (juce::AudioParameterFloat*)params.getUnchecked(27);
    mDelaySixGainSlider.setBounds(1200, 200 , 200, 200);
    mDelaySixGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelaySixGainSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelaySixGainSlider.setRange(delaySixGainParameter->range.start, delaySixGainParameter->range.end);
    mDelaySixGainSlider.setValue(*delaySixGainParameter);
    addAndMakeVisible(mDelaySixGainSlider);
    mDelaySixGainSlider.onValueChange = [this, delaySixGainParameter] { *delaySixGainParameter = mDelaySixGainSlider.getValue(); };
    mDelaySixGainSlider.onDragStart = [delaySixGainParameter] {delaySixGainParameter->beginChangeGesture(); };
    mDelaySixGainSlider.onDragEnd = [delaySixGainParameter] {delaySixGainParameter->endChangeGesture(); };
    
    
    
    juce::AudioParameterFloat* delaySixModDpethParameter = (juce::AudioParameterFloat*)params.getUnchecked(28);
    mDelaySixModDepthSlider.setBounds(1200, 300 , 200, 200);
    mDelaySixModDepthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelaySixModDepthSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelaySixModDepthSlider.setRange(delaySixModDpethParameter->range.start, delaySixModDpethParameter->range.end);
    mDelaySixModDepthSlider.setValue(*delaySixModDpethParameter);
    addAndMakeVisible(mDelaySixModDepthSlider);
    mDelaySixModDepthSlider.onValueChange = [this, delaySixModDpethParameter] { *delaySixModDpethParameter = mDelaySixModDepthSlider.getValue(); };
    mDelaySixModDepthSlider.onDragStart = [delaySixModDpethParameter] {delaySixModDpethParameter->beginChangeGesture(); };
    mDelaySixModDepthSlider.onDragEnd = [delaySixModDpethParameter] {delaySixModDpethParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delaySixModRateParameter = (juce::AudioParameterFloat*)params.getUnchecked(29);
    mDelaySixModRateSlider.setBounds(1200, 400 , 200, 200);
    mDelaySixModRateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelaySixModRateSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelaySixModRateSlider.setRange(delaySixModRateParameter->range.start, delaySixModRateParameter->range.end);
    mDelaySixModRateSlider.setValue(*delaySixModRateParameter);
    addAndMakeVisible(mDelaySixModRateSlider);
    mDelaySixModRateSlider.onValueChange = [this, delaySixModRateParameter] { *delaySixModRateParameter = mDelaySixModRateSlider.getValue(); };
    mDelaySixModRateSlider.onDragStart = [delaySixModRateParameter] {delaySixModRateParameter->beginChangeGesture(); };
    mDelaySixModRateSlider.onDragEnd = [delaySixModRateParameter] {delaySixModRateParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delaySixFeedbackParameter = (juce::AudioParameterFloat*)params.getUnchecked(30);
    mDelaySixFeedbackSlider.setBounds(1200, 500 , 200, 200);
    mDelaySixFeedbackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelaySixFeedbackSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelaySixFeedbackSlider.setRange(delaySixFeedbackParameter->range.start, delaySixFeedbackParameter->range.end);
    mDelaySixFeedbackSlider.setValue(*delaySixFeedbackParameter);
    addAndMakeVisible(mDelaySixFeedbackSlider);
    mDelaySixFeedbackSlider.onValueChange = [this, delaySixFeedbackParameter] { *delaySixFeedbackParameter = mDelaySixFeedbackSlider.getValue(); };
    mDelaySixFeedbackSlider.onDragStart = [delaySixFeedbackParameter] {delaySixFeedbackParameter->beginChangeGesture(); };
    mDelaySixFeedbackSlider.onDragEnd = [delaySixFeedbackParameter] {delaySixFeedbackParameter->endChangeGesture(); };
    
    
    juce::AudioParameterFloat* delaySevenTimeParameter = (juce::AudioParameterFloat*)params.getUnchecked(31);
    mDelaySevenTimeSlider.setBounds(1400, 100 , 200, 200);
    mDelaySevenTimeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelaySevenTimeSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelaySevenTimeSlider.setRange(delaySevenTimeParameter->range.start, delaySevenTimeParameter->range.end);
    mDelaySevenTimeSlider.setValue(*delaySevenTimeParameter);
    addAndMakeVisible(mDelaySevenTimeSlider);
    mDelaySevenTimeSlider.onValueChange = [this, delaySevenTimeParameter] { *delaySevenTimeParameter = mDelaySevenTimeSlider.getValue(); };
    mDelaySevenTimeSlider.onDragStart = [delaySevenTimeParameter] {delaySevenTimeParameter->beginChangeGesture(); };
    mDelaySevenTimeSlider.onDragEnd = [delaySevenTimeParameter] {delaySevenTimeParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delaySevenGainParameter = (juce::AudioParameterFloat*)params.getUnchecked(32);
    mDelaySevenGainSlider.setBounds(1400, 200 , 200, 200);
    mDelaySevenGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelaySevenGainSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelaySevenGainSlider.setRange(delaySevenGainParameter->range.start, delaySevenGainParameter->range.end);
    mDelaySevenGainSlider.setValue(*delaySevenGainParameter);
    addAndMakeVisible(mDelaySevenGainSlider);
    mDelaySevenGainSlider.onValueChange = [this, delaySevenGainParameter] { *delaySevenGainParameter = mDelaySevenGainSlider.getValue(); };
    mDelaySevenGainSlider.onDragStart = [delaySevenGainParameter] {delaySevenGainParameter->beginChangeGesture(); };
    mDelaySevenGainSlider.onDragEnd = [delaySevenGainParameter] {delaySevenGainParameter->endChangeGesture(); };
    
    
    
    juce::AudioParameterFloat* delaySevenModDpethParameter = (juce::AudioParameterFloat*)params.getUnchecked(33);
    mDelaySevenModDepthSlider.setBounds(1400, 300 , 200, 200);
    mDelaySevenModDepthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelaySevenModDepthSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelaySevenModDepthSlider.setRange(delaySevenModDpethParameter->range.start, delaySevenModDpethParameter->range.end);
    mDelaySevenModDepthSlider.setValue(*delaySevenModDpethParameter);
    addAndMakeVisible(mDelaySevenModDepthSlider);
    mDelaySevenModDepthSlider.onValueChange = [this, delaySevenModDpethParameter] { *delaySevenModDpethParameter = mDelaySevenModDepthSlider.getValue(); };
    mDelaySevenModDepthSlider.onDragStart = [delaySevenModDpethParameter] {delaySevenModDpethParameter->beginChangeGesture(); };
    mDelaySevenModDepthSlider.onDragEnd = [delaySevenModDpethParameter] {delaySevenModDpethParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delaySevenModRateParameter = (juce::AudioParameterFloat*)params.getUnchecked(34);
    mDelaySevenModRateSlider.setBounds(1400, 400 , 200, 200);
    mDelaySevenModRateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelaySevenModRateSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelaySevenModRateSlider.setRange(delaySevenModRateParameter->range.start, delaySevenModRateParameter->range.end);
    mDelaySevenModRateSlider.setValue(*delaySevenModRateParameter);
    addAndMakeVisible(mDelaySevenModRateSlider);
    mDelaySevenModRateSlider.onValueChange = [this, delaySevenModRateParameter] { *delaySevenModRateParameter = mDelaySevenModRateSlider.getValue(); };
    mDelaySevenModRateSlider.onDragStart = [delaySevenModRateParameter] {delaySevenModRateParameter->beginChangeGesture(); };
    mDelaySevenModRateSlider.onDragEnd = [delaySevenModRateParameter] {delaySevenModRateParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delaySevenFeedbackParameter = (juce::AudioParameterFloat*)params.getUnchecked(35);
    mDelaySevenFeedbackSlider.setBounds(1400, 500 , 200, 200);
    mDelaySevenFeedbackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelaySevenFeedbackSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelaySevenFeedbackSlider.setRange(delaySevenFeedbackParameter->range.start, delaySevenFeedbackParameter->range.end);
    mDelaySevenFeedbackSlider.setValue(*delaySevenFeedbackParameter);
    addAndMakeVisible(mDelaySevenFeedbackSlider);
    mDelaySevenFeedbackSlider.onValueChange = [this, delaySevenFeedbackParameter] { *delaySevenFeedbackParameter = mDelaySevenFeedbackSlider.getValue(); };
    mDelaySevenFeedbackSlider.onDragStart = [delaySevenFeedbackParameter] {delaySevenFeedbackParameter->beginChangeGesture(); };
    mDelaySevenFeedbackSlider.onDragEnd = [delaySevenFeedbackParameter] {delaySevenFeedbackParameter->endChangeGesture(); };
    
    
    juce::AudioParameterFloat* delayEightTimeParameter = (juce::AudioParameterFloat*)params.getUnchecked(36);
    mDelayEightTimeSlider.setBounds(1600, 100 , 200, 200);
    mDelayEightTimeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayEightTimeSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelayEightTimeSlider.setRange(delayEightTimeParameter->range.start, delayEightTimeParameter->range.end);
    mDelayEightTimeSlider.setValue(*delayEightTimeParameter);
    addAndMakeVisible(mDelayEightTimeSlider);
    mDelayEightTimeSlider.onValueChange = [this, delayEightTimeParameter] { *delayEightTimeParameter = mDelayEightTimeSlider.getValue(); };
    mDelayEightTimeSlider.onDragStart = [delayEightTimeParameter] {delayEightTimeParameter->beginChangeGesture(); };
    mDelayEightTimeSlider.onDragEnd = [delayEightTimeParameter] {delayEightTimeParameter->endChangeGesture(); };
    
    
    
    juce::AudioParameterFloat* delayEightGainParameter = (juce::AudioParameterFloat*)params.getUnchecked(37);
    mDelayEightGainSlider.setBounds(1600, 200 , 200, 200);
    mDelayEightGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayEightGainSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelayEightGainSlider.setRange(delayEightGainParameter->range.start, delayEightGainParameter->range.end);
    mDelayEightGainSlider.setValue(*delayEightGainParameter);
    addAndMakeVisible(mDelayEightGainSlider);
    mDelayEightGainSlider.onValueChange = [this, delayEightGainParameter] { *delayEightGainParameter = mDelayEightGainSlider.getValue(); };
    mDelayEightGainSlider.onDragStart = [delayEightGainParameter] {delayEightGainParameter->beginChangeGesture(); };
    mDelayEightGainSlider.onDragEnd = [delayEightGainParameter] {delayEightGainParameter->endChangeGesture(); };
    
    
    
    juce::AudioParameterFloat* delayEightModDpethParameter = (juce::AudioParameterFloat*)params.getUnchecked(38);
    mDelayEightModDepthSlider.setBounds(1600, 300 , 200, 200);
    mDelayEightModDepthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayEightModDepthSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelayEightModDepthSlider.setRange(delayEightModDpethParameter->range.start, delayEightModDpethParameter->range.end);
    mDelayEightModDepthSlider.setValue(*delayEightModDpethParameter);
    addAndMakeVisible(mDelayEightModDepthSlider);
    mDelayEightModDepthSlider.onValueChange = [this, delayEightModDpethParameter] { *delayEightModDpethParameter = mDelayEightModDepthSlider.getValue(); };
    mDelayEightModDepthSlider.onDragStart = [delayEightModDpethParameter] {delayEightModDpethParameter->beginChangeGesture(); };
    mDelayEightModDepthSlider.onDragEnd = [delayEightModDpethParameter] {delayEightModDpethParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delayEightModRateParameter = (juce::AudioParameterFloat*)params.getUnchecked(39);
    mDelayEightModRateSlider.setBounds(1600, 400 , 200, 200);
    mDelayEightModRateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayEightModRateSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelayEightModRateSlider.setRange(delayEightModRateParameter->range.start, delayEightModRateParameter->range.end);
    mDelayEightModRateSlider.setValue(*delayEightModRateParameter);
    addAndMakeVisible(mDelayEightModRateSlider);
    mDelayEightModRateSlider.onValueChange = [this, delayEightModRateParameter] { *delayEightModRateParameter = mDelayEightModRateSlider.getValue(); };
    mDelayEightModRateSlider.onDragStart = [delayEightModRateParameter] {delayEightModRateParameter->beginChangeGesture(); };
    mDelayEightModRateSlider.onDragEnd = [delayEightModRateParameter] {delayEightModRateParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delayEightFeedbackParameter = (juce::AudioParameterFloat*)params.getUnchecked(40);
    mDelayEightFeedbackSlider.setBounds(1600, 500 , 200, 200);
    mDelayEightFeedbackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayEightFeedbackSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 50);
    mDelayEightFeedbackSlider.setRange(delayEightFeedbackParameter->range.start, delayEightFeedbackParameter->range.end);
    mDelayEightFeedbackSlider.setValue(*delayEightFeedbackParameter);
    addAndMakeVisible(mDelayEightFeedbackSlider);
    mDelayEightFeedbackSlider.onValueChange = [this, delayEightFeedbackParameter] { *delayEightFeedbackParameter = mDelayEightFeedbackSlider.getValue(); };
    mDelayEightFeedbackSlider.onDragStart = [delayEightFeedbackParameter] {delayEightFeedbackParameter->beginChangeGesture(); };
    mDelayEightFeedbackSlider.onDragEnd = [delayEightFeedbackParameter] {delayEightFeedbackParameter->endChangeGesture(); };
    
}

WaylodelayUdAudioProcessorEditor::~WaylodelayUdAudioProcessorEditor()
{
}

//==============================================================================
void WaylodelayUdAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    
}

void WaylodelayUdAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}


void WaylodelayUdAudioProcessorEditor::setSliders(){
    
    auto& params = processor.getParameters();
    
    juce::AudioParameterFloat* dryGainParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(1);
    
    mDryGainSlider.setValue(*dryGainParameter2);
    
    juce::AudioParameterFloat* delayTimeParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(0);
    mDelayTimeSlider.setValue(*delayTimeParameter2);
    
    juce::AudioParameterFloat* delayOneGainParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(2);
    mDelayOneGainSlider.setValue(*delayOneGainParameter2);
    
    juce::AudioParameterFloat* delayOneModDpethParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(3);
    mDelayOneModDepthSlider.setValue(*delayOneModDpethParameter2);
    juce::AudioParameterFloat* delayOneModRateParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(4);
    mDelayOneModDepthSlider.setValue(*delayOneModRateParameter2);
    juce::AudioParameterFloat* delayOneFeedbackParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(5);
    mDelayOneFeedbackSlider.setValue(*delayOneFeedbackParameter2);
    juce::AudioParameterFloat* delayTwoTimeParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(6);
    mDelayTwoGainSlider.setValue(*delayTwoTimeParameter2);
    juce::AudioParameterFloat* delayTwoGainParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(7);
    mDelayTwoGainSlider.setValue(*delayTwoGainParameter2);
    juce::AudioParameterFloat* delayTwoModDpethParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(8);
    mDelayTwoModDepthSlider.setValue(*delayTwoModDpethParameter2);
    juce::AudioParameterFloat* delayTwoModRateParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(9);
    mDelayTwoModRateSlider.setValue(*delayTwoModRateParameter2);
    juce::AudioParameterFloat* delayTwoFeedbackParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(10);
    mDelayTwoFeedbackSlider.setValue(*delayTwoFeedbackParameter2);
    juce::AudioParameterFloat* delayThreeTimeParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(11);
    mDelayThreeTimeSlider.setValue(*delayThreeTimeParameter2);
    juce::AudioParameterFloat* delayThreeGainParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(12);
    mDelayThreeGainSlider.setValue(*delayThreeGainParameter2);
    juce::AudioParameterFloat* delayThreeModDpethParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(13);
    mDelayThreeModDepthSlider.setValue(*delayThreeModDpethParameter2);
    juce::AudioParameterFloat* delayThreeModRateParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(14);
    mDelayThreeModRateSlider.setValue(*delayThreeModRateParameter2);
    juce::AudioParameterFloat* delayThreeFeedbackParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(15);
    mDelayThreeFeedbackSlider.setValue(*delayThreeFeedbackParameter2);
    juce::AudioParameterFloat* delayFourTimeParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(16);
    mDelayFourTimeSlider.setValue(*delayFourTimeParameter2);
    juce::AudioParameterFloat* delayFourGainParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(17);
    mDelayFourGainSlider.setValue(*delayFourGainParameter2);
    juce::AudioParameterFloat* delayFourModDpethParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(18);
    mDelayFourModDepthSlider.setValue(*delayFourModDpethParameter2);
    juce::AudioParameterFloat* delayFourModRateParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(19);
    mDelayFourModRateSlider.setValue(*delayFourModRateParameter2);
    juce::AudioParameterFloat* delayFourFeedbackParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(20);
    mDelayFourFeedbackSlider.setValue(*delayFourFeedbackParameter2);
    juce::AudioParameterFloat* delayFiveTimeParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(21);
    mDelayFiveTimeSlider.setValue(*delayFiveTimeParameter2);
    juce::AudioParameterFloat* delayFiveGainParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(22);
    mDelayFiveGainSlider.setValue(*delayFiveGainParameter2);
    juce::AudioParameterFloat* delayFiveModDpethParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(23);
    mDelayFiveModDepthSlider.setValue(*delayFiveModDpethParameter2);
    juce::AudioParameterFloat* delayFiveModRateParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(24);
    mDelayFiveModRateSlider.setValue(*delayFiveModRateParameter2);
    juce::AudioParameterFloat* delayFiveFeedbackParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(25);
    mDelayFiveFeedbackSlider.setValue(*delayFiveFeedbackParameter2);
    juce::AudioParameterFloat* delaySixTimeParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(26);
    mDelaySixTimeSlider.setValue(*delaySixTimeParameter2);
    juce::AudioParameterFloat* delaySixGainParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(27);
    mDelaySixGainSlider.setValue(*delaySixGainParameter2);
    juce::AudioParameterFloat* delaySixModDpethParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(28);
    mDelaySixModDepthSlider.setValue(*delaySixModDpethParameter2);
    juce::AudioParameterFloat* delaySixModRateParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(29);
    mDelaySixModRateSlider.setValue(*delaySixModRateParameter2);
    juce::AudioParameterFloat* delaySixFeedbackParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(30);
    mDelaySixFeedbackSlider.setValue(*delaySixFeedbackParameter2);
    juce::AudioParameterFloat* delaySevenTimeParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(31);
    mDelaySevenTimeSlider.setValue(*delaySevenTimeParameter2);
    juce::AudioParameterFloat* delaySevenGainParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(32);
    mDelaySevenGainSlider.setValue(*delaySevenGainParameter2);
    juce::AudioParameterFloat* delaySevenModDpethParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(33);
    mDelaySevenModDepthSlider.setValue(*delaySevenModDpethParameter2);
    juce::AudioParameterFloat* delaySevenModRateParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(34);
    mDelaySevenModRateSlider.setValue(*delaySevenModRateParameter2);
    juce::AudioParameterFloat* delaySevenFeedbackParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(35);
    mDelaySevenFeedbackSlider.setValue(*delaySevenFeedbackParameter2);
    juce::AudioParameterFloat* delayEightTimeParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(36);
    mDelayEightTimeSlider.setValue(*delayEightTimeParameter2);
    juce::AudioParameterFloat* delayEightGainParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(37);
    mDelayEightGainSlider.setValue(*delayEightGainParameter2);
    juce::AudioParameterFloat* delayEightModDpethParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(38);
    mDelayEightModDepthSlider.setValue(*delayEightModDpethParameter2);
    juce::AudioParameterFloat* delayEightModRateParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(39);
    mDelayEightModRateSlider.setValue(*delayEightModRateParameter2);
    juce::AudioParameterFloat* delayEightFeedbackParameter2 = (juce::AudioParameterFloat*)params.getUnchecked(40);
    mDelayEightFeedbackSlider.setValue(*delayEightFeedbackParameter2);
    
    
    
}