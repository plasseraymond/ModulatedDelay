/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ChorusEffect.h"

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
                       )
#endif
{
}

ModulatedDelayAudioProcessor::~ModulatedDelayAudioProcessor()
{
    delete effect;
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
    effect = new ModulatedDelayEffect;
    effect->prepare(sampleRate);
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

    int N = buffer.getNumSamples();
    
    if(bypass)
        return;
    
    effect->setRate(effectRate);
    effect->setDepth(effectDepth);
    effect->setDelay(effectDelay);
    effect->setWet(effectWet);

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

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
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ModulatedDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void ModulatedDelayAudioProcessor::setEffect(int selection) {
    
    // CHORUS = 1
    // FLANGER = 2
    // PHASER = 3
    
    delete effect;
    
    if(selection == 0) { // temporary work-around for first instantiation of plug-in
        effect = new ModulatedDelayEffect;
    }
    
    if(selection == 1) {
        effect = new ModulatedDelayEffect;
    }
    
    if(selection == 2) {
        effect = new ChorusEffect;
    }
    
    effect->prepare(Fs);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ModulatedDelayAudioProcessor();
}
