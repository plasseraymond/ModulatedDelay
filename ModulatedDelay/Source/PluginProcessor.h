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
    
    juce::AudioProcessorValueTreeState apvts;
    
    // declare bypass button
    bool bypass = false;
    
    static const juce::StringRef CHORUSKNOB1;
    static const juce::StringRef CHORUSKNOB2;
    static const juce::StringRef CHORUSKNOB3;
    static const juce::StringRef CHORUSKNOB4;
    static const juce::StringRef FLANGERKNOB1;
    static const juce::StringRef FLANGERKNOB2;
    static const juce::StringRef FLANGERKNOB3;
    static const juce::StringRef FLANGERKNOB4;
    static const juce::StringRef PHASERKNOB1;
    static const juce::StringRef PHASERKNOB2;
    static const juce::StringRef PHASERKNOB3;
    static const juce::StringRef PHASERKNOB4;
    static const juce::StringRef BYPASSBUTTON;
    
    // establish whether effect is Chorus, Flanger, or Phaser processor using comboBox
    void setEffect(int selection);
    
    void chorusRateSliderChanged(float value);
    void chorusDepthSliderChanged(float value);
    void chorusDelaySliderChanged(float value);
    void chorusWetSliderChanged(float value);
    void flangerRateSliderChanged(float value);
    void flangerDepthSliderChanged(float value);
    void flangerDelaySliderChanged(float value);
    void flangerWetSliderChanged(float value);
    void phaserRateSliderChanged(float value);
    void phaserDepthSliderChanged(float value);
    void phaserCenterFreqSliderChanged(float value);
    void phaserWetSliderChanged(float value);
    void buttonClicked(bool value);
    
private:
    int ParameterVersionHint = 1;
    
    // create a pointer to a base class type efffect
    ModulatedDelayEffect * effect;
    double Fs = 1.0;
    
    juce::AudioProcessorValueTreeState::ParameterLayout createParams();
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModulatedDelayAudioProcessor)
};
