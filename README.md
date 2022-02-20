# Table of contents
* [General info](#general-info)
* [Data structure](#data-structure)
* [Built With](#built-with)
* [Save parameters](#save-parameters)
* [Prepare to play](#prepare-to-play)
* [License](#license)

# About The Project

## General info

<p class="text-justify">
The method used to design the algorithm solving the given problem is a heuristic algorithm
called Simulated Annealing, which consists of searching consecutive problem spaces in order to find
the best solution. In the case of the combinatorial problem, it will search successive permutations close to the
to the currently minimal one. In contrast to the previously implemented solutions, the end condition is not
finding the optimal solution but reaching the temperature set by the user.
</p>

## Data structure

To achieve a delayed effect I used the circular buffer structure which size depends on from the parameters set by the user.

![Product Name Screen Shot](https://github.com/jarekkopaczewski/TwinEcho/blob/6ff12e2a9b27c65e19132080ee0411574d6aaddc/CircularBuffer.jpg)

## Built With

* [C++](https://isocpp.org/)

## Save parameters

```cpp
void DelayAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = treeState.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void DelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(treeState.state.getType()))
            treeState.replaceState(juce::ValueTree::fromXml(*xmlState));
}
```

## Prepare to play

```cpp
void DelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    lastSampleRate = sampleRate;

    mCirclarBufferLenght = MAX_DELAY_TIME * sampleRate;

    if (mCircularBufferLeft == nullptr)
    {
        mCircularBufferLeft = new float[mCirclarBufferLenght];
    }

    juce::zeromem(mCircularBufferLeft, mCirclarBufferLenght * sizeof(float));

    if (mCircularBufferRight == nullptr)
    {
        mCircularBufferRight = new float[mCirclarBufferLenght];
    }

    juce::zeromem(mCircularBufferRight, mCirclarBufferLenght * sizeof(float));

    mCircularBufferWriterHead = 0;
    mCircularBufferWriterHeadLeft = 0;

    mDelaySmoothed = *treeState.getRawParameterValue(TIME_R_ID);
    mDelaySmoothedLeft = *treeState.getRawParameterValue(TIME_L_ID);
}
```

## License

Distributed under the MIT License.

<p align="right">(<a href="#top">back to top</a>)</p>
