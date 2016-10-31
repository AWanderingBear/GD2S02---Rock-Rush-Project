#include "Model.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Use to initialise a vertex array
Model::Model()
{

}

Model::~Model()
{
}

void Model::Initialise(ModelType Load, FragmentType Fill, GLuint Shader, std::string _strTexture, std::vector<GLfloat> Vertices, std::vector<GLuint> Elements, Camera* Camera){

	LoadType = Load;
	FillType = Fill;
	ShaderProgram = Shader;
	m_Vertices = Vertices;
	m_Elements = Elements;

	ModelTex.Initialise(_strTexture);
	m_Camera = Camera;

	//Vertex Buffer - Memory buffer in the GFX card we set aside for this information
	glGenBuffers(1, &VBO); //Generate
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // Tell Open GL this is the "active" buffer

	//Vertex Array Object (Holds attrib pointers) basically a settings list for how to handle the VBO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	if (LoadType == Vertex) {

		//Binds Vertexes into the VBO
		glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(GLfloat), m_Vertices.data(), GL_STATIC_DRAW); //Send Data to the buffer Open GL has active
		// (Buffer Type, Size of Data, Data, How GFX card should manage data)

		//Binds Elements into the EBO
		glGenBuffers(1, &EBO); //Generate
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Elements.size() * sizeof(GLuint), m_Elements.data(), GL_STATIC_DRAW);
	}
	else {

		//Model Loading
	}


	if (FillType == Colored) {
		//This is for the positions
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0); //Telling GL how to handle the VBO
		//( Layout Location in Shader, Size of Vertex (Vec3), Data Type, Coord Data is Normalized, Stride) 

		glEnableVertexAttribArray(0); //Setting the Attrib array to be Active so it is used with the active buffer

		//This is for the colors
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
	}
	else {

		//This is for the positions
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0); //Telling GL how to handle the VBO
		//( Layout Location in Shader, Size of Vertex (Vec3), Data Type, Coord Data is Normalized, Stride) 

		//This is for the colors
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		//This is for the Texture Coordinants
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
	}

	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

void Model::Render()
{

	glUseProgram(ShaderProgram);
	glBindTexture(GL_TEXTURE_2D, ModelTex.GetTexture());
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, m_Elements.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Model::Update(glm::vec3 Position, float Rotation)
{

	glm::mat4 model;
	model = glm::translate(model, Position);
	model = glm::rotate(model, Rotation, glm::vec3(0, 0, 1));

	glm::mat4 view;
	glm::mat4 projection;

	GLint ModelLoc = glGetUniformLocation(ShaderProgram, "model");
	glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, glm::value_ptr(model));

	GLint ViewLoc = glGetUniformLocation(ShaderProgram, "view");
	glUniformMatrix4fv(ViewLoc, 1, GL_FALSE, glm::value_ptr(m_Camera->GetView()));

	GLint ProjectionLoc = glGetUniformLocation(ShaderProgram, "projection");
	glUniformMatrix4fv(ProjectionLoc, 1, GL_FALSE, glm::value_ptr(m_Camera->GetProjection()));
}
