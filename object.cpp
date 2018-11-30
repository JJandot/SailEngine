#include "object.h"

Object::Object()
{

}

bool Object::loadObject(std::string path, std::vector<QVector3D> &outVertices, std::vector<QVector2D> &outUvs, std::vector<QVector3D> &outNormals)
{
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<QVector3D> tempVertices;
    std::vector<QVector2D> tempUvs;
    std::vector<QVector3D> tempNormals;

    FILE *file = fopen(path.c_str(), "r");
    if(file == NULL){
        std::cerr << "Object.cpp : Impossible to find specified file : " << path << std::endl;
        return false;
    }

    while(1){
        char lineHeader[255];
        int res = fscanf(file, "%s", lineHeader);
        if(res == EOF)
            break;

        if(strcmp(lineHeader, "v") == 0){
            QVector3D vertex;
            fscanf(file, "%f %f %f\n", vertex.x(), vertex.y(), vertex.z());
            tempVertices.push_back(vertex);
        }
        else if ( strcmp( lineHeader, "vt" ) == 0){
            QVector2D uv;
            fscanf(file, "%f %f\n", uv.x(), uv.y());
            tempUvs.push_back(uv);
        }
        else if ( strcmp( lineHeader, "vn" ) == 0){
            QVector3D normal;
            fscanf(file, "%f %f %f\n", normal.x(), normal.y(), normal.z());
            tempNormals.push_back(normal);
        }else if ( strcmp( lineHeader, "f" ) == 0){
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
            if (matches != 9){
                printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                return false;
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices    .push_back(uvIndex[0]);
            uvIndices    .push_back(uvIndex[1]);
            uvIndices    .push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }
    }

    for(unsigned int i = 0; i < vertexIndices.size(); ++i){
        unsigned int vertexIndex = vertexIndices[i];
        QVector3D vertex = tempVertices[vertexIndex - 1];
        outVertices.push_back(vertex);
    }
    for(unsigned int i = 0; i < uvIndices.size(); ++i){
        unsigned int uvIndex = uvIndices[i];
        QVector2D vertex = tempUvs[uvIndex - 1];
        outUvs.push_back(vertex);
    }
    for(unsigned int i = 0; i < normalIndices.size(); ++i){
        unsigned int normalIndex = normalIndices[i];
        QVector3D vertex = tempVertices[normalIndex - 1];
        outNormals.push_back(vertex);
    }
}
