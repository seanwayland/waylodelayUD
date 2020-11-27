/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WaylodelayUdAudioProcessor::WaylodelayUdAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    
    /**
     {0.5, 0.0236, 0.030, 0.0361, 0.0476, 0.3, 0.4, 0.341, 0.45, // dry gain plus delay times
     0.8,0.8, 0.8, 0.8, 0.5, 0.5, 0.5, 0.5, // delay gains
     0.1 , 0.1 , 0.1 , 0.1 , 0.1 , 0.1 ,0.1 ,0.1, // mod depths
     0.35, 0.4, 0.42 , 0.37, 0.35, 0.38, 0.47, 0.33, // mod rates
     0.0, 0.0, 0.0, 0.0, 0.45, 0.35, 0.43 , 0.34 // feedback levels
     },
     ***/

    
    addParameter(mDelayOneTimeParameter = new juce::AudioParameterFloat("delay one delaytime", "Delay One Delay Time", juce::NormalisableRange<float> (0.0f, 1.0f), 0.0236f));
    //addParameter(mDryGainParameter = new juce::AudioParameterFloat("drygain", "Dry Gain", 0.0f, 1.0f , 0.5f));
    addParameter (mDryGainParameter = new juce::AudioParameterFloat ("gain",                                      // parameter ID
                                                                     "Gain",                                      // parameter name
                                                                     juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                                     0.5f));                                      // default value
    addParameter(mDelayOneGainParameter = new juce::AudioParameterFloat("delayonegain", "Delay One Gain", juce::NormalisableRange<float> (0.0f, 1.0f), 0.5f));
    addParameter(mDelayOneModDepthParameter = new juce::AudioParameterFloat("delayonemodDepth", "Delay One Mod Depth", juce::NormalisableRange<float> (0.0f, 1.0f), 0.9f));
    addParameter(mDelayOneModRateParameter = new juce::AudioParameterFloat("delayonemodRate", "Delay One Mod Rate", juce::NormalisableRange<float> (0.0f, 1.0f), 0.35f));
    addParameter(mDelayOneFeedbackParameter = new juce::AudioParameterFloat("feedbackone", "Feedback One", juce::NormalisableRange<float> (0.0f, 0.98f), 0.0f));
    
    addParameter(mDelayTwoTimeParameter = new juce::AudioParameterFloat("delay two delaytime", "Delay Two Delay Time", juce::NormalisableRange<float> (0.0f, 1.0f), 0.030f));
    addParameter(mDelayTwoGainParameter = new juce::AudioParameterFloat("delaytowgain", "Delay Two Gain", juce::NormalisableRange<float> (0.0f, 1.0f), 0.5f));
    addParameter(mDelayTwoModDepthParameter = new juce::AudioParameterFloat("delaytwomodDepth", "Delay Two Mod Depth", juce::NormalisableRange<float> (0.0f, 1.0f), 0.1f));
    addParameter(mDelayTwoModRateParameter = new juce::AudioParameterFloat("delaytwomodDepth", "Delay Two Mod Depth", juce::NormalisableRange<float> (0.0f, 1.0f), 0.4f));
    addParameter(mDelayTwoFeedbackParameter = new juce::AudioParameterFloat("feedbacktwo", "Feedback Two", juce::NormalisableRange<float> (0.0f, 0.98f), 0.0f));
    
    addParameter(mDelayThreeTimeParameter = new juce::AudioParameterFloat("delay three delaytime", "Delay Three Delay Time", juce::NormalisableRange<float> (0.0f, 1.0f), 0.0361f));
    addParameter(mDelayThreeGainParameter = new juce::AudioParameterFloat("delaythreegain", "Delay Three Gain", juce::NormalisableRange<float> (0.0f, 1.0f), 0.5f));
    addParameter(mDelayThreeModDepthParameter = new juce::AudioParameterFloat("delaythreemodDepth", "Delay Three Mod Depth", juce::NormalisableRange<float> (0.0f, 1.0f), 0.1f));
    addParameter(mDelayThreeModRateParameter = new juce::AudioParameterFloat("delaythreemodDepth", "Delay Two Three Depth", juce::NormalisableRange<float> (0.0f, 1.0f), 0.42f));
    addParameter(mDelayThreeFeedbackParameter = new juce::AudioParameterFloat("feedbackthree", "Feedback Two", juce::NormalisableRange<float> (0.0f, 0.98f), 0.0f));
    
    addParameter(mDelayFourTimeParameter = new juce::AudioParameterFloat("delay four delaytime", "Delay Tour Delay Time", juce::NormalisableRange<float> (0.0f, 1.0f), 0.0476f));
    addParameter(mDelayFourGainParameter = new juce::AudioParameterFloat("delayfourgain", "Delay Four Gain", juce::NormalisableRange<float> (0.0f, 1.0f), 0.5f));
    addParameter(mDelayFourModDepthParameter = new juce::AudioParameterFloat("delayfourmodDepth", "Delay Four Mod Depth", juce::NormalisableRange<float> (0.0f, 1.0f), 0.1f));
    addParameter(mDelayFourModRateParameter = new juce::AudioParameterFloat("delayfourmodDepth", "Delay Four Mod Depth", juce::NormalisableRange<float> (0.0f, 1.0f), 0.37f));
    addParameter(mDelayFourFeedbackParameter = new juce::AudioParameterFloat("feedbackfour", "Feedback Four", juce::NormalisableRange<float> (0.0f, 0.98f), 0.0f));
    
    addParameter(mDelayFiveTimeParameter = new juce::AudioParameterFloat("delay five delaytime", "Delay five Delay Time",juce::NormalisableRange<float> (0.0f, 1.0f), 0.3f));
    addParameter(mDelayFiveGainParameter = new juce::AudioParameterFloat("delayfiveegain", "Delay Five Gain", juce::NormalisableRange<float> (0.0f, 1.0f), 0.5f));
    addParameter(mDelayFiveModDepthParameter = new juce::AudioParameterFloat("delayfivemodDepth", "Delay Five Mod Depth", 0.0f, 1.0f, 0.1f));
    addParameter(mDelayFiveModRateParameter = new juce::AudioParameterFloat("delayfivemodRate", "Delay Five Mod Rate", 0.0f, 1.0f, 0.35f));
    addParameter(mDelayFiveFeedbackParameter = new juce::AudioParameterFloat("feedbackfive", "Feedback Five", 0.0f, 0.98f, 0.0f));
    
    addParameter(mDelaySixTimeParameter = new juce::AudioParameterFloat("delay six delaytime", "Delay Six Delay Time", juce::NormalisableRange<float> (0.0f, 1.0f), 0.4f));
    addParameter(mDelaySixGainParameter = new juce::AudioParameterFloat("delaysixgain", "Delay Six Gain", juce::NormalisableRange<float> (0.0f, 1.0f), 0.5f));
    addParameter(mDelaySixModDepthParameter = new juce::AudioParameterFloat("delaysixmodDepth", "Delay Six Mod Depth", juce::NormalisableRange<float> (0.0f, 1.0f), 0.1f));
    addParameter(mDelaySixModRateParameter = new juce::AudioParameterFloat("delaysixmodDepth", "Delay Six Mod Depth", juce::NormalisableRange<float> (0.0f, 1.0f), 0.38f));
    addParameter(mDelaySixFeedbackParameter = new juce::AudioParameterFloat("feedbacksix", "Feedback Six", juce::NormalisableRange<float> (0.0f, 0.98f), 0.0f));
    
    addParameter(mDelaySevenTimeParameter = new juce::AudioParameterFloat("delay seven delaytime", "Delay Seven Delay Time", juce::NormalisableRange<float> (0.0f, 1.0f), 0.341f));
    addParameter(mDelaySevenGainParameter = new juce::AudioParameterFloat("delaysevengain", "Delay Seven Gain", juce::NormalisableRange<float> (0.0f, 1.0f), 0.5f));
    addParameter(mDelaySevenModDepthParameter = new juce::AudioParameterFloat("delaysevenmodDepth", "Delay Seven Mod Depth", juce::NormalisableRange<float> (0.0f, 1.0f), 0.1f));
    addParameter(mDelaySevenModRateParameter = new juce::AudioParameterFloat("delaysevenmodDepth", "Delay Seven Three Depth", juce::NormalisableRange<float> (0.0f, 1.0f), 0.47f));
    addParameter(mDelaySevenFeedbackParameter = new juce::AudioParameterFloat("feedbackseven", "Feedback Seven", juce::NormalisableRange<float> (0.0f, 0.98f), 0.0));
    
    addParameter(mDelayEightTimeParameter = new juce::AudioParameterFloat("delay eight delaytime", "Delay Eight Delay Time", juce::NormalisableRange<float> (0.0f, 1.0f), 0.45f));
    addParameter(mDelayEightGainParameter = new juce::AudioParameterFloat("delayeightgain", "Delay eight Gain", juce::NormalisableRange<float> (0.0f, 1.0f), 0.5f));
    addParameter(mDelayEightModDepthParameter = new juce::AudioParameterFloat("delayeightmodDepth", "Delay Eight Mod Depth", juce::NormalisableRange<float> (0.0f, 1.0f), 0.1f));
    addParameter(mDelayEightModRateParameter = new juce::AudioParameterFloat("delayeightmodDepth", "Delay Eight Mod Depth", juce::NormalisableRange<float> (0.0f, 1.0f), 0.33f));
    addParameter(mDelayEightFeedbackParameter = new juce::AudioParameterFloat("feedbackeight", "Feedback Eight ", juce::NormalisableRange<float> (0.0f, 0.98f), 0.0f));
    
    
    
    
    

    mCircularBufferWriteHead = 0;
    
    mCircularBufferLength = 0;
    
    mDelayTimeInSamples = 0.0;
    mDelayReadHead = 0.0;
    

    mCircularBufferWriteHeadTwo = 0;
    
    mDelayTwoTimeInSamples = 0.0;
    mDelayTwoReadHead = 0.0;
    

    mCircularBufferWriteHeadThree = 0;
    
    
    mDelayThreeTimeInSamples = 0.0;
    mDelayThreeReadHead = 0.0;
    

    mCircularBufferWriteHeadFour = 0;
    
    mDelayFourTimeInSamples = 0.0;
    mDelayFourReadHead = 0.0;
    

    mCircularBufferWriteHeadFive = 0;
    
    mDelayFiveTimeInSamples = 0.0;
    mDelayFiveReadHead = 0.0;
    

    mCircularBufferWriteHeadSix = 0;
    
    mDelaySixTimeInSamples = 0.0;
    mDelaySixReadHead = 0.0;
    

    mCircularBufferWriteHeadSeven = 0;
    
    mDelaySevenTimeInSamples = 0.0;
    mDelaySevenReadHead = 0.0;
    

    mCircularBufferWriteHeadEight = 0;
    
    mDelayEightTimeInSamples = 0.0;
    mDelayEightReadHead = 0.0;
    
    
    
    
    feedback = 0.5;
    mfeedbackLeft = 0.0;
    mDelayTimeSmoothed = 1;
    mLFOphase = 0;
    mLFOrate = 0.3f;
    
    feedbackTwo = 0.5;
    mfeedbackLeftTwo = 0.0;
    mDelayTimeSmoothedTwo = 1;
    mLFOphaseTwo = 0;
    mLFOrateTwo = 0.3f;
    
    feedbackThree = 0.5;
    mfeedbackLeftThree = 0.0;
    mDelayTimeSmoothedThree = 1;
    mLFOphaseThree = 0;
    mLFOrateThree = 0.3f;
    
    feedbackFour = 0.5;
    mfeedbackLeftFour = 0.0;
    mDelayTimeSmoothedFour = 1;
    mLFOphaseFour = 0;
    mLFOrateFour  = 0.3f;
    
    feedbackFive = 0.5;
    mfeedbackLeftFive = 0.0;
    mDelayTimeSmoothedFive = 1;
    mLFOphaseFive = 0;
    mLFOrateFive = 0.3f;
    
    feedbackSix = 0.5;
    mfeedbackLeftSix = 0.0;
    mDelayTimeSmoothedSix = 1;
    mLFOphaseSix = 0;
    mLFOrateSix = 0.3f;
    
    feedbackSeven = 0.5;
    mfeedbackLeftSeven = 0.0;
    mDelayTimeSmoothedSeven = 1;
    mLFOphaseSeven = 0;
    mLFOrateSeven  = 0.3f;
    
    feedbackEight = 0.5;
    mfeedbackLeftEight = 0.0;
    mDelayTimeSmoothedEight = 1;
    mLFOphaseEight = 0;
    mLFOrateEight  = 0.3f;
    
    
    
    
    
}

