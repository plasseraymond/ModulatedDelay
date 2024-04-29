/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "DSP/ChorusEffect.h"
#include "DSP/FlangerEffect.h"
#include "DSP/PhaserEffect.h"

// assign string literals to all string references
const juce::StringRef ModulatedDelayAudioProcessor::CHORUSKNOB1 = "CHORUSKNOB1";
const juce::StringRef ModulatedDelayAudioProcessor::CHORUSKNOB2 = "CHORUSKNOB2";
const juce::StringRef ModulatedDelayAudioProcessor::CHORUSKNOB3 = "CHORUSKNOB3";
const juce::StringRef ModulatedDelayAudioProcessor::CHORUSKNOB4 = "CHORUSKNOB4";
const juce::StringRef ModulatedDelayAudioProcessor::FLANGERKNOB1 = "FLANGERKNOB1";
const juce::StringRef ModulatedDelayAudioProcessor::FLANGERKNOB2 = "FLANGERKNOB2";
const juce::StringRef ModulatedDelayAudioProcessor::FLANGERKNOB3 = "FLANGERKNOB3";
const juce::StringRef ModulatedDelayAudioProcessor::FLANGERKNOB4 = "FLANGERKNOB4";
const juce::StringRef ModulatedDelayAudioProcessor::PHASERKNOB1 = "PHASERKNOB1";
const juce::StringRef ModulatedDelayAudioProcessor::PHASERKNOB2 = "PHASERKNOB2";
const juce::StringRef ModulatedDelayAudioProcessor::PHASERKNOB3 = "PHASERKNOB3";
const juce::StringRef ModulatedDelayAudioProcessor::PHASERKNOB4 = "PHASERKNOB4";
const juce::StringRef ModulatedDelayAudioProcessor::BYPASSBUTTON = "BYPASSBUTTON";
const juce::StringRef ModulatedDelayAudioProcessor::COMBOBOX = "COMBOBOX";

//==============================================================================
ModulatedDelayAudioProcessor::ModulatedDelayAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ) ,
#endif
// initialize APVTS based on parameters created below
apvts(*this, nullptr, "Params", createParams()) {
    // empty block
}

ModulatedDelayAudioProcessor::~ModulatedDelayAudioProcessor()
{
    // delete the effect pointer to prevent memory leak
    delete effect;
}

juce::AudioProcessorValueTreeState::ParameterLayout ModulatedDelayAudioProcessor::createParams() {
    // use ranged audio parameters for the vector of pointers to be used by the APVTS
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    // create all the necessary parameters
    params
        .push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID
        {CHORUSKNOB1,ParameterVersionHint},"Chorus Rate",0.1f,10.f,0.5f));
    params
        .push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID
        {CHORUSKNOB2,ParameterVersionHint},"Chorus Depth",1.f,10.f,7.f));
    params
        .push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID
        {CHORUSKNOB3,ParameterVersionHint},"Chorus Delay",10.f,50.f,40.f));
    params
        .push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID
        {CHORUSKNOB4,ParameterVersionHint},"Chorus Mix",0.f,100.f,50.f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{FLANGERKNOB1,ParameterVersionHint},"Flanger Rate",0.1f,10.f,0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{FLANGERKNOB2,ParameterVersionHint},"Flanger Depth",1.f,10.f,4.f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{FLANGERKNOB3,ParameterVersionHint},"Flanger Delay",1.f,50.f,5.f));
    params
        .push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID
        {FLANGERKNOB4,ParameterVersionHint},"Flanger Mix",0.f,100.f,50.f));
    params
        .push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID
        {PHASERKNOB1,ParameterVersionHint},"Phaser Rate",0.1f,10.f,0.8f));
    params
        .push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID
        {PHASERKNOB2,ParameterVersionHint},"Phaser Depth",500.f,1500.f,1000.f));
    params
        .push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID
        {PHASERKNOB3,ParameterVersionHint},"Phaser Center Freq",1600.f,14500.f,2000.f));
    params
        .push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID
        {PHASERKNOB4,ParameterVersionHint},"Phaser Mix",0.f,100.f,50.f));
    params.push_back(std::make_unique<juce::AudioParameterBool>(juce::ParameterID{BYPASSBUTTON,ParameterVersionHint},"Bypass",false));
    params.push_back(std::make_unique<juce::AudioParameterChoice>(juce::ParameterID{COMBOBOX,ParameterVersionHint},"Selection",juce::StringArray{"Chorus","Flanger","Phaser"},0));
    
    return {params.begin(),params.end()};
}

//==============================================================================
const juce::String ModulatedDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ModulatedDelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ModulatedDelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ModulatedDelayAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ModulatedDelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ModulatedDelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ModulatedDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ModulatedDelayAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ModulatedDelayAudioProcessor::getProgramName (int index)
{
    return {};
}

void ModulatedDelayAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ModulatedDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // instantiate a new ChorusEffect object to point the effect pointer at
    effect = new ChorusEffect;
    
    // call the ChorusEffect implementation of the prepare method and pass it the host's sample rate
    effect->prepare(sampleRate);
    
    // update DSP initial values based on APVTS parameters
    effect->setRate(*apvts.getRawParameterValue(CHORUSKNOB1));
    effect->setDepth(*apvts.getRawParameterValue(CHORUSKNOB2));
    effect->setDelay(*apvts.getRawParameterValue(CHORUSKNOB3));
    effect->setWet(*apvts.getRawParameterValue(CHORUSKNOB4));

    // assign the host's sample rate to the plugin's sample rate
    Fs = sampleRate;
}

void ModulatedDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ModulatedDelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
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

void ModulatedDelayAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // get the total number of samples in the buffer
    int N = buffer.getNumSamples();
    
    // simply bypass the processing if the toggle button is engaged
    if(bypass)
        return;

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // call the base class generic process method which inherently calls the derived class implementation of processSample
        effect->process(channelData, N, channel);
    }
}

//==============================================================================
bool ModulatedDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ModulatedDelayAudioProcessor::createEditor()
{
    return new ModulatedDelayAudioProcessorEditor (*this);
}

//==============================================================================
void ModulatedDelayAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto currentState = apvts.copyState();
    
    std::unique_ptr<juce::XmlElement> xml(currentState.createXml());
    
    copyXmlToBinary(*xml, destData);
}

void ModulatedDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
    
    juce::ValueTree newTree = juce::ValueTree::fromXml(*xml);
    
    apvts.replaceState(newTree);
}

void ModulatedDelayAudioProcessor::setEffect(int selection) {
        
    // CHORUS = 1
    // FLANGER = 2
    // PHASER = 3
    
    // first delete the pointer pointing to the current effect
    delete effect;
    
    // depending on the comboBox selection, create the correct effect and update the DSP
    if(selection == 1) {
        effect = new ChorusEffect;
        effect->setRate(*apvts.getRawParameterValue(CHORUSKNOB1));
        effect->setDepth(*apvts.getRawParameterValue(CHORUSKNOB2));
        effect->setDelay(*apvts.getRawParameterValue(CHORUSKNOB3));
        effect->setWet(*apvts.getRawParameterValue(CHORUSKNOB4));
    }
    
    if(selection == 2) {
        effect = new FlangerEffect;
        effect->setRate(*apvts.getRawParameterValue(FLANGERKNOB1));
        effect->setDepth(*apvts.getRawParameterValue(FLANGERKNOB2));
        effect->setDelay(*apvts.getRawParameterValue(FLANGERKNOB3));
        effect->setWet(*apvts.getRawParameterValue(FLANGERKNOB4));
    }
    
    if(selection == 3) {
        effect = new PhaserEffect;
        effect->setRate(*apvts.getRawParameterValue(PHASERKNOB1));
        effect->setDepth(*apvts.getRawParameterValue(PHASERKNOB2));
        effect->setDelay(*apvts.getRawParameterValue(PHASERKNOB3));
        effect->setWet(*apvts.getRawParameterValue(PHASERKNOB4));
    }
    
    // call the derived class's implementation of prepare and pass it the plugin's sample rate
    effect->prepare(Fs);
}

// implementations for each update parameter method
void ModulatedDelayAudioProcessor::chorusRateSliderChanged(float value) {
    effect->setRate(value);
}

void ModulatedDelayAudioProcessor::chorusDepthSliderChanged(float value) {
    effect->setDepth(value);
}

void ModulatedDelayAudioProcessor::chorusDelaySliderChanged(float value) {
    effect->setDelay(value);
}

void ModulatedDelayAudioProcessor::chorusWetSliderChanged(float value) {
    effect->setWet(value);
}

void ModulatedDelayAudioProcessor::flangerRateSliderChanged(float value) {
    effect->setRate(value);
}

void ModulatedDelayAudioProcessor::flangerDepthSliderChanged(float value) {
    effect->setDepth(value);
}

void ModulatedDelayAudioProcessor::flangerDelaySliderChanged(float value) {
    effect->setDelay(value);
}

void ModulatedDelayAudioProcessor::flangerWetSliderChanged(float value) {
    effect->setWet(value);
}

void ModulatedDelayAudioProcessor::phaserRateSliderChanged(float value) {
    effect->setRate(value);
}

void ModulatedDelayAudioProcessor::phaserDepthSliderChanged(float value) {
    effect->setDepth(value);
}

void ModulatedDelayAudioProcessor::phaserCenterFreqSliderChanged(float value) {
    effect->setDelay(value);
}

void ModulatedDelayAudioProcessor::phaserWetSliderChanged(float value) {
    effect->setWet(value);
}

void ModulatedDelayAudioProcessor::buttonClicked(bool value) {
    this->bypass = value;
}

void ModulatedDelayAudioProcessor::comboBoxChanged(int selection) {
    this->setEffect(selection);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ModulatedDelayAudioProcessor();
}
