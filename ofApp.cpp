#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();

	for (int x = -450; x <= 450; x += 450) {

		for (int y = -450; y <= 450; y += 450) {

			for (int radius = 70; radius <= 150; radius += 10) {

				this->setRingToMesh(this->face, this->frame, glm::vec3(x, y, 0), radius, 5, 60, 0, 360);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofSetColor(39);
	this->face.draw();

	ofSetColor(239);
	this->frame.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
void ofApp::setRingToMesh(ofMesh& face_target, ofMesh& frame_target, glm::vec3 location, float radius, float width, float height, int deg_start, int deg_end) {

	if (deg_start > deg_end) {

		auto tmp = deg_start - 1;
		deg_start = deg_end;
		deg_end = tmp;
	}

	int index = face_target.getNumVertices();
	int deg_span = 5;

	int angle_x = ofMap(ofNoise(location.x, radius * 0.0012 + ofGetFrameNum() * 0.006), 0, 1, 0, 360 * 2);
	angle_x = (angle_x / 30) * 30;
	auto rotation_x = glm::rotate(glm::mat4(), angle_x * (float)DEG_TO_RAD, glm::vec3(1, 0, 0));

	int angle_y = ofMap(ofNoise(location.y, radius * 0.0012 + ofGetFrameNum() * 0.006), 0, 1, 0, 360 * 2);
	angle_y = (angle_y / 30) * 30;
	auto rotation_y = glm::rotate(glm::mat4(), angle_y * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
	for (int deg = deg_start; deg < deg_end; deg += deg_span) {

		auto face_index = face_target.getNumVertices();

		vector<glm::vec3> vertices;
		vertices.push_back(location + glm::vec4((radius + width * 0.5) * cos(deg * DEG_TO_RAD), (radius + width * 0.5) * sin(deg * DEG_TO_RAD), height * -0.5, 0) * rotation_y * rotation_x);
		vertices.push_back(location + glm::vec4((radius + width * 0.5) * cos((deg + deg_span) * DEG_TO_RAD), (radius + width * 0.5) * sin((deg + deg_span) * DEG_TO_RAD), height * -0.5, 0) * rotation_y * rotation_x);
		vertices.push_back(location + glm::vec4((radius + width * 0.5) * cos((deg + deg_span) * DEG_TO_RAD), (radius + width * 0.5) * sin((deg + deg_span) * DEG_TO_RAD), height * 0.5, 0) * rotation_y * rotation_x);
		vertices.push_back(location + glm::vec4((radius + width * 0.5) * cos(deg * DEG_TO_RAD), (radius + width * 0.5) * sin(deg * DEG_TO_RAD), height * 0.5, 0) * rotation_y * rotation_x);

		vertices.push_back(location + glm::vec4((radius - width * 0.5) * cos(deg * DEG_TO_RAD), (radius - width * 0.5) * sin(deg * DEG_TO_RAD), height * -0.5, 0) * rotation_y * rotation_x);
		vertices.push_back(location + glm::vec4((radius - width * 0.5) * cos((deg + deg_span) * DEG_TO_RAD), (radius - width * 0.5) * sin((deg + deg_span) * DEG_TO_RAD), height * -0.5, 0) * rotation_y * rotation_x);
		vertices.push_back(location + glm::vec4((radius - width * 0.5) * cos((deg + deg_span) * DEG_TO_RAD), (radius - width * 0.5) * sin((deg + deg_span) * DEG_TO_RAD), height * 0.5, 0) * rotation_y * rotation_x);
		vertices.push_back(location + glm::vec4((radius - width * 0.5) * cos(deg * DEG_TO_RAD), (radius - width * 0.5) * sin(deg * DEG_TO_RAD), height * 0.5, 0) * rotation_y * rotation_x);

		face_target.addVertices(vertices);

		face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 1); face_target.addIndex(face_index + 2);
		face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 2); face_target.addIndex(face_index + 3);

		face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 5); face_target.addIndex(face_index + 6);
		face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 6); face_target.addIndex(face_index + 7);

		face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 5);
		face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 5); face_target.addIndex(face_index + 1);

		face_target.addIndex(face_index + 3); face_target.addIndex(face_index + 7); face_target.addIndex(face_index + 6);
		face_target.addIndex(face_index + 3); face_target.addIndex(face_index + 6); face_target.addIndex(face_index + 2);

		auto frame_index = frame_target.getNumVertices();

		frame_target.addVertices(vertices);

		frame_target.addIndex(frame_index + 0); frame_target.addIndex(frame_index + 1);
		frame_target.addIndex(frame_index + 2); frame_target.addIndex(frame_index + 3);
		frame_target.addIndex(frame_index + 4); frame_target.addIndex(frame_index + 5);
		frame_target.addIndex(frame_index + 6); frame_target.addIndex(frame_index + 7);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}