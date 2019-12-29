#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

#include <glm/gtx/string_cast.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

struct Material
{
	std::string mtlName;
	float shininess;
	glm::vec3 ambientColor;
	glm::vec3 diffuseColor;
	glm::vec3 specularColor;
	glm::vec3 emission;
	float indexOfRefraction;
	float dissolve;
	int illumination;

	std::string diffuseTexture;
	std::string alphaTexture;

	void View()
	{
		std::cout << "===================" << std::endl;
		std::cout << "Name: " << mtlName << std::endl;
		std::cout << "Ns: " << shininess << std::endl;
		std::cout << "Ka: " << glm::to_string(ambientColor) << std::endl;
		std::cout << "Kd: " << glm::to_string(diffuseColor) << std::endl;
		std::cout << "Ks: " << glm::to_string(specularColor) << std::endl;
		std::cout << "Ke: " << glm::to_string(emission) << std::endl;
		std::cout << "Ni: " << indexOfRefraction << std::endl;
		std::cout << "d: " << dissolve << std::endl;
		std::cout << "illum: " << illumination << std::endl;
		std::cout << "map_Kd" << diffuseTexture << std::endl;
		std::cout << "map_d" << alphaTexture << std::endl;
		std::cout << "===================" << std::endl;
	}
};


struct Vertex
{
	glm::vec3 position;
	glm::vec2 texCoord;
	glm::vec3 normal;

	bool operator==(const Vertex& other) const
	{
		return position == other.position && texCoord == other.texCoord && normal == other.normal;
	}
};

struct Mesh
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Material> materials;
};

namespace std {
	template<> struct hash<Vertex> {

		void hash_combine(::size_t& seed, const unsigned int& hash) const
		{
			seed ^= hash + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		}

		::size_t operator()(Vertex const& vertex) const
		{
			auto hasher = hash<glm::vec3>{};
			auto hashed_pos = hasher(vertex.position);
			auto hashed_nor = hasher(vertex.normal);
			auto hasher2 = hash<glm::vec2>{};
			auto hashed_tex = hasher2(vertex.texCoord);

			::size_t seed = 0;
			hash_combine(seed, hashed_pos);
			hash_combine(seed, hashed_nor);
			hash_combine(seed, hashed_tex);
			return seed;
		}
	};
}

class Loader
{
	static inline Mesh s_mesh = {};

	static inline std::vector<unsigned int> s_vertexIndicesTemp = {}, s_texCoordIndicesTemp = {}, s_normalsIndicesTemp = {};
	static inline std::vector<glm::vec3> s_verticesTemp = {};
	static inline std::vector<glm::vec2> s_texCoordsTemp = {};
	static inline std::vector<glm::vec3> s_normalsTemp = {};
	
public:
	static Mesh LoadMesh(const std::string& path)
	{
		
		if(path.find(".obj") != std::string::npos)
		{
			ParseOBJ(path);
		}
		else
		{
			std::cout << "MeshLoader ERROR: Sorry This FileFormat is not supported" << std::endl;
		}

		return s_mesh;
	}

