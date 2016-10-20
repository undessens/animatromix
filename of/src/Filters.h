 #pragma once
#include "CameraSettings.h"


class SettingsFilters  : public CameraSettings
{
    
public:
    
    
    vector<string> listOfFilter;
    int currentFilter;
    void setup(ofxRPiCameraVideoGrabber* videoGrabber_)
    {
        CameraSettings::setup( videoGrabber_);
        listOfFilter.push_back("None"); // None is the filter number 0, as defined in reset mode
        listOfFilter.push_back("Negative");
        listOfFilter.push_back("Sketch");
        listOfFilter.push_back("WashedOut");
        listOfFilter.push_back("Cartoon");
        listOfFilter.push_back("Hatch");
        listOfFilter.push_back("Posterise");
        listOfFilter.push_back("ColourSwap");
        currentFilter = 0;         
               
    }
    
    void update()
    {

    }

    void reset()
    {
        videoGrabber->setImageFilter("None");
        currentFilter = 0;
    }
    
    
    void onOsc(string address, int value)
    {
        if (address == "filterNum")
        {

                if(key>0 && key<listOfFilter.size())
                {
                    string name = "";
                    name = listOfFilter[value];
                    videoGrabber->setImageFilter(name);
                    currentFilter = key;
                }
            
        }

        if ( address== "nextFilter")
        {
            currentFilter++;
            if(currentFilter >= listOfFilter.size()) currentFilter = 0;
            string name = listOfFilter[value];
            videoGrabber->setImageFilter(name);
            currentFilter = key;

        }


        if ( address== "previousFilter")
        {
            currentFilter--;
            if(currentFilter < 0) currentFilter = ( listOfFilter.size() - 1 );
            string name = listOfFilter[value];
            videoGrabber->setImageFilter(name);
            currentFilter = key;

        }
        
    }
};