WaylodelayUdAudioProcessor::~WaylodelayUdAudioProcessor()
{
}

//==============================================================================
const juce::String WaylodelayUdAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool WaylodelayUdAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool WaylodelayUdAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool WaylodelayUdAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double WaylodelayUdAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int WaylodelayUdAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int WaylodelayUdAudioProcessor::getCurrentProgram()
{
    return 0;
}

void WaylodelayUdAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String WaylodelayUdAudioProcessor::getProgramName (int index)
{
    return {};
}

void WaylodelayUdAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

float WaylodelayUdAudioProcessor::linInterp(float sample_x, float sample_x1, float inPhase)
{
    return (1 - inPhase) * sample_x + inPhase * sample_x1;
    
}

//==============================================================================
void WaylodelayUdAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    mLFOphase = 0;
    mLFOrate = 0.3f;
    mLFOphaseTwo = 0;
    mLFOrateTwo = 0.3f;
    mLFOphaseThree = 0;
    mLFOrateThree = 0.3f;
    mLFOphaseFour = 0;
    mLFOrateFour = 0.3f;
    mLFOphaseFive = 0;
    mLFOrateFive = 0.3f;
    mLFOphaseSix = 0;
    mLFOrateSix = 0.3f;
    mLFOphaseSeven = 0;
    mLFOrateSeven = 0.3f;
    mLFOphaseEight = 0;
    mLFOrateEight = 0.3f;
    
    
    
    
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    // mCircularBufferLength = sampleRate*MAX_DELAY_TIME;
    mCircularBufferLength = 96000;
    
    
    

    
    
    
    
    mCircularBufferWriteHead = 0;
    
    mDelayTimeSmoothed = 0.5;
    mCircularBufferWriteHeadTwo = 0;
    mDelayTimeSmoothedTwo = 0.5;
    
    mCircularBufferWriteHeadThree = 0;
    mDelayTimeSmoothedThree = 0.5;
    
    mCircularBufferWriteHeadFour = 0;
    mDelayTimeSmoothedFour = 0.5;
    
    mCircularBufferWriteHeadFive = 0;
    mDelayTimeSmoothedFive = 0.5;
    
    mCircularBufferWriteHeadSix = 0;
    mDelayTimeSmoothedSix = 0.5;
    
    mCircularBufferWriteHeadSeven = 0;
    mDelayTimeSmoothedSeven = 0.5;
    
    mCircularBufferWriteHeadEight = 0;
    mDelayTimeSmoothedEight = 0.5;
    
    mDelayReadHead = 0;
    mDelayTwoReadHead = 0;
    mDelayThreeReadHead = 0;
    mDelayFourReadHead =0;
    mDelayFiveReadHead =0;
    mDelaySixReadHead =0;
    mDelaySevenReadHead =0;
    mDelayEightReadHead =0;
    
    
    
    
}

void WaylodelayUdAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool WaylodelayUdAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void WaylodelayUdAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    

    
    int sr = int(getSampleRate());
    int md = int(MAX_DELAY_TIME);
    int bufferlength = 96000;
    

    
    
    float* LeftChannel = buffer.getWritePointer(0);
    float* RightChannel = buffer.getWritePointer(1);
    
    for (int i = 0; i < buffer.getNumSamples(); ++i)
    {
        
        // generate the next LFO value
        
        float lfoOut = sin(2*M_PI * mLFOphase);
        float lfoOutTwo = sin(2*M_PI * mLFOphaseTwo);
        float lfoOutThree = sin(2*M_PI * mLFOphaseThree);
        float lfoOutFour = sin(2*M_PI * mLFOphaseFour);
        float lfoOutFive = sin(2*M_PI * mLFOphaseFive);
        float lfoOutSix = sin(2*M_PI * mLFOphaseSix);
        float lfoOutSeven = sin(2*M_PI * mLFOphaseSeven);
        float lfoOutEight = sin(2*M_PI * mLFOphaseEight);
        
        
        
        // move the LFO phase thru the sine wave
        
        mLFOphase += *mDelayOneModRateParameter / getSampleRate();
        mLFOphaseTwo += *mDelayTwoModRateParameter / getSampleRate();
        mLFOphaseThree += *mDelayThreeModRateParameter / getSampleRate();
        mLFOphaseFour += *mDelayFourModRateParameter / getSampleRate();
        mLFOphaseFive += *mDelayFiveModRateParameter / getSampleRate();
        mLFOphaseSix += *mDelaySixModRateParameter / getSampleRate();
        mLFOphaseSeven += *mDelaySevenModRateParameter / getSampleRate();
        mLFOphaseEight += *mDelayEightModRateParameter / getSampleRate();
        
        
        
        
        // LFO phase is moving between zero and one
        if ( mLFOphase > 1){
            mLFOphase -= 1;
        }
        if ( mLFOphaseTwo > 1){
            mLFOphaseTwo -= 1;
        }
        
        if ( mLFOphaseThree > 1){
            mLFOphaseThree -= 1;
        }
        
        if ( mLFOphaseFour > 1){
            mLFOphaseFour -= 1;
        }
        if ( mLFOphaseFive > 1){
            mLFOphaseFive -= 1;
        }
        if ( mLFOphaseSix > 1){
            mLFOphaseSix -= 1;
        }
        
        if ( mLFOphaseSeven > 1){
            mLFOphaseSeven -= 1;
        }
        if ( mLFOphaseEight > 1){
            mLFOphaseEight -= 1;
        }
        
        // attenuate the "depth" of the modulaton
        lfoOut *= *mDelayOneModDepthParameter;
        lfoOutTwo *= *mDelayTwoModDepthParameter;
        lfoOutThree *= *mDelayThreeModDepthParameter;
        lfoOutFour *= *mDelayFourModDepthParameter;
        lfoOutFive *= *mDelayFiveModDepthParameter;
        lfoOutSix *= *mDelaySixModDepthParameter;
        lfoOutSeven *= *mDelaySevenModDepthParameter;
        lfoOutEight *= *mDelayEightModDepthParameter;
        
        
        // convert -1 to 1 to changes in delay time of .005 min and .03 max
        float lfoOutMapped = juce::jmap(lfoOut,-1.f,1.f,0.001f, 0.1f);
        float lfoOutMappedTwo = juce::jmap(lfoOutTwo,-1.f,1.f,0.001f, 0.1f);
        float lfoOutMappedThree = juce::jmap(lfoOutThree,-1.f,1.f,0.001f, 0.1f);
        float lfoOutMappedFour = juce::jmap(lfoOutFour,-1.f,1.f,0.001f, 0.1f);
        float lfoOutMappedFive = juce::jmap(lfoOutFive,-1.f,1.f,0.001f, 0.1f);
        float lfoOutMappedSix = juce::jmap(lfoOutSix,-1.f,1.f,0.001f, 0.1f);
        float lfoOutMappedSeven = juce::jmap(lfoOutSeven,-1.f,1.f,0.001f, 0.1f);
        float lfoOutMappedEight = juce::jmap(lfoOutEight,-1.f,1.f,0.001f, 0.1f);
        
        
        
        // smoothly change the dely time
        mDelayTimeSmoothed = mDelayTimeSmoothed - 0.001*(mDelayTimeSmoothed - lfoOutMapped);
        mDelayTimeSmoothedTwo = mDelayTimeSmoothedTwo - 0.001*(mDelayTimeSmoothedTwo - lfoOutMappedTwo);
        mDelayTimeSmoothedThree = mDelayTimeSmoothedThree - 0.001*(mDelayTimeSmoothedThree - lfoOutMappedThree);
        mDelayTimeSmoothedFour = mDelayTimeSmoothedFour - 0.001*(mDelayTimeSmoothedFour - lfoOutMappedFour);
        mDelayTimeSmoothedFive = mDelayTimeSmoothedFive - 0.001*(mDelayTimeSmoothedFive - lfoOutMappedFive);
        mDelayTimeSmoothedSix = mDelayTimeSmoothedSix - 0.001*(mDelayTimeSmoothedSix - lfoOutMappedSix);
        mDelayTimeSmoothedSeven = mDelayTimeSmoothedSeven - 0.001*(mDelayTimeSmoothedSeven - lfoOutMappedSeven);
        mDelayTimeSmoothedEight = mDelayTimeSmoothedEight - 0.001*(mDelayTimeSmoothedEight - lfoOutMappedEight);
        
        
        
        // get the value of the delay time knob as an in in samples
        int dtime = static_cast<int>(*mDelayOneTimeParameter*getSampleRate());
        int dtimeTwo = static_cast<int>(*mDelayTwoTimeParameter*getSampleRate());
        int dtimeThree = static_cast<int>(*mDelayThreeTimeParameter*getSampleRate());
        int dtimeFour = static_cast<int>(*mDelayFourTimeParameter*getSampleRate());
        int dtimeFive = static_cast<int>(*mDelayFiveTimeParameter*getSampleRate());
        int dtimeSix = static_cast<int>(*mDelaySixTimeParameter*getSampleRate());
        int dtimeSeven = static_cast<int>(*mDelaySevenTimeParameter*getSampleRate());
        int dtimeEight = static_cast<int>(*mDelayEightTimeParameter*getSampleRate());
        
        
        // add the modulated delay time to the value the delay time is set to with the slider
        mDelayTimeInSamples = dtime + getSampleRate() * mDelayTimeSmoothed ;
        mDelayTwoTimeInSamples = dtimeTwo + getSampleRate() * mDelayTimeSmoothedTwo ;
        mDelayThreeTimeInSamples = dtimeThree + getSampleRate() * mDelayTimeSmoothedThree ;
        mDelayFourTimeInSamples = dtimeFour + getSampleRate() * mDelayTimeSmoothedFour ;
        mDelayFiveTimeInSamples = dtimeFive + getSampleRate() * mDelayTimeSmoothedFive ;
        mDelaySixTimeInSamples = dtimeSix + getSampleRate() * mDelayTimeSmoothedSix ;
        mDelaySevenTimeInSamples = dtimeSeven + getSampleRate() * mDelayTimeSmoothedSeven ;
        mDelayEightTimeInSamples = dtimeEight + getSampleRate() * mDelayTimeSmoothedEight ;
        
        
        
        
        // shove some of the input into the circular buffer also add some of the feedback
        mCircularBufferLeft[mCircularBufferWriteHead] = LeftChannel[i] + mfeedbackLeft;
        mCircularBufferRight[mCircularBufferWriteHead] = RightChannel[i] + mfeedbackRight;
        mCircularBufferLeftTwo[mCircularBufferWriteHeadTwo] = LeftChannel[i] + mfeedbackLeftTwo;
        mCircularBufferRightTwo[mCircularBufferWriteHeadTwo] = RightChannel[i] + mfeedbackRightTwo;
        mCircularBufferLeftThree[mCircularBufferWriteHeadThree] = LeftChannel[i] + mfeedbackLeftThree;
        mCircularBufferRightThree[mCircularBufferWriteHeadThree] = RightChannel[i] + mfeedbackRightThree;
        mCircularBufferLeftFour[mCircularBufferWriteHeadFour] = LeftChannel[i] + mfeedbackLeftFour;
        mCircularBufferRightFour[mCircularBufferWriteHeadFour] = RightChannel[i] + mfeedbackRightFour;
        mCircularBufferLeftFive[mCircularBufferWriteHeadFive] = LeftChannel[i] + mfeedbackLeftFive;
        mCircularBufferRightFive[mCircularBufferWriteHeadFive] = RightChannel[i] +mfeedbackRightFive;
        mCircularBufferLeftSix[mCircularBufferWriteHeadSix] = LeftChannel[i] + mfeedbackLeftSix;
        mCircularBufferRightSix[mCircularBufferWriteHeadSix] = RightChannel[i] + mfeedbackRightSix;
        mCircularBufferLeftSeven[mCircularBufferWriteHeadSeven] = LeftChannel[i] + mfeedbackLeftSeven;
        mCircularBufferRightSeven[mCircularBufferWriteHeadSeven] = RightChannel[i] + mfeedbackRightSeven;
        mCircularBufferLeftEight[mCircularBufferWriteHeadEight] = LeftChannel[i] + mfeedbackLeftEight;
        mCircularBufferRightEight[mCircularBufferWriteHeadEight] = RightChannel[i] + mfeedbackRightEight;
        
        
        
        // move the read head on the circular to the new delay position
        mDelayReadHead = mCircularBufferWriteHead - mDelayTimeInSamples;
        mDelayTwoReadHead = mCircularBufferWriteHeadTwo - mDelayTwoTimeInSamples;
        mDelayThreeReadHead = mCircularBufferWriteHeadThree - mDelayThreeTimeInSamples;
        mDelayFourReadHead = mCircularBufferWriteHeadFour - mDelayFourTimeInSamples;
        mDelayFiveReadHead = mCircularBufferWriteHeadFive - mDelayFiveTimeInSamples;
        mDelaySixReadHead = mCircularBufferWriteHeadSix - mDelaySixTimeInSamples;
        mDelaySevenReadHead = mCircularBufferWriteHeadSeven - mDelaySevenTimeInSamples;
        mDelayEightReadHead = mCircularBufferWriteHeadEight - mDelayEightTimeInSamples;
        
        
        // if read head is below zero wrap around
        if (mDelayReadHead < 0){
            mDelayReadHead += mCircularBufferLength;
        }
        
        if (mDelayTwoReadHead < 0){
            mDelayTwoReadHead += mCircularBufferLength;
        }
        if (mDelayThreeReadHead < 0){
            mDelayThreeReadHead += mCircularBufferLength;
        }
        if (mDelayFourReadHead < 0){
            mDelayFourReadHead += mCircularBufferLength;
        }
        
        if (mDelayFiveReadHead < 0){
            mDelayFiveReadHead += mCircularBufferLength;
        }
        
        if (mDelaySixReadHead < 0){
            mDelaySixReadHead += mCircularBufferLength;
        }
        
        if (mDelaySevenReadHead < 0){
            mDelaySevenReadHead += mCircularBufferLength;
        }
        
        if (mDelayEightReadHead < 0){
            mDelayEightReadHead += mCircularBufferLength;
        }
        
        
        // get the integer part of the read head
        int readHeadX = (int)mDelayReadHead;
        // get the part of the readHead after the decimal point
        float readHeadFloat = mDelayReadHead - readHeadX;
        // next integer sample position
        int readHeadX1 = readHeadX + 1;
        
        // get the integer part of the read head
        int readHeadXTwo = (int)mDelayTwoReadHead;
        // get the part of the readHead after the decimal point
        float readHeadFloatTwo = mDelayTwoReadHead - readHeadXTwo;
        // next integer sample position
        int readHeadX1Two = readHeadXTwo + 1;
        
        // get the integer part of the read head
        int readHeadXThree = (int)mDelayThreeReadHead;
        // get the part of the readHead after the decimal point
        float readHeadFloatThree = mDelayThreeReadHead - readHeadXThree;
        // next integer sample position
        int readHeadX1Three = readHeadXThree + 1;
        
        // get the integer part of the read head
        int readHeadXFour = (int)mDelayFourReadHead;
        // get the part of the readHead after the decimal point
        float readHeadFloatFour = mDelayFourReadHead - readHeadXFour;
        // next integer sample position
        int readHeadX1Four = readHeadXFour + 1;
        
        // get the integer part of the read head
        int readHeadXFive = (int)mDelayFiveReadHead;
        // get the part of the readHead after the decimal point
        float readHeadFloatFive = mDelayFiveReadHead - readHeadXFive;
        // next integer sample position
        int readHeadX1Five = readHeadXFive + 1;
        
        // get the integer part of the read head
        int readHeadXSix = (int)mDelaySixReadHead;
        // get the part of the readHead after the decimal point
        float readHeadFloatSix = mDelaySixReadHead - readHeadXSix;
        // next integer sample position
        int readHeadX1Six = readHeadXSix + 1;
        
        // get the integer part of the read head
        int readHeadXSeven = (int)mDelaySevenReadHead;
        // get the part of the readHead after the decimal point
        float readHeadFloatSeven = mDelaySevenReadHead - readHeadXSeven;
        // next integer sample position
        int readHeadX1Seven = readHeadXSeven + 1;
        
        // get the integer part of the read head
        int readHeadXEight = (int)mDelayEightReadHead;
        // get the part of the readHead after the decimal point
        float readHeadFloatEight = mDelayEightReadHead - readHeadXEight;
        // next integer sample position
        int readHeadX1Eight = readHeadXEight + 1;
        
        
        
        
        
        // if next sample position is outside the buffer
        if ( readHeadX1 >= mCircularBufferLength){
            readHeadX1 -= mCircularBufferLength;
        }
        
        if ( readHeadX1Two >= mCircularBufferLength){
            readHeadX1Two -= mCircularBufferLength;
        }
        
        if ( readHeadX1Three >= mCircularBufferLength){
            readHeadX1Three -= mCircularBufferLength;
        }
        
        if ( readHeadX1Four >= mCircularBufferLength){
            readHeadX1Four -= mCircularBufferLength;
        }
        
        if ( readHeadX1Five >= mCircularBufferLength){
            readHeadX1Five -= mCircularBufferLength;
        }
        
        if ( readHeadX1Six >= mCircularBufferLength){
            readHeadX1Six -= mCircularBufferLength;
        }
        
        if ( readHeadX1Seven >= mCircularBufferLength){
            readHeadX1Seven -= mCircularBufferLength;
        }
        
        if ( readHeadX1Eight >= mCircularBufferLength){
            readHeadX1Eight -= mCircularBufferLength;
        }
        
        
        
        
        // get the interpolated value of the delayed sample from the circular buffer
        float delay_sample_Left = WaylodelayUdAudioProcessor::linInterp(mCircularBufferLeft[readHeadX], mCircularBufferLeft[readHeadX1], readHeadFloat);
        float delay_sample_Right = WaylodelayUdAudioProcessor::linInterp(mCircularBufferRight[readHeadX], mCircularBufferRight[readHeadX1], readHeadFloat);
        float delay_sample_LeftTwo = WaylodelayUdAudioProcessor::linInterp(mCircularBufferLeftTwo[readHeadXTwo], mCircularBufferLeftTwo[readHeadX1Two], readHeadFloatTwo);
        float delay_sample_RightTwo = WaylodelayUdAudioProcessor::linInterp(mCircularBufferRightTwo[readHeadXTwo], mCircularBufferRightTwo[readHeadX1Two], readHeadFloatTwo);
        float delay_sample_LeftThree = WaylodelayUdAudioProcessor::linInterp(mCircularBufferLeftThree[readHeadXThree], mCircularBufferLeftThree[readHeadX1Three], readHeadFloatThree);
        float delay_sample_RightThree = WaylodelayUdAudioProcessor::linInterp(mCircularBufferRightThree[readHeadXThree], mCircularBufferRightThree[readHeadX1Three], readHeadFloatThree);
        float delay_sample_LeftFour = WaylodelayUdAudioProcessor::linInterp(mCircularBufferLeftFour[readHeadXFour], mCircularBufferLeftFour[readHeadX1Four], readHeadFloatFour);
        float delay_sample_RightFour = WaylodelayUdAudioProcessor::linInterp(mCircularBufferRightFour[readHeadXFour], mCircularBufferRightFour[readHeadX1Four], readHeadFloatFour);
        float delay_sample_LeftFive = WaylodelayUdAudioProcessor::linInterp(mCircularBufferLeftFive[readHeadXFive], mCircularBufferLeftFive[readHeadX1Five], readHeadFloatFive);
        float delay_sample_RightFive = WaylodelayUdAudioProcessor::linInterp(mCircularBufferRightFive[readHeadXFive], mCircularBufferRightFive[readHeadX1Five], readHeadFloatFive);
        float delay_sample_LeftSix = WaylodelayUdAudioProcessor::linInterp(mCircularBufferLeftSix[readHeadXSix], mCircularBufferLeftSix[readHeadX1Six], readHeadFloatSix);
        float delay_sample_RightSix = WaylodelayUdAudioProcessor::linInterp(mCircularBufferRightSix[readHeadXSix], mCircularBufferRightSix[readHeadX1Six], readHeadFloatSix);
        float delay_sample_LeftSeven = WaylodelayUdAudioProcessor::linInterp(mCircularBufferLeftSeven[readHeadXSeven], mCircularBufferLeftSeven[readHeadX1Seven], readHeadFloatSeven);
        float delay_sample_RightSeven = WaylodelayUdAudioProcessor::linInterp(mCircularBufferRightSeven[readHeadXSeven], mCircularBufferRightSeven[readHeadX1Seven], readHeadFloatSeven);
        float delay_sample_LeftEight = WaylodelayUdAudioProcessor::linInterp(mCircularBufferLeftEight[readHeadXEight], mCircularBufferLeftEight[readHeadX1Eight], readHeadFloatEight);
        float delay_sample_RightEight = WaylodelayUdAudioProcessor::linInterp(mCircularBufferRightEight[readHeadXEight], mCircularBufferRightEight[readHeadX1Eight], readHeadFloatEight);
        
        
        
        
        // store some delay for feedback
        
        mfeedbackLeft = delay_sample_Left* *mDelayOneFeedbackParameter;
        mfeedbackRight = delay_sample_Right* *mDelayOneFeedbackParameter;
        mfeedbackLeftTwo = delay_sample_LeftTwo* *mDelayTwoFeedbackParameter;
        mfeedbackRightTwo = delay_sample_RightTwo* *mDelayTwoFeedbackParameter;
        mfeedbackLeftThree = delay_sample_LeftThree* *mDelayThreeFeedbackParameter;
        mfeedbackRightThree = delay_sample_RightThree* *mDelayThreeFeedbackParameter;
        mfeedbackLeftFour = delay_sample_LeftFour* *mDelayFourFeedbackParameter;
        mfeedbackRightFour = delay_sample_RightFour* *mDelayFourFeedbackParameter;
        mfeedbackLeftFive = delay_sample_LeftFive* *mDelayFiveFeedbackParameter;
        mfeedbackRightFive = delay_sample_RightFive* *mDelayFiveFeedbackParameter;
        mfeedbackLeftSix = delay_sample_LeftSix* *mDelaySixFeedbackParameter;
        mfeedbackRightSix = delay_sample_RightSix* *mDelaySixFeedbackParameter;
        mfeedbackLeftSeven = delay_sample_LeftSeven* *mDelaySevenFeedbackParameter;
        mfeedbackRightSeven = delay_sample_RightSeven* *mDelaySevenFeedbackParameter;
        mfeedbackLeftEight = delay_sample_LeftEight* *mDelayEightFeedbackParameter;
        mfeedbackRightEight = delay_sample_RightEight* *mDelayEightFeedbackParameter;
        
        //mfeedbackLeftSeven = mfeedbackRightSeven = mfeedbackLeftEight = mfeedbackRightEight = 0;
        
        
        
        
        // add delay into live audio buffer
        
        
        
        buffer.setSample(0, i, buffer.getSample(0, i)* *mDryGainParameter +
                         delay_sample_Left* *mDelayOneGainParameter+ delay_sample_Right* *mDelayOneGainParameter
                         +delay_sample_LeftThree* *mDelayThreeGainParameter+ delay_sample_RightThree* *mDelayThreeGainParameter
                         +delay_sample_LeftFive* *mDelayFiveGainParameter+ delay_sample_RightFive* *mDelayFiveGainParameter
                         +delay_sample_LeftSeven* *mDelaySevenGainParameter+ delay_sample_RightSeven* *mDelaySevenGainParameter
                         
                         
                         
                         
                         );
        
        buffer.setSample(1, i, buffer.getSample(1, i)* *mDryGainParameter
                         + delay_sample_LeftTwo* *mDelayTwoGainParameter+ delay_sample_RightTwo* *mDelayTwoGainParameter
                         + delay_sample_LeftFour* *mDelayFourGainParameter+ delay_sample_RightFour* *mDelayFourGainParameter
                         + delay_sample_LeftSix* *mDelaySixGainParameter+ delay_sample_RightSix* *mDelaySixGainParameter
                         + delay_sample_LeftEight* *mDelayEightGainParameter+ delay_sample_RightEight* *mDelayEightGainParameter
                         
                         
                         
                         
                         
                         );
        
        
        

        
        
        // increment the buffer write head
        mCircularBufferWriteHead ++;
        mCircularBufferWriteHeadTwo ++;
        mCircularBufferWriteHeadThree ++;
        mCircularBufferWriteHeadFour ++;
        mCircularBufferWriteHeadFive ++;
        mCircularBufferWriteHeadSix ++;
        mCircularBufferWriteHeadSeven ++;
        mCircularBufferWriteHeadEight ++;
        
        
        // wrap around if needed
        if (mCircularBufferWriteHead == mCircularBufferLength){
            mCircularBufferWriteHead = 0;
        }
        if (mCircularBufferWriteHeadTwo == mCircularBufferLength){
            mCircularBufferWriteHeadTwo = 0;
        }
        if (mCircularBufferWriteHeadThree == mCircularBufferLength){
            mCircularBufferWriteHeadThree = 0;
        }
        if (mCircularBufferWriteHeadFour == mCircularBufferLength){
            mCircularBufferWriteHeadFour = 0;
        }
        if (mCircularBufferWriteHeadFive == mCircularBufferLength){
            mCircularBufferWriteHeadFive = 0;
        }
        
        if (mCircularBufferWriteHeadSix == mCircularBufferLength){
            mCircularBufferWriteHeadSix = 0;
        }
        
        if (mCircularBufferWriteHeadSeven == mCircularBufferLength){
            mCircularBufferWriteHeadSeven = 0;
        }
        if (mCircularBufferWriteHeadEight == mCircularBufferLength){
            mCircularBufferWriteHeadEight = 0;
        }
        
        
        //end main processing loop
    }
    
    
    // end process block
}