	static std::vector<Material> LoadMaterial(const std::string& path)
	{
		
		std::vector<Material> materials;
		
		std::ifstream stream(path, std::ifstream::in);
		if (!stream.good())
		{
			std::cout << "MeshLoader ERROR: Path Not Found!" << std::endl;
			stream.close();
			return materials;
		}

		std::string currentLine;
		unsigned int count = 0;
		int index = -1;
		
		while (std::getline(stream, currentLine))
		{
			if (currentLine.size() > 7 && currentLine.substr(0, 7) == "newmtl ")
			{
				std::cout << "MeshLoader: Material Loaded!" << std::endl;
				index++;
				materials.push_back({});
				std::istringstream ss(currentLine.substr(7));
				ss >> materials[index].mtlName;
			}
			else if (currentLine.size() > 3 && currentLine.substr(0, 3) == "Ns ")
			{
				std::istringstream ss(currentLine.substr(3));
				ss >> materials[index].shininess;
			}
			else if (currentLine.size() > 3 && currentLine.substr(0, 3) == "Ka ")
			{
				std::istringstream ss(currentLine.substr(3));
				ss >> materials[index].ambientColor.x; ss >> materials[index].ambientColor.y; ss >> materials[index].ambientColor.z;
			}
			else if (currentLine.size() > 3 && currentLine.substr(0, 3) == "Kd ")
			{
				std::istringstream ss(currentLine.substr(3));
				ss >> materials[index].diffuseColor.x; ss >> materials[index].diffuseColor.y; ss >> materials[index].diffuseColor.z;
			}
			else if (currentLine.size() > 3 && currentLine.substr(0, 3) == "Ks ")
			{
				std::istringstream ss(currentLine.substr(3));
				ss >> materials[index].specularColor.x; ss >> materials[index].specularColor.y; ss >> materials[index].specularColor.z;
			}
			else if (currentLine.size() > 3 && currentLine.substr(0, 3) == "Ke ")
			{
				std::istringstream ss(currentLine.substr(3));
				ss >> materials[index].emission.x; ss >> materials[index].emission.y; ss >> materials[index].emission.z;
			}
			else if (currentLine.size() > 3 && currentLine.substr(0, 3) == "Ni ")
			{
				std::istringstream ss(currentLine.substr(3));
				ss >> materials[index].indexOfRefraction;
			}
			else if (currentLine.size() > 2 && currentLine.substr(0, 2) == "d ")
			{
				std::istringstream ss(currentLine.substr(2));
				ss >> materials[index].dissolve;
			}
			else if (currentLine.size() > 6 && currentLine.substr(0, 6) == "illum ")
			{
				std::istringstream ss(currentLine.substr(6));
				ss >> materials[index].illumination;
			}
			else if (currentLine.size() > 7 && currentLine.substr(0, 7) == "map_Kd ")
			{
				std::istringstream ss(currentLine.substr(7));
				ss >> materials[index].diffuseTexture;
			}
			else if (currentLine.size() > 7 && currentLine.substr(0, 6) == "map_d ")
			{
				std::istringstream ss(currentLine.substr(6));
				ss >> materials[index].alphaTexture;
			}
		}
		stream.close();
		return materials;
	}

private:
	static void Log(std::vector<glm::vec3>& target)
	{
		for (glm::vec3& vec : target)
		{
			std::cout << glm::to_string(vec) << std::endl;
		}
	}

	static void Log(std::vector<glm::vec2>& target)
	{
		for (glm::vec2& vec : target)
		{
			std::cout << glm::to_string(vec) << std::endl;
		}
	}
	
	static void Log(const std::string& msg)
	{
		std::cout << "MeshLoader: " << msg << std::endl;
	}

	static void Log(std::vector<unsigned int>& target)
	{
		for (unsigned int& i : target)
		{
			std::cout << i << " ";
		}
		std::cout << std::endl;
	}

	static std::string RemoveEnd(const std::string& source)
	{
		std::string temp;
		for(unsigned int i = 0; i < source.size(); i++)
		{
			char chr = source[source.size() - i];
			if (chr == '/')
				return source.substr(0, source.size() - i + 1);
		}
		return temp;
	}
	
	static void ParseOBJ(const std::string& path)
	{
		const std::string filePath = RemoveEnd(path);
		std::string materialName;
		
		std::ifstream stream(path, std::ifstream::in);
		if (!stream.good())
		{
			std::cout << "MeshLoader ERROR: Path Not Found!" << std::endl;
			stream.close();
			return;
		}

		std::string currentLine;

		while(std::getline(stream, currentLine))
		{
			if (currentLine.length() > 7 && currentLine.substr(0, 7) == "mtllib ")
			{
				std::istringstream ss(currentLine.substr(7));
				ss >> materialName;
				
			}
			else if (currentLine.length() > 2 && currentLine.substr(0,2) == "v ")
			{
				std::istringstream ss(currentLine.substr(2));
				glm::vec3 temp; ss >> temp.x; ss >> temp.y; ss >> temp.z;
				s_verticesTemp.push_back(temp);
			}
			else if (currentLine.length() > 3 && currentLine.substr(0, 3) == "vt ")
			{
				std::istringstream ss(currentLine.substr(3));
				glm::vec2 temp; ss >> temp.x; ss >> temp.y;
				s_texCoordsTemp.push_back(temp);
			}
			else if (currentLine.length() > 3 && currentLine.substr(0, 3) == "vn ")
			{
				std::istringstream ss(currentLine.substr(3));
				glm::vec3 temp; ss >> temp.x; ss >> temp.y; ss >> temp.z;
				s_normalsTemp.push_back(temp);
			}
			else if (currentLine.length() > 2 && currentLine.substr(0, 2) == "f ")
			{
				std::string line = currentLine.substr(2);
				
				if (IsTriangulated(line))
					ReadFace(line, 3);
				else
					ReadFace(line, 4);
			}
		}		
		if (!materialName.empty())
			s_mesh.materials = LoadMaterial(std::string(filePath+materialName));
		
		stream.close();
		
		UncompressValues(s_verticesTemp, s_vertexIndicesTemp);
		UncompressValues(s_normalsTemp, s_normalsIndicesTemp);

		Log("Old Vertices: " + std::to_string(s_verticesTemp.size()));
		GenerateMeshVertices();
		Log("New Vertices: " + std::to_string(s_mesh.vertices.size()));
		std::cout << "MeshLoader: Model Loaded!" << std::endl;
	}

