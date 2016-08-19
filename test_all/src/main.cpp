#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

int main() { 
    ofGLFWWindowSettings settings;
    settings.width = 1280;
    settings.height = 720;
    settings.setPosition(ofVec2f(300,0));
    settings.resizable = true;
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
    mainWindow->setFullscreen(true);
    
    settings.width = 500;
    settings.height = 800;
    settings.setPosition(ofVec2f(0,0));
    shared_ptr<ofAppBaseWindow> guiWindow = ofCreateWindow(settings);
    
    shared_ptr<ofApp> mainApp(new ofApp);
    mainApp->setupGui();
    ofAddListener(guiWindow->events().draw, mainApp.get(), &ofApp::drawGui);
    
    ofRunApp(mainWindow, mainApp);
    ofRunMainLoop();
}
