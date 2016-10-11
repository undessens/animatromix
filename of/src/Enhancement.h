#pragma once
#include "CameraSettings.h"


class SettingsEnhancement  : public CameraSettings
{
    
public:
    
    

    
    int sharpness;
    int contrast;
    int brightness;
    int saturation;
    
    bool doSharpness;
    bool doContrast; 
    bool doBrightness; 
    bool doSaturation;
    
    bool doValueReset;
    bool doValueResetToZero;
    bool doDRE;
    int dreLevel;
    
    void setup(ofxRPiCameraVideoGrabber* videoGrabber_)
    {
        CameraDemo::setup( videoGrabber_);
        doSharpness = false;
        doContrast = false;
        doBrightness = false;
        doSaturation = false;
        doDRE = false;
        dreLevel = 0;
        doValueReset = false;
        
        //videoGrabber->enableAutoExposure();
    }
    
    void update()
    {

        if(doValueReset)
        {
            videoGrabber->setSharpness(-50);
            videoGrabber->setContrast(-10);
            videoGrabber->setBrightness(50);
            videoGrabber->setSaturation(0);
            videoGrabber->setDRE(0);
            doSharpness = false;
            doContrast = false;
            doBrightness = false;
            doSaturation = false;
            doDRE = false;
            dreLevel = 0;
            doValueReset = false;
            
        }
        
      

        
        stringstream info;

        info << "sharpness: "   << videoGrabber->getSharpness()    << "\n";
        info << "contrast: "    << videoGrabber->getContrast()     << "\n";
        info << "brightness: "  << videoGrabber->getBrightness()   << "\n";
        info << "saturation: "  << videoGrabber->getSaturation()   << "\n";
                
        info << "\n";
        info << "Press 1 to cycle sharpness" << "\n";
        info << "Press 2 to cycle contrast" << "\n";
        info << "Press 3 to cycle brightness" << "\n";
        info << "Press 4 to cycle saturation" << "\n";
        info << "Press 5 to increment Dynamic Range Expansion (DRE): " << videoGrabber->getDRE() << "\n";
        info << "Press 0 to reset above to defaults" << "\n";
        

        infoString = info.str();
   
    };
    
    void draw()
    {
        
    }
    
    void onKey(int key)
    {
        if (key == '1')
        {
            doSharpness = !doSharpness;
        }
        
        if (key == '2')
        {
            doContrast = !doContrast;
        }
        
        if (key == '3')
        {
            doBrightness = !doBrightness;
        }
        if (key == '4')
        {
            doSaturation = !doSaturation;
        }
        if (key == '5')
        {
            doDRE = true;
        }
        if (key == '0')
        {
            doValueReset = true;
        }

        
    };
};
