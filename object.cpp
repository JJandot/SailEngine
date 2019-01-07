#include "object.h"

struct VertexData
{
    QVector3D position;
    //QVector2D texCoord;
};

Object::Object(QString path){
    arrayBuf.create();
    indexBuf.create();
    initObject(path);
}

/*
bool Object::loadObject(QString path, std::vector<QVector3D> &outVertices, std::vector<QVector2D> &outUvs, std::vector<QVector3D> &outNormals)
{
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<QVector3D> tempVertices;
    std::vector<QVector2D> tempUvs;
    std::vector<QVector3D> tempNormals;

    FILE *file = fopen(path.c_str(), "r");
    if(file == nullptr){
        std::cerr << "Object.cpp : Impossible to find specified file : " << path << std::endl;
        return false;
    }

    while(1){
        char lineHeader[255];
        int res = fscanf_s(file, "%s", lineHeader);
        if(res == EOF)
            break;

        if(strcmp(lineHeader, "v") == 0){
            QVector3D vertex;
            fscanf_s(file, "%f %f %f\n", vertex.x(), vertex.y(), vertex.z());
            tempVertices.push_back(vertex);
        }
        else if ( strcmp( lineHeader, "vt" ) == 0){
            QVector2D uv;
            fscanf_s(file, "%f %f\n", uv.x(), uv.y());
            tempUvs.push_back(uv);
        }
        else if ( strcmp( lineHeader, "vn" ) == 0){
            QVector3D normal;
            fscanf_s(file, "%f %f %f\n", normal.x(), normal.y(), normal.z());
            tempNormals.push_back(normal);
        }else if ( strcmp( lineHeader, "f" ) == 0){
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
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
    return true;
}
*/
void Object::initObject(QString path){

    std::vector<QVector3D> tempVertices;
    std::vector<QVector2D> tempUvs;
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<QVector3D> outVertices;


    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)){
        std::cerr << "Object.cpp : Impossible to find specified file : " << path.toStdString() << std::endl;
        exit(-1);
    }

    QTextStream stream(&file);
    QString line;
    QStringList splittedString;
    QString first;

    while(!stream.atEnd()){
        line = stream.readLine();
        splittedString = line.split(" ");
        first = splittedString[0];
        if(first == "v"){
            QVector3D vertex;
            vertex.setX(splittedString[1].toFloat());
            vertex.setY(splittedString[2].toFloat());
            vertex.setZ(splittedString[3].toFloat());
            tempVertices.push_back(vertex);
        }
        else if (first == "vt"){
            QVector2D uv;
            uv.setX(splittedString[1].toFloat());
            uv.setY(splittedString[2].toFloat());
            tempUvs.push_back(uv);
        }
        else if (first == "f") {
            //std::string vertex1, vertex2, vertex3;
            if (splittedString.size() != 4){
                std::cerr << "Object.cpp : erreur face. " << splittedString.size() << std::endl;
                exit(-1);
            }
            QStringList f1, f2, f3;
            f1 = splittedString[1].split('/');
            f2 = splittedString[2].split('/');
            f3 = splittedString[3].split('/');

            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            vertexIndex[0] = f1[0].toUInt();
            uvIndex[0] = f1[1].toUInt();
            normalIndex[0] = f1[2].toUInt();
            vertexIndex[1] = f2[0].toUInt();
            uvIndex[1] = f2[1].toUInt();
            normalIndex[1] = f2[2].toUInt();
            vertexIndex[2] = f3[0].toUInt();
            uvIndex[2] = f3[1].toUInt();
            normalIndex[2] = f3[2].toUInt();

            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices    .push_back(uvIndex[0]);
            uvIndices    .push_back(uvIndex[1]);
            uvIndices    .push_back(uvIndex[2]);
        }
    }

    for(unsigned int i = 0; i < vertexIndices.size(); ++i){
        unsigned int vertexIndex = vertexIndices[i];
        QVector3D vertex = tempVertices[vertexIndex - 1];
        outVertices.push_back(vertex);
    }

    VertexData *vertices = (VertexData*)malloc(outVertices.size() * sizeof (VertexData));
    for(unsigned int i = 0; i < outVertices.size(); ++i){
        VertexData v;
        v.position = outVertices[i];
        vertices[i] = v;
    }

    arrayBuf.bind();
    arrayBuf.allocate(vertices, outVertices.size() * sizeof(VertexData));
}

void Object::drawObject(QOpenGLShaderProgram *program)
{
    arrayBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);
}
