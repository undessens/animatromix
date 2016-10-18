#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup()
{
    
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetLogLevel("ofThread", OF_LOG_ERROR);
    doDrawInfo = true;    
    doPrintInfo = false;
    //allows keys to be entered via terminal remotely (ssh)
    consoleListener.setup(this);

    // OSC			
    receiver.setup(12345);
    
    // OMX camera settings
    omxCameraSettings.width = 1280;
    omxCameraSettings.height = 720;
    omxCameraSettings.framerate = 30;
    omxCameraSettings.enableTexture = true;
    //pass in the settings and it will start the camera

    videoGrabber.setup(omxCameraSettings);
    int settingsCount = 0;
   
    SettingsEnhancement* enhancement= new SettingsEnhancement();
    enhancement->setup(&videoGrabber);
    enhancement->name = "enhancement";
    listOfSettings[settingsCount] = enhancement;
    settingsCount++;

    SettingsZoomCrop* zoomCrop= new SettingsZoomCrop();
    zoomCrop->setup(&videoGrabber);
    zoomCrop->name = "zoomCrop";
    listOfSettings[settingsCount] = zoomCrop;
    settingsCount++;

    SettingsFilters* filters = new SettingsFilters();
    filters->setup(&videoGrabber);
    filters->name = "filters";
    listOfSettings[settingsCount] = filters;
    settingsCount++;

    SettingsWhiteBalance* whiteBalance = new SettingsWhiteBalance();
    whiteBalance->setup(&videoGrabber);
    whiteBalance->name = "enhancement";
    listOfSettings[settingsCount] = whiteBalance;
    settingsCount++;
    
}


//--------------------------------------------------------------
void ofApp::update()
{

	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(m);
		int value = m.getArgAsInt32(0);
		string add0= ofSplitString(m.getAddress(), "/")[0];
	    string add1= ofSplitString(m.getAddress(), "/")[1];
	    

		for (int i=0; i<NB_SETTINGS; i++){
			
			if( add0 == (listOfSettings[i]->name)){
				ofLogVerbose() << "\n OSC settings:" << add0 << " - " << add1 << " : " << ofToString(value);

				//ROUTE osc message according the type of settings
				// Then transmit the adress and value to the specific setting class
				(listOfSettings[i])->onOsc(add1, value);

				//Finally update the class to apply new settings
				(listOfSettings[i])->update();				


			}


	    	}
			
		

	 }
	
		

 
    
}


//--------------------------------------------------------------
void ofApp::draw()
{
    if(videoGrabber.isTextureEnabled())
    {
        //draws at camera resolution
        videoGrabber.draw();
        
        //draw a smaller version via the getTextureReference() method
        /*
	int drawWidth = videoGrabber.getWidth()/4;
        int drawHeight = videoGrabber.getHeight()/4;
        videoGrabber.getTextureReference().draw(videoGrabber.getWidth()-drawWidth, videoGrabber.getHeight()-drawHeight, drawWidth, drawHeight);
        */    
    }
    
    if (doDrawInfo || doPrintInfo) 
    {
        stringstream info;
        info << endl;
        info << "App FPS: " << ofGetFrameRate() << endl;
        info << "CAMERA RESOLUTION: "   << videoGrabber.getWidth() << "x" << videoGrabber.getHeight()	<< " @ "<< videoGrabber.getFrameRate() <<"FPS"<< endl;
        info << endl;
        info << endl;
        info << "Press SPACE for next Demo" << endl;
        info << "Press r to reset camera settings" << endl;
        info << "Press z TO START RECORDING" << endl;
        info << "Press x TO STOP RECORDING" << endl;

        if (doDrawInfo) 
        {
            int x = 100;
            if(videoGrabber.getWidth()<1280)
            {
                x = videoGrabber.getWidth();
            }
            ofDrawBitmapStringHighlight(info.str(), x, 40, ofColor(ofColor::black, 50), ofColor::yellow);
        }
        if (doPrintInfo) 
        {
            ofLogVerbose() << info.str();
            doPrintInfo = false;
        }
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key)
{
    ofLog(OF_LOG_VERBOSE, "%c keyPressed", key);
    switch (key) 
    {
        
        case 'd':
        {
            doDrawInfo = !doDrawInfo;
            break;
        }
        case 'i':
        {
            doPrintInfo = !doPrintInfo;
            break;
        }
        case 'p' :
        {
            break;
        }
        case 'r' :
        {
            videoGrabber.reset();
            break;
        }
            
        case 'z' :
        {
            videoGrabber.startRecording();
            break;
        }
        case 'x' :
        {
            videoGrabber.stopRecording();
            break;
        }
        default:
        {
            break;
        }
            
    }
}

void ofApp::onCharacterReceived(KeyListenerEventData& e)
{
    keyPressed((int)e.character);
}
