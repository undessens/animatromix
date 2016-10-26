#pragma once
#include "CameraSettings.h"


class SettingsWhiteBalance  : public CameraSettings
{
    
public:
    
    bool doChangeWhiteBalance;
    size_t currentWhiteBalanceIndex;
    vector<string> whiteBalanceNames;
    void setup(ofxRPiCameraVideoGrabber* videoGrabber_)
    {
        CameraSettings::setup( videoGrabber_);
        doChangeWhiteBalance = false;
        doEvCompensation = false;
        doChangeFlickerCancellation = false;        
        currentWhiteBalanceIndex = 0;
        whiteBalanceNames = OMX_Maps::getInstance().getWhiteBalanceNames();
    };
    
    void update()
    {
      
    }

    void reset()
    {
        currentWhiteBalanceIndex = 0;
        videoGrabber->setWhiteBalance(GetWhiteBalance(whiteBalanceNames[currentWhiteBalanceIndex]));
    }

    
    void onOsc(string address, int key)
    {
        //Example How to change white balance
        // if(currentWhiteBalanceIndex+1 < whiteBalanceNames.size())
        //     {
        //         currentWhiteBalanceIndex++;
        //     }else
        //     {
        //         currentWhiteBalanceIndex = 0;
        //     }
        //     videoGrabber->setWhiteBalance(GetWhiteBalance(whiteBalanceNames[currentWhiteBalanceIndex]));
        //     doChangeWhiteBalance = false

    }
};
