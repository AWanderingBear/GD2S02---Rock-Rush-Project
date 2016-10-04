#pragma once
#include <vector>
#include "glew.h"

struct VertexStruct {

	glm::vec3 position;
	glm::vec3 texCoords;
};

std::vector<GLfloat> BackgroundVertices({
	// Positions          // Colors           // Texture Coords
	2049.0f,  384.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // Top Right
	2049.0f, -384.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // Bottom Right
	-2049.0f, -384.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Bottom Left
	-2049.0f,  384.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // Top Left 
});

std::vector<GLuint> Indices({  // Note that we start from 0!
	0, 1, 3,   // First Triangle
	1, 2, 3    // Second Triangle
});

std::vector<GLfloat> mainPlatformVertices({
	// Positions          // Colors           // Texture Coords
	384.0f,  25.0f, 0.0f,   1.0f, 0.0f, 0.0f,   10.0f, 1.0f,   // Top Right
	384.0f, -25.0f, 0.0f,   0.0f, 1.0f, 0.0f,   10.0f, 0.0f,   // Bottom Right
	-384.0f, -25.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Bottom Left
	-384.0f,  25.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // Top Left 
});

std::vector<GLfloat> startPlatformVertices({
	// Positions          // Colors           // Texture Coords
	77.0f,  5.0f, 0.0f,   1.0f, 0.0f, 0.0f,   10.0f, 1.0f,   // Top Right
	77.0f, -5.0f, 0.0f,   0.0f, 1.0f, 0.0f,   10.0f, 0.0f,   // Bottom Right
	-77.0f, -5.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Bottom Left
	-77.0f,  5.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // Top Left 
});

std::vector<GLfloat> SmallSquareVertices({
	// Positions          // Colors           // Texture Coords
	25.0f,  25.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // Top Right
	25.0f, -25.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // Bottom Right
	-25.0f, -25.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Bottom Left
	-25.0f,  25.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // Top Left 
});

std::vector<GLfloat> RailgunVertices({
	// Positions          // Colors           // Texture Coords
	250.0f,  75.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // Top Right
	250.0f, -75.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // Bottom Right
	-250.0f, -75.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Bottom Left
	-250.0f,  75.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // Top Left 
});

std::vector<GLfloat> GenericWorldPieceVertices({
	// Positions          // Colors           // Texture Coords
	100.0f,  25.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // Top Right
	100.0f, -25.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // Bottom Right
	-100.0f, -25.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Bottom Left
	-100.0f,  25.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // Top Left 
});

std::vector<GLfloat> ChainPieceVertices({
	// Positions          // Colors           // Texture Coords
	3.125,  15.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // Top Right
	3.125, -15.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // Bottom Right
	-3.125, -15.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Bottom Left
	-3.125,  15.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // Top Left 
});
