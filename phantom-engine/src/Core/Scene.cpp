#include "Scene.h"
#include "Component.h"
#include "Object.h"
#include "Components/Transform2D.h"
#include "Components/Transform3D.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

namespace Phantom {
    Scene::Scene()
    {
    }

    Scene::~Scene()
    {
    }

    void Scene::Start()
    {
    }

    void Scene::Update(double deltaTime)
    {
    }

    Object Scene::CreateObject()
    {
        Object object = { m_Registry.create(), this};
        object.AddComponent<Transform3D>();
        return object;
    }

    std::string Scene::GetValue(const std::string& json, const std::string& key) {
        size_t keyPos = json.find(key);
        if (keyPos == std::string::npos) return "";

        size_t startPos = json.find(':', keyPos) + 1;
        size_t endPos = json.find(',', startPos);
        if (endPos == std::string::npos) endPos = json.find('}', startPos);

        return json.substr(startPos, endPos - startPos);
    }

    std::vector<float> Scene::ParseFloatArray(const std::string& arrayStr) {
        std::vector<float> result;
        std::stringstream ss(arrayStr);
        std::string item;
        while (std::getline(ss, item, ',')) {
            result.push_back(std::stof(item));
        }
        return result;
    }

    std::vector<unsigned short> Scene::ParseUShortArray(const std::string& arrayStr) {
        std::vector<unsigned short> result;
        std::stringstream ss(arrayStr);
        std::string item;
        while (std::getline(ss, item, ',')) {
            result.push_back(static_cast<unsigned short>(std::stoi(item)));
        }
        return result;
    }

Model Scene::LoadPMD(const std::string& filename) {
    // Load JSON data from file
    std::ifstream file(filename);
    if (!file.is_open()) {
        TraceLog(LOG_ERROR, "Failed to open JSON file: %s", filename.c_str());
        //return nullptr; MAKE THIS RETURN A FUNNY MESH
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string jsonData = buffer.str();
    file.close();

    // Extract mesh data (simplified example)
    std::string verticesStr = GetValue(jsonData, "\"vertices\"");
    std::string texcoordsStr = GetValue(jsonData, "\"texcoords\"");
    std::string normalsStr = GetValue(jsonData, "\"normals\"");
    std::string colorsStr = GetValue(jsonData, "\"colors\"");
    std::string tangentsStr = GetValue(jsonData, "\"tangents\"");
    std::string texcoords2Str = GetValue(jsonData, "\"texcoords2\"");
    std::string indicesStr = GetValue(jsonData, "\"indices\"");

    // Parse and setup mesh
    Mesh mesh = { 0 };
    std::vector<float> vertices = ParseFloatArray(verticesStr);
    std::vector<float> texcoords = ParseFloatArray(texcoordsStr);
    std::vector<float> normals = ParseFloatArray(normalsStr);
    std::vector<unsigned char> colors;
    std::vector<float> tangents = ParseFloatArray(tangentsStr);
    std::vector<float> texcoords2 = ParseFloatArray(texcoords2Str);
    std::vector<unsigned short> indices = ParseUShortArray(indicesStr);

    if (!colorsStr.empty()) {
        std::vector<float> colorFloats = ParseFloatArray(colorsStr);
        colors.assign(colorFloats.begin(), colorFloats.end());
    }

    mesh.vertexCount = vertices.size() / 3;
    mesh.vertices = vertices.data();
    mesh.texcoords = texcoords.data();
    mesh.normals = normals.data();
    mesh.colors = colors.data();
    mesh.tangents = tangents.data();
    mesh.texcoords2 = texcoords2.data();
    mesh.triangleCount = indices.size() / 3;
    mesh.indices = indices.data();

    // Upload mesh to GPU
    Model model = LoadModelFromMesh(mesh);
    return model;
    // Optionally, handle materials here if present in JSON
}

} // Phantom
