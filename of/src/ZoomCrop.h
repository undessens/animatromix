#pragma once
#include "CameraSettings.h"


class SettingsZoomCrop  : public CameraSettings
{
    
public:
    
    
    bool doCrop;
    bool resetCrop;
    
    bool doZoomIn;
    bool doZoomOut;
    bool doRandomZoom;
    bool resetZoom;
    void setup(ofxRPiCameraVideoGrabber* videoGrabber_)
    {
        CameraSettings::setup( videoGrabber_);
       
    };
    
    void update()
    {

            //videoGrabber->zoomIn();
            //videoGrabber->zoomOut();
    };
    
    void reset()
    {
        videoGrabber->setZoomLevelNormalized(0);
    };
    
    void onOsc(string address, int key)
    {      
        if (key == '1')
        {
            doCrop = !doCrop;
        }
        if (key == '2')
        {
            resetCrop = true;
        }
        if (key == '3') 
        {
            doZoomIn = true;
        }
        
        if (key == '4') 
        {
            doZoomOut = true;
        }
        
        if (key == '5') 
        {
            doRandomZoom = true;
        }
        
        if (key == '6') 
        {
            resetZoom = true;
        }
    };
};
