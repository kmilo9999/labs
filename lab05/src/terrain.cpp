#include "terrain.h"

#include <math.h>
#include "gl/shaders/ShaderAttribLocations.h"

Terrain::Terrain() : m_numRows(100), m_numCols(m_numRows)
{
}


/**
 * Returns a pseudo-random value between -1.0 and 1.0 for the given row and column.
 */
float Terrain::randValue(int row, int col, float amplitude, float frequencyX,float frequencyY,float G) {
    return -1.0 + 2.0 * glm::fract(sin(row * 127.1f + col * 311.7f) * 43758.5453123f);
    //return -1.0 + 2.0 * glm::fract( amplitude *sin(G * (row * frequencyX + col * frequencyY)) );
}


float Terrain::randValue2(int row, int col, float amplitude, float frequencyX,float frequencyY,float G) {
    //return -1.0 + 2.0 * glm::fract(sin(row * 127.1f + col * 311.7f) * 43758.5453123f);
    float pi = glm::pi<float>();
    return -1.0 + 2.0 * glm::fract(amplitude * sin(frequencyX * 2.0*pi ));
}

/**
 * Returns the object-space position for the terrain vertex at the given row and column.
 */
glm::vec3 Terrain::getPosition(int row, int col) {
    glm::vec3 position;

    position.x = 10 * row/m_numRows - 5;
    position.y = 0;
    position.z = 10 * col/m_numCols - 5;

    float x = (float)row /20.0f;
    float y = (float)col /20.0f;



    int new_row = glm::floor(x);
    int new_col = glm::floor(y);

    //-------------
    //
    //      X-----X1
    //      |
    //      |
    //      X2    X3
    //--

    int x1 = new_row + 1;
    int y1 = new_col + 1;

    float heigth1 = 0.0;
    float heigth2 = 0.0;
    float heigth3 = 0.0;
    float heigth4 = 0.0;

//    if(x1 < 5 && y1 <5)
//    {
      float dx =  glm::fract( x - (float)new_row);
      dx = (3.0f * dx * dx ) -( 2.0*dx*dx*dx);
      float dy =  glm::fract( y - (float) new_col);
      dy = (3.0f * dy * dy ) -( 2.0*dy*dy*dy);


      heigth1 = randValue(new_row, new_col,43758.5453123f,127.1f,311.7f,1.0) ;
      heigth2 = randValue(new_row, new_col  + 1,43758.5453123f,127.1f,311.7f,1.0) ;

      heigth3 = randValue(new_row + 1,new_col,43758.5453123f,127.1f,311.7f,1.0);
      heigth4 = randValue(new_row + 1,new_col  + 1,43758.5453123f,127.1f,311.7f,1.0);

      float a = glm::mix(heigth1,heigth2,dy);
      float b = glm::mix(heigth3,heigth4,dy);

      float r1 = glm::mix(a,b,dx);

      float x0 = (float)row /10.0f;
      float y0 = (float)col /10.0f;

      new_row = glm::floor(x0);
      new_col = glm::floor(y0);
      dx =  glm::fract( x0 - (float)new_row);
      dx = (3.0f * dx * dx ) -( 2.0*dx*dx*dx);
      dy =  glm::fract( y0 - (float) new_col);
      dy = (3.0f * dy * dy ) -( 2.0*dy*dy*dy);

      heigth1 = 1.0/glm::exp2(2.0) + randValue(new_row,new_col,43758.5453123f,100*127.1f,100*311.7f,1.0) ;
      heigth2 = 1.0/glm::exp2(2.0) + randValue(new_row,new_col  + 1,43758.5453123f,100*127.1f,100*311.7f,1.0) ;

      heigth3 = 1.0/glm::exp2(2.0) + randValue(new_row + 1,new_col,43758.5453123f,100*127.1f,100*311.7f,1.0);
      heigth4 = 1.0/glm::exp2(2.0) + randValue(new_row + 1,new_col  + 1,43758.5453123f,100*127.1f,100*311.7f,1.0);

//      heigth1 = randValue2(new_row, new_col,1,2.0,2.0*311.7f,128.0 ) ;
//      heigth2 = randValue(new_row, new_col  + 1,1,2.0,2.0*311.7f,128.0) ;

//      heigth3 = randValue2(new_row + 1,new_col,1,2.0,2.0*311.7f,128.0);
//      heigth4 = randValue2(new_row + 1,new_col  + 1,1,2.0,2.0*311.7f,128.0);

      a = glm::mix(heigth1,heigth2,dy);
      b = glm::mix(heigth3,heigth4,dy);

      float r2 = glm::mix(a,b,dx);


//      heigth1 = randValue(new_row, new_col,43758.5453123f/glm::exp2(4.f),4.0*127.1f,4.0*311.7f,1.0 ) ;
//      heigth2 = randValue(new_row, new_col  + 1,43758.5453123f/glm::exp2(4.f),4.0*127.1f,4.0*311.7f,1.0) ;

//      heigth3 = randValue(new_row + 1,new_col,43758.5453123f/glm::exp2(4.f),4.0*127.1f,4.0*311.7f,1.0);
//      heigth4 = randValue(new_row + 1,new_col  + 1,43758.5453123f/glm::exp2(4.f),4.0*127.1f,4.0*311.7f,1.0);

       x0 = (float)row /5.0f;
       y0 = (float)col /5.0f;

       new_row = glm::floor(x0);
       new_col = glm::floor(y0);
       dx =  glm::fract( x0 - (float)new_row);
       dx = (3.0f * dx * dx ) -( 2.0*dx*dx*dx);
       dy =  glm::fract( y0 - (float) new_col);
       dy = (3.0f * dy * dy ) -( 2.0*dy*dy*dy);

       heigth1 = 1.0/glm::exp2(4.0) + randValue(new_row,new_col,43758.5453123f,100*127.1f,100*311.7f,1.0) ;
       heigth2 = 1.0/glm::exp2(4.0) + randValue(new_row,new_col  + 1,43758.5453123f,100*127.1f,100*311.7f,1.0) ;

       heigth3 = 1.0/glm::exp2(4.0) + randValue(new_row + 1,new_col,43758.5453123f,100*127.1f,100*311.7f,1.0);
       heigth4 = 1.0/glm::exp2(4.0) + randValue(new_row + 1,new_col  + 1,43758.5453123f,100*127.1f,100*311.7f,1.0);

      a = glm::mix(heigth1,heigth2,dy);
      b = glm::mix(heigth3,heigth4,dy);

      float r3 = glm::mix(a,b,dx);

      position.y = r1+r2+r3;

//    }
//    else
//    {
//     position.y = randValue( position.x , position.z) ;
//    }




    return position;
}


