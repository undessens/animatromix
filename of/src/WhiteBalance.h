#pragma once
#include "CameraSettings.h"


class SettingsWhiteBalance  : public CameraSettings
{
    
public:
    
    bool doChangeWhiteBalance;
    bool doEvCompensation;
    bool doChangeFlickerCancellation;
    size_t currentWhiteBalanceIndex;
    vector<string> whiteBalanceNames;
    void setup(ofxRPiCameraVideoGrabber* videoGrabber_)
    {
        CameraDemo::setup( videoGrabber_);
        doChangeWhiteBalance = false;
        doEvCompensation = false;
        doChangeFlickerCancellation = false;        
        currentWhiteBalanceIndex = 0;
        whiteBalanceNames = OMX_Maps::getInstance().getWhiteBalanceNames();
    };
    
    void update()
    {

        if(doChangeWhiteBalance)
        {
            if(currentWhiteBalanceIndex+1 < whiteBalanceNames.size())
            {
                currentWhiteBalanceIndex++;
            }else
            {
                currentWhiteBalanceIndex = 0;
            }
            videoGrabber->setWhiteBalance(GetWhiteBalance(whiteBalanceNames[currentWhiteBalanceIndex]));
            doChangeWhiteBalance = false;
        }

        stringstream info;
        
        info << "\n";
        info << "Press 1 to Change White Balance: "     << videoGrabber->getWhiteBalance()      <<  "\n";
     

        infoString = info.str();
        
    };
    
    void draw()
    {
        
        
        
        
        
    };
    
    void onKey(int key)
    {
        switch (key)
        {
                
            case '1':
            {
                doChangeWhiteBalance = true;
                break;
            }
            case '2':
            {
                doEvCompensation = true;
                break;
            }
            case '3':
            {
                 doChangeFlickerCancellation = true;
                break;
            }
            default:
            {
                break;
            }
        }
        
    };
};