	static bool IsTriangulated(const std::string& line)
	{
		std::istringstream ss(line);
		std::string face;
		unsigned int count = 0;
		
		while (ss >> face)
			count++;

		return  (count == 3) ? true : false;
	}

	static void ReadFace(const std::string& line, const unsigned int faces)
	{
		std::vector<unsigned> vIndices, nIndices;
		
		std::istringstream ss(line);
		std::string face;
		unsigned int value;
		char avoidCharacter;

		for(unsigned int i = 0; i < faces; i++)
		{
			ss >> face;
			std::istringstream currentFace(face);

			currentFace >> value; vIndices.push_back(value);
			currentFace >> avoidCharacter;
			currentFace >> value; s_texCoordIndicesTemp.push_back(value);
			currentFace >> avoidCharacter;
			currentFace >> value; nIndices.push_back(value);
		}
		
		SetIndices(s_vertexIndicesTemp,vIndices, faces);
		SetIndices(s_normalsIndicesTemp,nIndices, faces);
	}

	static void SetIndices(std::vector<unsigned int>& target, const std::vector<unsigned int>& indices, const unsigned int& count)
	{
		if (count == 4)
		{
			target.push_back(indices[0]);
			target.push_back(indices[1]);
			target.push_back(indices[2]);

			target.push_back(indices[0]);
			target.push_back(indices[2]);
			target.push_back(indices[3]);
			
		}
		else if (count == 3)
		{
			target.push_back(indices[0]);
			target.push_back(indices[1]);
			target.push_back(indices[2]);
		}
		else
		{
			std::cout << "MeshLoader ERROR: Unable To Set Indices!" << std::endl;
		}
	}

	static void UncompressValues(std::vector<glm::vec3>& target, const std::vector<unsigned int>& indices)
	{
		std::vector<glm::vec3> newValues;

		for(unsigned int i = 0; i < indices.size(); i++)
		{
			unsigned int index = indices[i];
			glm::vec3 item = target[index - 1];
			newValues.push_back(item);
		}
		
		target = newValues;
	}

	static void GenerateVetexValues()
	{
		if (s_verticesTemp.size() != s_normalsTemp.size())
		{
			std::cout << "Vertices: " << s_verticesTemp.size() << std::endl;
			std::cout << "Normals: " << s_normalsTemp.size() << std::endl;
			std::cout << "MeshLoader ERROR: Vertices & Normals Are Not Generated Correctly" << std::endl;
			return;
		}

		for(unsigned int i = 0; i < s_verticesTemp.size(); i++)
		{
			Vertex vertex = {};

			vertex.position = s_verticesTemp[i];
			vertex.normal = s_normalsTemp[i];
			
			s_mesh.vertices.push_back(vertex);
		}
	}

	static void AddTexCoords(std::vector<Vertex>& vertices)
	{
		for (int i = 0; i < vertices.size(); i++)
		{
			vertices[i].texCoord = s_texCoordsTemp[i];
		}
	}
	
	static void GenerateMeshVertices()
	{
		GenerateVetexValues();
		std::unordered_map<Vertex, unsigned int> uniqueVertices;

		unsigned int index = 0;
		std::vector<Vertex> tempVertices = {};
		std::vector<unsigned int> tempIndices = {};
		
		for(Vertex& vert : s_mesh.vertices)
		{
			if (uniqueVertices.count(vert) == 0)
			{
				uniqueVertices[vert] = tempVertices.size();
				
				tempIndices.push_back(tempVertices.size());
				tempVertices.push_back(vert);
			}
			else
			{
				tempIndices.push_back(uniqueVertices.at(vert));
			}
		}

		AddTexCoords(tempVertices);
		s_mesh.vertices = tempVertices;
		s_mesh.indices = tempIndices;
		
	}
};