//==============================================================================
bool WaylodelayUdAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* WaylodelayUdAudioProcessor::createEditor()
{
    return new WaylodelayUdAudioProcessorEditor (*this);
}

//==============================================================================
void WaylodelayUdAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    std::unique_ptr<juce::XmlElement> xml(new juce::XmlElement ("waylodelayUD"));
    xml->setAttribute("drygain", *mDryGainParameter);
    xml->setAttribute("delayonetime", *mDelayOneTimeParameter);
    xml->setAttribute("delayonegain", *mDelayOneGainParameter);
    xml->setAttribute("delayonedepth", *mDelayOneModDepthParameter);
    xml->setAttribute("delayonerate", *mDelayOneModRateParameter);
    xml->setAttribute("delayonefeedback", *mDelayOneFeedbackParameter);
    xml->setAttribute("delaytwotime", *mDelayTwoTimeParameter);
    xml->setAttribute("delaytwogain", *mDelayTwoGainParameter);
    xml->setAttribute("delaytwodepth", *mDelayTwoModDepthParameter);
    xml->setAttribute("delaytworate", *mDelayTwoModRateParameter);
    xml->setAttribute("delaytwofeedback", *mDelayTwoFeedbackParameter);
    xml->setAttribute("delaythreetime", *mDelayThreeTimeParameter);
    xml->setAttribute("delaythreegain", *mDelayThreeGainParameter);
    xml->setAttribute("delaythreedepth", *mDelayThreeModDepthParameter);
    xml->setAttribute("delaythreerate", *mDelayThreeModRateParameter);
    xml->setAttribute("delaythreefeedback", *mDelayThreeFeedbackParameter);
    xml->setAttribute("delayfourtime", *mDelayFourTimeParameter);
    xml->setAttribute("delayfourgain", *mDelayFourGainParameter);
    xml->setAttribute("delayfourdepth", *mDelayFourModDepthParameter);
    xml->setAttribute("delayfourrate", *mDelayFourModRateParameter);
    xml->setAttribute("delayfourfeedback", *mDelayFourFeedbackParameter);
    xml->setAttribute("delayfivetime", *mDelayFiveTimeParameter);
    xml->setAttribute("delayfivegain", *mDelayFiveGainParameter);
    xml->setAttribute("delayfivedepth", *mDelayFiveModDepthParameter);
    xml->setAttribute("delayfiverate", *mDelayFiveModRateParameter);
    xml->setAttribute("delayfivefeedback", *mDelayFiveFeedbackParameter);
    xml->setAttribute("delaysixtime", *mDelaySixTimeParameter);
    xml->setAttribute("delaysixgain", *mDelaySixGainParameter);
    xml->setAttribute("delaysixdepth", *mDelaySixModDepthParameter);
    xml->setAttribute("delaysixrate", *mDelaySixModRateParameter);
    xml->setAttribute("delaysixfeedback", *mDelaySixFeedbackParameter);
    xml->setAttribute("delayseventime", *mDelaySevenTimeParameter);
    xml->setAttribute("delaysevengain", *mDelaySevenGainParameter);
    xml->setAttribute("delaysevendepth", *mDelaySevenModDepthParameter);
    xml->setAttribute("delaysevenrate", *mDelaySevenModRateParameter);
    xml->setAttribute("delaysevenfeedback", *mDelaySevenFeedbackParameter);
    xml->setAttribute("delayeighttime", *mDelayEightTimeParameter);
    xml->setAttribute("delayeightgain", *mDelayEightGainParameter);
    xml->setAttribute("delayeightdepth", *mDelayEightModDepthParameter);
    xml->setAttribute("delayeightrate", *mDelayEightModRateParameter);
    xml->setAttribute("delayeightfeedback", *mDelayEightFeedbackParameter);
    
    
    copyXmlToBinary(*xml, destData);
}

void WaylodelayUdAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<juce::XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
    if (xml.get() != nullptr && xml->hasTagName("waylodelayUD"))
    {
        
        
        
        *mDryGainParameter = xml->getDoubleAttribute("drygain");
        //this->setGainSlider(xml->getDoubleAttribute("drygain"));
        
        
        
        *mDelayOneTimeParameter = xml->getDoubleAttribute("delayonetime");
        *mDelayOneGainParameter = xml->getDoubleAttribute("delayonegain");
        *mDelayOneModDepthParameter = xml->getDoubleAttribute("delayonedepth");
        *mDelayOneModRateParameter = xml->getDoubleAttribute("delayonerate");
        *mDelayOneFeedbackParameter = xml->getDoubleAttribute("delayonefeedback");
        
        *mDelayTwoTimeParameter = xml->getDoubleAttribute("delaytwotime");
        *mDelayTwoGainParameter = xml->getDoubleAttribute("delaytwogain");
        *mDelayTwoModDepthParameter = xml->getDoubleAttribute("delaytwodepth");
        *mDelayTwoModRateParameter = xml->getDoubleAttribute("delaytworate");
        *mDelayTwoFeedbackParameter = xml->getDoubleAttribute("delayonefeedback");
        
        *mDelayThreeTimeParameter = xml->getDoubleAttribute("delaythreetime");
        *mDelayThreeGainParameter = xml->getDoubleAttribute("delaythreegain");
        *mDelayThreeModDepthParameter = xml->getDoubleAttribute("delaythreedepth");
        *mDelayThreeModRateParameter = xml->getDoubleAttribute("delaythreerate");
        *mDelayThreeFeedbackParameter = xml->getDoubleAttribute("delaythreefeedback");
        
        *mDelayFourTimeParameter = xml->getDoubleAttribute("delayfourtime");
        *mDelayFourGainParameter = xml->getDoubleAttribute("delayfourgain");
        *mDelayFourModDepthParameter = xml->getDoubleAttribute("delayfourdepth");
        *mDelayFourModRateParameter = xml->getDoubleAttribute("delayfourrate");
        *mDelayFourFeedbackParameter = xml->getDoubleAttribute("delayfourfeedback");
        
        *mDelayFiveTimeParameter = xml->getDoubleAttribute("delayfivetime");
        *mDelayFiveGainParameter = xml->getDoubleAttribute("delayfivegain");
        *mDelayFiveModDepthParameter = xml->getDoubleAttribute("delayfivedepth");
        *mDelayFiveModRateParameter = xml->getDoubleAttribute("delayfiverate");
        *mDelayFiveFeedbackParameter = xml->getDoubleAttribute("delayfivefeedback");
        
        *mDelaySixTimeParameter = xml->getDoubleAttribute("delaysixtime");
        *mDelaySixGainParameter = xml->getDoubleAttribute("delaysixgain");
        *mDelaySixModDepthParameter = xml->getDoubleAttribute("delaysixdepth");
        *mDelaySixModRateParameter = xml->getDoubleAttribute("delaysixrate");
        *mDelaySixFeedbackParameter = xml->getDoubleAttribute("delaysixfeedback");
        
        *mDelaySevenTimeParameter = xml->getDoubleAttribute("delayseventime");
        *mDelaySevenGainParameter = xml->getDoubleAttribute("delaysevengain");
        *mDelaySevenModDepthParameter = xml->getDoubleAttribute("delaysevendepth");
        *mDelaySevenModRateParameter = xml->getDoubleAttribute("delaysevenrate");
        *mDelayOneFeedbackParameter = xml->getDoubleAttribute("delaysevenfeedback");
        
        *mDelayEightTimeParameter = xml->getDoubleAttribute("delayeighttime");
        *mDelayEightGainParameter = xml->getDoubleAttribute("delayeightgain");
        *mDelayEightModDepthParameter = xml->getDoubleAttribute("delayeightdepth");
        *mDelayEightModRateParameter = xml->getDoubleAttribute("delayeightrate");
        *mDelayEightFeedbackParameter = xml->getDoubleAttribute("delayeightfeedback");
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new WaylodelayUdAudioProcessor();
}