/**
 * Returns the normal vector for the terrain vertex at the given row and column.
 */
glm::vec3 Terrain::getNormal(int row, int col) {
    // TODO: Compute the normal at the given row and column using the positions of the
    //       neighboring vertices.

    int movex[9] = {-1, -1, -1,  0, 1,  1, 1, 0,-1};
    int movey[9] = {-1,  0,  1,  1, 1,  0, -1, -1,-1};

    glm::vec3 acc(0.0,0.0,0.0);
    int numTriangles = 0;

    for(int i = 0 ; i< 8 ; i++)
    {
        int x = row+movex[i];
        int y = col+movey[i];
        int x1 = row+movex[i+1];
        int y1 = col+movey[i+1];


        if(x >= 0 && x < m_numRows && y>= 0 && y < m_numCols
            &&  x1 >= 0 && x1 < m_numRows && y1>= 0 && y1 < m_numCols  )
        {
          glm::vec3 pos = getPosition(row,col);
          glm::vec3 pos1 = getPosition(x,y);
          glm::vec3 pos2 = getPosition(x1,y1);

          glm::vec3 norm = glm::normalize(glm::cross(pos-pos1,pos-pos2));
          acc+=norm;
          numTriangles++;
        }
    }

    acc/=numTriangles;

    return acc;
}


/**
 * Initializes the terrain by storing positions and normals in a vertex buffer.
 */
void Terrain::init() {
    // TODO: Change from GL_LINE to GL_FILL in order to render full triangles instead of wireframe.
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


    // Initializes a grid of vertices using triangle strips.
    int numVertices = (m_numRows - 1) * (2 * m_numCols + 2);
    std::vector<glm::vec3> data(2 * numVertices);
    int index = 0;
    for (int row = 0; row < m_numRows - 1; row++) {
        for (int col = m_numCols - 1; col >= 0; col--) {
            data[index++] = getPosition(row, col);
            data[index++] = getNormal  (row, col);
            data[index++] = getPosition(row + 1, col);
            data[index++] = getNormal  (row + 1, col);
        }
        data[index++] = getPosition(row + 1, 0);
        data[index++] = getNormal  (row + 1, 0);
        data[index++] = getPosition(row + 1, m_numCols - 1);
        data[index++] = getNormal  (row + 1, m_numCols - 1);
    }

    // Initialize OpenGLShape.
    m_shape = std::make_unique<OpenGLShape>();
    m_shape->setVertexData(&data[0][0], data.size() * 3, VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLE_STRIP, numVertices);
    m_shape->setAttribute(ShaderAttrib::POSITION, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, false);
    m_shape->setAttribute(ShaderAttrib::NORMAL, 3, sizeof(glm::vec3), VBOAttribMarker::DATA_TYPE::FLOAT, false);
    m_shape->buildVAO();
}


/**
 * Draws the terrain.
 */
void Terrain::draw()
{
    m_shape->draw();
}
