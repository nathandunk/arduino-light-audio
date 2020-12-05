#include <BTrack.h>
#include <iostream>

int main(){
    BTrack b; 

    std::vector<double> frame(1024, 2.5);

    for i = 100{
        b.processAudioFrame(frame);
        if (b.beatDueInCurrentFrame){
            std::cout << "here";
        }
        else{
            std::cout << "no beat due";
        }
    }
    
}