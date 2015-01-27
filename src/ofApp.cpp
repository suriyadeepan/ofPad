#include "ofApp.h"
#include "ctype.h"

ofTrueTypeFont tFont;
ofTrueTypeFont modeFont;

string prompt = "Suriyadeepan_Ram@Goa >> ";
string cmdOp = " ";
string currCmd="";

bool uVar = false;
char gKey;


char READ = 'R';
char INSERT = 'I';
int mode = READ;

//--------------------------------------------------------------
void ofApp::setup(){

	// set background
	ofBackgroundHex(0xf8f8ff);

	//tFont.loadFont("segoeuil.ttf", 48);
	//tFont.loadFont("LiberationMono-Bold.ttf", 15);
	tFont.loadFont("LiberationMono-Bold.ttf", 14, true, false, false, 0.3, 96);
	modeFont.loadFont("TlwgMono-Bold.ttf",30);
 	ofSetEscapeQuitsApp(false);

}

//--------------------------------------------------------------
void ofApp::update(){

	if(uVar == true && gKey == 13){

			char * writable = new char[currCmd.size() + 1];
			std::copy(currCmd.begin(), currCmd.end(), writable);
			writable[currCmd.size()] = '\0'; // don't forget the terminating 0

			cmdOp = exec(writable); 
			// don't forget to free the string after finished using it
			delete[] writable;

			gKey = 0;
			currCmd = "";

	}

	else if(uVar == true && gKey == 8 && currCmd.size() > 0)
			currCmd.erase(currCmd.size() -1, 1 );

	gKey = 0;

}

//--------------------------------------------------------------
void ofApp::draw(){

	ofSetColor(0x80,0x80,0x80,250);
	tFont.drawString( prompt + currCmd + "\n" + cmdOp, 30, 30);
	ofSetColor(0xd8,0x17,0x45,170);
	modeFont.drawString(ofToString((char)mode),950,30);
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	// transfer to global char
	gKey = char(key);

	if(mode == INSERT){
		// check if alphanumeric
		//if( (key>=65 && key<=90) || (key>=97 && key<=122) || key == 32){
		if(key >= 32 && key <= 126){

			currCmd += (char)key;
			// activate update()
			uVar = true;
		}
		else{

			if(key == 27){
				cmdOp = "";
				mode = READ;
			}
		}
	}

	else{

		if( (char)key == 'i'){
			mode = INSERT;
		}

		else if(key == 27){
			currCmd = ""; cmdOp = ""; uVar = true;
		}

		// carriage return
		else if(key == 13){
			printf("\nCarriage return ...");

			gKey = key;
			uVar = true;
		}

		else if(key == 8){
			printf("\nBackspace ...");
			uVar = true;
		}
			

	}

		

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

/*
 * Utilities - bash command
 */

string ofApp::exec(char* cmd) {

	FILE* pipe = popen(cmd, "r");
	if (!pipe) return "ERROR";
	char buffer[128];
	std::string result = "";
	while(!feof(pipe)) {
		if(fgets(buffer, 128, pipe) != NULL)
			result += buffer;
	}
	pclose(pipe);
	return result;

}





