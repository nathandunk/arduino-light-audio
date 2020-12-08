#include <BTrack.h>
#include <iostream>
#include "AudioFile.h"

int main(){
    AudioFile<double> audioFile;
    audioFile.load ("D:/Downloads/RogerThat - Blondie (Master V1).wav");
    std::cout << "sample rate: " << audioFile.getSampleRate() << std::endl;

    std::cout << "num channels: " << audioFile.getNumChannels() << std::endl;

    std::cout << "num seconds: " << audioFile.getLengthInSeconds() << std::endl;
    
    std::cout <<"num samples per channel: " << audioFile.getNumSamplesPerChannel() << std::endl;

    int numSamples = audioFile.getNumSamplesPerChannel();

    int channel = 0;

    for (int i = 0; i < numSamples; i++)
    {
        double currentSample = audioFile.samples[channel][i];
        // std::cout << currentSample << std::endl;
    }

    int frame_size = 1024;
    int half_frame_size = frame_size/2;

    BTrack b; 
    std::vector<double> frame(frame_size,0.0);
    std::vector<double> half_frame;
    half_frame.reserve(half_frame_size);
    double last_time(0.0);
    int frame_num = 1;

    for (size_t i = 0; i < numSamples; i++){
        half_frame[i%half_frame_size] = audioFile.samples[channel][i];
        if (i%half_frame_size == 0 ){
            frame_num++;
            std::copy(frame.begin()+half_frame_size,frame.end(),frame.begin());
            std::copy(half_frame.begin(),half_frame.end(),frame.begin()+half_frame_size);
            if (i > frame_size){
                b.processAudioFrame(&frame[0]);
                
                if(b.beatDueInCurrentFrame()){
                    double curr_time = (double)i/(double)audioFile.getSampleRate();
                    std::cout << "time: " << curr_time << " s" << std::endl;
                    std::cout << "diff: " << curr_time - last_time << " s\n";
                    std::cout << "frame num: " << frame_num << std::endl;
                    std::cout << "beat due!\n\n";
                    last_time = curr_time;
                }
                else{
                    // std::cout << "beat not due!\n\n";
                }
            }
        }
    }

    // for(int i; i < 100; i++){

    //     b.processAudioFrame(&frame[0]);
    //     if (b.beatDueInCurrentFrame()){
    //         std::cout << "here\n";
    //     }
    //     else{
    //         std::cout << "no beat due\n";
    //     }
    // }
    
}