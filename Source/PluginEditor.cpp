/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
SimplePluginAudioProcessorEditor::SimplePluginAudioProcessorEditor (SimplePluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    for (int i = 0; i < processor.numParams(); ++i) // Add GUI slider/label for
    {                                               // every parameter in params

        const AudioParameterFloat& param = processor.getParam(i);

        Slider* newSlider = new Slider (param.name);
        jassert (newSlider);
        sliders.add (newSlider);

        newSlider->setSliderStyle (Slider::LinearHorizontal);
        newSlider->setTextBoxStyle (Slider::TextBoxRight,false,unit*8,unit*2);
        newSlider->setColour (Slider::thumbColourId, Colours::silver);
        newSlider->setColour (Slider::textBoxTextColourId, Colour (0xff404040));
        newSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0xff909090));
        newSlider->setDoubleClickReturnValue (true, param.get()); // param.get() is
                                                                  // now default value

        newSlider->setRange (param.range.start,     // set min/max values
                             param.range.end,
                             param.range.interval);

        addAndMakeVisible (newSlider);

        newSlider->addListener (this);

        const String name = param.name;
        Label* aLabel = new Label (name, name);
        jassert (aLabel);
        labels.add (aLabel);

        aLabel->setJustificationType (Justification::centredLeft);
        aLabel->setEditable (false, false, false);
        aLabel->setColour (Label::textColourId, Colour (0xff404040));
        aLabel->setColour (TextEditor::textColourId, Colours::black);
        aLabel->setColour (TextEditor::backgroundColourId,Colour (0x00000000));

        addAndMakeVisible (aLabel);
    }
    jassert (sliders.size() == labels.size());

    updateSlidersFromProcParams();      // set slider values and ranges

    const int numRows = sliders.size(); // set width and height of editor
    const int height = margin           // (must be set before xtor finished)
                     + numRows * 2 * heightComponent
                     + margin / 2;
    setSize (width, height);

    startTimerHz (30);                  // Start our timerCallBack()
}

SimplePluginAudioProcessorEditor::~SimplePluginAudioProcessorEditor()
{
}

//==============================================================================
void SimplePluginAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::grey);
}

void SimplePluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    for (int i = 0; i < sliders.size(); ++i)    // Position our GUI elements
    {                                           // according to our relative
        jassert (sliders[i]);                   // layout enum
        sliders[i]->setBounds(margin,
                              margin + i * 2 * heightComponent + 16,
                              widthComponent,
                              heightComponent);
    }

    for (int i = 0; i < labels.size(); ++i)
    {
        jassert (labels[i]);
        labels[i]->setBounds (margin,
                              margin + i * 2 * heightComponent,
                              widthComponent,
                              heightComponent);
    }
}

//==============================================================================
void SimplePluginAudioProcessorEditor::sliderValueChanged (Slider* movedSlider)
{
    jassert (movedSlider);
    setProcParamFromSlider (*movedSlider);
}

//==============================================================================
void SimplePluginAudioProcessorEditor::timerCallback()
{
    updateSlidersFromProcParams();
}

//==============================================================================
void SimplePluginAudioProcessorEditor::setProcParamFromSlider (const Slider& slider) const
{
    int i = sliders.indexOf (&slider);
    const float sliderVal = static_cast<float> (slider.getValue()); // getValue()
                                                                    // is double
    processor.setParam (i, sliderVal);
}

//==============================================================================
void SimplePluginAudioProcessorEditor::updateSlidersFromProcParams()
{
    for (int i = 0; i < processor.numParams(); ++i)
    {
        const auto& p = processor.getParam(i);

        jassert (i < sliders.size());
        jassert (sliders[i]);

                            // (sliders have double values, parameters have floats)
        sliders[i]->setValue (static_cast<double> (p.get()), dontSendNotification);
    }
}
