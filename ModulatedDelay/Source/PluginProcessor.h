/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ModulatedDelayEffect.h"

//==============================================================================
/**
*/
class ModulatedDelayAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    ModulatedDelayAudioProcessor();
    ~ModulatedDelayAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    // establish whether effect is Chorus, Flanger, or Phaser processor using comboBox
    void setEffect(int selection);
    
    // initialize effect variables to connect with GUI knobs/sliders
    float effectRate = 0.1f;
    float effectDepth = 1.f;
    float effectDelay = 10.f;
    float effectWet = 0.f;
    
    // declare bypass button
    bool bypass = false;

private:
    // create a pointer to a base class type efffect
    ModulatedDelayEffect * effect;
    double Fs = 1.0;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModulatedDelayAudioProcessor)
};
