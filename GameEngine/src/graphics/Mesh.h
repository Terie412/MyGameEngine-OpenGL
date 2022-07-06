#include <vector>
#include <GLM/glm.hpp>

#include "Vertex.h"

using std::vector;

class Mesh {
public:
	vector<Vertex>			vertices;
	vector<unsigned int>	triangleIndices;
};